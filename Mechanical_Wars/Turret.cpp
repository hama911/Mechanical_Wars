#include"Turret.h"
#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"

extern Array<Unit> units;
extern Array<Bullet> bullets;

void Turret::update()
{
	if (!Enabled) return;
	--ReloadCount;
	if (Type == 3 && BaseUnit->getSpeedDouble() > 0)
	{
		TargetAngle = BaseUnit->Angle;
	}
	else
	{
		Unit* target = searchEnemyUnit();
		if (target != NULL)
		{
			TargetAngle = calculateDeviation(getRealPosition(), target->Position, BulletSpeed, target->getSpeedVec2());
			if (Type == 3)	BaseUnit->Target = target;
		}
		else
		{
			if (Type == 3)	BaseUnit->Target = NULL;
			TargetAngle = BaseUnit->Angle;
		}
		shot();
	}
	updateAngle();
}

void Turret::draw() const
{

	if (!Enabled) return;
	drawTurret();
}

Vec2 Turret::getRealPosition() const
{
	return BaseUnit->Position + LocalPosition.rotated(Vec2ToRadian(BaseUnit->Angle));
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
	if (ReloadCount < 0)
	{
		if (ammo <= 0)
		{
			double needSupply = 0;
			if (Type == 0) needSupply = 3;
			if (Type == 1) needSupply = 1;
			if (Type == 2) needSupply = 3;
			if (Type == 3) needSupply = 0.5;
			if (Type == 4) needSupply = 1;
			if (needSupply > BaseUnit->Supply) return;
			BaseUnit->Supply -= needSupply;
			if (Type == 0) ammo = 1;
			if (Type == 1) ammo = 1;
			if (Type == 2) ammo = 1;
			if (Type == 3) ammo = 5;
			if (Type == 4) ammo = 20;
		}
		Unit* target = searchEnemyUnit();
		if (target != NULL)
		{
			TargetAngle = calculateDeviation(getRealPosition(), target->Position, BulletSpeed, target->getSpeedVec2());
			if (abs(TargetAngle.cross(GlobalAngle)) < Sin(TurningPerformance) && TargetAngle.dot(GlobalAngle) > 0)
			{
				Count = int(calculateCollisionTime(getRealPosition(), target->Position, BulletSpeed, target->getSpeedVec2()));
				switch (Type)
				{
				case 0:
					SoundAsset(L"cannon1").playMulti(getSoundVolume(getRealPosition()) * 2);
					break;
				case 1:
					SoundAsset(L"cannon2").playMulti(getSoundVolume(getRealPosition()));
					break;
				case 3:
					SoundAsset(L"shot1").playMulti(getSoundVolume(getRealPosition()));
					break;
				case 4:
					SoundAsset(L"pom").playMulti(getSoundVolume(getRealPosition()));
					break;
				default:
					break;
				}

				for (auto& bullet : bullets)
					if (bullet.set(this, target)) break;
				{
					double reloadTime = 0;
					--ammo;
					if (ammo <= 0)
					{
						if (Type == 0) reloadTime = 300;
						if (Type == 1) reloadTime = 600;
						if (Type == 2) reloadTime = 300;
						if (Type == 3) reloadTime = 180;
						if (Type == 4) reloadTime = 240;
					}
					else {
						if (Type == 0) reloadTime = 300;
						if (Type == 1) reloadTime = 600;
						if (Type == 2) reloadTime = 300;
						if (Type == 3) reloadTime = 30;
						if (Type == 4) reloadTime = 10;
					}
					ReloadCount = int(reloadTime*Random(0.8, 1.2));
				}
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
		if (Type == 0 && (unit.Type != 0 && unit.Type != 2)) continue;
		if (Type == 3 && !(unit.Type == 3 || unit.Type == 2)) continue;
		if (Type == 4 && (unit.Type != 3)) continue;
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