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
			switch (Type)
			{
			case 0:
				unit.addDamege(0.1);
				break;
			case 1:
				unit.addDamege(0.5);
				break;
			default:
				break;
			}
		}
	}
	return target;
}

void Bullet::draw() const
{
	switch (Type)
	{
	case 0:
		Circle(ConvertVec2ToVec2(Position), 2 * getZoom()).draw(HSV(IFF, 1, 1));
		break;
	case 1:
		Circle(ConvertVec2ToVec2(Position), 5 * getZoom()).draw(HSV(IFF, 1, 1));
		break;
	default:
		break;
	}

}


Bullet::Bullet(Turret* turret)
{
	Count = 0;

	IFF = turret->getIFF();
	Position = turret->getRealPosition();
	Angle = turret->getTargetAngle();
	Type = turret->getType();

	//追跡システム
	serchEnemyUnit();

}
Vec2 Bullet::getPosition()
{
	return Position;
}

int Bullet::getType()
{
	return Type;
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