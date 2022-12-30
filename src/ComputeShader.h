#include <vulkan/vulkan.h>
#include <vector>
#include <string.h>
#include <iostream>
#include "Image.h"

const int WORKGROUP_SIZE = 32;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

// Used for validating return values of Vulkan API calls.
#define VK_CHECK_RESULT(f) 																				\
{																										\
    VkResult res = (f);																					\
    if (res != VK_SUCCESS)																				\
    {																									\
        printf("Fatal : VkResult is %d in %s at line %d\n", res,  __FILE__, __LINE__); \
    }																									\
}

class ComputeShader {
public:
    ComputeShader(int width, int height);
    ~ComputeShader();

    void Run(Image& image);
    
private:

    void CreateInstance();
    void FindPhysicalDevice();
    uint32_t GetComputeQueueFamilyIndex();
    void CreateDevice();
    uint32_t FindMemoryType(uint32_t memoryTypeBits, VkMemoryPropertyFlags properties);
    void CreateBuffer();
    void CreateDescriptorSetLayout();
    void CreateDescriptorSet();
    uint32_t* ReadFile(uint32_t& length, const char* filename);
    void CreateComputePipeline();
    void CreateCommandBuffer();

    int m_Width = 0;
    int m_Height = 0;
    VkInstance instance;
    VkDebugReportCallbackEXT debugReportCallback;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
    VkShaderModule computeShaderModule;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    VkDescriptorSetLayout descriptorSetLayout;
    VkBuffer buffer;
    VkDeviceMemory bufferMemory;
    uint32_t bufferSize;
    VkQueue queue;
    uint32_t queueFamilyIndex;

};
