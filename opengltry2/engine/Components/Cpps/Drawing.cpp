
#include "../Include/Helper.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <map>


#define DRAWINGIMPLEMENTATION
#include "../Include/Drawing.h"

#include "../Include/Text.h"
#include "../Include/UI.h"

//One time use. May become invalid after adding or deleating window, safe if otherwise.
Window* GetWindow(int id)
{
	for (int i = 0; i < Windows.size(); i++)
		if (Windows[i].id == id)return &Windows[i];
}

glm::vec2 Window::GetSize() 
{
	return (ViewportSize*0.5f) * Scale;
}

void Window::RecalculateSize()
{

	inited = false;
	Destroy();
	inited = true;
	w_ScreenAspectRatio = ViewportSize.x / ViewportSize.y;


	w_ScreenDivisorX = (ViewportSize.x / (w_ScreenAspectRatio * 2));
	w_ScreenDivisorY = (ViewportSize.y / 2.0f);

	w_ScreenDivisorX = 1.0f / w_ScreenDivisorX;
	w_ScreenDivisorY = 1.0f / w_ScreenDivisorY;
	w_ScaleMultiplyer = 1.0f / ViewportSize.y * 2.0f;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &Texture);

	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
	glBindTexture(GL_TEXTURE_2D, Texture);
	if (hdr)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, ViewportSize.x, ViewportSize.y, 0, GL_RGBA, GL_FLOAT, NULL);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ViewportSize.x, ViewportSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture, 0);

	glGenFramebuffers(1, &NormalMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);
	glGenTextures(1, &NormalMapColorBuffer);
	glBindTexture(GL_TEXTURE_2D, NormalMapColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, ViewportSize.x, ViewportSize.y, 0, GL_RGBA, GL_FLOAT, NULL);
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, ViewportSize.x, ViewportSize.y, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, LightColorBuffer, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
void Window::Init(glm::vec2 ViewportSize, bool linearFilter, bool hdr)
{
	Use();
	this->ViewportSize = ViewportSize;
	RecalculateSize();


	this->linearFilter = linearFilter;
	this->hdr = hdr;
	GetWindow(window_id)->Use();
	inited = true;
}

void Window::Use()
{



	Window* prevWindow = GetWindow(window_id);
	prevWindow->w_LightSources = LightSources;
	prevWindow->w_SceneLayers = SceneLayers;
	
	prevWindow->w_CameraPosition = CameraPosition;
	prevWindow->w_CameraScale = CameraScale;
	

	ScreenAspectRatio = w_ScreenAspectRatio ;

	LightSources = this->w_LightSources;
	SceneLayers = this->w_SceneLayers;

	ScreenDivisorX = w_ScreenDivisorX ;
	ScreenDivisorY = w_ScreenDivisorY ;
	ScaleMultiplyer = w_ScaleMultiplyer;

	CameraPosition = w_CameraPosition;
	CameraScale = w_CameraScale;

	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
	glViewport(0, 0, ViewportSize.x, ViewportSize.y);
	WIDTH = ViewportSize.x;
	HEIGHT = ViewportSize.y;
	if (id == 0)
	{
		ScreenMousePosition = { (lastX - WIDTH * 0.5f) ,(-lastY + HEIGHT * 0.5f) };
		//ScreenMousePosition -= Position;

		MousePosition.x = ScreenMousePosition.x / CameraScale.x + CameraPosition.x;
		MousePosition.y = ScreenMousePosition.y / CameraScale.y + CameraPosition.y;

		WindowMousePosition = ScreenMousePosition;
	}
	else
	{
		WindowMousePosition = (prevWindow->WindowMousePosition - Position);
		WindowMousePosition /= Scale;
		MousePosition.x = WindowMousePosition.x / CameraScale.x + CameraPosition.x;
		MousePosition.y = WindowMousePosition.y / CameraScale.y + CameraPosition.y;
		ScreenMousePosition = WindowMousePosition;
	}

	window_id = id;
}

void  Window::Clear(glm::vec4 Color)
{
	glViewport(0, 0, ViewportSize.x, ViewportSize.y);

	glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, LightColorFBO);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(Color.r, Color.g, Color.b, Color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// why making a transparent texture so hard?
	glBlendFunc(GL_ZERO, GL_ONE);
	glBindVertexArray(ScreenVAO);
	UseShader(FillScreenShader);
	SetShader4f(&FillScreenShader, "color", Color);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	DetachShader();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GetWindow(window_id)->Use();
}
void Window::End()
{

	GetWindow(0)->Use();
}

