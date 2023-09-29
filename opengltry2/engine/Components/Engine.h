#pragma once

/* EXAMPLE CODE

#include "engine/Components/Engine.h"

void On_Create()
{

}
void On_Update()
{

}

int main()
{
	initEngine();

}

*/


#ifndef EngineMainModule
#include "Include/Helper.h"
#else 
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


#include "Include/Mathematics.h"





//Requeres DLL, + works funky
//#include "engine/Components/sounds.h"



glm::vec2 CameraPosition;
glm::vec2 CameraScale;

GLuint WIDTH, HEIGHT;
std::string TextFromKeyboard;
bool TextEditMode = false;// disables keyboard key inputs, only TextFromKeyboard, enter, escape, backspace

GLFWwindow* window;



GLfloat lastX;
GLfloat lastY;


glm::vec4 BackgroundColor;

glm::vec2 MousePosition;
glm::vec2 ScreenMousePosition;
glm::vec2 scrpos;

bool keys[1024];
bool JustPressedkey[1024];
bool JustReleasedkey[1024];
bool Holdingkey[1024];
bool buttons[64];
bool JustPressedbutton[64];
bool JustReleasedbutton[64];
bool Holdingbutton[64];
int scrollmovement = 0;

bool SettingsWindow = true;
int  threadcount;

bool VSync = true;
int ifpsHardLock = 60;
bool bfpsHardLock = false;

int framecount = 0;
float delta = 0.0f;
float timer = 0.0f, lt = 0.0f;

float SceneExposure = 0.7f;


enum SHAPE { CIRCLE, QUAD, LINE, TRIANGLE };
bool DrawCubicColiders = false;


float ScaleMultiplyer = 0.043545f * 0.05f;

float ScreenAspectRatio = 1.0f;

float ScreenDivisorX = 1.0;
float ScreenDivisorY = 1.0;


bool HDR = true;
bool bloom = true;
bool Lighting = true;

//DrameBufferShowing
bool NormalMap = false;
bool RegularMap = false;
bool LightingMap = false;


//Lighting
float AmbientLight = 1.0f;
float DirectionalLight = 1.0f;
//Bloom
float bloomIntensity = 0.3f;

bool BloomLevelsWindow = false;
//Chromatic abberation
float ChromaticStrength = 0.0f;
glm::vec2 ChromaticPoint = glm::vec2(0.5f);
glm::vec4 AmbientColor = glm::vec4(1.0f);



bool ReleasedLMB = false;
bool HoldingLMB = false;
bool JustPressedLMB = false;
#endif 

#include "Include/Shader.h"
#include "Include/Drawing.h"
#include "Include/Objects.h"
#include "Include/Collisions.h"
#include "Include/Physics.h"
#include "Include/Text.h"
#include "Include/UI.h"


#include "Include/Objects/Scene.h";
#include "Include/Objects/Softbody.h";

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void character_callback(GLFWwindow* window, unsigned int codepoint);













void On_Create();
void On_Update();
void initEngine(const char* Name = "Application", GLuint width = 1280, GLuint height = 920, bool fullScreen = false);





