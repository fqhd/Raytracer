#include "Raytracer.h"
#include "Metal.h"
#include "Lambertian.h"

int main() {
	Raytracer raytracer(
		800, 600, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), 90.0f, 0.0f, 3.0f, 500
	);

	raytracer.World.AddSphere(glm::vec3(0.0f, 0.0f, -3.0f), 0.5, std::make_shared<Lambertian>(glm::vec3(0.0f, 0.0f, 1.0f)));
	raytracer.World.AddSphere(glm::vec3(0.0f, -100.5f, -3.0f), 100.0, std::make_shared<Lambertian>(glm::vec3(0.0f, 1.0f, 0.0f)));

	raytracer.Draw();
	raytracer.Canvas.Save("Output.png");

	return 0;
}
