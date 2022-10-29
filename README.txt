To boot this engine up you need:
1) in engine/components unpack Libraries.rar // cuz there is too many files, and github allows to upload only 100/time
2) in Project settings (atleast it is how its done in Visual Studio), add "include" and "libraries" path. This directories are located in Libraries.



Also, i don't know what are the rigths of everything that is in directory "Libraries", so in future i'll simply add all the links to "assemble" this directory by yourself
+ some of .lib's are better to compile on the OS you're using, cuz now this thing can completely not work on different PC's.


Some features:

existing variables:
  BackgroundColor, type glm::vec4, color of background;
  MousePosition, glm::vec2, position of mouse;

bool keys and bool buttons, input system by GLFW, // example:  if (keys[GLFW_KEY_SPACE])//space is pressed, if (buttons[GLFW_MOUSE_BUTTON_1])//lmb is pressed

bool SettingsWindow = false; // opens or closes main """settings""" window

bool DrawingOrder = true; // true - cubes first, false- circles first. Helpfull when you need to draw cubes behind circles or opposite. Aloso, DrawLine() draws a quad, so it is affected too.

float delta = 0.0f; // dt of whole application

float SceneExposure = 0.7f; // HDR setting, controls exposure.

float dt_of_sim = 0.017f; // controls the dt of simulation, 0.017 will be a real time at 60fps, to make simulation realtime 100% of the time, simply dt_of_sim = delta. Helpfull if simulation is too big to be realtime, and precision is required

int substeps = 8; // substeps of simulation per frame. the more substeps, the more preciese is sim, but it is wery hungry on CPU. 8 is stable for 99% of the cases.

glm::vec2 g = glm::vec2(0.0f); //gravity, 
float friction = 1.0f; // friction
for more stuff chek Structs.h in engine/Components

functions:
 check Components Directory, Mathematics.h, Collisions.h
 Drawing:
 
   DrawCube(glm::vec2 position, glm::vec2 scale, glm::vec3 rotation = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f))
   !! rotation is for all 3 axis, for simple 2D rotation, z = rotation. I've done that for some cool shenanigans with rotations.
   
   
   DrawCircle(glm::vec2 position, float r, float edgesmoothness = 0.0001f, glm::vec4 color = glm::vec4(1.0f))
   // edgesmoothness is how thicc is edge of circle. actual radius of Drawn circle is r+edge. This allows to make a uber antialiased circles at edge ~ 1.0f-2.0f
   // also cool effect if you'll swap r and edge (if r = 0, and edge IS r), cool option for sparks, stars, fire, clouds and everything like that. + GPU free "bloom".
   
   DrawLine(glm::vec2 p1, glm::vec2 p2, float width = 0.1f, glm::vec4 color = glm::vec4(1.0f)) // Draws a line, between 2 points, with a given width. simple
   
