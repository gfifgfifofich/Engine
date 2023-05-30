#pragma once

/* TODO
1) compleate polygon collisions
2) remake Drawing to compleatly 2D, for optimization (or leave it for some 2.5d shananigans)
3) better bloom
Features:
	

	Lighting is kinda cool too
	
	Tilemap
	Sprite & textures
*/


/* Example implimentation


#include "engine/Components/Engine.h"
class application : public Engine
{
	void On_Create() override
	{

	}
	void On_Update() override
	{

	}
};
int main()
{
	application app;
	app.init();
	return 0;
}



*/







#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif



#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <strstream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>




//stbi
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>




// Engine parts
#include "engine/Components/Shader.h"
#include "engine/Components/Mathematics.h"



GLuint WIDTH = 1280, HEIGHT = 720;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;


glm::vec4 BackgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

glm::vec2 MousePosition;
glm::vec2 scrpos = glm::vec2(0, 0);
bool keys[1024];
bool JustPressedkey[1024];
bool JustReleasedkey[1024];
bool Holdingkey[1024];
bool buttons[64];
bool JustPressedbutton[64];
bool JustReleasedbutton[64];
bool Holdingbutton[64];
bool SettingsWindow = true;


int framecount = 0;
float delta = 0.0f;
float timer = 0.0f, lt = 0.0f;
GLFWwindow* window;

float SceneExposure = 0.7f;


float dt_of_sim = 0.017f;


	
enum SHAPE {CIRCLE,QUAD,LINE,TRIANGLE};
bool DrawCubicColiders = false;


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
float bloomLevelDivisor = 5.0f;
//Chromatic abberation
float ChromaticStrength = 0.0f;
glm::vec2 ChromaticPoint = glm::vec2(0.5f);





#include "engine/Components/Objects/VerletObject.h";

#include "engine/Components/Objects/Ball.h";

std::vector <ball*> ballsptr;

#include "engine/Components/Collisions/BallToBall.h";

#include "engine/Components/Objects/Quad.h";

std::vector <cube*> cubes;


glm::vec4 AmbientColor = glm::vec4(1.0f);


#include "engine/Components/Drawing.h"

#include "engine/Components/Collisions/CircleToQuad.h";
#include "engine/Components/Collisions/QuadToQuad.h";


#include "engine/Components/Objects/Line.h";
#include "engine/Components/Collisions/BallToLine.h";

#include "engine/Components/Objects/Polygon.h";
#include "engine/Components/Collisions/Ball to Polygon.h";


#include "engine/Components/Objects/Ray.h";
#include "engine/Components/Collisions/RayCastToShapes.h";

#include "Physics/Spring.h";
#include "Physics/Strut.h";

#include "Objects/Box.h";
#include "Collisions/BoxToBox.h";

#include "Objects/SoftBody.h";




#include "engine/Components/Text.h"
#include "Objects/Particle.h";
std::vector <ParticleEmiter*> ParticleEmiters;




#include "engine/Components/Classes.h"


//Requeres DLL, + works funky
//#include "engine/Components/sounds.h"





#include "engine/Components/Objects/Scene.h";







bool ReleasedLMB = false;
bool HoldingLMB = false;
bool JustPressedLMB = false;


