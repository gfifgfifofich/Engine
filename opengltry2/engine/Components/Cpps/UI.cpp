
#include "../Include/Helper.h"
#include "../Include/Drawing.h"
#include "../Include/Text.h"
#include "../Include/Objects.h"
#include "../Include/UI.h"

//void UI_NormalMapDraw(position, scale, NormalMap, rotation, Z_Index, texture);


void UI_NormalMapDraw(glm::vec2 position, glm::vec2 scale, unsigned int NormalMap, float rotation, int Z_Index, unsigned int Texture, bool Additive)
{
	if (NormalMap != BallNormalMapTexture && NormalMap != CubeNormalMapTexture)
	{

		int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false
		float aspx = ScreenDivisorX;
		float aspy = ScreenDivisorY;

		position *= glm::vec2(aspx, aspy);
		scale *= glm::vec2(aspx, aspy);


		int TQA = -1;

		for (int i = 0; i < SceneLayers[SLI].NormalMaps.size(); i++)
			if (SceneLayers[SLI].NormalMaps[i].Texture == NormalMap && SceneLayers[SLI].NormalMaps[i].Texture2 == Texture)
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
		float aspx = ScreenDivisorX;
		float aspy = ScreenDivisorY;

		position *= glm::vec2(aspx, aspy);
		scale *= glm::vec2(aspx, aspy);



		int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false

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
void UI_DrawTexturedQuad(glm::vec2 position, glm::vec2 scale, unsigned int texture, float rotation, glm::vec4 color, int Z_Index, unsigned int NormalMap, bool Additive)
{

	if (NormalMap != NULL)
		UI_NormalMapDraw(position, scale, NormalMap, rotation, Z_Index, texture);

	float aspx = ScreenDivisorX;
	float aspy = ScreenDivisorY;

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
void UI_DrawTexturedQuad(cube c, unsigned int texture, glm::vec4 color, float rotation, int Z_Index, unsigned int NormalMap, bool Additive)
{


	glm::vec2 position = c.position;
	glm::vec2 scale = glm::vec2(c.width, c.height);

	if (NormalMap != NULL)
		UI_NormalMapDraw(position, scale, NormalMap, rotation, Z_Index, texture);
	float aspx = ScreenDivisorX;
	float aspy = ScreenDivisorY;

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
void UI_DrawFlippedTexturedQuad(glm::vec2 position, glm::vec2 scale, unsigned int texture, float rotation, glm::vec4 color, int Z_Index, unsigned int NormalMap, bool Additive)
{
	if (NormalMap != NULL)
		NormalMapDraw(position, scale, NormalMap, rotation, Z_Index, texture);
	float aspx = ScreenDivisorX;
	float aspy = ScreenDivisorY;

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
void UI_DrawTexturedLine(unsigned int Texture, glm::vec2 p1, glm::vec2 p2, float width, glm::vec4 color, unsigned int NormalMap, int Z_Index)
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y) * 0.5f;
	UI_DrawTexturedQuad(midpos, glm::vec2(width, length), Texture, rotation, color, Z_Index, NormalMap);
}
void UI_DrawCircle(glm::vec2 position, float r, glm::vec4 color, bool Lighted, unsigned int NormalMap, int Z_Index, bool Additive)
{
	glm::vec2 scale = glm::vec2(r, r);

	if (Lighted)
		UI_NormalMapDraw(position, scale, NormalMap, 0.0f, Z_Index);

	float aspx = ScreenDivisorX;
	float aspy = ScreenDivisorY;

	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);



	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false

	SceneLayers[SLI].CirclePosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].CircleRotations.push_back(0.0f);
	SceneLayers[SLI].Circlecolors.push_back(color);

}
void UI_DrawCircle(ball b, glm::vec4 color, bool Lighted, unsigned int NormalMap, int Z_Index, bool Additive)
{

	glm::vec2 position = b.position;
	float r = b.r;
	glm::vec2 scale = glm::vec2(r, r);
	if (Lighted)
		UI_NormalMapDraw(position, scale, NormalMap, 0.0f, Z_Index);

	float aspx = ScreenDivisorX;
	float aspy = ScreenDivisorY;

	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);

	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false


	SceneLayers[SLI].CirclePosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].CircleRotations.push_back(0.0f);
	SceneLayers[SLI].Circlecolors.push_back(color);
}
void UI_DrawCube(glm::vec2 position, glm::vec2 scale, float rotation, glm::vec4 color, bool Lighted, unsigned int NormalMap, int Z_Index, bool Additive)
{


	if (Lighted)
		UI_NormalMapDraw(position, scale, NormalMap, rotation, Z_Index);

	float aspx = ScreenDivisorX;
	float aspy = ScreenDivisorY;

	position *= glm::vec2(aspx, aspy);
	scale *= glm::vec2(aspx, aspy);




	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false

	SceneLayers[SLI].QuadPosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].QuadRotations.push_back(rotation);

	SceneLayers[SLI].Quadcolors.push_back(color);


}
void UI_DrawCube(cube c, glm::vec4 color, float rotation, bool Lighted, unsigned int NormalMap, int Z_Index, bool Additive)
{


	if (Lighted)
		UI_NormalMapDraw(c.position, glm::vec2(c.width, c.height), NormalMap, rotation, Z_Index);

	float aspx = ScreenDivisorX;
	float aspy = ScreenDivisorY;

	glm::vec2 position = c.position;
	position *= glm::vec2(aspx, aspy);
	glm::vec2 scale = glm::vec2(c.width, c.height) * glm::vec2(aspx, aspy);

	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false

	SceneLayers[SLI].QuadPosScale.push_back(glm::vec4(position, scale));
	SceneLayers[SLI].QuadRotations.push_back(rotation);

	SceneLayers[SLI].Quadcolors.push_back(color);
}
void UI_DrawLine(glm::vec2 p1, glm::vec2 p2, float width, glm::vec4 color, bool Lighted, unsigned int NormalMap, int Z_Index)
{
	glm::vec2 midpos = (p2 + p1) / 2.0f;
	float rotation = get_angle_between_points(p1, p2);
	glm::vec2 dif = p1 - p2;
	float length = sqrt(dif.x * dif.x + dif.y * dif.y) * 0.5f;
	UI_DrawCube(midpos, glm::vec2(width, length), rotation, color, Lighted, NormalMap, Z_Index);
}
void UI_DrawBall(ball b, glm::vec4 Color1, glm::vec4 Color2, bool Lighted, unsigned int NormalMap, int Z_Index)
{

	glm::vec2 univec;
	univec.x = cos(b.rotation * 5) - sin(b.rotation * 5);
	univec.y = sin(b.rotation * 5) + cos(b.rotation * 5);
	UI_DrawLine(b.position - univec * b.r * 0.7f, b.position + univec * b.r * 0.7f, 3.0f, Color2, Lighted, CubeNormalMapTexture, Z_Index);
	UI_DrawLine(b.position + glm::vec2(-univec.y * b.r * 0.7f, univec.x * b.r * 0.7f), b.position + glm::vec2(univec.y * b.r * 0.7f, -univec.x * b.r * 0.7f), 3.0f, Color2, Lighted, CubeNormalMapTexture, Z_Index);
	UI_DrawCircle(b, Color1, Lighted, NormalMap, Z_Index - 1);
}
void _UI_DrawText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color)
{
	//glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(
		(position.x) * ScreenDivisorX,
		(position.y) * ScreenDivisorY,
		0.0f));


	trans = glm::scale(trans, glm::vec3(ScaleMultiplyer, ScaleMultiplyer, 0.0f));



	// Activate corresponding render state
	UseShader(TextShader);
	glUniform4f(glGetUniformLocation(TextShader, "color"), color.x, color.y, color.z, color.w);
	glUniformMatrix4fv(glGetUniformLocation(TextShader, "transform"), 1, GL_FALSE, glm::value_ptr(trans));

	glUniform2f(glGetUniformLocation(TextShader, "scr"), (float)WIDTH, (float)HEIGHT);
	glUniform1i(glGetUniformLocation(TextShader, "flipY"), true);


	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(TextVAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = (x)+ch.Bearing.x * scale;
		GLfloat ypos = (y)-(ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },

			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, TextVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}
