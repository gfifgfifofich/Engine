#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif


#include <stdio.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <strstream>
#include <vector>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Mathematics.h"

extern glm::vec2 CameraPosition;
extern glm::vec2 CameraScale;

extern GLuint WIDTH, HEIGHT ;
extern std::string TextFromKeyboard;
extern bool TextEditMode;// disables keyboard key inputs, only TextFromKeyboard, enter, escape, backspace

extern GLFWwindow* window;



extern GLfloat lastX;
extern GLfloat lastY;


extern glm::vec4 BackgroundColor;

extern glm::vec2 MousePosition;
extern glm::vec2 scrpos;

extern bool keys[1024];
extern bool JustPressedkey[1024];
extern bool JustReleasedkey[1024];
extern bool Holdingkey[1024];
extern bool buttons[64];
extern bool JustPressedbutton[64];
extern bool JustReleasedbutton[64];
extern bool Holdingbutton[64];
extern int scrollmovement;

extern bool SettingsWindow ;
extern int threadcount;

extern bool VSync;
extern int ifpsHardLock;
extern bool bfpsHardLock;

extern int framecount ;
extern float delta;
extern float timer, lt;

extern float SceneExposure;


enum SHAPE { CIRCLE, QUAD, LINE, TRIANGLE };
extern bool DrawCubicColiders ;


extern float ScaleMultiplyer ;

extern float ScreenAspectRatio ;

extern float ScreenDivisorX ;
extern float ScreenDivisorY ;


extern bool HDR ;
extern bool bloom ;
extern bool Lighting ;

//DrameBufferShowing
extern bool NormalMap ;
extern bool RegularMap ;
extern bool LightingMap;


//Lighting
extern float AmbientLight ;
extern float DirectionalLight ;
//Bloom
extern float bloomIntensity;

extern bool BloomLevelsWindow ;
//Chromatic abberation
extern float ChromaticStrength ;
extern glm::vec2 ChromaticPoint ;
extern glm::vec4 AmbientColor ;

extern bool ReleasedLMB;
extern bool HoldingLMB;
extern bool JustPressedLMB;

