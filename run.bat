cl /Fe:out.exe src/*.cpp -IC:\VulkanSDK\Include /link C:\VulkanSDK\Lib\vulkan-1.lib
del *.obj
out.exe