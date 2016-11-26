#include"Bullet.h"
#include"Unit.h"
#include"Motion.h"
#include"Graphics.h"

extern Array<Unit> units;
extern Array<Motion> motions;

void Bullet::update()
{
	if (Enabled)
	{
		--Count;
		Position.moveBy(Angle*SpeedPerformance);
		if (Count+60 <= Random(60))
		{
			Enabled = false;
			motions.push_back(Motion(this));
		}

		if (hitCheck())
		{
			Enabled = false;
			motions.push_back(Motion(this));
		}

	}
}

Unit* Bullet::hitCheck()
{
	Unit* target = NULL;
	for (auto& unit : units)
	{
		if (unit.getEnabled() && IFF != unit.getIFF() && unit.hitCheck(Position))
		{
			target = &unit;
			switch (Type)
			{
			case 0:
				unit.addDamege(0.2);
				break;
			case 1:
				unit.addDamege(10.0);
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
	if (Enabled)
	{
		drawBullet();
	}
}


Bullet::Bullet(Turret* turret)
{
	Count = turret->getCount();
	Enabled = true;
	IFF = turret->getBaseUnit()->getIFF();
	Position = turret->getRealPosition();
	Angle = turret->getTargetAngle();
	Type = turret->getType();
	setBulletData();
	//追跡システム
	//serchEnemyUnit();

}
Vec2 Bullet::getPosition() const
{
	return Position;
}

int Bullet::getType() const
{
	return Type;
}

bool Bullet::getEnabled() const
{
	return Enabled;
}

Unit* Bullet::serchEnemyUnit()
{

	double length = 300.0;	//索敵可能距離
	Unit* target = NULL;	//ターゲット
	for (auto& unit : units)
	{
		if (unit.getEnabled() && IFF != unit.getIFF() && Position.distanceFrom(unit.getPosition()) < length)
		{
			length = Position.distanceFrom(unit.getPosition());
			target = &unit;
		}
	}
	if (target != NULL)
	{
		Angle = (target->getPosition() + target->getAngle()*target->getSpeedPerformance()*((target->getPosition().distanceFrom(Position) / (Angle*SpeedPerformance - target->getAngle()*target->getSpeedPerformance()).length())) - Position).normalized();

	}
	return target;
}

Bullet::~Bullet()
{
}

void Bullet::setCount(int count)
{
	Count = count;
}