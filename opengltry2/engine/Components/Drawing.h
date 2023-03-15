#pragma once

glm::vec2 CameraPosition = glm::vec2(0.0f);
glm::vec2 CameraScale = glm::vec2(1.0f);

//QUAD
Shader* TexturedQuadShader;
Shader* FilShader;
Shader* TexturedTriangleShader;


unsigned int quadVAO, quadVBO,
ScreenVAO, ScreenVBO,
CircleVAO, CircleVBO,
TriangleVAO, TriangleVBO,
TexturedTriangleVAO, TexturedTriangleVBO
;
std::vector <glm::mat4> Circletranslations;
std::vector <glm::vec4> Circlecolors;

float ScaleMultiplyer = 0.043545f*0.05f;

float ScreenAspectRatio = 1.0f;

float ScreenDivisorX = 1.0;
float ScreenDivisorY = 1.0;



void DrawCircle(glm::vec2 position, float r, glm::vec4 color = glm::vec4(1.0f))
{
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x ) * ScreenDivisorX * CameraScale.x,
		(position.y ) * ScreenDivisorY *CameraScale.y,
		0.0f));

	trans = glm::scale(trans, glm::vec3(r  * ScaleMultiplyer * CameraScale.x, r * ScaleMultiplyer * CameraScale.y, 0.0f));


	Circletranslations.push_back(trans);
	Circlecolors.push_back(color);
}
void DrawCircle(ball b, glm::vec4 color = glm::vec4(1.0f))
{
	glm::vec2 position = b.position;
	float r = b.r;
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3((position.x) * ScreenDivisorX * CameraScale.x, (position.y) * ScreenDivisorY * CameraScale.y, 0.0f));

	trans = glm::scale(trans, glm::vec3(r * ScaleMultiplyer * CameraScale.x, r * ScaleMultiplyer * CameraScale.y, 0.0f));


	Circletranslations.push_back(trans);
	Circlecolors.push_back(color);
}

std::vector <glm::mat4> Quadtranslations;
std::vector <glm::vec4> Quadcolors;
void DrawCube(glm::vec2 position, glm::vec2 scale, glm::vec3 rotation = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f))
{
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f),glm::vec3(
		(position.x) * ScreenDivisorX * CameraScale.x,
		(position.y) * ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x* CameraScale.x * ScaleMultiplyer, scale.y* CameraScale.y * ScaleMultiplyer, 0.0f));


	Quadtranslations.push_back(trans);
	Quadcolors.push_back(color);


}
void DrawCube(cube c, glm::vec4 color = glm::vec4(1.0f),glm::vec3 rotation=glm::vec3(0.0f))
{
	glm::vec2 position = c.position;
	position -= CameraPosition;
	glm::vec2 scale = glm::vec2(c.width, c.height);

	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x) * ScreenDivisorX * CameraScale.x,
		(position.y) * ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x * CameraScale.x * ScaleMultiplyer, scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));

		
	Quadtranslations.push_back(trans);
	Quadcolors.push_back(color);
}


void DrawLine(glm::vec2 p1, glm::vec2 p2, float width = 1.0f, glm::vec4 color = glm::vec4(1.0f))
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y)*0.5f;
	DrawCube(midpos, glm::vec2(length  , width), glm::vec3(0.0f, 0.0f, rotation), color);
}

void DrawBall(ball b, glm::vec4 Color1 = glm::vec4(1.0f), glm::vec4 Color2 = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
{
	glm::vec2 univec;
	univec.x = cos(b.rotation * 5) - sin(b.rotation * 5);
	univec.y = sin(b.rotation * 5) + cos(b.rotation * 5);
	DrawLine(b.position - univec * b.r * 0.7f, b.position + univec * b.r * 0.7f, 3.0f, Color2);
	DrawLine(b.position + glm::vec2(-univec.y * b.r * 0.7f, univec.x * b.r * 0.7f), b.position + glm::vec2(univec.y * b.r * 0.7f, -univec.x * b.r * 0.7f), 3.0f, Color2);
	DrawCircle(b, Color1);
}



// will load texture from filename, to texture 
void LoadTexture(const char* filename,unsigned int* texture,int chanelsAmount = 4)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
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
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(Texture);
	glBindTexture(GL_TEXTURE_2D, 0);

}

Shader* NoizeGenShaderptr;
Shader* BlurShaderPtr;
Shader* RoundShaderptr;


