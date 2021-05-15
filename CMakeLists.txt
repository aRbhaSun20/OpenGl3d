# Project definition
cmake_minimum_required(VERSION 3.1)
project(OpenGL C CXX)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(SOURCE_FILE "${SRC_DIR}/index.cpp")

# Vetex Buffer
set(VERTEX_DIR "${SRC_DIR}/VertexBuffers")
set(VERTEX_BUFFER "${VERTEX_DIR}/VertexBuffer.h" 
    "${VERTEX_DIR}/VertexBuffer.cpp") 

# Index Buffer
set(INDEX_DIR "${SRC_DIR}/IndexBuffers")
set(INDEX_BUFFER  "${INDEX_DIR}/IndexBuffer.h" 
    "${INDEX_DIR}/IndexBuffer.cpp")

# Vertex Array 
set(VERTEX_ARRAY_DIR "${SRC_DIR}/VertexArrays")
set(VERTEX_ARRAY "${VERTEX_ARRAY_DIR}/VertexArray.h" 
            "${VERTEX_ARRAY_DIR}/VertexArray.cpp")

# Vertex Buffer Layout   
set(VERTEX_BUFFER_LAYOUT_DIR "${SRC_DIR}/VertexBufferLayouts")      
set(VERTEX_BUFFER_LAYOUT "${VERTEX_BUFFER_LAYOUT_DIR}/VertexBufferLayout.h" 
                "${VERTEX_BUFFER_LAYOUT_DIR}/VertexBufferLayout.cpp")

# Shader Contents
set(SHADER_DIR "${SRC_DIR}/Shaders")
set(SHADER_FILES "${SHADER_DIR}/ShaderInitialize.h" 
    "${SHADER_DIR}/ShaderInitialize.cpp")

# Renderer Contents
set(RENDERER_DIR "${SRC_DIR}/Renderer")    
set(RENDERER_FILES "${RENDERER_DIR}/Renderer.h"
    "${RENDERER_DIR}/Renderer.cpp")

# Texture Contents
set(TEXTURE_DIR "${SRC_DIR}/Texture")
set(TEXTURE_FILES "${TEXTURE_DIR}/Texture.h" "${TEXTURE_DIR}/Texture.cpp")

#Mvp Handler
set(MVP_DIR "${SRC_DIR}/Mvps")
set(MVP_FILES "${MVP_DIR}/ProjectionMatrix.h" "${MVP_DIR}/ModelMatrix.h" 
"${MVP_DIR}/MvpMatrix.h" "${MVP_DIR}/MvpMatrix.cpp")

#Camera Contents
set(CAMERA_DIR "${SRC_DIR}/Camera")
set(CAMERA_FILES "${CAMERA_DIR}/OrthographicCamera.h" "${CAMERA_DIR}/OrthographicCamera.cpp"
"${CAMERA_DIR}/PerspectiveCamera.h" "${CAMERA_DIR}/PerspectiveCamera.cpp")

#Core Contents
set(CORE_DIRS "${SRC_DIR}/Core")
set(CORE_FILES "${CORE_DIRS}/Timestep.h" 
"${CORE_DIRS}/ExecuteCommands.h" "${CORE_DIRS}/ExecuteCommands.cpp" "${CORE_DIRS}/KeyCodes.h"
"${CORE_DIRS}/MouseCodes.h" "${CORE_DIRS}/LightType.h" "${CORE_DIRS}/LogFile.h" "${CORE_DIRS}/LogFile.cpp"
)

#Material Contents
set(MATERIAL_DIRS "${SRC_DIR}/Materials")
set(MATERIAL_FILES "${MATERIAL_DIRS}/Materials.h")

#Events Contents
set(EVENT_DIRS "${SRC_DIR}/Events")
set(EVENT_FILES "${EVENT_DIRS}/Event.h" "${EVENT_DIRS}/Event.cpp")

#Geometrical Structures
set(GEOMETRICAL_DIR "${SRC_DIR}/GeometricalStructure")
set(GEOMETRICAL_FILES "${GEOMETRICAL_DIR}/CubeStructure.h" "${GEOMETRICAL_DIR}/CubeStructure.cpp")

