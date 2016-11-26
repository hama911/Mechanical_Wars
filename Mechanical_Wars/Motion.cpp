#include"Motion.h"
#include"Graphics.h"

bool Motion::update()
{
	++Count;
	return Count > 20;
}

void Motion::draw() const
{
	switch (Type)
	{
	case 0:
		Circle(ConvertVec2ToVec2(Position), Count / 4 + 2 * getZoom()).draw(Color(255, 128, 0, 240 - Count * 12));
		break;
	case 1:
		Circle(ConvertVec2ToVec2(Position), Count + 8 * getZoom()).draw(Color(255, 128, 0, 240 - Count * 12));
		break;
	default:
		break;
	}
}

Motion::Motion(Bullet* bullet)
{
	Count = 0;
	Position = bullet->getPosition();
	Type = bullet->getType();
}

Motion::~Motion()
{
}