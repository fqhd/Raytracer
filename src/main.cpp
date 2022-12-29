#include "Raytracer.h"
#include "Metal.h"
#include "Lambertian.h"
#include "Utils.h"
#include "Dielectric.h"

void DrawRandomScenes();

int main() {

	DrawRandomScenes();

	return 0;
}

void DrawRandomScenes() {
	Raytracer raytracer(
		1920, 1080, glm::vec3(13.0f, 2.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), 20.0f, 0.1f, 10.0f, 500
	);

	int numScenes = 1;
	for (int i = 0; i < numScenes; i++) {
		raytracer.World.Clear();

		auto groundMaterial = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
		raytracer.World.AddSphere(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0, groundMaterial);

        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                auto choose_mat = randomFloatU();
                glm::vec3 center(a + 0.9 * randomFloatU(), 0.2, b + 0.9 * randomFloatU());

                if ((center - glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
                    std::shared_ptr<Material> sphere_material;

                    if (choose_mat < 0.8) {
                        // diffuse
                        auto albedo = randomColor();;
                        sphere_material = std::make_shared<Lambertian>(albedo);
                        raytracer.World.AddSphere(center, 0.2f, sphere_material);
                    }
                    else if (choose_mat < 0.95) {
                        // metal
                        float r = randomFloatU() * 0.5f;
                        auto albedo = glm::vec3(r + 0.5f);
                        auto fuzz = randomFloatU() * 0.5f;
                        sphere_material = std::make_shared<Metal>(albedo, fuzz);
                        raytracer.World.AddSphere(center, 0.2f, sphere_material);
                    }
                    else {
                        // glass
                        sphere_material = std::make_shared<Dielectric>(1.5f);
                        raytracer.World.AddSphere(center, 0.2f, sphere_material);
                    }
                }
            }
        }

		raytracer.Draw();
		raytracer.Canvas.Save("Output.png");
	}
}