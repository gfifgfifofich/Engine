#pragma once
#include "Shader.h"

#define FT_FREETYPE_H
#include <ft2build.h>
#include <freetype/freetype.h>

//Text

void LoadFont(const char* font);
void DrawText(std::string text, glm::vec2 position, GLfloat scale, glm::vec4 color = glm::vec4(1.0f), bool aboveEverything = false);
void DrawText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec4 color = glm::vec4(1.0f), bool aboveEverything = false);

