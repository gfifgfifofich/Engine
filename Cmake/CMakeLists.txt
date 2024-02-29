cmake_minimum_required(VERSION 3.3)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)



set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

project(Engine)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(src ${OPENGL_INCLUDE_DIRS})





add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/GLFW)
add_subdirectory(dependencies/stb_image)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/glew/build/cmake)
add_subdirectory(dependencies/freetype)
add_subdirectory(dependencies/openal)


set(imgui-directory dependencies/imgui)

set(imgui-source ${imgui-directory}/imconfig.h
	${imgui-directory}/imgui.h
	${imgui-directory}/imgui.cpp
	${imgui-directory}/imgui_draw.cpp
	${imgui-directory}/imgui_internal.h
	${imgui-directory}/imgui_widgets.cpp
	${imgui-directory}/imstb_rectpack.h
	${imgui-directory}/imstb_textedit.h
	${imgui-directory}/imstb_truetype.h
    ${imgui-directory}/imgui_tables.cpp
	${imgui-directory}/imgui_demo.cpp
	${imgui-directory}/imgui_impl_glfw.cpp
	${imgui-directory}/imgui_impl_opengl3.cpp
)
file(GLOB_RECURSE source CONFIGURE_DEPENDS "Include/*.h" "Include/**/*.h" "Source/*.cpp" "Source/**/*.cpp")

add_executable(Engine ${source} ${imgui-source})
target_link_libraries(Engine ${OPENGL_LIBRARIES} glad glfw stb_image glm glew freetype OpenAL ${OPENAL_LIBRARY})
target_include_directories(Engine PRIVATE ${imgui-directory}) # <Added this line>



file(COPY resources/ DESTINATION ${PROJECT_BINARY_DIR}/)
file(COPY engine/ DESTINATION ${PROJECT_BINARY_DIR}/engine/)

