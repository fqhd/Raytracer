clang++ -DDEBUG -O0 -std=c++20 src/*.cpp -I/opt/homebrew/Cellar/glm/0.9.9.8/include -I/Users/fahd/VulkanSDK/1.2.198.1/macOS/include -L/Users/fahd/VulkanSDK/1.2.198.1/macOS/lib -lvulkan
# clang++ -O3 -std=c++20 src/*.cpp -I/opt/homebrew/Cellar/glm/0.9.9.8/include -I/Users/fahd/VulkanSDK/1.2.198.1/macOS/include -L/Users/fahd/VulkanSDK/1.2.198.1/macOS/lib -lvulkan
./a.out
