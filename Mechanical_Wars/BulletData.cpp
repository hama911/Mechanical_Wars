#include"Bullet.h"
#include"Graphics.h"

void Bullet::setBulletData()
{
	switch (Type)
	{
	case 0:
		SpeedPerformance = 3.0;
		break;
	case 1:
		SpeedPerformance = 1.0;
	case 2:
		SpeedPerformance = 3.0;
		break;
	default:
		break;
	}
}

void Bullet::drawBullet() const
{
	switch (Type)
	{
	case 0:
		Circle(ConvertVec2ToVec2(Position), 1 * getZoom()).draw(HSV(IFF, 1, 1));
		break;
	case 1:
		Circle(ConvertVec2ToVec2(Position), 2 * getZoom()).draw(HSV(IFF, 1, 1));
		break;
	case 2:
		Circle(ConvertVec2ToVec2(Position), 1 * getZoom()).draw(HSV(IFF, 1, 1));
		break;
	default:
		break;
	}
}