![github3](https://github.com/gfifgfifofich/Engine/blob/main/opengltry2/Textures/Cool%20picture.png)

## booting up project
in Project settings (atleast it is how its done in Visual Studio), add "include" and "libraries" path.Set include and lib directories to "your_project_location"/opengltry2/engine/Libraries/lib and to Libraries/include respectively

all .cpp's in main folder - example projects. Include one of them in project to run.

To build this as library, create a "static library" project with same settings, delete everything, disable precompiled headers, include everything from components, compile.

## features
- most of collision types
- Z-Index layered drawing
- Lighting
- physics (springs, struts, ropes)
- Particle system (up to 500k particles at 60FPS on my pc)
- Neural network class, ~Easy to use

## libraries
[Dear imgui](https://github.com/ocornut/imgui) 
[GLM](https://github.com/g-truc/glm) 
[GLFW](https://github.com/glfw/glfw) 
[glew](https://glew.sourceforge.net/) 
[glad](https://github.com/Dav1dde/glad) 
[freetype](https://freetype.org/download.html or https://github.com/freetype/freetype) 
[OpenAL](https://github.com/kcat/openal-soft) 
[stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) 



in case of need to rebuild libraries:

Libraries/lib should contain:
	freetype.lib
	glew32s.lib
	glfw3.lib
	OpenAL32.lib
	sndfile.lib
 
Libraries/Include should contain folowing directories:
	AL (from openAL),
	freetype (from freetype),
	GL (from glew),
	glad (from glad),
	GLFW (from GLFW),
	glm (from GLM),
	stb (that contains stb_image.h)
	
 and files:
	ft2build.h
	sndfile.h
	sndfile.hh


OpenAL32.dll in directory "Engine/opengltry2", or any other way of connectin a dll.
	

