#pragma once

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

#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// GLEW
#define GLEW_STATIC
#include <GL/glew.h>


// GLFW
#include <GLFW/glfw3.h>
#include <windows.h>

// Engine parts
#include "engine/Components/Shader.h"
#include "engine/Components/Mathematics.h"



const GLuint WIDTH = 1280, HEIGHT = 920;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;


glm::vec4 BackgroundColor = glm::vec4(0.01f, 0.01f, 0.01f, 1.0f);

glm::vec2 MousePosition;
glm::vec2 scrpos = glm::vec2(0, 0);
bool keys[1024];
bool buttons[64];
bool SettingsWindow = false;

bool DrawingOrder = true; // 1 - cubes, 0- ballllz

int framecount = 0;
float delta = 0.0f;
float timer = 0.0f, lt = 0.0f;
GLFWwindow* window;

float SceneExposure = 0.7f;



float dt_of_sim = 0.017f;
int substeps = 1;

glm::vec2 g = glm::vec2(0.0f);
float friction = 1.0f;

#include "engine/Components/Objects/VerletObject.h";

#include "engine/Components/Objects/Ball.h";
#include "engine/Components/Collisions/BallToBall.h";

#include "engine/Components/Objects/Quad.h";
#include "engine/Components/Collisions/CircleToQuad.h";


#include "engine/Components/Objects/Line.h";
#include "engine/Components/Collisions/BallToLine.h";

#include "engine/Components/Objects/Polygon.h";


//------------------------------------------------------------------------------------------------------------------------------------------------------------
// SETTINGS kind of
//------------------------------------------------------------------------------------------------------------------------------------------------------------

bool HDR = true;
bool bloom = true;
//----------



////---------------------------------------------- QUAD
unsigned int quadVAO,quadVBO,
ScreenVAO,ScreenVBO,
CircleVAO, CircleVBO
;
////---------------------------------------------- QUAD








std::vector <glm::mat4> Circletranslations;
std::vector <glm::vec4> Circlecolors;
std::vector <glm::vec4> CirclePosRadEdg; //(x,y,r,edgeWidth)


void DrawCircle(glm::vec2 position, float r, float edgesmoothness = 0.0001f, glm::vec4 color = glm::vec4(1.0f))
{


	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) / (HEIGHT / 2) - 1.25f + scrpos.x * 2, (position.y) / (HEIGHT / 2) - 1.0f + scrpos.y * 2, 0.0f));

	trans = glm::scale(trans, glm::vec3((r + edgesmoothness) / (0.0225 * HEIGHT), (r + edgesmoothness) / (0.0225 * HEIGHT), 0.0f)); 
	
	glm::vec4 PosRadEdge = glm::vec4(position.x, position.y, r, edgesmoothness);
	
		Circletranslations.push_back(trans);
		Circlecolors.push_back(color);
		CirclePosRadEdg.push_back(PosRadEdge);
}


std::vector <glm::mat4> Quadtranslations;
std::vector <glm::vec4> Quadcolors;
void DrawCube(glm::vec2 position, glm::vec2 scale, glm::vec3 rotation = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f))
{
	scale *= 0.04;
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3((position.x) / (HEIGHT / 2) - 1.25f + scrpos.x * 2, (position.y) / (HEIGHT / 2) - 1.0f + scrpos.y * 2, 0.0f));

	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x, scale.y, 0.0f));
	

	Quadtranslations.push_back(trans);
	Quadcolors.push_back(color);
	
	
}


void DrawLine(glm::vec2 p1, glm::vec2 p2, float width = 1.0f, glm::vec4 color = glm::vec4(1.0f))
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y) / (0.20 * 1280);
	DrawCube(midpos, glm::vec2(length*5.56f*25, width), glm::vec3(0.0f, 0.0f, rotation),color);
}












ImVec4  firecolor = ImVec4(1.0f, 0.53f, 0.3f, 0.117f);

static float f = 3.0f;
// The engine class, main core block


