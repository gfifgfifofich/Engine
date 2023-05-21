#pragma once




// collision ball-cube, but cube's velocity/position is unchanged
void BallToStaticQuadCollision(ball* b, cube quad)
{
    float roughness = b->roughness < quad.roughness ? b->roughness : quad.roughness;
    glm::vec2 posdifference = quad.position - b->position;

    if (posdifference.x > quad.width)
        posdifference.x = quad.width;
    else if (posdifference.x < -quad.width)
        posdifference.x = -quad.width;
    if (posdifference.y > quad.height)
        posdifference.y = quad.height;
    else if (posdifference.y < -quad.height)
        posdifference.y = -quad.height;


    glm::vec2 distvec = (quad.position - posdifference) - b->position;
    float dist = distvec.x * distvec.x + distvec.y * distvec.y;

    if (quad.position - posdifference != b->position)
        BallToPointCollision(b, quad.position - posdifference,roughness);
    else
    {
        bool plane1, plane2;// y = x, y=-x;
        glm::vec2 relpos = b->position - quad.position;
        relpos.x *= quad.height / quad.width;
        if (relpos.y < relpos.x)
            plane1 = false;// under
        else
            plane1 = true; // above
        if (relpos.y < -relpos.x)
            plane2 = false;// under
        else
            plane2 = true; // above
        if (plane1 && !plane2) 
        {//left
            b->position.x = quad.position.x - quad.width;
            posdifference.x = b->position.x - b->r * 0.5f;
        }
        if (plane1 && plane2) 
        {//up 
            b->position.y = quad.position.y + quad.height;
            posdifference.y = b->position.y + b->r * 0.5f;
        }
        if (!plane1 && plane2) 
        {//right 
            b->position.x = quad.position.x + quad.width;
            posdifference.x = b->position.x + b->r * 0.5f;
        }
        if (!plane1 && !plane2) 
        {//down 
            b->position.y = quad.position.y - quad.height;
            posdifference.y = b->position.y - b->r * 0.5f;
        }
        BallToPointCollision(b, quad.position - posdifference, roughness);
    }

}

int BtCCollisionCheckSides(ball b, cube c)
{


    glm::vec2 posdifference = c.position - b.position;

    if (posdifference.x > c.width)
        posdifference.x = c.width;
    else if (posdifference.x < -c.width)
        posdifference.x = -c.width;

    if (posdifference.y > c.height)
        posdifference.y = c.height;
    else if (posdifference.y < -c.height)
        posdifference.y = -c.height;

    glm::vec2 distvec = (c.position - posdifference) - b.position;
    float dist = distvec.x * distvec.x + distvec.y * distvec.y;
    if (dist < b.r * b.r)
    {
        bool plane1, plane2;// y = x, y=-x;
        glm::vec2 relpos = b.position - c.position;
        relpos.y /= c.height;
        relpos.x /= c.width;
        if (relpos.y < relpos.x)
            plane1 = false;// under y=x
        else
            plane1 = true; // above y=x
        if (relpos.y < -relpos.x)
            plane2 = false;// under y=-x
        else
            plane2 = true; // above y=-x

        if (plane1 && plane2) {
            return 1;//up 0
        }
        else if (!plane1 && plane2) {
            return 2;//right 1
        }
        else if (!plane1 && !plane2) {
            return 3;//down 2
        }
        else if (plane1 && !plane2) {
            return 4;//left 3
        }
        else return 0;
    }
}
bool BtCCollisionCheck(ball b, cube c)
{


    glm::vec2 posdifference = c.position - b.position;

    if (posdifference.x > c.width)
        posdifference.x = c.width;
    else if (posdifference.x < -c.width)
        posdifference.x = -c.width;

    if (posdifference.y > c.height)
        posdifference.y = c.height;
    else if (posdifference.y < -c.height)
        posdifference.y = -c.height;

    glm::vec2 distvec = (c.position - posdifference) - b.position;
    float dist = distvec.x * distvec.x + distvec.y * distvec.y;
    if (dist < b.r * b.r)
        return true;
        return false;
}

