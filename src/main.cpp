#include "Raytracer.h"
#include "Metal.h"
#include "Lambertian.h"
#include "Utils.h"
#include "Dielectric.h"
#include "SceneData.h"
#include "Benchmarker.h"

void DrawRandomScenes();

int main() {

    std::cout << "SceneData Size: " << sizeof(SceneData) << std::endl;

	DrawRandomScenes();

	return 0;
}

void DrawRandomScenes() {
	Raytracer raytracer(
		800, 600, glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 5.0f), 60.0f, 0.01f, 10.0f
	);

	int numScenes = 1;
	for (int i = 0; i < numScenes; i++) {
		raytracer.World.Clear();

		auto groundMaterial = std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f));
		raytracer.World.Add(std::make_shared<Sphere>(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f, groundMaterial));

        for (int a = 0; a < 4; a++) {
            for (int b = 0; b < 4; b++) {
                auto choose_mat = randomFloatU();
                glm::vec3 center(a * 2.0 - 3.0, 0.35, b * 2.0 + 4.0);

                if ((center - glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
                    std::shared_ptr<Material> sphere_material;

                    if (choose_mat < 0.6) {
                        // diffuse
                        auto albedo = randomColor();
                        sphere_material = std::make_shared<Lambertian>(albedo);
                        raytracer.World.Add(std::make_shared<Sphere>(center, 0.35f, sphere_material));
                    }
                    else if (choose_mat < 0.9) {
                        // metal
                        float r = randomFloatU() * 0.5f;
                        auto albedo = glm::vec3(r + 0.5f);
                        auto fuzz = randomFloatU() * 0.5f;
                        sphere_material = std::make_shared<Metal>(albedo, fuzz);
                        raytracer.World.Add(std::make_shared<Sphere>(center, 0.35f, sphere_material));
                    }
                    else {
                        // glass
                        sphere_material = std::make_shared<Dielectric>(1.5f);
                        raytracer.World.Add(std::make_shared<Sphere>(center, 0.35f, sphere_material));
                    }
                }
            }
        }

		Benchmarker::Start("Draw");
		raytracer.DrawGPU();
		Benchmarker::End("Draw");
		raytracer.Canvas.Save("output.png");
	}
}