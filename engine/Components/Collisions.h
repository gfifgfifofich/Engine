#pragma once
//Object CircleToStaticQuadCollision(Object circl, Object quad)
//{
//    Object circle = circl;
//    glm::vec2 posdifference = quad.pos - circle.pos;
//
//    if (posdifference.x > quad.r)
//        posdifference.x = quad.r;
//    else if (posdifference.x < -quad.r)
//        posdifference.x = -quad.r;
//    if (posdifference.y > quad.r)
//        posdifference.y = quad.r;
//    else if (posdifference.y < -quad.r)
//        posdifference.y = -quad.r;
//
//    glm::vec2 distvec = (quad.pos - posdifference) - circle.pos;
//    float dist = distvec.x * distvec.x + distvec.y * distvec.y;
//    if (dist <= circle.r * circle.r)
//    {
//        // it's colieded
//        circle.colided = true;
//        bool plane1, plane2;// y = x, y=-x;
//        glm::vec2 relpos = circle.pos - quad.pos;
//        if (relpos.y < relpos.x)
//            plane1 = false;// under
//        else
//            plane1 = true; // above
//        if (relpos.y < -relpos.x)
//            plane2 = false;// under
//        else
//            plane2 = true; // above
//
//
//
//        if (plane1 && plane2) {
//            circle.pos.y = quad.pos.y - posdifference.y + circle.r;// +0.02f; //up 2
//            circle.pos.x = quad.pos.x - posdifference.x;
//        }
//        if (!plane1 && !plane2) {
//            circle.pos.y = quad.pos.y - posdifference.y - circle.r;// -0.02f;//down 4
//            circle.pos.x = quad.pos.x - posdifference.x;
//        }
//        if (!plane1 && plane2) {
//            circle.pos.x = quad.pos.x - posdifference.x + circle.r;// *2.0f; //right 3
//            circle.pos.y = quad.pos.y - posdifference.y;
//        }
//        if (plane1 && !plane2) {
//            circle.pos.x = quad.pos.x - posdifference.x - circle.r;// *2.0f; //left 1
//            circle.pos.y = quad.pos.y - posdifference.y;
//        }
//
//    }
//
//    circle.ACpos = circle.pos;
//    return circle;
//}