class Engine
 {
 public:
	 unsigned int DownScaleBuffers[6];

	virtual void On_Create()
	{
		std::cout << "NO On_Create() FUNCTION FOUNDED!\n";
	}
	virtual void On_Update()
	{
		std::cout << "NO On_Update() FUNCTION FOUNDED!\n";
	}


	void init(const char* Name = "Application", GLuint width = 1280, GLuint height = 920, bool fullScreen = false)
	{

		WIDTH = width;
		HEIGHT = height;

		ScreenAspectRatio = (float)WIDTH / HEIGHT;

		

		ScreenDivisorX = (WIDTH / (ScreenAspectRatio * 2)) - ScreenAspectRatio * 0.75f;
		ScreenDivisorY = (HEIGHT / 2.0f) - 1.0f;

		ScreenDivisorX = 1.0f / ScreenDivisorX;
		ScreenDivisorY = 1.0f / ScreenDivisorY;

		ScaleMultiplyer = 1.0f / HEIGHT * 2.0f;
		//AL_init();
		// Init GLFW
		glfwInit();
		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Create a GLFWwindow object that we can use for GLFW's functions
		if (fullScreen)
			window = glfwCreateWindow(WIDTH, HEIGHT, Name, glfwGetPrimaryMonitor(), nullptr);
		else
			window = glfwCreateWindow(WIDTH, HEIGHT, Name, nullptr, nullptr);
		glfwMakeContextCurrent(window);

		// Set the required callback functions
		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;
		// Initialize GLEW to setup the OpenGL Function pointers
		glewInit();

		// Define the viewport dimensions
		int swidth, sheight;
		glfwGetFramebufferSize(window, &swidth, &sheight);

		glViewport(0, 0, swidth, sheight);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		//ScreenShaderStuff for HDR and postprocessing


		GLuint InctanceQuadShader;
		GLuint InstanceTexturedQuadShader;

		LoadShader(&InctanceQuadShader, "engine/Shaders/Quad/instance.vert", "engine/Shaders/Quad/Quad.frag");
		LoadShader(&InstanceTexturedQuadShader, "engine/Shaders/InstancedTexturedQuad/InstancedTexturedQuad.vert", "engine/Shaders/InstancedTexturedQuad/InstancedTexturedQuad.frag");
		
		//Texture Generation
		LoadShader(&GradientGenShader, "engine/Shaders/Quad/TexturedQuad.vert", "engine/Shaders/Quad/TexturedQuad.frag");
		LoadShader(&NoizeGenShader, "engine/Shaders/NoizeGen/NoizeGen.vert", "engine/Shaders/NoizeGen/NoizeGen.frag");
		LoadShader(&RoundShader, "engine/Shaders/Round/Round.vert", "engine/Shaders/Round/Round.frag");
		LoadShader(&AddTexturesShader, "engine/Shaders/Default.vert", "engine/Shaders/Textures/AddTextures.frag");
		LoadShader(&GenNormalMapShader, "engine/Shaders/Default.vert", "engine/Shaders/NormalMap/GenNormalMap.frag");
		LoadShader(&GenLightSphereShader, "engine/Shaders/Default.vert", "engine/Shaders/Light/GenLightSphere.frag");
		
		//Post processing
		LoadShader(&BlurShader, "engine/Shaders/blur/blur.vert", "engine/Shaders/blur/blur.frag");
		LoadShader(&shaderBloom, "engine/Shaders/Default.vert", "engine/Shaders/Bloom/bloom.frag");
		LoadShader(&ScrShade, "engine/Shaders/Default.vert", "engine/Shaders/Screen.frag");
		LoadShader(&Chromatic, "engine/Shaders/Default.vert", "engine/Shaders/Chromatic/Chromatic.frag");
		LoadShader(&DownsampleBlur, "engine/Shaders/Default.vert", "engine/Shaders/blur/DownscaleBlur.frag");
		LoadShader(&UpsampleBlur, "engine/Shaders/Default.vert", "engine/Shaders/blur/UpsampleBlur.frag");

		//Drawing
		//Quad
		LoadShader(&FillShader, "engine/Shaders/Quad/default.vert", "engine/Shaders/Quad/Quad.frag");
		LoadShader(&TexturedQuadShader, "engine/Shaders/Quad/TexturedQuad.vert", "engine/Shaders/Quad/TexturedQuad.frag");

		//Circle	
		LoadShader(&CircleShader, "engine/Shaders/Circle/Circle.vert", "engine/Shaders/Circle/Circle.frag");

		//Lighting
		LoadShader(&InstancedNormalMapShader, "engine/Shaders/InstancedNormalMap/InstancedNMDraw.vert", "engine/Shaders/InstancedNormalMap/NormalMapDraw.frag");
		LoadShader(&NormalMapDrawShader, "engine/Shaders/NormalMap/NormalMapDraw.vert", "engine/Shaders/NormalMap/NormalMapDraw.frag");

		LoadShader(&LightShader, "engine/Shaders/Light/Light.vert", "engine/Shaders/Light/LightProcess.frag");

		//Triangle	
		LoadShader(&FillTriangleShader, "engine/Shaders/Triangle/Fill.vert", "engine/Shaders/Triangle/Fill.frag");
		LoadShader(&TexturedTriangleShader, "engine/Shaders/Triangle/TexturedTriangle.vert", "engine/Shaders/Triangle/TexturedTriangle.frag");

		//Text
		LoadShader(&TextShader, "engine/Shaders/Quad/TexturedQuad.vert", "engine/Shaders/Text.frag");

		PreLoadShaders();
		PreLoadShaders();
		
		float ScreenVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};

		glGenVertexArrays(1, &ScreenVAO);
		glGenVertexArrays(1, &ScreenVAO);
		glGenBuffers(1, &ScreenVBO);
		glBindVertexArray(ScreenVAO);
		glBindBuffer(GL_ARRAY_BUFFER, ScreenVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ScreenVertices), ScreenVertices, GL_STATIC_DRAW);



		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		glGenFramebuffers(1, &FrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);

		glGenTextures(1, &ColorBuffer);
		glBindTexture(GL_TEXTURE_2D, ColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorBuffer, 0);




		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//Bloom stuff
		//setting weights

		//creating buffers for downscale



		// downscale frame buffer and textures
		unsigned int downscaleFBO[6];
		glGenFramebuffers(6, downscaleFBO);
		for (int i = 0; i < 6; i++)
		{

			glBindFramebuffer(GL_FRAMEBUFFER, downscaleFBO[i]);
			glGenTextures(1, &DownScaleBuffers[i]);
			glBindTexture(GL_TEXTURE_2D, DownScaleBuffers[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH / (pow(2.0f,i+1)), HEIGHT / (pow(2.0f, i + 1)), 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			glBindTexture(GL_TEXTURE_2D, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, DownScaleBuffers[i], 0);

		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		glGenFramebuffers(1, &NormalMapFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);
		glGenTextures(1, &NormalMapColorBuffer);
		glBindTexture(GL_TEXTURE_2D, NormalMapColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, NormalMapColorBuffer, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glGenFramebuffers(1, &LightColorFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, LightColorFBO);
		glGenTextures(1, &LightColorBuffer);
		glBindTexture(GL_TEXTURE_2D, LightColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, LightColorBuffer, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		//HDR
			unsigned int hdrFBO;
			glGenFramebuffers(1, &hdrFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
			// create 1 floating point color buffers
			GLuint colorBuffer2;
			glGenTextures(1, &colorBuffer2);
			
				glBindTexture(GL_TEXTURE_2D, colorBuffer2);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				// attach texture to framebuffer
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer2, 0);


			// create and attach depth buffer (renderbuffer)
			unsigned int rboDepth;
			glGenRenderbuffers(1, &rboDepth);
			glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
			// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
			unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
			glDrawBuffers(2, attachments);
			// finally check if framebuffer is complete
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "Framebuffer not complete!" << std::endl;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
			// ping-pong-framebuffer for blurring
			unsigned int blurFBO[2];
			unsigned int blurColorbuffers[2];
			glGenFramebuffers(2, blurFBO);
			glGenTextures(2, blurColorbuffers);
			for (unsigned int i = 0; i < 2; i++)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[i]);
				glBindTexture(GL_TEXTURE_2D, blurColorbuffers[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blurColorbuffers[i], 0);
				// also check if framebuffers are complete (no need for depth buffer)
				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					std::cout << "Framebuffer not complete ping!" << std::endl;
			}
		



		float Vertices[] = {
			// coordinates  // UV
			-1.0f,  1.0f, 0.0f,1.0f,
			 1.0f, -1.0f, 1.0f,0.0f,
			-1.0f, -1.0f, 0.0f,0.0f,

			-1.0f,  1.0f, 0.0f,1.0f,
			 1.0f, -1.0f, 1.0f,0.0f,
			 1.0f,  1.0f, 1.0f,1.0f
		};
		
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);



	



		glGenVertexArrays(1, &CircleVAO);
		glGenBuffers(1, &CircleVBO);

		glBindVertexArray(CircleVAO);
		glBindBuffer(GL_ARRAY_BUFFER, CircleVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);


		glGenVertexArrays(1, &TextVAO);
		glGenBuffers(1, &TextVBO);
		glBindVertexArray(TextVAO);
		glBindBuffer(GL_ARRAY_BUFFER, TextVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		glGenVertexArrays(1, &TriangleVAO);
		glGenBuffers(1, &TriangleVBO);
		glBindVertexArray(TriangleVAO);
		glBindBuffer(GL_ARRAY_BUFFER, TriangleVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 2, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glGenVertexArrays(1, &TexturedTriangleVAO);
		glGenBuffers(1, &TexturedTriangleVBO);
		glBindVertexArray(TexturedTriangleVAO);
		glBindBuffer(GL_ARRAY_BUFFER, TexturedTriangleVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		

		

		GenNormalMapTexture(&BallNormalMapTexture, 1000, 2);
		GenNormalMapTexture(&CubeNormalMapTexture, 1000, 0);
		GenLightSphereTexture(&LightSphereTexture, 100);
		

		unsigned int instanceCircleVBO;
		unsigned int instanceNormalMapCircleVBO;
		unsigned int instanceNormalMapCubeVBO;
		unsigned int instanceNormalMapTextureVBO;
		unsigned int instanceTexturedQuadVBO;
		unsigned int instanceVBO;
		


		

		LoadFont("engine/fonts/arial.ttf");

		On_Create();


		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();


			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);
			glClearColor(0.0f,0.0f,0.0f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBindFramebuffer(GL_FRAMEBUFFER, LightColorFBO);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (HDR)
				glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
			else
				glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glClearColor(BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			MousePosition.x = (lastX - WIDTH * 0.5f) / CameraScale.x + CameraPosition.x;
			MousePosition.y = (-lastY + HEIGHT * 0.5f) / CameraScale.y + CameraPosition.y;

			for (int i = 0; i < 1024; i++)
			{
				if (!Holdingkey[i] && keys[i]) JustPressedkey[i] = true;
				else JustPressedkey[i] = false;

				if (Holdingkey[i] && !keys[i]) JustReleasedkey[i] = true;
				else JustReleasedkey[i] = false;

				if (keys[i]) Holdingkey[i] = true;
				else Holdingkey[i] = false;
			}
			for (int i = 0; i < 64; i++)
			{
				if (!Holdingbutton[i] && buttons[i]) JustPressedbutton[i] = true;
				else JustPressedbutton[i] = false;

				if (Holdingbutton[i] && !buttons[i]) JustReleasedbutton[i] = true;
				else JustReleasedbutton[i] = false;

				if (buttons[i]) Holdingbutton[i] = true;
				else Holdingbutton[i] = false;
			}

			if (!HoldingLMB && buttons[GLFW_MOUSE_BUTTON_1]) JustPressedLMB = true;
			else JustPressedLMB = false;

			if (HoldingLMB && !buttons[GLFW_MOUSE_BUTTON_1]) ReleasedLMB = true;
			else ReleasedLMB = false;

			if (buttons[GLFW_MOUSE_BUTTON_1]) HoldingLMB = true;
			else HoldingLMB = false;


			// update Scene
			On_Update();



			//Particle Processing LineParticles
			for (int i = 0; i < ParticleEmiters.size(); i++)
				ParticleEmiters[i]->Process(dt_of_sim);

			// Collision processing
				for (int i = 0; i < ballsptr.size(); i++)
				{
					if (ballsptr[i]->Collision_Mask != -1)
					{
						for (int a = 0; a < ballsptr.size(); a++)
						{
							if (a != i && ballsptr[i]->Collision_Mask == ballsptr[a]->Collision_Level)
								BtBCollision(ballsptr[i], ballsptr[a]);
						}
						for (int a = 0; a < cubes.size(); a++)
						{
							if (ballsptr[i]->Collision_Mask == cubes[a]->Collision_Level)
							{

								BallToStaticQuadCollision(ballsptr[i], *cubes[a]);
							}
						}
					}
				}
				for (int i = 0; i < cubes.size(); i++)
				{
					if (cubes[i]->Collision_Mask != -1)
						for (int a = 0; a < cubes.size(); a++)
							if (a != i && cubes[i]->Collision_Mask == cubes[a]->Collision_Level)
							{
								QuadToQuadCollision(cubes[i], cubes[a]);
								if (DrawCubicColiders)
								{
									DrawCube(cubes[i]->position, glm::vec2(cubes[i]->width, cubes[i]->height), 0.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
									DrawCube(cubes[a]->position, glm::vec2(cubes[a]->width, cubes[a]->height), 0.0f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
								}
							}
				}
			




				float aspect = (float)HEIGHT / WIDTH;

				for (int i = 0; i < SceneLayers.size(); i++)
				{
					// instancing
					{
						glGenBuffers(1, &instanceCircleVBO);
						glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO);
						glBindVertexArray(CircleVAO);


						glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].Circlecolors.size(), &SceneLayers[i].Circlecolors[0], GL_STATIC_DRAW);

						glEnableVertexAttribArray(1);
						glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
						glVertexAttribDivisor(1, 1);

						glGenBuffers(1, &instanceCircleVBO);
						glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO);
						glBindVertexArray(CircleVAO);

						glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].CirclePosScale.size(), &SceneLayers[i].CirclePosScale[0], GL_STATIC_DRAW);

						glEnableVertexAttribArray(2);
						glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);


						glVertexAttribDivisor(2, 1);



						glGenBuffers(1, &instanceCircleVBO);
						glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO);
						glBindVertexArray(CircleVAO);

						glBufferData(GL_ARRAY_BUFFER, sizeof(float)* SceneLayers[i].CircleRotations.size(), &SceneLayers[i].CircleRotations[0], GL_STATIC_DRAW);

						glEnableVertexAttribArray(3);
						glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

						glBindVertexArray(0);
						glBindBuffer(GL_ARRAY_BUFFER, 0);
					}
					//quads
					{
						glGenBuffers(1, &instanceVBO);
						glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

						glBindVertexArray(quadVAO);

						glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].Quadcolors.size(), &SceneLayers[i].Quadcolors[0], GL_STATIC_DRAW);

						glEnableVertexAttribArray(2);
						glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

						glVertexAttribDivisor(2, 1);



						glGenBuffers(1, &instanceVBO);

						glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

						glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].QuadPosScale.size(), &SceneLayers[i].QuadPosScale[0], GL_STATIC_DRAW);


						glEnableVertexAttribArray(3);
						glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);


						glVertexAttribDivisor(3, 1);

						glGenBuffers(1, &instanceVBO);

						glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

						glBufferData(GL_ARRAY_BUFFER, sizeof(float)* SceneLayers[i].QuadRotations.size(), &SceneLayers[i].QuadRotations[0], GL_STATIC_DRAW);


						glEnableVertexAttribArray(4);
						glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);


						glVertexAttribDivisor(4, 1);


						glBindVertexArray(0);
						glBindBuffer(GL_ARRAY_BUFFER, 0);

					}

					UseShader(InctanceQuadShader);
					glUniform1f(glGetUniformLocation(InctanceQuadShader, "aspect"), aspect);
					glBindVertexArray(quadVAO);
					glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].Quadcolors.size());
					glBindVertexArray(0);

					glDeleteBuffers(7, &instanceVBO);

					UseShader(CircleShader);
					glUniform1f(glGetUniformLocation(CircleShader, "aspect"), aspect);
					glBindVertexArray(CircleVAO);
					glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].Circlecolors.size());
					glBindVertexArray(0);

					glDeleteBuffers(7, &instanceCircleVBO);

					SceneLayers[i].Quadcolors.clear();
					SceneLayers[i].QuadPosScale.clear();
					SceneLayers[i].QuadRotations.clear();

					SceneLayers[i].Circlecolors.clear();
					SceneLayers[i].CirclePosScale.clear();
					SceneLayers[i].CircleRotations.clear();


					for (int TQA = 0; TQA < SceneLayers[i].TexturedQuads.size(); TQA++)
					{
						UseShader(InstanceTexturedQuadShader);

						glUniform1f(glGetUniformLocation(InstanceTexturedQuadShader, "aspect"), aspect);


						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, SceneLayers[i].TexturedQuads[TQA].Texture);
						glUniform1i(glGetUniformLocation(InstanceTexturedQuadShader, "Texture"), 0);

						glGenBuffers(1, &instanceTexturedQuadVBO);
						glBindBuffer(GL_ARRAY_BUFFER, instanceTexturedQuadVBO);
						glBindVertexArray(quadVAO);
						glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)* SceneLayers[i].TexturedQuads[TQA].Quadcolors.size(), &SceneLayers[i].TexturedQuads[TQA].Quadcolors[0], GL_STATIC_DRAW);

						glEnableVertexAttribArray(1);
						glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

						glVertexAttribDivisor(1, 1);


						glGenBuffers(1, &instanceTexturedQuadVBO);
						glBindBuffer(GL_ARRAY_BUFFER, instanceTexturedQuadVBO);
						glBindVertexArray(quadVAO);

						glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)* SceneLayers[i].TexturedQuads[TQA].QuadPosScale.size(), &SceneLayers[i].TexturedQuads[TQA].QuadPosScale[0], GL_STATIC_DRAW);

						glEnableVertexAttribArray(2);
						glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

						glVertexAttribDivisor(2, 1);

						glGenBuffers(1, &instanceTexturedQuadVBO);

						glBindBuffer(GL_ARRAY_BUFFER, instanceTexturedQuadVBO);

						glBufferData(GL_ARRAY_BUFFER, sizeof(float)* SceneLayers[i].TexturedQuads[TQA].QuadRotations.size(), &SceneLayers[i].TexturedQuads[TQA].QuadRotations[0], GL_STATIC_DRAW);


						glEnableVertexAttribArray(3);
						glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);


						glVertexAttribDivisor(3, 1);

						glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].TexturedQuads[TQA].QuadPosScale.size());
						glDeleteBuffers(7, &instanceTexturedQuadVBO);

						glBindVertexArray(0);
						glBindBuffer(GL_ARRAY_BUFFER, 0);

						SceneLayers[i].TexturedQuads[TQA].Quadcolors.clear();
						SceneLayers[i].TexturedQuads[TQA].QuadPosScale.clear();
						SceneLayers[i].TexturedQuads[TQA].QuadRotations.clear();
					}


					// NormalMaps
						if (Lighting)
						{
							glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);

							UseShader(InstancedNormalMapShader);



							glUniform1f(glGetUniformLocation(InstancedNormalMapShader, "aspect"), aspect);


							glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, CubeNormalMapTexture);
							glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "Texture"), 0);

							glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "AlphaTexture"), false);
							glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "generated"), true);
							glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "flipY"), false);



							glGenBuffers(1, &instanceNormalMapCubeVBO);
							glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapCubeVBO);
							glBindVertexArray(quadVAO);
							glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].NormalMapCubeRotations.size(), &SceneLayers[i].NormalMapCubeRotations[0], GL_STATIC_DRAW);

							glEnableVertexAttribArray(1);
							glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

							glVertexAttribDivisor(1, 1);


							glGenBuffers(1, &instanceNormalMapCubeVBO);
							glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapCubeVBO);
							glBindVertexArray(quadVAO);

							glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].NormalMapCubePosScale.size(), &SceneLayers[i].NormalMapCubePosScale[0], GL_STATIC_DRAW);

							glEnableVertexAttribArray(2);
							glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);


							glVertexAttribDivisor(2, 1);

							glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].NormalMapCubePosScale.size());
							glDeleteBuffers(7, &instanceNormalMapCubeVBO);

							glBindVertexArray(0);
							glBindBuffer(GL_ARRAY_BUFFER, 0);



							glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, BallNormalMapTexture);
							glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "Texture"), 0);

							glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "AlphaTexture"), false);
							glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "generated"), true);
							glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "flipY"), false);

							glGenBuffers(1, &instanceNormalMapCircleVBO);
							glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapCircleVBO);
							glBindVertexArray(quadVAO);
							glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].NormalMapCircleRotations.size(), &SceneLayers[i].NormalMapCircleRotations[0], GL_STATIC_DRAW);

							glEnableVertexAttribArray(1);
							glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

							glVertexAttribDivisor(1, 1);

							glGenBuffers(1, &instanceNormalMapCircleVBO);
							glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapCircleVBO);
							glBindVertexArray(quadVAO);

							glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].NormalMapCirclePosScale.size(), &SceneLayers[i].NormalMapCirclePosScale[0], GL_STATIC_DRAW);

							glEnableVertexAttribArray(2);
							glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

							glVertexAttribDivisor(2, 1);
							glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].NormalMapCirclePosScale.size());
							glDeleteBuffers(7, &instanceNormalMapCircleVBO);

							glBindVertexArray(0);
							glBindBuffer(GL_ARRAY_BUFFER, 0);



							SceneLayers[i].NormalMapCirclePosScale.clear();
							SceneLayers[i].NormalMapCubePosScale.clear();
							SceneLayers[i].NormalMapCircleRotations.clear();
							SceneLayers[i].NormalMapCubeRotations.clear();


							for (int NQA = 0; NQA < SceneLayers[i].NormalMaps.size(); NQA++)
							{
								UseShader(InstancedNormalMapShader);

								glUniform1f(glGetUniformLocation(InstancedNormalMapShader, "aspect"), aspect);

								glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "generated"), false);
								glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "flipY"), true);

								glActiveTexture(GL_TEXTURE0);
								glBindTexture(GL_TEXTURE_2D, SceneLayers[i].NormalMaps[NQA].Texture);
								glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "Texture"), 0);


								glActiveTexture(GL_TEXTURE1);
								glBindTexture(GL_TEXTURE_2D, SceneLayers[i].NormalMaps[NQA].Texture2);
								glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "Texture2"), 1);

								if (SceneLayers[i].NormalMaps[NQA].Texture2 != NULL)
									glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "AlphaTexture"), true);
								else
									glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "AlphaTexture"), false);


								glGenBuffers(1, &instanceNormalMapTextureVBO);
								glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapTextureVBO);
								glBindVertexArray(quadVAO);
								glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].NormalMaps[NQA].QuadRotations.size(), &SceneLayers[i].NormalMaps[NQA].QuadRotations[0], GL_STATIC_DRAW);

								glEnableVertexAttribArray(1);
								glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

								glVertexAttribDivisor(1, 1);


								glGenBuffers(1, &instanceNormalMapTextureVBO);
								glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapTextureVBO);
								glBindVertexArray(quadVAO);

								glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].NormalMaps[NQA].QuadPosScale.size(), &SceneLayers[i].NormalMaps[NQA].QuadPosScale[0], GL_STATIC_DRAW);

								glEnableVertexAttribArray(2);
								glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

								glVertexAttribDivisor(2, 1);

								glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].NormalMaps[NQA].QuadPosScale.size());
								glDeleteBuffers(6, &instanceNormalMapTextureVBO);

								glBindVertexArray(0);
								glBindBuffer(GL_ARRAY_BUFFER, 0);

								SceneLayers[i].NormalMaps[NQA].Quadcolors.clear();
								SceneLayers[i].NormalMaps[NQA].QuadPosScale.clear();
								SceneLayers[i].NormalMaps[NQA].QuadRotations.clear();
							}


							if (HDR)
								glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
							else
								glBindFramebuffer(GL_FRAMEBUFFER, 0);
						}

				}

			


			



			if (Lighting) {

				glBindFramebuffer(GL_FRAMEBUFFER, LightColorFBO);

				UseShader(LightShader);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, NormalMapColorBuffer);
				glUniform1i(glGetUniformLocation(LightShader, "NormalMap"), 0);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, ColorBuffer);
				glUniform1i(glGetUniformLocation(LightShader, "BaseColor"), 2);

				
				for (int i = 0; i < LightSources.size(); i++)
				{




					glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
						(LightSources[i].position.x - CameraPosition.x) * ScreenDivisorX * CameraScale.x,
						(LightSources[i].position.y - CameraPosition.y) * ScreenDivisorY * CameraScale.y,
						0.0f));


					if (LightSources[i].rotation != 0)
						trans = glm::rotate(trans, LightSources[i].rotation, glm::vec3(0.0f, 0.0f, 1.0f));

					trans = glm::scale(trans, glm::vec3(LightSources[i].scale.x * CameraScale.x * ScaleMultiplyer, LightSources[i].scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));



					float ahigh = 1.0 / HEIGHT;

					LightSources[i].position -= CameraPosition;
					LightSources[i].position.x *= CameraScale.x / WIDTH;
					LightSources[i].position.y *= CameraScale.y * ahigh;

					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, LightSources[i].texture);
					glUniform1i(glGetUniformLocation(LightShader, "Texture"), 1);

					glUniform4f(glGetUniformLocation(LightShader, "color"), LightSources[i].color.r, LightSources[i].color.g, LightSources[i].color.b, LightSources[i].color.a);
					glUniform2f(glGetUniformLocation(LightShader, "position"), LightSources[i].position.x, LightSources[i].position.y);
					glUniform2f(glGetUniformLocation(LightShader, "scale"), LightSources[i].scale.x, LightSources[i].scale.y);
					glUniform1f(glGetUniformLocation(LightShader, "volume"), LightSources[i].volume);


					glUniform3f(glGetUniformLocation(LightShader, "scr"), WIDTH, HEIGHT, WIDTH * ahigh);
					glUniformMatrix4fv(glGetUniformLocation(LightShader, "transform"), 1, GL_FALSE, glm::value_ptr(trans));



					glBindVertexArray(quadVAO);
					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);


				}

				if (HDR)
					glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
				else
					glBindFramebuffer(GL_FRAMEBUFFER, 0);
				LightSources.clear();

				glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);

				UseShader(AddTexturesShader);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, LightColorBuffer);
				glUniform1i(glGetUniformLocation(AddTexturesShader, "Texture1"), 0);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, ColorBuffer);
				glUniform1i(glGetUniformLocation(AddTexturesShader, "Texture2"), 1);
				glUniform2f(glGetUniformLocation(AddTexturesShader, "proportions"), DirectionalLight, AmbientLight);

				glBindVertexArray(ScreenVAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
				glActiveTexture(GL_TEXTURE0);

			}

			//Text that marked ato Draw Above Everything else
			for (int i = 0; i < TextLines.size(); i++)
				DrawText(TextLines[i].text, TextLines[i].x, TextLines[i].y, TextLines[i].scale, TextLines[i].color, false);
			TextLines.clear();


			int fb = 0;
			if (SettingsWindow)
			{
				ImGui::Begin("Settings");
				
				
				if (ImGui::Button("Lighting"))
					Lighting = !Lighting;

				if (HDR)
					ImGui::SliderFloat("SceneExposure", &SceneExposure, 0.0f, 2.0f);
				
				
				if (ImGui::Button("bloom"))
					bloom = !bloom;
				ImGui::SameLine();
				if (bloom)
					ImGui::Text("on");
				else
					ImGui::Text("off");

				ImGui::SliderFloat("AmbientLight", &AmbientLight, 0.0f, 1.0f);
				ImGui::SliderFloat("DirectionalLight", &DirectionalLight, 0.0f, 1.0f);


				ImGui::SliderFloat("bloomIntensity", &bloomIntensity, 0.0f, 10.0f);
				ImGui::SliderFloat("bloomLevelDivisor", &bloomLevelDivisor, 1.0f, 10.0f);

				ImGui::SliderFloat("strength", &ChromaticStrength, 0.0f, 1.0f);

				float col[4] = { BackgroundColor.r ,BackgroundColor.g,BackgroundColor.b,BackgroundColor.a };
				ImGui::ColorEdit4("BackgroundColor", col);
				BackgroundColor = { col[0],col[1],col[2],col[3] };

				if (ImGui::Button("Show NormalMaps"))
				{
					NormalMap = true;
					RegularMap = false;
					LightingMap = false;
				}
				if (ImGui::Button("Show RegularMap"))
				{
					NormalMap = false;
					RegularMap = true;
					LightingMap = false;
				}
				if (ImGui::Button("Show LightingMap"))
				{
					NormalMap = false;
					RegularMap = false;
					LightingMap = true;
				}
				if (NormalMap)fb = 8;
				if (RegularMap)fb = 0;
				if (LightingMap)fb = 9;

				ImGui::End();
			}
			/*Imgui example
			{
				// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
				

				// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
				//{
				//	static int counter = 0;

				//	ImGui::Begin("Settings");                          // Create a window called "Hello, world!" and append into it.

				//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

				//	ImGui::SliderFloat("float", &f, 0.0f, 10.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				//	ImGui::ColorEdit4("clear color", (float*)&firecolor); // Edit 3 floats representing a color

				//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				//		counter++;
				//	ImGui::SameLine();
				//	ImGui::Text("counter = %d", counter);

				//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
				//		1000.0f / ImGui::GetIO().Framerate,
				//		ImGui::GetIO().Framerate);
				//	ImGui::End();
				//}

				// 3. Show another simple window.
				//if (show_another_window)
				//{
				//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
				//	ImGui::Text("Hello from another window!");
				//	if (ImGui::Button("Close Me"))
				//		show_another_window = false;
				//	ImGui::End();
				//}
			}
			*/




			if (HDR)
			{
				if (bloom) {

					glBindFramebuffer(GL_FRAMEBUFFER, 0);

					glClear(GL_COLOR_BUFFER_BIT );


					glBindVertexArray(ScreenVAO);
					glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[0]);
					glDisable(GL_DEPTH_TEST);
					glClear(GL_COLOR_BUFFER_BIT);

					//threshholding the main image
					UseShader(shaderBloom);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, ColorBuffer);
					glUniform1i(glGetUniformLocation(shaderBloom, "screenTexture"), 1);
					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindFramebuffer(GL_FRAMEBUFFER, 0);

					//Downsample and blur a few times
					glBindVertexArray(ScreenVAO);
					UseShader(DownsampleBlur);
					for (int i = 0; i < 6; i++)
					{ 
						glViewport(0, 0, WIDTH / (pow(2.0f, i + 1)), HEIGHT / (pow(2.0f, i + 1)));
						glBindFramebuffer(GL_FRAMEBUFFER, downscaleFBO[i]);

						//input texture
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, i == 0 ? blurColorbuffers[0] : DownScaleBuffers[i - 1]);
						glUniform1i(glGetUniformLocation(DownsampleBlur, "srcTexture"), 0);


						glUniform2f(glGetUniformLocation(DownsampleBlur, "srcResolution"), WIDTH/ (pow(2.0f, i + 1)), HEIGHT/ (pow(2.0f, i + 1)));

						glDrawArrays(GL_TRIANGLES, 0, 6);

					}


					//Upsample backwards and blur
					glBindVertexArray(ScreenVAO);
					UseShader(UpsampleBlur);
					glUniform1f(glGetUniformLocation(UpsampleBlur, "filterRadius"), 10.0f);
					for (int i = 5; i > 0; i--)
					{ 
						glViewport(0, 0, WIDTH / (pow(2.0f, i )), HEIGHT / (pow(2.0f, i )));
						glBindFramebuffer(GL_FRAMEBUFFER, downscaleFBO[i - 1]);

						//input texture
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, DownScaleBuffers[i]);
						glUniform1i(glGetUniformLocation(UpsampleBlur, "srcTexture"), 0);


						glActiveTexture(GL_TEXTURE1);
						glBindTexture(GL_TEXTURE_2D, DownScaleBuffers[i-1]);
						glUniform1i(glGetUniformLocation(UpsampleBlur, "PrevTexture"), 1);

						glUniform1f(glGetUniformLocation(UpsampleBlur, "weight"),i/ bloomLevelDivisor);

						glDrawArrays(GL_TRIANGLES, 0, 6);

					}
					//Reset parameters back to normal
					glViewport(0, 0, WIDTH, HEIGHT);


					glBindFramebuffer(GL_FRAMEBUFFER, blurFBO[0]);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
					UseShader(ScrShade);

					glUniform1f(glGetUniformLocation(ScrShade, "bloom"), bloom);
					glUniform1f(glGetUniformLocation(ScrShade, "exposure"), SceneExposure);

					glUniform1f(glGetUniformLocation(ScrShade, "BloomStrength"), bloomIntensity);


					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, ColorBuffer);
					glUniform1i(glGetUniformLocation(ScrShade, "scene"), 1);

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, DownScaleBuffers[0]);
					glUniform1i(glGetUniformLocation(ScrShade, "bloomBlur"), 0);


					glDrawArrays(GL_TRIANGLES, 0, 6); 
					unsigned int fm = blurColorbuffers[0];

					if(fb ==0)
						fm = blurColorbuffers[0];
					else 
						fm = fb;

					UseShader(Chromatic);
					glBindFramebuffer(GL_FRAMEBUFFER,0);
					glBindTexture(GL_TEXTURE_2D, fm);
					
					ChromaticPoint = glm::vec2(0.5f,0.5f);
					glUniform2f(glGetUniformLocation(Chromatic, "point"), ChromaticPoint.x, ChromaticPoint.y);
					
					
					glUniform1f(glGetUniformLocation(Chromatic, "strength"), ChromaticStrength);

					glDrawArrays(GL_TRIANGLES, 0, 6);// the last drawing, directly to screen
					


					glBindVertexArray(0);


				}
				else
				{
					glBindFramebuffer(GL_FRAMEBUFFER, 0);

					glBindVertexArray(ScreenVAO);

					UseShader(ScrShade);

					glBindTexture(GL_TEXTURE_2D, ColorBuffer);

					glUniform1f(glGetUniformLocation(ScrShade, "bloom"), bloom);
					glUniform1f(glGetUniformLocation(ScrShade, "exposure"), SceneExposure);
					glDisable(GL_DEPTH_TEST);

					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);
				}
			}



			delta = (clock() - lt)*0.001f;
			lt = clock();
			//if(17 - delta * 1000>0)
				//Sleep(16 - delta * 1000);
			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			glfwSwapBuffers(window);
		}
		glfwTerminate();
		//AL_Destroy();
	}
};


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < 64)
	{
		if (action == GLFW_PRESS)
			buttons[button] = true;
		else if (action == GLFW_RELEASE)
			buttons[button] = false;
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	lastX = xpos;
	lastY = ypos;


}



