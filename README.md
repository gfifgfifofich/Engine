
![github3](https://github.com/gfifgfifofich/Engine/blob/main/VS%20project/opengltry2/Textures/Cool%20picture.png)

## Build

```bash
mkdir build
cd build
cmake ../
cmake --build ./
```
VS Project directory contains a project for VS, but it may not run on some PC's. Cmake is preferable 
Linux version is highly untested.
## features
- most of collision types
- physics (springs, struts, ropes)
- Lighting and postprocessing
- CPU Particle system (up to 500k particles at 60FPS on my pc)
- All sorts of functions for UI.
- Neural network class for no reason.
- Scene class that can store all sorts of data about a scene. (For now can only use already implemented objects, like quads, polygons, particles, textures etc.)
Scene redactor preview:
![github3](https://github.com/gfifgfifofich/Engine/blob/main/VS%20project/opengltry2/Textures/Redactor%20preview%20.png)


## libraries
[Dear imgui](https://github.com/ocornut/imgui), 
[GLM](https://github.com/g-truc/glm), 
[GLFW](https://github.com/glfw/glfw), 
[glew](https://glew.sourceforge.net/), 
[glad](https://github.com/Dav1dde/glad), 
[freetype](https://freetype.org/download.html), 
[OpenAL](https://github.com/kcat/openal-soft), 
[stb_image](https://github.com/nothings/stb/blob/master/stb_image.h), 

	