void Window::Destroy()
{
	if (inited)
		Destroyed = true;
	if (Texture != NULL)
		glDeleteTextures(1, &Texture);
	if (this->framebuffer != NULL)
		glDeleteFramebuffers(1, &this->framebuffer);


	if (LightColorBuffer != NULL)
		glDeleteTextures(1, &LightColorBuffer);
	if (this->LightColorFBO != NULL)
		glDeleteFramebuffers(1, &this->LightColorFBO);


	if (NormalMapColorBuffer != NULL)
		glDeleteTextures(1, &NormalMapColorBuffer);
	if (this->NormalMapFBO != NULL)
		glDeleteFramebuffers(1, &this->NormalMapFBO);

	if (window_id == id)
		window_id = 0;
}
void Window::_Draw()
{
	Use();





	unsigned int instanceCircleVBO[3];
	unsigned int instanceNormalMapCircleVBO[2];
	unsigned int instanceVBO[3];
	unsigned int instanceNormalMapCubeVBO[2];
	unsigned int instanceNormalMapTextureVBO[2];
	unsigned int instanceTexturedQuadVBO[3];

	float aspect = (float)HEIGHT / WIDTH;

	for (int i = 0; i < SceneLayers.size(); i++)
	{
		if (SceneLayers[i].Additive)
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		else
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// instancing
		{
			glGenBuffers(3, &instanceCircleVBO[0]);
			glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO[0]);
			glBindVertexArray(CircleVAO);


			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].Circlecolors.size(), &SceneLayers[i].Circlecolors[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
			glVertexAttribDivisor(1, 1);

			glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO[1]);
			glBindVertexArray(CircleVAO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].CirclePosScale.size(), &SceneLayers[i].CirclePosScale[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

			glVertexAttribDivisor(2, 1);

			glBindBuffer(GL_ARRAY_BUFFER, instanceCircleVBO[2]);
			glBindVertexArray(CircleVAO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].CircleRotations.size(), &SceneLayers[i].CircleRotations[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		//quads
		{
			glGenBuffers(3, instanceVBO);
			glBindBuffer(GL_ARRAY_BUFFER, instanceVBO[0]);

			glBindVertexArray(quadVAO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].Quadcolors.size(), &SceneLayers[i].Quadcolors[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

			glVertexAttribDivisor(2, 1);



			glBindBuffer(GL_ARRAY_BUFFER, instanceVBO[1]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].QuadPosScale.size(), &SceneLayers[i].QuadPosScale[0], GL_STATIC_DRAW);
			glBindVertexArray(quadVAO);


			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);


			glVertexAttribDivisor(3, 1);


			glBindBuffer(GL_ARRAY_BUFFER, instanceVBO[2]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].QuadRotations.size(), &SceneLayers[i].QuadRotations[0], GL_STATIC_DRAW);
			glBindVertexArray(quadVAO);


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


		DetachShader();
		UseShader(CircleShader);
		glUniform1f(glGetUniformLocation(CircleShader, "aspect"), aspect);
		glBindVertexArray(CircleVAO);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].Circlecolors.size());
		glBindVertexArray(0);

		glDeleteBuffers(3, instanceCircleVBO);



		glDeleteBuffers(3, instanceVBO);
		DetachShader();
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

			glGenBuffers(3, instanceTexturedQuadVBO);
			glBindBuffer(GL_ARRAY_BUFFER, instanceTexturedQuadVBO[0]);
			glBindVertexArray(quadVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].TexturedQuads[TQA].Quadcolors.size(), &SceneLayers[i].TexturedQuads[TQA].Quadcolors[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

			glVertexAttribDivisor(1, 1);


			glBindBuffer(GL_ARRAY_BUFFER, instanceTexturedQuadVBO[1]);
			glBindVertexArray(quadVAO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].TexturedQuads[TQA].QuadPosScale.size(), &SceneLayers[i].TexturedQuads[TQA].QuadPosScale[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

			glVertexAttribDivisor(2, 1);


			glBindBuffer(GL_ARRAY_BUFFER, instanceTexturedQuadVBO[2]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].TexturedQuads[TQA].QuadRotations.size(), &SceneLayers[i].TexturedQuads[TQA].QuadRotations[0], GL_STATIC_DRAW);


			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);


			glVertexAttribDivisor(3, 1);

			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].TexturedQuads[TQA].QuadPosScale.size());
			glDeleteBuffers(3, instanceTexturedQuadVBO);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			SceneLayers[i].TexturedQuads[TQA].Quadcolors.clear();
			SceneLayers[i].TexturedQuads[TQA].QuadPosScale.clear();
			SceneLayers[i].TexturedQuads[TQA].QuadRotations.clear();
			DetachShader();
		}
		for (int TQA = 0; TQA < SceneLayers[i].FlippedTexturedQuads.size(); TQA++)
		{
			UseShader(InstanceFlippedTexturedQuadShader);

			glUniform1f(glGetUniformLocation(InstanceFlippedTexturedQuadShader, "aspect"), aspect);


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, SceneLayers[i].FlippedTexturedQuads[TQA].Texture);
			glUniform1i(glGetUniformLocation(InstanceFlippedTexturedQuadShader, "Texture"), 0);

			glGenBuffers(3, instanceTexturedQuadVBO);
			glBindBuffer(GL_ARRAY_BUFFER, instanceTexturedQuadVBO[0]);
			glBindVertexArray(quadVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)* SceneLayers[i].FlippedTexturedQuads[TQA].Quadcolors.size(), &SceneLayers[i].FlippedTexturedQuads[TQA].Quadcolors[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

			glVertexAttribDivisor(1, 1);


			glBindBuffer(GL_ARRAY_BUFFER, instanceTexturedQuadVBO[1]);
			glBindVertexArray(quadVAO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)* SceneLayers[i].FlippedTexturedQuads[TQA].QuadPosScale.size(), &SceneLayers[i].FlippedTexturedQuads[TQA].QuadPosScale[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

			glVertexAttribDivisor(2, 1);


			glBindBuffer(GL_ARRAY_BUFFER, instanceTexturedQuadVBO[2]);

			glBufferData(GL_ARRAY_BUFFER, sizeof(float)* SceneLayers[i].FlippedTexturedQuads[TQA].QuadRotations.size(), &SceneLayers[i].FlippedTexturedQuads[TQA].QuadRotations[0], GL_STATIC_DRAW);


			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);


			glVertexAttribDivisor(3, 1);

			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].FlippedTexturedQuads[TQA].QuadPosScale.size());
			glDeleteBuffers(3, instanceTexturedQuadVBO);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			SceneLayers[i].FlippedTexturedQuads[TQA].Quadcolors.clear();
			SceneLayers[i].FlippedTexturedQuads[TQA].QuadPosScale.clear();
			SceneLayers[i].FlippedTexturedQuads[TQA].QuadRotations.clear();
			DetachShader();
		}
		SceneLayers[i].FlippedTexturedQuads.clear();
		//Text that marked ato Draw Above Everything else
		for (int tt = 0; tt < SceneLayers[i].TextLines.size(); tt++)
			_DrawText(SceneLayers[i].TextLines[tt].text, SceneLayers[i].TextLines[tt].x, SceneLayers[i].TextLines[tt].y, SceneLayers[i].TextLines[tt].scale, SceneLayers[i].TextLines[tt].color);
		SceneLayers[i].TextLines.clear();

		for (int tt = 0; tt < SceneLayers[i].UI_TextLines.size(); tt++)
			_UI_DrawText(SceneLayers[i].UI_TextLines[tt].text, SceneLayers[i].UI_TextLines[tt].x, SceneLayers[i].UI_TextLines[tt].y, SceneLayers[i].UI_TextLines[tt].scale, SceneLayers[i].UI_TextLines[tt].color);
		SceneLayers[i].UI_TextLines.clear();

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// NormalMaps
		if (Lighting)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBindFramebuffer(GL_FRAMEBUFFER, NormalMapFBO);

			UseShader(InstancedNormalMapShader);


			glUniform1f(glGetUniformLocation(InstancedNormalMapShader, "aspect"), aspect);


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, CubeNormalMapTexture);
			glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "Texture"), 0);

			glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "AlphaTexture"), false);
			glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "generated"), true);
			glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "flipY"), false);



			glGenBuffers(2, instanceNormalMapCubeVBO);
			glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapCubeVBO[0]);
			glBindVertexArray(quadVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].NormalMapCubeRotations.size(), &SceneLayers[i].NormalMapCubeRotations[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

			glVertexAttribDivisor(1, 1);


			glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapCubeVBO[1]);
			glBindVertexArray(quadVAO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].NormalMapCubePosScale.size(), &SceneLayers[i].NormalMapCubePosScale[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);


			glVertexAttribDivisor(2, 1);

			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].NormalMapCubePosScale.size());

			glDeleteBuffers(2, instanceNormalMapCubeVBO);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, BallNormalMapTexture);
			glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "Texture"), 0);

			glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "AlphaTexture"), false);
			glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "generated"), true);
			glUniform1i(glGetUniformLocation(InstancedNormalMapShader, "flipY"), false);

			glGenBuffers(2, instanceNormalMapCircleVBO);
			glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapCircleVBO[0]);
			glBindVertexArray(quadVAO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].NormalMapCircleRotations.size(), &SceneLayers[i].NormalMapCircleRotations[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

			glVertexAttribDivisor(1, 1);

			glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapCircleVBO[1]);
			glBindVertexArray(quadVAO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].NormalMapCirclePosScale.size(), &SceneLayers[i].NormalMapCirclePosScale[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

			glVertexAttribDivisor(2, 1);
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].NormalMapCirclePosScale.size());
			glDeleteBuffers(2, instanceNormalMapCircleVBO);



			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);



			SceneLayers[i].NormalMapCirclePosScale.clear();
			SceneLayers[i].NormalMapCubePosScale.clear();
			SceneLayers[i].NormalMapCircleRotations.clear();
			SceneLayers[i].NormalMapCubeRotations.clear();
			DetachShader();

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


				glGenBuffers(2, instanceNormalMapTextureVBO);
				glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapTextureVBO[0]);
				glBindVertexArray(quadVAO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SceneLayers[i].NormalMaps[NQA].QuadRotations.size(), &SceneLayers[i].NormalMaps[NQA].QuadRotations[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

				glVertexAttribDivisor(1, 1);


				glBindBuffer(GL_ARRAY_BUFFER, instanceNormalMapTextureVBO[1]);
				glBindVertexArray(quadVAO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * SceneLayers[i].NormalMaps[NQA].QuadPosScale.size(), &SceneLayers[i].NormalMaps[NQA].QuadPosScale[0], GL_STATIC_DRAW);

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

				glVertexAttribDivisor(2, 1);

				glDrawArraysInstanced(GL_TRIANGLES, 0, 6, SceneLayers[i].NormalMaps[NQA].QuadPosScale.size());
				glDeleteBuffers(2, instanceNormalMapTextureVBO);

				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				SceneLayers[i].NormalMaps[NQA].Quadcolors.clear();
				SceneLayers[i].NormalMaps[NQA].QuadPosScale.clear();
				SceneLayers[i].NormalMaps[NQA].QuadRotations.clear();
				DetachShader();
			}

			SceneLayers[i].NormalMaps.clear();

			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		}

	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




	if (Lighting) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindFramebuffer(GL_FRAMEBUFFER, LightColorFBO);

		UseShader(LightShader);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, NormalMapColorBuffer);
		glUniform1i(glGetUniformLocation(LightShader, "NormalMap"), 0);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(glGetUniformLocation(LightShader, "BaseColor"), 2);

		//std::cout<<"\ni "<<id<<" ls = "<<LightSources.size();

		for (int i = 0; i < LightSources.size(); i++)
		{

			float aspx = ScreenDivisorX * CameraScale.x;
			float aspy = ScreenDivisorY * CameraScale.y;
			glm::vec2 Apos = glm::vec2(LightSources[i].position.x, LightSources[i].position.y);
			Apos -= CameraPosition;
			Apos.x *= aspx;
			Apos.y *= aspy;
			LightSources[i].scale *= glm::vec2(aspx, aspy);

			LightSources[i].position.x -= CameraPosition.x;
			LightSources[i].position.y -= CameraPosition.y;
			LightSources[i].position.x *= CameraScale.x / WIDTH;
			LightSources[i].position.y *= CameraScale.y / HEIGHT;

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, LightSources[i].texture);
			glUniform1i(glGetUniformLocation(LightShader, "Texture"), 1);

			glUniform3f(glGetUniformLocation(LightShader, "position"), LightSources[i].position.x, LightSources[i].position.y, LightSources[i].position.z);
			glUniform2f(glGetUniformLocation(LightShader, "Aposition"), Apos.x, Apos.y);
			glUniform2f(glGetUniformLocation(LightShader, "scale"), LightSources[i].scale.x, LightSources[i].scale.y);
			glUniform1f(glGetUniformLocation(LightShader, "angle"), LightSources[i].rotation);

			glUniform4f(glGetUniformLocation(LightShader, "color"), LightSources[i].color.r, LightSources[i].color.g, LightSources[i].color.b, LightSources[i].color.a);
			glUniform1f(glGetUniformLocation(LightShader, "volume"), LightSources[i].volume);
			glUniform1f(glGetUniformLocation(LightShader, "aspect"), aspect);
			glUniform2f(glGetUniformLocation(LightShader, "scr"), WIDTH, HEIGHT);



			glBindVertexArray(quadVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);


		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		DetachShader();

		LightSources.clear();

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		UseShader(AddTexturesShader);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, LightColorBuffer);
		glUniform1i(glGetUniformLocation(AddTexturesShader, "Texture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(glGetUniformLocation(AddTexturesShader, "Texture2"), 1);
		glUniform2f(glGetUniformLocation(AddTexturesShader, "proportions"), DirectionalLight, AmbientLight);

		glBindVertexArray(ScreenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);

		DetachShader();
	}

}



