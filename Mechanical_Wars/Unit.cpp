#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"
#include"Motion.h"
#include"Platoon.h"
#include"Game.h"
#include"Facility.h"
#include"Mission.h"

extern Array<Facility> facilities;
extern Array<Bullet> bullets;
extern Array<Unit> units;
extern Array<Motion> motions;
extern Array<Platoon> platoons;

void Unit::update()
{
	if (!Enabled) return;

	//updatePlatoon();	//加入を行う処理
		//ターゲットアングルの変更
	if (MyPlatoon != NULL && (!MyPlatoon->Enabled)) MyPlatoon = NULL;
	if(MyPlatoon!=NULL) TargetPosition = MyPlatoon->getUnitTargetPosition(this);
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
		if (FuelMax - Fuel > 0.3 && MyPlatoon->SupplyUnit->Fuel > 0.3)
		{
			Fuel += 0.3;
			MyPlatoon->SupplyUnit->Fuel -= 0.3;
		}
	}

	if (Supply < 0) Supply = 0;
	if (Fuel < 0) Fuel = 0;

	if (Health <= 0)
	{
		for (auto& motion : motions)
			if (motion.setFromUnit(this)) break;
		reset();
	}
	switch (Type)
	{
	case 2:
		if (Fuel <= 50 || Supply <= 1)
		{
			double distance = 10000;
			Facility *supplyFacility = NULL;
			for (auto& facility : facilities)
			{
				if (facility.Enabled && facility.LocatedMission->IFF == IFF && facility.LocatedMission->BAL != 0 && facility.Type == 1 && facility.LocatedMission->Position.distanceFrom(Position) < distance)
				{
					distance = facility.LocatedMission->Position.distanceFrom(Position);
					supplyFacility = &facility;
				}
			}
			if (supplyFacility == NULL) return;
			if (supplyFacility->LocatedMission->Position.distanceFrom(Position) > 16)
			{
				TargetPosition = supplyFacility->LocatedMission->Position;
			}
			else
			{
				if (supplyFacility->Fuel > FuelMax - Fuel)
				{
					supplyFacility->Fuel -= FuelMax - Fuel;
					Fuel = FuelMax;
				}
				else
				{
					Fuel += supplyFacility->Fuel;
					supplyFacility->Fuel = 0;
				}

				if (supplyFacility->Supply > SupplyMax - Supply)
				{
					supplyFacility->Supply -= SupplyMax - Supply;
					Supply = SupplyMax;
				}
				else
				{
					Supply += supplyFacility->Supply;
					supplyFacility->Supply = 0;
				}
			}
		}
		break;
	case 3:	//歩兵

		break;
	default:
		break;
	}

	turnUpdate();

	//ターレット制御
	for (auto& turret : turrets)
		turret.update();

	//速度制御
	Position.moveBy(getSpeedVec2());
	if (Type != 3 && Type != 2)
	{
		Fuel -= getSpeedDouble()*10;
	}
}

Vec2 Unit::getSpeedVec2()
{
	return Angle*getSpeedDouble();
}

double Unit::getSpeedDouble()
{
	if (MyPlatoon == NULL) return 0;
	if (TargetPosition.distanceFrom(Position) < 1) return 0;
	if ((TargetPosition - Position).normalized() == Angle)
	{
		return SpeedPerformance;
	}

	return 0;
}

void Unit::turnUpdate()
{
	if (MyPlatoon == NULL) return;
	Vec2 targetAngle = (TargetPosition - Position).normalized();
	if (TargetPosition.distanceFrom(Position) < 1 && MyPlatoon != NULL)
	{
		switch (Type)
		{
		case 3:
			if (Target != NULL) targetAngle = (Target->Position - Position).normalized();
			else targetAngle = MyPlatoon->TargetAngle;
			break;
		default:
			targetAngle = MyPlatoon->TargetAngle;
			break;
		}
	}

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
	Target = NULL;
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

void Unit::addDamege(Bullet* bullet)
{
	/*
	相性

	*/
	switch (bullet->Type)
	{
	case 0:	//76mm
		if (Type == 0) Health = RandomBool(0.5)*Health;
		if (Type == 2) Health = 0;
		if (Type == 3) Health -= 0.1;
		break;
	case 1:
		break;
	case 2:
		break;
	case 3: //7.6mm
		if (Type == 0) Health -= 0;
		if (Type == 2) Health -= 1.0;
		if (Type == 3) Health -= 1.0;
		break;
	case 4: //7.6mm
		if (Type == 0) Health -= 0;
		if (Type == 2) Health -= 1.0;
		if (Type == 3) Health -= 1.0;
		break;
	default:
		break;
	}
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
	reset();
	IFF = IFF_p;
	Type = type;
	Position = position;
	MyPlatoon = NULL;
	setUnitData();
	return true;
}