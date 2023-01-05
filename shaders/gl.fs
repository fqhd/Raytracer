#version 330 core

out vec4 outColor;

#define PI 3.14159265359
#define MAX_SPHERES 20

struct Ray {
	vec3 origin;
	vec3 direction;
};

struct Material {
	vec3 albedo;
	float ir;
	float roughness;
	int type;
};

struct HitRecord {
	vec3 p;
	vec3 normal;
	float t;
	bool frontFace;
	Material material;
};

struct Sphere {
	Material material;
	vec3 center;
	float radius;
	int visible;
};

struct Camera {
	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	vec3 w;
	vec3 u;
	vec3 v;
	float lensRadius;
};

struct HittableList {
	Sphere spheres[MAX_SPHERES];
};

struct SceneData {
	int width;
	int height;
	Camera camera;
	HittableList list;
};

uniform SceneData sceneData;

// Utilities
/*
    static.frag
    by Spatial
    05 July 2013
*/

// A single iteration of Bob Jenkins' One-At-A-Time hashing algorithm.
uint hash( uint x ) {
    x += ( x << 10u );
    x ^= ( x >>  6u );
    x += ( x <<  3u );
    x ^= ( x >> 11u );
    x += ( x << 15u );
    return x;
}

// Compound versions of the hashing algorithm I whipped together.
uint hash( uvec2 v ) { return hash( v.x ^ hash(v.y)                         ); }
uint hash( uvec3 v ) { return hash( v.x ^ hash(v.y) ^ hash(v.z)             ); }
uint hash( uvec4 v ) { return hash( v.x ^ hash(v.y) ^ hash(v.z) ^ hash(v.w) ); }

// Construct a float with half-open range [0:1] using low 23 bits.
// All zeroes yields 0.0, all ones yields the next smallest representable value below 1.0.
float floatConstruct( uint m ) {
    const uint ieeeMantissa = 0x007FFFFFu; // binary32 mantissa bitmask
    const uint ieeeOne      = 0x3F800000u; // 1.0 in IEEE binary32

    m &= ieeeMantissa;                     // Keep only mantissa bits (fractional part)
    m |= ieeeOne;                          // Add fractional part to 1.0

    float  f = uintBitsToFloat( m );       // Range [1:2]
    return f - 1.0;                        // Range [0:1]
}

// Pseudo-random value in half-open range [0:1].
float random( float x ) { return floatConstruct(hash(floatBitsToUint(x))); }
float random( vec2  v ) { return floatConstruct(hash(floatBitsToUint(v))); }
float random( vec3  v ) { return floatConstruct(hash(floatBitsToUint(v))); }
float random( vec4  v ) { return floatConstruct(hash(floatBitsToUint(v))); }

float randCounter = 0.0;
float rand(){
	randCounter += 0.01;
	return random(vec2(800 * gl_FragCoord.y + gl_FragCoord.x, randCounter));
}

vec3 randomInUnitSphere() {
    float u = rand();
    float v = rand();
    float theta = u * 2.0 * PI;
    float phi = acos(2.0 * v - 1.0);
    float r = pow(rand(), 1/3.0);
    float sinTheta = sin(theta);
    float cosTheta = cos(theta);
    float sinPhi = sin(phi);
    float cosPhi = cos(phi);
    float x = r * sinPhi * cosTheta;
    float y = r * sinPhi * sinTheta;
    float z = r * cosPhi;
    return vec3(x, y, z);
}

vec3 randomUnitVector() {
	return normalize(randomInUnitSphere());
}

vec3 randomInHemisphere(vec3 normal) {
	vec3 inUnitSphere = randomInUnitSphere();
	if(dot(inUnitSphere, normal) > 0.0){
		return inUnitSphere;
	}else{
		return -inUnitSphere;
	}
}

bool nearZero(vec3 v){
	float s = 1e-8;
	return (abs(v.x) < s) && (abs(v.y) < s) && (abs(v.z) < s);
}

