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
		for (auto& motion : motions)
			if (motion.setFromBulletLine(Position, Position + Angle*(SpeedPerformance-1))) break;
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
		if (unit.Enabled && IFF != unit.IFF && unit.hitCheck(Position))
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
	Count = int(turret->Count*1.2);
	IFF = turret->BaseUnit->IFF;
	Position = turret->getRealPosition();
	Angle = turret->TargetAngle;
	Type = turret->Type;
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
		if (unit.Enabled && IFF != unit.IFF && Position.distanceFrom(unit.Position) < length)
		{
			length = Position.distanceFrom(unit.Position);
			target = &unit;
		}
	}
	if (target != NULL)
	{
		Angle = (target->Position + target->Angle*target->getSpeedVec2()*((target->Position.distanceFrom(Position) / (Angle*SpeedPerformance - target->Angle*target->getSpeedVec2()).length())) - Position).normalized();

	}
	return target;
}