enum
{
	SQUERE = 0,
	SMOOTH_EDGE = 1,
	ROUND = 2
};
void GenNoizeTexture(unsigned int* texture1,int Size, int Layers =3,float freq = 10, int shape = ROUND)
{

	glDeleteTextures(1, texture1);
	unsigned int framebuffer[2], texture2;

	glGenFramebuffers(2, framebuffer);
	glGenTextures(1, &texture2);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[0]);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture2, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[1]);
	glBindTexture(GL_TEXTURE_2D, *texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Size, Size, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texture1, 0);

	bool even = false;
	glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, Size, Size);

	glm::vec2 rngoffset = glm::vec2(rand(), rand());

	for (int i = 0; i < Layers; i++)
	{
		NoizeGenShaderptr->Use();

		float weight = 1.0f / (i + 1);
		// add new layer (higher freq, less wieght)
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[even]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, even ? *texture1 : texture2);
		glUniform1i(glGetUniformLocation(NoizeGenShaderptr->Program, "PrevTexture"), 0);

		glUniform1f(glGetUniformLocation(NoizeGenShaderptr->Program, "sizex"), (i + 1) * freq);
		glUniform1f(glGetUniformLocation(NoizeGenShaderptr->Program, "sizey"), (i + 1) * freq);
		glUniform1f(glGetUniformLocation(NoizeGenShaderptr->Program, "weight"), weight);

		glUniform1i(glGetUniformLocation(NoizeGenShaderptr->Program, "shape"), shape);

		glUniform2f(glGetUniformLocation(NoizeGenShaderptr->Program, "offset"), rngoffset.x, rngoffset.y);

		glBindVertexArray(ScreenVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		even = !even;
		
	}
	glDeleteFramebuffers(2, framebuffer);

	*texture1 = texture2;

	glViewport(0, 0, WIDTH, HEIGHT);

	if (HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}






void DrawTexturedQuad(glm::vec2 position, glm::vec2 scale, unsigned int texture, glm::vec3 rotation = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f))
{
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x) * ScreenDivisorX * CameraScale.x,
		(position.y) * ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x * CameraScale.x * ScaleMultiplyer, scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));

	TexturedQuadShader->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(TexturedQuadShader->Program, "Texture"), 0);


	glUniform4f(glGetUniformLocation(TexturedQuadShader->Program, "color"), color.x, color.y, color.z, color.w);
	glUniform2f(glGetUniformLocation(TexturedQuadShader->Program, "scr"), WIDTH, HEIGHT);
	glUniformMatrix4fv(glGetUniformLocation(TexturedQuadShader->Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
	
	
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void DrawTexturedQuad(cube c, unsigned int texture, glm::vec4 color = glm::vec4(1.0f), glm::vec3 rotation = glm::vec3(0.0f))
{
	glm::vec2 position = c.position;
	glm::vec2 scale = glm::vec2(c.width, c.height);
	position -= CameraPosition;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x) / ScreenDivisorX * CameraScale.x,
		(position.y) / ScreenDivisorY * CameraScale.y,
		0.0f));


	if (rotation.z != 0)
		trans = glm::rotate(trans, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	if (rotation.y != 0)
		trans = glm::rotate(trans, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	if (rotation.x != 0)
		trans = glm::rotate(trans, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(scale.x * CameraScale.x * ScaleMultiplyer, scale.y * CameraScale.y * ScaleMultiplyer, 0.0f));

	TexturedQuadShader->Use();

	glBindTexture(GL_TEXTURE_2D, texture);

	glUniform4f(glGetUniformLocation(TexturedQuadShader->Program, "color"), color.x, color.y, color.z, color.w);
	glUniform2f(glGetUniformLocation(TexturedQuadShader->Program, "scr"), WIDTH, HEIGHT);
	glUniformMatrix4fv(glGetUniformLocation(TexturedQuadShader->Program, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

	
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void DrawTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec4 color = glm::vec4(1.0f))
{
	FilShader->Use();
	glBindVertexArray(TriangleVAO);
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

	glUniform4f(glGetUniformLocation(FilShader->Program, "Color"), color.x, color.y, color.z, color.w);

	glUniform2f(glGetUniformLocation(FilShader->Program, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);



}
void DrawTexturedTriangle(
	glm::vec2 p1,
	glm::vec2 p2,
	glm::vec2 p3,
	unsigned int texture,
	glm::vec4 color = glm::vec4(1.0f),
	glm::vec2 texcoord1 = glm::vec2(0.0f,1.0f),
	glm::vec2 texcoord2 = glm::vec2(0.5f, 0.0f),
	glm::vec2 texcoord3 = glm::vec2(1.0f, 1.0f)
	)
{
	TexturedTriangleShader->Use();
	glBindVertexArray(TexturedTriangleVAO);
	float aspx = 1.0f * ScreenDivisorX * CameraScale.x;
	float aspy = 1.0f * ScreenDivisorY * CameraScale.y;

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
	glUniform1i(glGetUniformLocation(TexturedTriangleShader->Program, "Texture"),0);
	
	glUniform4f(glGetUniformLocation(TexturedTriangleShader->Program, "color"), color.x, color.y, color.z, color.w);
	glUniform2f(glGetUniformLocation(TexturedTriangleShader->Program, "scr"), WIDTH, HEIGHT);


	glDrawArrays(GL_TRIANGLES, 0, 3);


}