float lengthSquared(vec3 v){
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

vec3 randomInUnitDisk() {
    while (true) {
        vec3 p = vec3(rand() * 2.0 - 1.0, rand() * 2.0 - 1.0, 0.0);
        if (lengthSquared(p) >= 1.0) continue;
        return p;
    }
}

float reflectance(float cosine, float refIndex) {
	// Use Schlick's approximation for reflectance.
	float r0 = (1.0-refIndex) / (1.0 + refIndex);
	r0 = r0*r0;
	return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
}

Ray createRay(vec3 origin, vec3 direction){
	Ray r;
	r.origin = origin;
	r.direction = direction;
	return r;
}

vec3 at(Ray r, float t){
	return r.origin + r.direction * t;
}

void setFaceNormal(inout HitRecord record, Ray r, vec3 outwardNormal){
	record.frontFace = dot(r.direction, outwardNormal) < 0.0;
	record.normal = record.frontFace ? outwardNormal : -outwardNormal;
}

bool hit(Sphere s, Ray r, float tmin, float tmax, inout HitRecord rec) {
	vec3 oc = r.origin - s.center;
	float a = lengthSquared(r.direction);
	float half_b = dot(oc, r.direction);
	float c = lengthSquared(oc) - s.radius * s.radius;

	float discriminant = half_b * half_b - a * c;
	if(discriminant < 0.0) return false;
	float sqrtd = sqrt(discriminant);

	float root = (-half_b - sqrtd) / a;
	if(root < tmin || tmax < root){
		root = (-half_b + sqrtd) / a;
		if(root < tmin || tmax < root){
			return false;
		}
	}

	rec.t = root;
	rec.p = at(r, rec.t);
	vec3 outwardNormal = (rec.p - s.center) / s.radius;
	setFaceNormal(rec, r, outwardNormal);
	rec.material = s.material;

	return true;
}

Ray getRay(const Camera camera, float x, float y){
	vec3 rd = camera.lensRadius * randomInUnitDisk();
	vec3 offset = camera.u * rd.x + camera.v * rd.y;

	return createRay(
		camera.origin + offset,
		camera.lowerLeftCorner + x * camera.horizontal + y * camera.vertical - camera.origin - offset
	);
}

void scatter(const HitRecord rec, inout vec3 throughput, inout Ray ray){
	if(rec.material.type == 0){ // Lambertian
		vec3 scatterDirection = rec.normal + randomUnitVector();

		if(nearZero(scatterDirection)){
			scatterDirection = rec.normal;
		}

		ray = createRay(rec.p, scatterDirection);
		throughput *= rec.material.albedo;
	}else if(rec.material.type == 1){ // Metal
		vec3 reflected = reflect(normalize(ray.direction), rec.normal);
		ray = createRay(rec.p, reflected + rec.material.roughness * randomInUnitSphere());
		throughput *= rec.material.albedo;
	}else if(rec.material.type == 2){ // Dielectric
		throughput *= vec3(1.0);
		float refractionRatio = rec.frontFace ? (1.0/rec.material.ir) : rec.material.ir;

		vec3 unitDirection = normalize(ray.direction);
		float cosTheta = min(dot(-unitDirection, rec.normal), 1.0);
		float sinTheta = sqrt(1.0 - cosTheta*cosTheta);

		bool cannotRefract = refractionRatio * sinTheta > 1.0;
		vec3 direction;

		if (cannotRefract || reflectance(cosTheta, refractionRatio) > rand()){
			direction = reflect(unitDirection, rec.normal);
		}
		else{
			direction = refract(unitDirection, rec.normal, refractionRatio);
		}

		ray = createRay(rec.p, direction);
	}
}

Ray getNextRay(HitRecord record){
	return createRay(record.p, randomInHemisphere(record.normal));
}

bool hitHittableList(HittableList list, Ray r, float tmin, float tmax, inout HitRecord rec){
	HitRecord tempRec;
	bool hitAnything = false;
	float closestSoFar = tmax;
	for(int i = 0; i < MAX_SPHERES; i++){
		if(list.spheres[i].visible == 1){
			if (hit(list.spheres[i], r, tmin, closestSoFar, tempRec)){
				hitAnything = true;
				closestSoFar = tempRec.t;
				rec = tempRec;
			}
		}
	}
	return hitAnything;
}

vec3 getMissColor(Ray r){
	vec3 unitDirection = normalize(r.direction);
	float t = 0.5 * (unitDirection.y + 1.0);
	return (1.0 - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0);
}

vec3 rayColor(Ray ray, HittableList list, int depth){
	vec3 color = vec3(0.0);
	vec3 throughput = vec3(1.0);
	HitRecord record;

	while (depth-- > 0) {
		if(!hitHittableList(list, ray, 0.001, 1000.0, record)){
			color += getMissColor(ray) * throughput;
			break;
		}
		
		scatter(record, throughput, ray);
	}

	return color;
}

void main() {
	int depth = 10;

	vec3 color = vec3(0.0);
	const int pixelWidth = 2;
	for(int i = 0; i < pixelWidth; i++){
		for(int j = 0; j < pixelWidth; j++){
			float x = (float(gl_FragCoord.x) + float(j) / pixelWidth) / float(sceneData.width - 1);
			float y = (float(gl_FragCoord.y) + float(i) / pixelWidth) / float(sceneData.height - 1);
			Ray r = getRay(sceneData.camera, x, y);
			color += rayColor(r, sceneData.list, depth);
		}
	}
	
	float scale = 1.0 / (pixelWidth * pixelWidth);
	color = sqrt(color * scale);
	
	outColor = vec4(color, 1.0);
}