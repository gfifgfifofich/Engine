#pragma once



std::vector <ball*> ballsptr;
std::vector <cube> cubes;


// collision ball-cube, but cube's velocity/position is unchanged
void BallToStaticQuadCollision(ball* b, cube quad)
{
    ball circle = *b;
    glm::vec2 posdifference = quad.position - circle.position;

    if (posdifference.x > quad.width)
        posdifference.x = quad.width;
    else if (posdifference.x < -quad.width)
        posdifference.x = -quad.width;
    if (posdifference.y > quad.height)
        posdifference.y = quad.height;
    else if (posdifference.y < -quad.height)
        posdifference.y = -quad.height;

    glm::vec2 distvec = (quad.position - posdifference) - circle.position;
    float dist = distvec.x * distvec.x + distvec.y * distvec.y;
    if (dist < circle.r * circle.r)
    {
        bool plane1, plane2;// y = x, y=-x;
        glm::vec2 relpos = circle.position - quad.position;
        if (relpos.y < relpos.x)
            plane1 = false;// under
        else
            plane1 = true; // above
        if (relpos.y < -relpos.x)
            plane2 = false;// under
        else
            plane2 = true; // above



        if (plane1 && plane2) {
            circle.position.y = quad.position.y - posdifference.y + circle.r;//up 2
            circle.position.x = quad.position.x - posdifference.x;
            circle.velocity.y *= -1;
        }
        if (!plane1 && !plane2) {
            circle.position.y = quad.position.y - posdifference.y - circle.r;//down 4
            circle.position.x = quad.position.x - posdifference.x;
            circle.velocity.y *= -1;
        }
        if (!plane1 && plane2) {
            circle.position.x = quad.position.x - posdifference.x + circle.r;//right 3
            circle.position.y = quad.position.y - posdifference.y;
            circle.velocity.x *= -1;
        }
        if (plane1 && !plane2) {
            circle.position.x = quad.position.x - posdifference.x - circle.r;//left 1
            circle.position.y = quad.position.y - posdifference.y;
            circle.velocity.x *= -1;
        }

    }
    *b = circle;
}

int BtCCollisionCheck(ball b, cube c)
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
