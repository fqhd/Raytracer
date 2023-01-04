cls
glslc shaders/shader.comp -o shaders/comp.spv

:: This command is for release builds
:: cl /EHsc /O2 /DEBUG:NONE /Fe:out.exe src/*.cpp -IC:\VulkanSDK\Include /link C:\VulkanSDK\Lib\vulkan-1.lib

:: This command is for debug builds
cl /EHsc /Od /DEBUG:FULL /DDEBUG /Fe:out.exe src/*.cpp -IC:\VulkanSDK\Include /link C:\VulkanSDK\Lib\vulkan-1.lib

del *.obj
out.exe
del out.exe