int CreateWindow()
{
	Window w;
	w.id = Windows.size();
	Windows.push_back(w);

	CurrentWindow = GetWindow(window_id);
	return w.id;
}


void UseWindow(int id)
{
	GetWindow(id)->Use();
}
void EndOfWindow()
{
	window_id = 0;
}




void PreLoadShaders()
{


	LoadShader(&FillScreenShader, "engine/Shaders/Default.vert", "engine/Shaders/FillScreen.frag");

	LoadShader(&InctanceQuadShader, "engine/Shaders/Quad/instance.vert", "engine/Shaders/Quad/Quad.frag");
	LoadShader(&InstanceTexturedQuadShader, "engine/Shaders/InstancedTexturedQuad/InstancedTexturedQuad.vert", "engine/Shaders/InstancedTexturedQuad/InstancedTexturedQuad.frag");
	LoadShader(&InstanceFlippedTexturedQuadShader, "engine/Shaders/InstancedTexturedQuad/InstancedFlippedTexturedQuad.vert", "engine/Shaders/InstancedTexturedQuad/InstancedFlippedTexturedQuad.frag");


	//Texture Generation
	LoadShader(&GradientGenShader, "engine/Shaders/Default.vert", "engine/Shaders/GradientGen/GradientGen.frag");
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



	LoadShader(&GenPrimitiveTextureShader, "engine/Shaders/Default.vert", "engine/Shaders/GenPrimitiveTextureShader.frag");
}
void SortSceneLayers()
{
	if (SceneLayers.size() > 2)
	{
		int i = 1;
		int a = 2;

		while (i <SceneLayers.size())
		{
			if ((SceneLayers[i - 1].Z_Index < SceneLayers[i].Z_Index) ||
				(SceneLayers[i - 1].Z_Index == SceneLayers[i].Z_Index) && !SceneLayers[i - 1].Additive && SceneLayers[i].Additive)
			{
				i = a;
				a++;
			}
			else if ((SceneLayers[i - 1].Z_Index > SceneLayers[i].Z_Index) ||
				((SceneLayers[i - 1].Z_Index == SceneLayers[i].Z_Index) && SceneLayers[i - 1].Additive && !SceneLayers[i].Additive))
			{
				SceneLayer tmp = SceneLayers[i - 1];
				SceneLayers[i - 1] = SceneLayers[i];
				SceneLayers[i] = tmp;
				i--;
				if (i == 0)
				{
					i = a;
					a++;
				}
			}
		}
	}
	else if (SceneLayers.size() == 2)
	{
		if ((SceneLayers[0].Z_Index >SceneLayers[1].Z_Index) ||
			((SceneLayers[0].Z_Index == SceneLayers[1].Z_Index) && SceneLayers[0].Additive && !SceneLayers[1].Additive))
		{
			SceneLayer tmp = SceneLayers[0];
			SceneLayers[0] = SceneLayers[1];
			SceneLayers[1] = tmp;
		}
	}
}
int FindSceneLayer(int Z_Index, bool Additive)
{
	int SLI = -1;

	for (int i = 0; i < SceneLayers.size(); i++)
		if (SceneLayers[i].Z_Index == Z_Index && SceneLayers[i].Additive == Additive)
			SLI = i;
	if (SLI == -1)
	{
		SceneLayer sl;
		sl.Z_Index = Z_Index;
		sl.Additive = Additive;
		SceneLayers.push_back(sl);
		SortSceneLayers();
		for (int i = 0; i < SceneLayers.size(); i++)
			if (SceneLayers[i].Z_Index == Z_Index)
				SLI = i;
	}
	return SLI;
}