void UI_DrawText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color, int Z_Index, bool Additive)
{
	TextLine txtline;

	txtline.text = text;
	txtline.x = x;
	txtline.y = y;
	txtline.scale = scale;
	txtline.color = color;
	txtline.aboveEverything = false;
	int SLI = FindSceneLayer(Z_Index, Additive);// ,bool Additive =false

	SceneLayers[SLI].UI_TextLines.push_back(txtline);

	
}
void UI_DrawText(std::string text, glm::vec2 position, GLfloat scale, glm::vec4 color, int Z_Index, bool Additive)
{
	UI_DrawText(text, position.x, position.y, scale, color, Z_Index, Additive);
}
void UI_DrawTextOnPlate(std::string text, glm::vec2 position, GLfloat scale, glm::vec4 color, glm::vec4 platecolor, int Z_Index, bool Additive)
{
	UI_DrawText(text, position.x, position.y, scale, color, Z_Index, Additive);

	glm::vec2 scl = getTextSize(text, scale);
	UI_DrawCube(position + scl * 0.50f, scl * 0.6f, 0.0f, platecolor,false,NULL, Z_Index -1, Additive);
}
bool UI_CheckBox(bool* param, const char* text, glm::vec2 scrPosition, float scale, float textScale , glm::vec4 colorON , glm::vec4 ColorOFF, int Z_Index , bool Additive )
{



	float r = scale  * 1.25;
	if (sqrlength(ScreenMousePosition - scrPosition) <= r * r)
	{
		scale *= 1.1f;
		if (JustReleasedbutton[GLFW_MOUSE_BUTTON_1])
			*param = !*param;
	}
	float TextScale = textScale;
	glm::vec2 textOffset = glm::vec2(30.0f , -20.0f  * TextScale);




	if (*param)
	{
		UI_DrawCube(scrPosition, { scale , scale }, pi * 0.25f, colorON, false, 0, Z_Index, Additive);
		UI_DrawText(text, scrPosition + textOffset, TextScale, colorON, Z_Index, Additive);
	}
	else
	{
		UI_DrawCube(scrPosition, { scale , scale }, pi * 0.25f, ColorOFF, false, 0, Z_Index, Additive);
		UI_DrawText(text, scrPosition + textOffset, TextScale , ColorOFF, Z_Index, Additive);
	}



	return param;
}
bool UI_buttonOnlyON(bool* param, const char* text, glm::vec2 scrPosition, float scale , float textScale , glm::vec4 colorON , glm::vec4 ColorOFF, int Z_Index , bool Additive )
{



	float r = scale  * 1.25;
	if (sqrlength(ScreenMousePosition - scrPosition) <= r * r)
	{
		scale *= 1.1f;
		if (JustReleasedbutton[GLFW_MOUSE_BUTTON_1])
			*param = true;
	}
	float TextScale = textScale;
	glm::vec2 textOffset = glm::vec2(30.0f , -20.0f * TextScale);




	if (*param)
	{
		UI_DrawCube(scrPosition, { scale , scale }, pi * 0.25f, colorON, false, 0, Z_Index, Additive);
		UI_DrawText(text, scrPosition + textOffset, TextScale, colorON, Z_Index, Additive);
	}
	else
	{
		UI_DrawCube(scrPosition, { scale , scale }, pi * 0.25f, ColorOFF, false, 0, Z_Index, Additive);
		UI_DrawText(text, scrPosition + textOffset, TextScale , ColorOFF, Z_Index, Additive);
	}



	return param;
}
void UI_InputText(bool* edit, int maxTextSize, std::string* text, glm::vec2 scrPosition, float scale, float textScale , glm::vec4 colorON , glm::vec4 ColorOFF, int Z_Index , bool Additive)
{



	float r = scale  * 1.25;
	if (sqrlength(ScreenMousePosition - scrPosition) <= r * r)
	{
		scale *= 1.1f;
		if (JustReleasedbutton[GLFW_MOUSE_BUTTON_1])
			*edit = !*edit;
	}
	float TextScale = textScale;
	glm::vec2 textOffset = glm::vec2(30.0f  -20.0f * TextScale);



	TextEditMode = *edit;

	if (*edit)
	{

		if (JustPressedkey[GLFW_KEY_BACKSPACE] && text->size() > 0)
			text->pop_back();
		else if (TextFromKeyboard.size() > 0 && (TextFromKeyboard.size() + text->size() <= maxTextSize || maxTextSize < 0))
			*text += TextFromKeyboard;
		if (JustPressedkey[GLFW_KEY_ENTER] || JustPressedkey[GLFW_KEY_ESCAPE])
			*edit = false;

		UI_DrawCube(scrPosition, { scale , scale }, pi * 0.25f, colorON, NULL , Z_Index, Additive);
		UI_DrawText(*text, scrPosition + textOffset, TextScale, colorON, Z_Index, Additive);
	}
	else
	{
		UI_DrawCube(scrPosition, { scale , scale  }, pi * 0.25f, ColorOFF , NULL, Z_Index, Additive);
		UI_DrawText(*text, scrPosition + textOffset, TextScale , ColorOFF, Z_Index, Additive);
	}
}
