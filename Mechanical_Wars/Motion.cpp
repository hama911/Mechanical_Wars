#include"Motion.h"
#include"Graphics.h"

void Motion::update()
{
	if (Enabled)
	{
		++Count;
		Enabled = Count < 20;
	}
}

void Motion::draw() const
{
	if (Enabled)
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
}

bool Motion::getEnabled() const
{
	return Enabled;
}

Motion::Motion(Bullet* bullet)
{
	Enabled = true;
	Count = 0;
	Position = bullet->getPosition();
	Type = bullet->getType();
}

Motion::~Motion()
{
}