void DrawLight(glm::vec2 position, glm::vec2 scale, glm::vec4 color, float volume, float rotation, unsigned int texture)
{
	LightSource ls;
	ls.volume = volume;
	ls.position = glm::vec3(position, -0.5f);
	ls.scale = scale;
	ls.rotation = rotation;
	ls.color = color;
	ls.texture = texture;
	LightSources.push_back(ls);
}
void DrawLight(glm::vec3 position, glm::vec2 scale, glm::vec4 color, float volume, float rotation, unsigned int texture)
{
	LightSource ls;
	ls.volume = volume;
	ls.position = position;
	ls.scale = scale;
	ls.rotation = rotation;
	ls.color = color;
	ls.texture = texture;
	LightSources.push_back(ls);
}
void NormalMapDraw(glm::vec2 position, glm::vec2 scale, unsigned int NormalMap , float rotation, int Z_Index , unsigned int Texture, bool Additive )
{
	if (NormalMap != BallNormalMapTexture && NormalMap != CubeNormalMapTexture)
	{

		int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false
		float aspx = ScreenDivisorX * CameraScale.x;
		float aspy = ScreenDivisorY * CameraScale.y;

		position -= CameraPosition;
		position *= glm::vec2(aspx, aspy);
		scale *= glm::vec2(aspx, aspy);


		int TQA = -1;

		for (int i = 0; i < SceneLayers[SLI].NormalMaps.size(); i++)
			if (SceneLayers[SLI].NormalMaps[i].Texture == NormalMap &&SceneLayers[SLI].NormalMaps[i].Texture2 == Texture)
				TQA = i;

		if (TQA == -1)
		{
			TexturedQuadArray NewTQA;
			NewTQA.Texture = NormalMap;
			NewTQA.Texture2 = Texture;
			SceneLayers[SLI].NormalMaps.push_back(NewTQA);
			for (int i = 0; i < SceneLayers[SLI].NormalMaps.size(); i++)
				if (SceneLayers[SLI].NormalMaps[i].Texture == NormalMap && SceneLayers[SLI].NormalMaps[i].Texture2 == Texture)
					TQA = i;
		}

		SceneLayers[SLI].NormalMaps[TQA].QuadPosScale.push_back(glm::vec4(position, scale));
		SceneLayers[SLI].NormalMaps[TQA].QuadRotations.push_back(rotation);


	}
	else
	{
		float aspx = ScreenDivisorX * CameraScale.x;
		float aspy = ScreenDivisorY * CameraScale.y;

		position -= CameraPosition;
		position *= glm::vec2(aspx, aspy);
		scale *= glm::vec2(aspx, aspy);



		int SLI =FindSceneLayer(Z_Index, Additive);

		if (NormalMap == BallNormalMapTexture)
		{
			SceneLayers[SLI].NormalMapCircleRotations.push_back(rotation);
			SceneLayers[SLI].NormalMapCirclePosScale.push_back(glm::vec4(position, scale));
		}
		else
		{
			SceneLayers[SLI].NormalMapCubeRotations.push_back(rotation);
			SceneLayers[SLI].NormalMapCubePosScale.push_back(glm::vec4(position, scale));
		}
	}
}
void NormalMapDrawTriangle(
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	unsigned int NormalMap,
	glm::vec2 texcoord1,
	glm::vec2 texcoord2,
	glm::vec2 texcoord3 
)
{

	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->NormalMapFBO);
	UseShader(TexturedTriangleShader);
	glBindVertexArray(TexturedTriangleVAO);
	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	p1.x = (p1.x - CameraPosition.x) * aspx;
	p1.y = (p1.y - CameraPosition.y) * aspy;

	p2.x = (p2.x - CameraPosition.x) * aspx;
	p2.y = (p2.y - CameraPosition.y) * aspy;

	p3.x = (p3.x - CameraPosition.x) * aspx;
	p3.y = (p3.y - CameraPosition.y) * aspy;

	GLfloat vertices[3][4] =
	{
		{ p1.x, p1.y,texcoord1.x,texcoord1.y},
		{ p2.x, p2.y,texcoord2.x,texcoord2.y},
		{ p3.x, p3.y,texcoord3.x,texcoord3.y}
	};


	glBindBuffer(GL_ARRAY_BUFFER, TexturedTriangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, NormalMap);
	glUniform1i(glGetUniformLocation(TexturedTriangleShader, "Texture"), 0);

	glUniform4f(glGetUniformLocation(TexturedTriangleShader, "color"), 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform2f(glGetUniformLocation(TexturedTriangleShader, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);



	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->framebuffer);
}
void DrawCircle(glm::vec2 position, float r, glm::vec4 color , bool Lighted , unsigned int NormalMap , int Z_Index, bool Additive )
{
	glm::vec2 scale = glm::vec2(r, r);

	if (Lighted)
		NormalMapDraw(position, scale, NormalMap, 0.0f, Z_Index);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);



	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false

	SceneLayers[SLI].CirclePosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].CircleRotations.push_back(0.0f);
	SceneLayers[SLI].Circlecolors.push_back(color);

}
void DrawCircle(ball b, glm::vec4 color , bool Lighted, unsigned int NormalMap , int Z_Index, bool Additive)
{

	glm::vec2 position = b.position;
	float r = b.r;
	glm::vec2 scale = glm::vec2(r, r);
	if (Lighted)
		NormalMapDraw(position, scale, NormalMap, 0.0f, Z_Index);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);

	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false


	SceneLayers[SLI].CirclePosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].CircleRotations.push_back(0.0f);
	SceneLayers[SLI].Circlecolors.push_back(color);
}
void DrawCube(glm::vec2 position, glm::vec2 scale, float rotation, glm::vec4 color, bool Lighted , unsigned int NormalMap , int Z_Index, bool Additive)
{


	if (Lighted)
		NormalMapDraw(position, scale, NormalMap, rotation, Z_Index);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);




	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false

	SceneLayers[SLI].QuadPosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].QuadRotations.push_back(rotation);

	SceneLayers[SLI].Quadcolors.push_back(color);


}
void DrawCube(cube c, glm::vec4 color, float rotation , bool Lighted, unsigned int NormalMap, int Z_Index , bool Additive)
{


	if (Lighted)
		NormalMapDraw(c.position, glm::vec2(c.width, c.height), NormalMap, rotation, Z_Index);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	glm::vec2 position = c.position - CameraPosition;
	position *= glm::vec2(aspx, aspy);
	glm::vec2 scale = glm::vec2(c.width, c.height) * glm::vec2(aspx, aspy);

	int SLI =FindSceneLayer(Z_Index, Additive);// ,bool Additive =false

	SceneLayers[SLI].QuadPosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].QuadRotations.push_back(rotation);

	SceneLayers[SLI].Quadcolors.push_back(color);
}
void DrawLine(glm::vec2 p1, glm::vec2 p2, float width, glm::vec4 color , bool Lighted, unsigned int NormalMap , int Z_Index)
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y) * 0.5f;
	DrawCube(midpos, glm::vec2(width, length), rotation, color, Lighted, NormalMap, Z_Index);
}
void DrawBall(ball b, glm::vec4 Color1 , glm::vec4 Color2 , bool Lighted, unsigned int NormalMap , int Z_Index)
{

	glm::vec2 univec;
	univec.x = cos(b.rotation * 5) - sin(b.rotation * 5);
	univec.y = sin(b.rotation * 5) + cos(b.rotation * 5);
	DrawLine(b.position - univec * b.r * 0.7f, b.position + univec * b.r * 0.7f, 3.0f, Color2, Lighted, CubeNormalMapTexture, Z_Index);
	DrawLine(b.position + glm::vec2(-univec.y * b.r * 0.7f, univec.x * b.r * 0.7f), b.position + glm::vec2(univec.y * b.r * 0.7f, -univec.x * b.r * 0.7f), 3.0f, Color2, Lighted, CubeNormalMapTexture, Z_Index);
	DrawCircle(b, Color1, Lighted, NormalMap, Z_Index - 1);
}
void LoadTexture(const char* filename, unsigned int* texture, int chanelsAmount)
{
	if (*texture != NULL)
	{
		glDeleteTextures(1, texture);
		*texture = NULL;
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int ImageW, ImageH, nrChannels;
	unsigned char* Texture = stbi_load(filename, &ImageW, &ImageH, &nrChannels, chanelsAmount);

	if (Texture)
	{
		if (chanelsAmount == 1)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R, ImageW, ImageH, 0, GL_R, GL_UNSIGNED_BYTE, Texture);

		if (chanelsAmount == 2)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, ImageW, ImageH, 0, GL_RG, GL_UNSIGNED_BYTE, Texture);

		if (chanelsAmount == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageW, ImageH, 0, GL_RGB, GL_UNSIGNED_BYTE, Texture);

		if (chanelsAmount == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImageW, ImageH, 0, GL_RGBA, GL_UNSIGNED_BYTE, Texture);


		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glDeleteTextures(1, texture);
		*texture = NULL;
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(Texture);
	glBindTexture(GL_TEXTURE_2D, 0);

}
void LoadTextureFromData(unsigned int* texture, int width, int height, unsigned char* Data, int chanelsAmount)
{
	if (*texture != NULL)
	{
		glDeleteTextures(1, texture);
		*texture = NULL;
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



	if (chanelsAmount == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R, width, height, 0, GL_R, GL_UNSIGNED_BYTE, Data);

	if (chanelsAmount == 2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, Data);

	if (chanelsAmount == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);

	if (chanelsAmount == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);


	glGenerateMipmap(GL_TEXTURE_2D);


	//Data = *new unsigned char*;

	/*glDeleteTextures(1, texture);
	*texture = NULL;
	std::cout << "Failed to load texture" << std::endl;
*/
	glBindTexture(GL_TEXTURE_2D, 0);

}
void fLoadTextureFromData(unsigned int* texture, int width, int height, float* Data, int chanelsAmount)
{
	if (*texture != NULL)
	{
		glDeleteTextures(1, texture);
		*texture = NULL;
	}
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



	if (chanelsAmount == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, Data);

	if (chanelsAmount == 2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, width, height, 0, GL_RG, GL_FLOAT, Data);

	if (chanelsAmount == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, Data);

	if (chanelsAmount == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, Data);


	glGenerateMipmap(GL_TEXTURE_2D);


	//Data = *new unsigned char*;

	/*glDeleteTextures(1, texture);
	*texture = NULL;
	std::cout << "Failed to load texture" << std::endl;
*/
	glBindTexture(GL_TEXTURE_2D, 0);

}
void GenNoizeTexture(unsigned int* texture1, int Size, int Layers , float freq , int shape )
{
	//std::cout << "ImputTexture ID  " << *texture1;
	if (*texture1 != NULL)
	{
		//std::cout << "DELETED " << *texture1 << "\n";
		glDeleteTextures(10, texture1);
		*texture1 = NULL;
	}
	unsigned int framebuffer[2], textures[2];

	glGenFramebuffers(2, framebuffer);
	glGenTextures(2, textures);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[0], 0);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[1]);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[1], 0);

	bool even = false;
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);


	for (int i = 0; i < Layers; i++)
	{
		glm::vec2 rngoffset = glm::vec2(rand() % 10000, rand() % 10000);
		//std::cout<<"texture "<< *texture1 <<"  x " << rngoffset.x << "  y " << rngoffset.y<<"\n";
		UseShader(NoizeGenShader);

		float weight = 1.0f;
		if (i == 0) weight = 1.0f;
		else weight = 1.0f / (pow(2, i));
		// add new layer (higher freq, less wieght)
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[even]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, even ? textures[1] : textures[0]);
		glUniform1i(glGetUniformLocation(NoizeGenShader, "PrevTexture"), 0);

		glUniform1f(glGetUniformLocation(NoizeGenShader, "sizex"), (i + 1) * freq);
		glUniform1f(glGetUniformLocation(NoizeGenShader, "sizey"), (i + 1) * freq);
		glUniform1f(glGetUniformLocation(NoizeGenShader, "weight"), weight);

		glUniform1i(glGetUniformLocation(NoizeGenShader, "shape"), shape);

		glUniform2f(glGetUniformLocation(NoizeGenShader, "offset"), rngoffset.x, rngoffset.y);

		glBindVertexArray(ScreenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);



		even = !even;

	}
	//unsigned int tmp = *texture1;
	*texture1 = textures[0];
	//texture2 = tmp;
	glDeleteFramebuffers(2, framebuffer);
	glDeleteTextures(1, &textures[1]);
	//std::cout << "	ExitTexture ID  " << *texture1 << "\n\n";

	glViewport(0, 0, WIDTH, HEIGHT);



	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->framebuffer);
}
void GenPrimitiveTexture(unsigned int* texture1, int Size, int shape )
{

	glDeleteTextures(1, texture1);
	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);


	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);

	UseShader(GenPrimitiveTextureShader);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	int i = 0;
	if (shape == ROUND)
		i = 0;
	else
		i = 1;
	glUniform1i(glGetUniformLocation(GenNormalMapShader, "Type"), i);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);


	glDeleteFramebuffers(1, &framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->framebuffer);
}
void GenNormalMapTexture(unsigned int* texture1, int Size, int shape )
{

	glDeleteTextures(1, texture1);
	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);


	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);

	UseShader(GenNormalMapShader);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	int i = 0;
	if (shape == ROUND)
		i = 0;
	else if (shape == SQUERE)
		i = 1;
	else if (shape == SMOOTH_EDGE)
		i = 2;
	glUniform1i(glGetUniformLocation(GenNormalMapShader, "Type"), i);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);


	glDeleteFramebuffers(1, &framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->framebuffer);
}
void GenLightSphereTexture(unsigned int* texture1, int Size)
{

	glDeleteTextures(1, texture1);
	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);

	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);

	UseShader(GenLightSphereShader);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glDeleteFramebuffers(1, &framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->framebuffer);
}
void GenGradientTexture(unsigned int* texture1, glm::vec4 Color1 , glm::vec4 Color2 , int Size )
{
	glDeleteTextures(1, texture1);
	unsigned int framebuffer, texture2;

	glGenFramebuffers(1, &framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);

	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);

	UseShader(GradientGenShader);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glUniform4f(glGetUniformLocation(GradientGenShader, "Color1"), Color1.x, Color1.y, Color1.z, Color1.w);
	glUniform4f(glGetUniformLocation(GradientGenShader, "Color2"), Color2.x, Color2.y, Color2.z, Color2.w);

	glBindVertexArray(ScreenVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glDeleteFramebuffers(1, &framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, CurrentWindow->framebuffer);
}
void Texture::Load()
{
	if (texture != NULL)
		Delete();
	if (Type == 0)
		LoadTexture(FileName.c_str(), &texture);
	else if (Type == 1)
		GenNoizeTexture(&texture, Size, Noize_Layers, Noize_Frequency, ROUND);
	else if (Type == 2)
		GenNoizeTexture(&texture, Size, Noize_Layers, Noize_Frequency, SQUERE);
	else if (Type == 3)
		GenNoizeTexture(&texture, Size, Noize_Layers, Noize_Frequency, SMOOTH_EDGE);
	else if (Type == 4)
		GenGradientTexture(&texture, Gradient_Color1, Gradient_Color2, Size);
	if (texture == NULL)
		std::cout << "Failed to load texture:  " << FileName.c_str() << std::endl;
}
void Texture::Delete()
{
	glDeleteTextures(1, &texture);
	texture = NULL;
}
void DrawShaderedQuad(glm::vec2 position, glm::vec2 scale, float rotation, unsigned int shaderProgram)
{
	if (shaderProgram != NULL)
	{
		float aspx = ScreenDivisorX * CameraScale.x;
		float aspy = ScreenDivisorY * CameraScale.y;

		position -= CameraPosition;
		position *= glm::vec2(aspx, aspy);
		scale *= glm::vec2(aspx, aspy);

		UseShader(shaderProgram);
		SetShader2f(&shaderProgram, "position", position);
		SetShader2f(&shaderProgram, "scale", scale);
		SetShader1f(&shaderProgram, "rotation", rotation);
		SetShader1f(&shaderProgram, "aspect", (float)HEIGHT / WIDTH);
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
}
void DrawTexturedQuad(glm::vec2 position, glm::vec2 scale, unsigned int texture, float rotation, glm::vec4 color, int Z_Index , unsigned int NormalMap , bool Additive)
{

	if (NormalMap != NULL)
		NormalMapDraw(position, scale, NormalMap, rotation, Z_Index, texture);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);


	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false


	int TQA = -1;

	for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
		if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
			TQA = i;
	if (TQA == -1)
	{
		TexturedQuadArray NewTQA;
		NewTQA.Texture = texture;
		SceneLayers[SLI].TexturedQuads.push_back(NewTQA);
		for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
			if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
				TQA = i;
	}
	SceneLayers[SLI].TexturedQuads[TQA].Quadcolors.push_back(color);
	SceneLayers[SLI].TexturedQuads[TQA].QuadPosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].TexturedQuads[TQA].QuadRotations.push_back(rotation);

}
void DrawTexturedQuad(cube c, unsigned int texture, glm::vec4 color , float rotation, int Z_Index , unsigned int NormalMap, bool Additive)
{


	glm::vec2 position = c.position;
	glm::vec2 scale = glm::vec2(c.width, c.height);

	if (NormalMap != NULL)
		NormalMapDraw(position, scale, NormalMap, rotation, Z_Index, texture);
	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);


	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false

	int TQA = -1;

	for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
		if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
			TQA = i;
	if (TQA == -1)
	{
		TexturedQuadArray NewTQA;
		NewTQA.Texture = texture;
		SceneLayers[SLI].TexturedQuads.push_back(NewTQA);
		for (int i = 0; i < SceneLayers[SLI].TexturedQuads.size(); i++)
			if (SceneLayers[SLI].TexturedQuads[i].Texture == texture)
				TQA = i;
	}
	SceneLayers[SLI].TexturedQuads[TQA].Quadcolors.push_back(color);
	SceneLayers[SLI].TexturedQuads[TQA].QuadPosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].TexturedQuads[TQA].QuadRotations.push_back(rotation);



}
void DrawFlippedTexturedQuad(glm::vec2 position, glm::vec2 scale, unsigned int texture, float rotation, glm::vec4 color, int Z_Index, unsigned int NormalMap, bool Additive)
{

	if (NormalMap != NULL)
		NormalMapDraw(position, scale, NormalMap, rotation, Z_Index, texture);

	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	position -= CameraPosition;
	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);


	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false


	int TQA = -1;

	for (int i = 0; i < SceneLayers[SLI].FlippedTexturedQuads.size(); i++)
		if (SceneLayers[SLI].FlippedTexturedQuads[i].Texture == texture)
			TQA = i;
	if (TQA == -1)
	{
		TexturedQuadArray NewTQA;
		NewTQA.Texture = texture;
		SceneLayers[SLI].FlippedTexturedQuads.push_back(NewTQA);
		for (int i = 0; i < SceneLayers[SLI].FlippedTexturedQuads.size(); i++)
			if (SceneLayers[SLI].FlippedTexturedQuads[i].Texture == texture)
				TQA = i;
	}
	SceneLayers[SLI].FlippedTexturedQuads[TQA].Quadcolors.push_back(color);
	SceneLayers[SLI].FlippedTexturedQuads[TQA].QuadPosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].FlippedTexturedQuads[TQA].QuadRotations.push_back(rotation);

}
void DrawTexturedLine(unsigned int Texture, glm::vec2 p1, glm::vec2 p2, float width, glm::vec4 color, unsigned int NormalMap, int Z_Index)
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y) * 0.5f;
	DrawTexturedQuad(midpos, glm::vec2(width, length), Texture, rotation, color, Z_Index, NormalMap);
}
void DrawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec4 color)
{

	glBindVertexArray(TriangleVAO);
	UseShader(FillTriangleShader);
	float aspx = 1.0f * ScreenDivisorX * CameraScale.x;
	float aspy = 1.0f * ScreenDivisorY * CameraScale.y;
	p1.x = (p1.x - CameraPosition.x) * aspx;
	p1.y = (p1.y - CameraPosition.y) * aspy;

	p2.x = (p2.x - CameraPosition.x) * aspx;
	p2.y = (p2.y - CameraPosition.y) * aspy;

	p3.x = (p3.x - CameraPosition.x) * aspx;
	p3.y = (p3.y - CameraPosition.y) * aspy;

	GLfloat vertices[3][2] =
	{

		{ p1.x, p1.y},
		{ p2.x, p2.y},
		{ p3.x, p3.y}
	};


	glBindBuffer(GL_ARRAY_BUFFER, TriangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUniform4f(glGetUniformLocation(FillTriangleShader, "Color"), color.x, color.y, color.z, color.w);

	glUniform2f(glGetUniformLocation(FillTriangleShader, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);



}
void DrawTexturedTriangle(
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	unsigned int texture,
	glm::vec4 color ,
	glm::vec2 texcoord1,
	glm::vec2 texcoord2,
	glm::vec2 texcoord3
)
{

	UseShader(TexturedTriangleShader);
	glBindVertexArray(TexturedTriangleVAO);
	float aspx = ScreenDivisorX * CameraScale.x;
	float aspy = ScreenDivisorY * CameraScale.y;

	p1.x = (p1.x - CameraPosition.x) * aspx;
	p1.y = (p1.y - CameraPosition.y) * aspy;

	p2.x = (p2.x - CameraPosition.x) * aspx;
	p2.y = (p2.y - CameraPosition.y) * aspy;

	p3.x = (p3.x - CameraPosition.x) * aspx;
	p3.y = (p3.y - CameraPosition.y) * aspy;

	GLfloat vertices[3][4] =
	{
		{ p1.x, p1.y,texcoord1.x,texcoord1.y},
		{ p2.x, p2.y,texcoord2.x,texcoord2.y},
		{ p3.x, p3.y,texcoord3.x,texcoord3.y}
	};


	glBindBuffer(GL_ARRAY_BUFFER, TexturedTriangleVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(TexturedTriangleShader, "Texture"), 0);

	glUniform4f(glGetUniformLocation(TexturedTriangleShader, "color"), color.x, color.y, color.z, color.w);
	glUniform2f(glGetUniformLocation(TexturedTriangleShader, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	DetachShader();


}

void Window::Draw(int Z_Index)
{
	UI_DrawFlippedTexturedQuad(Position, GetSize(), Texture,0.0f);
}