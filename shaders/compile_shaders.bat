C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/standard/shader.vert
C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/standard/shader.frag
if not exist "./compiled/standard" mkdir "./compiled/standard"
move ./*.spv ./compiled/standard/


C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/normal_visualizer/shader.vert
C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/normal_visualizer/shader.geom
C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/normal_visualizer/shader.frag
if not exist "./compiled/normal_visualizer" mkdir "./compiled/normal_visualizer"
move ./*.spv ./compiled/normal_visualizer/