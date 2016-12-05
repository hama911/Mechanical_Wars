#include"Turret.h"
#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"
#include"Motion.h"
extern Array<Motion> motions;

extern Array<Unit> units;
extern Array<Bullet> bullets;

void Turret::update()
{
	if (!Enabled) return;
	Unit* target = searchEnemyUnit();
	if (target != NULL)
	{
		TargetAngle = calculateDeviation(getRealPosition(), target->Position, BulletSpeed, target->getSpeedVec2());	
	}
	else
	{
		TargetAngle = BaseUnit->Angle;
	}

	updateAngle();
	shot();
}

void Turret::draw() const
{

	if (Enabled)
	{
		drawTurret();
	}
}

Vec2 Turret::getRealPosition() const
{
	return BaseUnit->Position + LocalPosition.rotated(Vec2ToRadian(BaseUnit->Angle)) + TargetAngle * 16;
}


void Turret::setLocalPosition(Vec2 position)
{
	Enabled = true;
	LocalPosition = position;
}

void Turret::addRotate(double angle)
{
	if (Enabled)
		GlobalAngle.rotate(angle);
}

void Turret::updateAngle()
{
	if (abs(TargetAngle.cross(GlobalAngle)) < Sin(TurningPerformance) && TargetAngle.dot(GlobalAngle) > 0)
		GlobalAngle = TargetAngle;
	else
	{
		if (TargetAngle.cross(GlobalAngle) > 0)
			GlobalAngle.rotate(-TurningPerformance);
		else
			GlobalAngle.rotate(TurningPerformance);
	}
}

void Turret::shot()
{
	if (BaseUnit->Supply < 0.5) return;
	--ReloadCount;
	if (ReloadCount < 0)
	{
		Unit* target = searchEnemyUnit();
		if (target != NULL)
		{
			TargetAngle = calculateDeviation(getRealPosition(), target->Position, BulletSpeed, target->getSpeedVec2());

			Count = int(calculateCollisionTime(getRealPosition(), target->Position, BulletSpeed, target->getSpeedVec2()));
			if (abs(TargetAngle.cross(GlobalAngle)) < Sin(TurningPerformance) && TargetAngle.dot(GlobalAngle) > 0)
			{
				if (Type == 1) SoundAsset(L"cannon1").playMulti(getSoundVolume(getRealPosition()) * 5);
				else SoundAsset(L"cannon2").playMulti(getSoundVolume(getRealPosition()));
				for (auto& bullet : bullets)
					if (bullet.set(this)) break;
				ReloadCount = ReloadTime;
				BaseUnit->Supply -= 0.5;
			}
		}
	}
}

Unit* Turret::searchEnemyUnit()
{
	Unit* target = NULL;
	double distance = Range;
	Vec2 realPosition = getRealPosition();
	for (auto& unit : units)
	{
		if (unit.Enabled && BaseUnit->IFF != unit.IFF && realPosition.distanceFrom(unit.Position) < distance)
		{
			distance = realPosition.distanceFrom(unit.Position);
			target = &unit;
		}
	}
	if (target == NULL)
		Status = 0;
	else
		Status = 1;
	return target;
}