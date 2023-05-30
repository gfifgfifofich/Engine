#pragma once
//
//void BoxToBoxCollision(box* b1, box* b2)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		bool bob[4];
//
//
//		float len;
//		glm::vec2 norm;
//		glm::ivec2 NearestLine;
//
//
//
//		for (int a = 0; a < 4; a++)
//		{
//			glm::vec2 d;
//			if (a != 0) d = b2->balls[a].position - b2->balls[a - 1].position;
//			else d = b2->balls[a].position - b2->balls[3].position;
//			glm::vec2 normal = glm::vec2(-d.y, d.x) / length(d);
//			float ln = DOT(b1->balls[i].position - b2->balls[a].position, normal);
//
//			if (a == 0 || ln > len)
//			{
//				len = ln;
//				norm = normal;
//				if (a != 0) NearestLine = glm::ivec2(a, a - 1);
//				else NearestLine = NearestLine = glm::ivec2(a, 3);
//			}
//			bob[a] = ln <= 0.0f;
//		}
//
//
//
//		if (bob[3] && bob[2] && bob[1] && bob[0]) // point b1.balls[i] colided
//		{
//
//
//
//			b1->colided = true;
//			b2->colided = true;
//			glm::vec2 dif = glm::vec2(0.0f);
//			glm::vec2 PointOnLine = b2->balls[NearestLine.x].position - (b1->balls[i].position - len * norm);
//
//			float stage = 0.0f;
//
//			if (abs(PointOnLine.x) > abs(PointOnLine.y))
//			{
//				float X = b2->balls[NearestLine.x].position.x - b2->balls[NearestLine.y].position.x;
//				stage = PointOnLine.x / X;
//			}
//			else
//			{
//				float Y = b2->balls[NearestLine.x].position.y - b2->balls[NearestLine.y].position.y;
//				stage = PointOnLine.y / Y;
//			}
//			float stage2 = stage;
//			stage = (1.0f - stage);
//
//			dif = b1->balls[i].position;
//			//DrawCircle(PointOnLine, 10,glm::vec4(1.0f,0.0f,0.0f,1.0f));
//
//
//		// all the normals
//			glm::vec2 n2 = norm;
//			glm::vec2 n1 = -n2;
//			glm::vec2 CollisionLine = glm::vec2(-n1.y, n1.x);
//
//
//			glm::vec2 velocity1 = DOT(b1->balls[i].velocity, CollisionLine) * CollisionLine;
//			glm::vec2 velocity2 = DOT(b2->balls[NearestLine.x].velocity, CollisionLine) * CollisionLine;
//			glm::vec2 velocity3 = DOT(b2->balls[NearestLine.y].velocity, CollisionLine) * CollisionLine;
//
//			float energy1 = DOT(b1->balls[i].velocity, n1);
//			float energy2 = DOT(b2->balls[NearestLine.x].velocity, n2);
//			float energy3 = DOT(b2->balls[NearestLine.y].velocity, n2);
//
//
//			glm::vec2 a = n1 * energy2 * stage + n1 * energy3 * stage2;
//			glm::vec2 b = n2 * energy1 * stage;
//			glm::vec2 c = n2 * energy1 * stage2;
//
//			velocity1 -= a;
//			velocity2 -= b;
//			velocity3 -= c;
//
//			//positions
//			b1->position += n1 * (len * 0.5f);
//
//			b1->balls[i].velocity = velocity1;
//
//
//			b2->balls[NearestLine.x].position += n2 * len * stage;
//			b2->balls[NearestLine.y].position += n2 * len * stage2;
//
//			b2->balls[NearestLine.x].velocity = velocity2;
//			b2->balls[NearestLine.y].velocity = velocity3;
//		};
//	}
//	for (int i = 0; i < 4; i++)
//	{
//		bool bob[4];
//
//
//		float len;
//		glm::vec2 norm;
//		glm::ivec2 NearestLine;
//
//
//
//		for (int a = 0; a < 4; a++)
//		{
//			glm::vec2 d;
//			if (a != 0) d = b1->balls[a].position - b1->balls[a - 1].position;
//			else d = b1->balls[a].position - b1->balls[3].position;
//			glm::vec2 normal = glm::vec2(-d.y, d.x) / length(d);
//			float ln = DOT(b2->balls[i].position - b1->balls[a].position, normal);
//
//			if (a == 0 || ln > len)
//			{
//				len = ln;
//				norm = normal;
//				if (a != 0) NearestLine = glm::ivec2(a, a - 1);
//				else NearestLine = NearestLine = glm::ivec2(a, 3);
//			}
//			bob[a] = ln <= 0.0f;
//		}
//
//
//
//		if (bob[3] && bob[2] && bob[1] && bob[0]) // point b1.balls[i] colided
//		{
//
//
//
//			b2->colided = true;
//			b1->colided = true;
//			glm::vec2 dif = glm::vec2(0.0f);
//			glm::vec2 PointOnLine = b1->balls[NearestLine.x].position - (b2->balls[i].position - len * norm);
//
//			float stage = 0.0f;
//
//			if (abs(PointOnLine.x) > abs(PointOnLine.y))
//			{
//				float X = b1->balls[NearestLine.x].position.x - b1->balls[NearestLine.y].position.x;
//				stage = PointOnLine.x / X;
//			}
//			else
//			{
//				float Y = b1->balls[NearestLine.x].position.y - b1->balls[NearestLine.y].position.y;
//				stage = PointOnLine.y / Y;
//			}
//			float stage2 = stage;
//			stage = (1.0f - stage);
//
//			dif = b2->balls[i].position;
//			//DrawCircle(PointOnLine, 10,glm::vec4(1.0f,0.0f,0.0f,1.0f));
//
//
//		// all the normals
//			glm::vec2 n2 = norm;
//			glm::vec2 n1 = -n2;
//			glm::vec2 CollisionLine = glm::vec2(-n1.y, n1.x);
//
//
//			glm::vec2 velocity1 = DOT(b2->balls[i].velocity, CollisionLine) * CollisionLine;
//			glm::vec2 velocity2 = DOT(b1->balls[NearestLine.x].velocity, CollisionLine) * CollisionLine;
//			glm::vec2 velocity3 = DOT(b1->balls[NearestLine.y].velocity, CollisionLine) * CollisionLine;
//
//			float energy1 = DOT(b2->balls[i].velocity, n1);
//			float energy2 = DOT(b1->balls[NearestLine.x].velocity, n2);
//			float energy3 = DOT(b1->balls[NearestLine.y].velocity, n2);
//
//
//			glm::vec2 a = n1 * energy2 * stage + n1 * energy3 * stage2;
//			glm::vec2 b = n2 * energy1 * stage;
//			glm::vec2 c = n2 * energy1 * stage2;
//
//			velocity1 -= a;
//			velocity2 -= b;
//			velocity3 -= c;
//
//			//positions
//			b2->position += n1 * (len * 0.5f);
//
//			b2->balls[i].velocity = velocity1;
//
//
//			b1->balls[NearestLine.x].position += n2 * len * stage;
//			b1->balls[NearestLine.y].position += n2 * len * stage2;
//
//			b1->balls[NearestLine.x].velocity = velocity2;
//			b1->balls[NearestLine.y].velocity = velocity3;
//		};
//	}
//}