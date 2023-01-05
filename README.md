# Raytracer

I coded the raytracer for this project following the raytracing series by Peter Shirley at: https://raytracing.github.io/
The goal of the project is to research the possibility of using a neural network to raytrace a 3D scene in realtime. This will be accomplished by generating training data using the Raytracer and using a deep learning library such as tensorflow to train a the neural network. The hope is to run the neural network on a webbrowser using tensorflow.js.

---

## Raytracer API
Here is an example of code using the Raytracer: 
```cpp
int main() {
	Raytracer raytracer(
		800, 600, glm::vec3(0.0f, 1.4f, 0.0f), glm::vec3(0.0f, 0.0f, -3.0f), 90.0f, 0.0f, 3.0f, Backend::OpenGL /*OpenGL and CPU are supported as well*/
	);

	raytracer.World.Objects.push_back(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -3.0f), 0.5f, std::make_shared<Dielectric>(0.12f)));
	raytracer.World.Objects.push_back(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -3.0f), 100.0f, std::make_shared<Lambertian>(glm::vec3(0.5f, 0.5f, 0.5f))));

	raytracer.Draw();
	raytracer.Canvas.Save("output.png");

	return 0;
}
```
Along with the image it generates:

![enter image description here](https://raw.githubusercontent.com/fqhd/Raytracer/master/images/example.png)

--- 

## Example Images

Here are some images generated using the raytracer:

![enter image description here](https://raw.githubusercontent.com/fqhd/Raytracer/master/images/image1.png)
![enter image description here](https://raw.githubusercontent.com/fqhd/Raytracer/master/images/image2.png)
![enter image description here](https://raw.githubusercontent.com/fqhd/Raytracer/master/images/image3.png)

