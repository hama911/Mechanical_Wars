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
		if (Count < 0)
		{
			for (auto& motion : motions)
				if (motion.setFromBullet(this)) break;
			reset();
		}

		if (hitCheck())
		{
			for (auto& motion : motions)
				if (motion.setFromBullet(this)) break;
			reset();
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
				unit.addDamege(0.5);
				break;
			case 1:
				unit.addDamege(10.0);
				break;
			case 2:
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
	if (Enabled)
	{
		drawBullet();
	}
}

void Bullet::reset()
{
	Enabled = false;
	IFF = 0;
	Position = Vec2(0, 0);
	Angle = Vec2(0, 0);
	Count = 0;
	Type = 0;
	SpeedPerformance = 0;
}

bool Bullet::set(Turret* turret)
{
	if (Enabled) return false;
	Enabled = true;
	Count = turret->getCount()*1.2;
	IFF = turret->getBaseUnit()->getIFF();
	Position = turret->getRealPosition();
	Angle = turret->getTargetAngle();
	Type = turret->getType();
	setBulletData();
	//追跡システム
	//serchEnemyUnit();
	return true;
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
		Angle = (target->getPosition() + target->getAngle()*target->getSpeed()*((target->getPosition().distanceFrom(Position) / (Angle*SpeedPerformance - target->getAngle()*target->getSpeed()).length())) - Position).normalized();

	}
	return target;
}
