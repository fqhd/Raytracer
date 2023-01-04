#include "Raytracer.h"
#include "Metal.h"
#include "Lambertian.h"
#include "Utils.h"
#include "Dielectric.h"
#include "SceneData.h"
#include "Benchmarker.h"

int main() {
	Raytracer raytracer(
		800, 600, glm::vec3(0.0f, 1.4f, 0.0f), glm::vec3(0.0f, 0.0f, -3.0f), 90.0f, 0.0f, 3.0f, Backend::Vulkan
	);

	raytracer.World.Add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -3.0f), 0.5f, std::make_shared<Dielectric>(0.12f)));
	raytracer.World.Add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -3.0f), 100.0f, std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f))));

	raytracer.Draw();
	raytracer.Canvas.Save("output.png");

	return 0;
}
