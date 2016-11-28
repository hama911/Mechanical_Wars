#include"Turret.h"
#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"

extern Array<Unit> units;
extern Array<Bullet> bullets;

void Turret::update()
{
	if (!Enabled) return;
	Unit* target = searchEnemyUnit();
	if (target != NULL)
	{
		TargetAngle = (target->getPosition() - getRealPosition()).normalized();	//射撃角をセット
		for (int i = 0; i < 3; i++)
			TargetAngle = (target->getPosition() + target->getAngle()*target->getSpeed()*((target->getPosition().distanceFrom(getRealPosition()) / (TargetAngle*BulletSpeed - target->getAngle()*target->getSpeed()).length())) - getRealPosition()).normalized();
	}
	else
	{
		TargetAngle = BaseUnit->getAngle();
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
	return BaseUnit->getPosition() + LocalPosition.rotated(Vec2ToRadian(BaseUnit->getAngle()));
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
	--ReloadCount;
	if (ReloadCount < 0)
	{
		Unit* target = searchEnemyUnit();
		if (target != NULL)
		{
			TargetAngle = (target->getPosition() - getRealPosition()).normalized();	//射撃角をセット
			for (int i = 0; i < 10; i++)
				TargetAngle = (target->getPosition() + target->getAngle()*target->getSpeed()*((target->getPosition().distanceFrom(getRealPosition()) / (TargetAngle*BulletSpeed - target->getAngle()*target->getSpeed()).length())) - getRealPosition()).normalized();

			Count = int(target->getPosition().distanceFrom(getRealPosition()) / (TargetAngle*BulletSpeed - target->getAngle()*target->getSpeed()).length());
			if (abs(TargetAngle.cross(GlobalAngle)) < Sin(TurningPerformance) && TargetAngle.dot(GlobalAngle) > 0)
			{
				if (Type == 1) SoundAsset(L"cannon1").playMulti(getSoundVolume(getRealPosition()) * 5);
				else SoundAsset(L"cannon2").playMulti(getSoundVolume(getRealPosition()));
				for (auto& bullet : bullets)
					if (bullet.set(this)) break;
				ReloadCount = ReloadTime;
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
		if (unit.getEnabled() && BaseUnit->getIFF() != unit.getIFF() && realPosition.distanceFrom(unit.getPosition()) < distance)
		{
			distance = realPosition.distanceFrom(unit.getPosition());
			target = &unit;
		}
	}
	if (target == NULL)
		Status = 0;
	else
		Status = 1;
	return target;
}