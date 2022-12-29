#include <iostream>
#include "Image.h"
#include "Ray.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "World.h"
#include "fastPRNG.h"
#include <chrono>
#include "Utils.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int PIXEL_WIDTH = 4;

int main() {
	Image image(WIDTH, HEIGHT);

	glm::vec3 lookfrom(3.0f, 3.0f, 2.0f);
	glm::vec3 lookat(0.0f, 0.0f, -1.0f);
	glm::vec3 vup(0.0f, 1.0f, 0.0f);
	float focusDistance = glm::length(lookfrom - lookat);
	float aperture = 2.0f;

	Camera camera(lookfrom, lookat, vup, WIDTH, HEIGHT, 20.0f, aperture, focusDistance);
	World world;
	
	auto material_ground = std::make_shared<Lambertian>(glm::vec3(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<Lambertian>(glm::vec3(0.1f, 0.2f, 0.5f));
	auto material_left = std::make_shared<Dielectric>(1.5f);
	auto material_right = std::make_shared<Metal>(glm::vec3(0.8, 0.6, 0.2), 0.0f);

	world.AddSphere(glm::vec3(0.0, 0.0, -1.0), 0.5, material_center);
	world.AddSphere(glm::vec3(-1.0, 0.0, -1.0), 0.5, material_left);
	world.AddSphere(glm::vec3(-1.0, 0.0, -1.0), -0.45, material_left);
	world.AddSphere(glm::vec3(0.0, -100.5, -1.0), 100.0, material_ground);
	world.AddSphere(glm::vec3(1.0, 0.0, -1.0), 0.5, material_right);

	auto start = std::chrono::high_resolution_clock::now();
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			glm::vec3 color(0.0f);
			for (int i = 0; i < PIXEL_WIDTH; i++) {
				for (int j = 0; j < PIXEL_WIDTH; j++) {
					Ray r = camera.GetScreenRay(x + j / (float)PIXEL_WIDTH, y + i / (float)PIXEL_WIDTH);
					color += world.GetRayColor(r);
				}
			}

			float scale = 1.0 / (float)(PIXEL_WIDTH * PIXEL_WIDTH);
			color.r = sqrt(scale * color.r);
			color.g = sqrt(scale * color.g);
			color.b = sqrt(scale * color.b);

			Pixel p;
			p.R = (unsigned char)(color.r * 255);
			p.G = (unsigned char)(color.g * 255);
			p.B = (unsigned char)(color.b * 255);

			image.SetPixel(x, y, p);
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Time: " << duration.count() << " seconds" << std::endl;

	image.Save("Output.png");

	return 0;
}
