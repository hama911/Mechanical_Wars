#include"Bullet.h"
#include"Unit.h"
#include"Motion.h"
#include"Graphics.h"

extern Array<Unit> units;
extern Array<Motion> motions;

bool Bullet::update()
{
	bool flag = false;
	++Count;
	Position.moveBy(Angle*5.0);
	if (Random(Count) > 100)
	{
		flag = true;
		motions.push_back(Motion(this));
	}

	if (hitCheck())
	{
		flag = true;
		motions.push_back(Motion(this));
	}

	return flag;
}

Unit* Bullet::hitCheck()
{
	Unit* target = NULL;
	for (auto& unit : units)
	{
		if (Position.distanceFrom(unit.getPosition()) < 5 && IFF != unit.getIFF())
		{
			target = &unit;
			unit.addDamege(1.0);
		}
	}
	return target;
}

void Bullet::draw() const
{
	Circle(ConvertVec2ToVec2(Position), 2 * getZoom()).draw(HSV(IFF, 1, 1));

}


Bullet::Bullet()
{
	Count = 0;

	//追跡システム
	serchEnemyUnit();

}
Vec2 Bullet::getPosition()
{
	return Position;
}

Unit* Bullet::serchEnemyUnit()
{
	double length = 300.0;	//索敵可能距離
	Unit* target = NULL;	//ターゲット
	for (auto& unit : units)
	{
		if (Position.distanceFrom(unit.getPosition()) < length && IFF != unit.getIFF())
		{
			length = Position.distanceFrom(unit.getPosition());
			target = &unit;
		}
	}
	if (target != NULL)
	{
		Angle = (target->getPosition() + target->getAngle()*target->getSpeedPerformance()*Position.distanceFrom(target->getPosition()) / 5.0 - Position).normalize();
	}
	return target;
}

Bullet::~Bullet()
{
}