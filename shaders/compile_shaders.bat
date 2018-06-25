del /S "*.spv"

if not exist "./compiled" mkdir "./compiled"

C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/phong/shader.vert
C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/phong/shader.frag
if not exist "./compiled/phong" mkdir "./compiled/phong"
move ./*.spv ./compiled/phong/


C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/gouraud/shader.vert
C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/gouraud/shader.frag
if not exist "./compiled/gouraud" mkdir "./compiled/gouraud"
move ./*.spv ./compiled/gouraud/


C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/normal_visualizer/shader.vert
C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/normal_visualizer/shader.geom
C:/VulkanSDK/1.1.73.0/Bin32/glslangValidator.exe -V ./glsl/normal_visualizer/shader.frag
if not exist "./compiled/normal_visualizer" mkdir "./compiled/normal_visualizer"
move ./*.spv ./compiled/normal_visualizer/