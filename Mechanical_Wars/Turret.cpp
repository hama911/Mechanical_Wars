#include"Turret.h"
#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"

extern Array<Unit> units;
extern Array<Bullet> bullets;

void Turret::update()
{
	if (Enabled)
	{



		Unit* target = searchEnemyUnit();
		if (target != NULL)
		{
			TargetAngle = (target->getPosition() - getRealPosition()).normalized();	//射撃角をセット
			for (int i = 0; i < 3; i++)
				TargetAngle = (target->getPosition() + target->getAngle()*target->getSpeedPerformance()*((target->getPosition().distanceFrom(getRealPosition()) / (TargetAngle*BulletSpeed - target->getAngle()*target->getSpeedPerformance()).length())) - getRealPosition()).normalized();
		}


		if (Status == 1)
			updateAngle();
		shot();
	}
}

void Turret::draw() const
{

	if (Enabled)
	{
		drawTurret();
	}
}
Turret::Turret()
{
	Enabled = false;
	LocalPosition = Vec2(0, 0);
	GlobalAngle = Vec2(1, 0);
	TargetAngle = Vec2(1, 0);
	Range = 300.0;
	ReloadCount = 0;
	ReloadTime = 10;
	TurningPerformance = 0.2;
	BaseUnit = NULL;
	Type = 0;
}

Turret::~Turret()
{
}

Vec2 Turret::getTargetAngle() const
{
	return TargetAngle;
}


int Turret::getType() const
{
	return Type;
}

Unit* Turret::getBaseUnit() const
{
	return BaseUnit;
}

Vec2 Turret::getRealPosition() const
{
	return BaseUnit->getPosition() + LocalPosition.rotated(Vec2ToRadian(BaseUnit->getAngle()));
}

void Turret::setBaseUnit(Unit *unit)
{
	BaseUnit = unit;
}

void Turret::setRange(double range)
{
	Range = range;
}

void Turret::setAngle(Vec2 angle)
{
	GlobalAngle = angle;
}

void Turret::setEnable(bool flag)
{
	Enabled = flag;
}

void Turret::setLocalPosition(Vec2 position)
{
	Enabled = true;
	LocalPosition = position;
}

void Turret::setType(int type)
{
	Type = type;
	setTurretData();
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
				TargetAngle = (target->getPosition() + target->getAngle()*target->getSpeedPerformance()*((target->getPosition().distanceFrom(getRealPosition()) / (TargetAngle*BulletSpeed - target->getAngle()*target->getSpeedPerformance()).length())) - getRealPosition()).normalized();

			Count = int(target->getPosition().distanceFrom(getRealPosition()) / (TargetAngle*BulletSpeed - target->getAngle()*target->getSpeedPerformance()).length());
			if (abs(TargetAngle.cross(GlobalAngle)) < 0.1)
			{
				bullets.push_back(this);
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

int Turret::getCount() const
{
	return Count;
}