class Engine
 {
 public:


	

	unsigned int FrameBuffer, ColorBuffer;

	virtual void On_Create()
	{
		std::cout << "NO On_Create() FUNCTION FOUNDED!\n";
	}
	virtual void On_Update()
	{
		std::cout << "NO On_Update() FUNCTION FOUNDED!\n";
	}



	void init()
	{


		

		


		// Init GLFW
		glfwInit();
		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Create a GLFWwindow object that we can use for GLFW's functions
		window = glfwCreateWindow(WIDTH, HEIGHT, "Stuff", nullptr, nullptr);
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
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



		//ScreenShaderStuff for HDR and postprocessing
		

		
			Shader shaderBlur("engine/Shaders/blur.vert", "engine/Shaders/blur.frag");
			Shader shaderBloom("engine/Shaders/Screen.vert", "engine/Shaders/bloom.frag");//выборка из hdr буффера

			Shader ScrShade("engine/Shaders/Screen.vert", "engine/Shaders/Screen.frag");



			float ScreenVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
				// positions   // texCoords
				-1.0f,  1.0f,  0.0f, 1.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,

				-1.0f,  1.0f,  0.0f, 1.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f
			};

			/*Shader ScreenShader("Screen.vert", "Screen.frag");
			ScrShade = &ScreenShader;*/
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

			unsigned int hdrFBO;
			glGenFramebuffers(1, &hdrFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
			// create 2 floating point color buffers (1 for normal rendering, other for brightness threshold values)
			GLuint colorBuffer2;
			glGenTextures(1, &colorBuffer2);
			
				glBindTexture(GL_TEXTURE_2D, colorBuffer2);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
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
			unsigned int pingpongFBO[2];
			unsigned int pingpongColorbuffers[2];
			glGenFramebuffers(2, pingpongFBO);
			glGenTextures(2, pingpongColorbuffers);
			for (unsigned int i = 0; i < 2; i++)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
				glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
				// also check if framebuffers are complete (no need for depth buffer)
				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
					std::cout << "Framebuffer not complete ping!" << std::endl;
			}
		



		float Vertices[] = {
			// координаты  // цвета
			-0.05f,  0.05f,
			 0.05f, -0.05f, 
			-0.05f, -0.05f, 

			-0.05f,  0.05f, 
			 0.05f, -0.05f,  
			 0.05f,  0.05f
		};
		


		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);




		glGenVertexArrays(1, &CircleVAO);
		glGenBuffers(1, &CircleVBO);

		glBindVertexArray(CircleVAO);
		glBindBuffer(GL_ARRAY_BUFFER, CircleVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);



		Shader FillShader("engine/Shaders/default.vert", "engine/Shaders/Quad.frag");
		Shader CircleShader("engine/Shaders/Circle.vert", "engine/Shaders/Circle.frag");
		Shader InctanceQuadShader("engine/Shaders/instance.vert", "engine/Shaders/Quad.frag");



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
		

		



		unsigned int instanceCircleVBO;
		unsigned int instanceVBO;

		On_Create();

		

		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();


			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();


			if (HDR)
				glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
			else
				glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glClearColor(BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			MousePosition.x = lastX - scrpos.x * HEIGHT;
			MousePosition.y = -lastY + HEIGHT - scrpos.y * HEIGHT;




			// Collision processing
			for (int i = 0; i < ballsptr.size(); i++)
			{

				for (int a = 0; a < ballsptr.size(); a++)
				{
					if (a > i)
						BtBCollision(ballsptr[i], ballsptr[a]);
				}

			}

			// Main update
			On_Update();






			// instancing
			{
				glGenBuffers(1, &instanceCircleVBO);
				glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO);

				glBindVertexArray(CircleVAO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Circlecolors.size(), &Circlecolors[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

				glVertexAttribDivisor(1, 1);





				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glGenBuffers(1, &instanceCircleVBO);
				glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO);

				glBindVertexArray(CircleVAO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * CirclePosRadEdg.size(), &CirclePosRadEdg[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

				glVertexAttribDivisor(2, 1);


				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);



				glGenBuffers(1, &instanceCircleVBO);
				glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO);

				glBindVertexArray(CircleVAO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * Circletranslations.size(), &Circletranslations[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);

				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));

				glEnableVertexAttribArray(5);
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));

				glEnableVertexAttribArray(6);
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

				glVertexAttribDivisor(3, 1);
				glVertexAttribDivisor(4, 1);
				glVertexAttribDivisor(5, 1);
				glVertexAttribDivisor(6, 1);


				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

			}

			{
				glGenBuffers(1, &instanceVBO);
				glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

				glBindVertexArray(quadVAO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * Quadcolors.size(), &Quadcolors[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

				glVertexAttribDivisor(2, 1);


				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);


				glGenBuffers(1, &instanceVBO);
				glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

				glBindVertexArray(quadVAO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * Quadtranslations.size(), &Quadtranslations[0], GL_STATIC_DRAW);


				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);

				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));

				glEnableVertexAttribArray(5);
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));

				glEnableVertexAttribArray(6);
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

				glVertexAttribDivisor(3, 1);
				glVertexAttribDivisor(4, 1);
				glVertexAttribDivisor(5, 1);
				glVertexAttribDivisor(6, 1);



				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}


			



			if (DrawingOrder)
			{
				InctanceQuadShader.Use();
				glBindVertexArray(quadVAO);
				glDrawArraysInstanced(GL_TRIANGLES, 0, 6, Quadcolors.size());
				glBindVertexArray(0);

				glDeleteBuffers(5, &instanceVBO);

				CircleShader.Use();
				glBindVertexArray(CircleVAO);
				glDrawArraysInstanced(GL_TRIANGLES, 0, 6, Circlecolors.size());
				glBindVertexArray(0);

				glDeleteBuffers(5, &instanceCircleVBO);

				Quadcolors.clear();
				Quadtranslations.clear();
				Circlecolors.clear();
				CirclePosRadEdg.clear();
				Circletranslations.clear();
			}
			else {
				
				CircleShader.Use();
				glBindVertexArray(CircleVAO);
				glDrawArraysInstanced(GL_TRIANGLES, 0, 6, Circlecolors.size());
				glBindVertexArray(0);

				glDeleteBuffers(5, &instanceCircleVBO);

				InctanceQuadShader.Use();
				glBindVertexArray(quadVAO);
				glDrawArraysInstanced(GL_TRIANGLES, 0, 6, Quadcolors.size());
				glBindVertexArray(0);

				glDeleteBuffers(5, &instanceVBO);

				Quadcolors.clear();
				Quadtranslations.clear();
				Circlecolors.clear();
				CirclePosRadEdg.clear();
				Circletranslations.clear();
			}


			if (SettingsWindow)
			{
				ImGui::Begin("Settings");
				
				
				if (ImGui::Button("HDR"))
					HDR = !HDR;
				if (HDR)
					ImGui::SliderFloat("SceneExposure", &SceneExposure, 0.0f, 2.0f);
				
				
				if (ImGui::Button("bloom"))
					bloom = !bloom;
				ImGui::SameLine();
				if (bloom)
					ImGui::Text("on");
				else
					ImGui::Text("off");
				if (ImGui::Button("Drawing order"))
					DrawingOrder = !DrawingOrder;
				ImGui::SameLine();
				if (DrawingOrder)
					ImGui::Text("rects first");
				else
					ImGui::Text("circles first");

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
					glBindVertexArray(ScreenVAO);
					glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[0]);
					glDisable(GL_DEPTH_TEST);

					glClear(GL_COLOR_BUFFER_BIT );

					shaderBloom.Use();


					glBindTexture(GL_TEXTURE_2D, ColorBuffer);

					glDrawArrays(GL_TRIANGLES, 0, 6);

					glBindFramebuffer(GL_FRAMEBUFFER, 0);
					
					bool horizontal = true, first_iteration = true;
					unsigned int amount = 10;
					shaderBlur.Use();
					for (unsigned int i = 0; i < amount; i++)
					{
						glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
						glUniform1i(glGetUniformLocation(shaderBlur.Program, "horizontal"), horizontal);
						glBindTexture(GL_TEXTURE_2D, first_iteration ? pingpongColorbuffers[0] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
						glDrawArrays(GL_TRIANGLES, 0, 6);
						horizontal = !horizontal;
						if (first_iteration)
							first_iteration = false;
					}



					glBindFramebuffer(GL_FRAMEBUFFER, 0);

					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					ScrShade.Use();


					glUniform1f(glGetUniformLocation(ScrShade.Program, "bloom"), bloom);
					glUniform1f(glGetUniformLocation(ScrShade.Program, "exposure"), SceneExposure);



					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, ColorBuffer);
					glUniform1i(glGetUniformLocation(ScrShade.Program, "scene"), 1);

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
					glUniform1i(glGetUniformLocation(ScrShade.Program, "bloomBlur"), 0);

					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);
					////Sleep(100);
				}
				else
				{
					glBindFramebuffer(GL_FRAMEBUFFER, 0);

					glBindVertexArray(ScreenVAO);

					ScrShade.Use();

					glBindTexture(GL_TEXTURE_2D, ColorBuffer);

					glUniform1f(glGetUniformLocation(ScrShade.Program, "bloom"), bloom);
					glUniform1f(glGetUniformLocation(ScrShade.Program, "exposure"), SceneExposure);
					glDisable(GL_DEPTH_TEST);

					glDrawArrays(GL_TRIANGLES, 0, 6);
					glBindVertexArray(0);
				}
			}



			//float delta = 0.0f;
			//float timer = 0.0f, lt = 0.0f;
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