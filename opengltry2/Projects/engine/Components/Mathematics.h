#pragma once



glm::vec2 Normalize(glm::vec2 a)
{
    float length = sqrt(a.x * a.x + a.y * a.y);
    return a / length;
}

float length(glm::vec2 a)
{
    float length = sqrt(a.x * a.x + a.y * a.y);
    return length;
}
float sqrlength(glm::vec2 a)
{
    float length = a.x * a.x + a.y * a.y;
    return length;
}


float DOT(glm::vec2 v1, glm::vec2 v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

glm::vec2 NormalizeSquered(glm::vec2 a)
{
    // Fast, not preciese at all
    int negative[2];
    negative[0] = -std::signbit(a.x) * 2 + 1;
    negative[1] = -std::signbit(a.y) * 2 + 1;
    float sqrlen = a.x * a.x + a.y * a.y;
    return glm::vec2((a.x * a.x) / sqrlen * negative[0], (a.y * a.y) / sqrlen * negative[1]);

}

GLfloat get_angle_between_points(glm::vec2 vec1, glm::vec2 vec2)
{
    glm::vec2 vec3 = vec1 - vec2;
    GLfloat tan = vec3.y / vec3.x;
    return atan(tan);
}



glm::vec2 GetNormal(glm::vec2 a)// i'm stupid, so this function rotates vec 'a' by 90 degrees lol
{
    return Normalize(glm::vec2(-a.y, a.x));
}

glm::mat3x3 CreateTransformMat3x3(glm::vec2 position, glm::vec2 scale, float rotation)
{

    float cosPhi = cos(rotation);
    float sinPhi = sin(rotation);


    return glm::mat3x3{ cosPhi * scale.x,	-sinPhi * scale.y,  cosPhi * position.x - sinPhi * position.y,
                        sinPhi * scale.x, 	cosPhi * scale.y,     cosPhi * position.y + sinPhi * position.x,
                        0.0f,						0.0f,		1.0f };
}
float LinearInterpolation(float a0, float a1, float w) {
    return (a1 - a0) * w + a0;
}

float SmoothStep(float a0, float a1, float w) {
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

float SmootherStep(float a0, float a1, float w) {
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}