#Initializer Contents
set(INITIALIZER_DIR "${SRC_DIR}/Initializer")
set(INITIALIZER_FILES "${INITIALIZER_DIR}/Initialize.h" "${INITIALIZER_DIR}/Initialize.cpp")

# Imgui Handler
set(IMGUI_HANDLER_DIR "${SRC_DIR}/ImguiHandle")
set(IMGUI_HANDLER_FILES "${IMGUI_HANDLER_DIR}/ImGuiBuild.h" 
"${IMGUI_HANDLER_DIR}/ImguiHandle.h" "${IMGUI_HANDLER_DIR}/ImguiHandle.cpp")

#Model and Mesh
set(MODEL_MESH_DIR "${SRC_DIR}/Model_Mesh")
set(MODEL_MESH_FILES 
"${MODEL_MESH_DIR}/mesh.h" "${MODEL_MESH_DIR}/mesh.cpp" 
"${MODEL_MESH_DIR}/model.h" "${MODEL_MESH_DIR}/model.cpp")


#Light Contents
set(LIGHT_DIR "${SRC_DIR}/Light")
set(LIGHT_FILES "${LIGHT_DIR}/Light.h")

# Application files 
set(SECONDARY "${SRC_DIR}/index.h" "${INITIALIZER_FILES}" 
    "${VERTEX_BUFFER}" "${INDEX_BUFFER}" "${SHADER_FILES}" "${CORE_FILES}"
    "${VERTEX_ARRAY}" "${VERTEX_BUFFER_LAYOUT}"  "${TEXTURE_FILES}"  
    "${MVP_FILES}" "${CAMERA_FILES}" "${EVENT_FILES}" "${MATERIAL_FILES}" 
    "${RENDERER_FILES}" "${GEOMETRICAL_FILES}" "${MODEL_MESH_FILES}"
    "${LIGHT_FILES}" "${IMGUI_HANDLER_FILES}" 
)
 

# spdlog libraires
file(GLOB_RECURSE SPDLOG
"${LIB_DIR}/spdlog/*.h" "${LIB_DIR}/spdlog/cfg/*.h" "${LIB_DIR}/spdlog/details/*.h" "${LIB_DIR}/spdlog/fmt/*.h"
 "${LIB_DIR}/spdlog/fmt/bundled/*.h" "${LIB_DIR}/spdlog/sinks/*.h") 

# Library files
set(LIBRARY_FILES "${SPDLOG}")

#source Executables
set(SOURCES "${SOURCE_FILE}" "${SECONDARY}" "${LIBRARY_FILES}")

# Executable definition and properties
add_executable("${PROJECT_NAME}" "${SOURCES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY C CXX_STANDARD 11 ) 

#precomiler headers
set(PRECOMZ_DIR "${LIB_DIR}/Precomz")
add_subdirectory(${PRECOMZ_DIR})
target_link_libraries("${PROJECT_NAME}" "precomz")

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# stb_image
set(STB_IMAGE_DIR "${LIB_DIR}/StdImage")
add_library("STB_IMAGE" "${STB_IMAGE_DIR}/stb_image.cpp")
target_include_directories("STB_IMAGE" PRIVATE "${STB_IMAGE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${STB_IMAGE_DIR}")
target_link_libraries(${PROJECT_NAME} "STB_IMAGE" "libassimp.so.5.0.1")

# Math Library
set(GLM_DIR "${LIB_DIR}/glm")
add_subdirectory("${GLM_DIR}" EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} glm)

# Imgui Library
set(IMGUI_DIR "${LIB_DIR}/imgui")
add_subdirectory(${IMGUI_DIR})
target_link_libraries(${PROJECT_NAME} "imgui")

# Json Library
set(JSON_DIR "${LIB_DIR}/json")
add_subdirectory(${JSON_DIR})
target_link_libraries(${PROJECT_NAME} "json")

# Assimp Library
set(ASSIMP_DIR "${LIB_DIR}/assimp/include")
target_link_libraries("${PROJECT_NAME}" libassimp.so.5.0.1)