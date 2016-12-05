#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"
#include"Motion.h"
#include"Platoon.h"
#include"Game.h"

extern Array<Bullet> bullets;
extern Array<Unit> units;
extern Array<Motion> motions;
extern Array<Platoon> platoons;

void Unit::update()
{
	if (!Enabled) return;
	updatePlatoon();
	for (auto& turret : turrets)
		turret.BaseUnit = this;


	limitMoving();

	if (MyPlatoon != NULL && MyPlatoon->SupplyUnit != NULL && Position.distanceFrom(MyPlatoon->SupplyUnit->Position) < 64)
	{
		if (SupplyMax - Supply > 0.1 && MyPlatoon->SupplyUnit->Supply > 0.1)
		{
			Supply += 0.1;
			MyPlatoon->SupplyUnit->Supply -= 0.1;
		}
		if (FuelMax - Fuel > 0.1 && MyPlatoon->SupplyUnit->Fuel > 0.1)
		{
			Fuel += 0.1;
			MyPlatoon->SupplyUnit->Fuel -= 0.1;
		}
	}

	if (Supply < 0) Supply = 0;
	if (Fuel < 0) Fuel = 0;

	if (Health < 0)
	{
		for (auto& motion : motions)
			if (motion.setFromUnit(this)) break;
		reset();
	}
	//ターレット制御
	for (auto& turret : turrets)
		turret.update();



	updateUnit();

	turnUpdate();

	//速度制御
	Position.moveBy(getSpeedVec2());
	Fuel -= getSpeedDouble();

}

Vec2 Unit::getSpeedVec2() const
{
	return Angle*getSpeedDouble();
}

double Unit::getSpeedDouble() const
{
	if (TargetPosition.distanceFrom(Position) < 1) return 0;
	if ((TargetPosition - Position).normalized() == Angle)
	{
		return SpeedPerformance;
	}

	return 0;
}

void Unit::turnUpdate()
{
	Vec2 targetAngle = (TargetPosition - Position).normalized();
	if (TargetPosition.distanceFrom(Position) < 1 && MyPlatoon != NULL)
		targetAngle = MyPlatoon->TargetAngle;

	if (abs(targetAngle.cross(Angle)) < Sin(TurningPerformance) && targetAngle.dot(Angle) > 0)
	{
		Angle = targetAngle;
	}
	else
	{
		if (targetAngle.cross(Angle) > 0)
		{
			Angle.rotate(-TurningPerformance);
			for (auto& turret : turrets) turret.addRotate(-TurningPerformance);
		}
		else
		{
			Angle.rotate(TurningPerformance);
			for (auto& turret : turrets) turret.addRotate(TurningPerformance);
		}
	}
}

void Unit::reset()
{
	Supply = 0;
	Fuel = 0;
	Enabled = false;
	Position = Vec2(0, 0);
	Angle = Vec2(1, 0);
	TargetPosition = Vec2(0, 0);
	IFF = 0;
	Health = 0.0;
	MyPlatoon = NULL;
	SpeedPerformance = 0.0;
	TurningPerformance = 0.0;
	HealthPerformance = 0.0;
	Type = 0;
	for (auto& turret : turrets)
		turret.Enabled = false;
}

void Unit::updatePlatoon()
{
	if (MyPlatoon == NULL)
	{
		double distance = 10000;
		Platoon *option = NULL;
		for (auto& platoon : platoons)
		{
			if (platoon.getJoinDistance(this) < distance)
			{
				distance = platoon.getJoinDistance(this);
				option = &platoon;
			}
		}
		if (option != NULL) {
			option->joinPlatoon(this);
		}
		else {
			for (auto& platoon : platoons)
			{
				if (platoon.joinPlatoon(this)) break;
			}
		}
	}
	else
	{
		if (!MyPlatoon->Enabled)
		{
			MyPlatoon = NULL;
			return;
		}
		//ターゲットアングルの変更
		TargetPosition = MyPlatoon->getUnitTargetPosition(this);
		//より多いところに加入
		if (MyPlatoon->getTotalMember() <= 2)
		{
			for (auto& platoon : platoons)
			{
				if (platoon.Enabled && &platoon != MyPlatoon&&platoon.LeaderUnit->IFF == IFF && platoon.getTotalMember() + MyPlatoon->getTotalMember() <= 5 && platoon.getTotalMember() >= MyPlatoon->getTotalMember())
				{
					platoon.joinPlatoon(this);
				}
			}
		}
	}
}


void Unit::draw() const
{
	if (Enabled)
	{

		//本体
		drawUnit();

		//ターレット描画
		for (auto& turret : turrets)
			turret.draw();

	}
}

void Unit::addDamege(double value)
{
	Health -= value;
}

void Unit::limitMoving()
{
	if (Position.x < GROUND_LIMIT_MIN_X) Position.x = GROUND_LIMIT_MIN_Y;
	if (Position.y < GROUND_LIMIT_MIN_Y) Position.y = GROUND_LIMIT_MIN_Y;
	if (Position.x > GROUND_LIMIT_MAX_X) Position.x = GROUND_LIMIT_MAX_X;
	if (Position.y > GROUND_LIMIT_MAX_Y) Position.y = GROUND_LIMIT_MAX_Y;
}




bool Unit::setUnit(int IFF_p, int type, Vec2 position)
{
	if (Enabled) return false;
	IFF = IFF_p;
	Type = type;
	Position = position;
	MyPlatoon = NULL;
	setUnitData();
	return true;
}

int Unit::getMotionType() const
{
	switch (Type)
	{
	case 0:
		return 2;
		break;
	case 1:
		return 3;
		break;
	default:
		break;
	}
	return 0;
}