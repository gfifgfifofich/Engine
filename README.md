![github3](https://github.com/gfifgfifofich/Engine/blob/main/opengltry2/Textures/Cool%20picture.png)

## booting up project
For now its just a Visual studio solution project. Will be reconfigured to use a build system later

## features
- most of collision types
- Z-Index layered drawing
- Lighting
- physics (springs, struts, ropes)
- CPU Particle system (up to 500k particles at 60FPS on my pc)
- Neural network class for no reason, ~Easy to use
Scene class that can store all sorts of data about a scene. (For now can only use already implemented objects, like quads, polygons, particles, textures etc.)
Scebe redactor preview:
![github3](https://github.com/gfifgfifofich/Engine/blob/main/opengltry2/Textures/Redactor%20preview%20.png)


## libraries
[Dear imgui](https://github.com/ocornut/imgui), 
[GLM](https://github.com/g-truc/glm), 
[GLFW](https://github.com/glfw/glfw), 
[glew](https://glew.sourceforge.net/), 
[glad](https://github.com/Dav1dde/glad), 
[freetype](https://freetype.org/download.html), 
[OpenAL](https://github.com/kcat/openal-soft), 
[stb_image](https://github.com/nothings/stb/blob/master/stb_image.h), 



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
	

