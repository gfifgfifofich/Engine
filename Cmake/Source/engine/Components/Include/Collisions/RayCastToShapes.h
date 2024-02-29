#pragma once
#include "../Objects.h"
#include "BallToBall.h"
#include "BallToLine.h"
#include "BallToPolygon.h"
#include "CircleToQuad.h"
glm::vec2 CastRayToQuad(Ray* r, cube c);
glm::vec2 CastRayToBall(Ray* r, ball b);
glm::vec2 CastRayToTriangle(Ray* r, Triangle t);