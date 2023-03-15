#pragma once
void Strut(ball* a, ball* b, float StrutLength, bool Draw = false)
{
	glm::vec2 posdif = b->position - a->position;

	glm::vec2 norm = Normalize(posdif);

	glm::vec2 Difference = posdif - norm * StrutLength;



	a->position += Difference * 0.5f;
	b->position += -Difference * 0.5f;

	glm::vec2  velbuf = a->velocity;

	a->velocity -= DOT(a->velocity - b->velocity, norm) * norm * 0.5f;
	b->velocity -= DOT(b->velocity - velbuf, norm) * norm * 0.5f;

	if (Draw)
		DrawLine(a->position, b->position, (a->r + b->r) * 0.5f);
}
