#include"Unit.h"
#include"Bullet.h"
#include"Graphics.h"
#include"Motion.h"
#include"Game.h"
#include"Facility.h"
#include"Mission.h"
#include"Division.h"

extern Array<Division> divisions;
extern Array<Facility> facilities;
extern Array<Bullet> bullets;
extern Array<Unit> units;
extern Array<Motion> motions;

void Unit::update()
{
	if (!Enabled) return;


	for (auto& turret : turrets)
		turret.BaseUnit = this;

	//師団に加入する処理
	if (AssignedDivision == NULL)
	{
		double distance = 0xFFFFFF;
		Division* target = NULL;
		for (auto& division : divisions)
		{
			if (!division.canJoinDivision(this)) continue;
			if (division.getJoinPriority(this) >= distance) continue;
			distance = division.getJoinPriority(this);
			target = &division;
		}
		if (target != NULL) target->JoinDivision(this);
	}
	else
	{
		//方向を決める
		TargetPosition = AssignedDivision->getTargetPosition(this);

		//補給処理
		if(!isSupplyUnit())	AssignedDivision->receiveSupply(this);
	}
	

	limitMoving();



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
	if (Fuel >= 0)
	{
		Position.moveBy(getSpeedVec2());
		if (Type != 3 && Type != 2)
		{
		//	Fuel -= getSpeedDouble();
		}
	}
	if (Fuel < -1) Fuel = -1;
	if (Supply < -1) Supply = -1;
}

Vec2 Unit::getSpeedVec2()
{
	return Angle*getSpeedDouble();
}

double Unit::getSpeedDouble()
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
	if (TargetPosition.distanceFrom(Position) < 1)
	{
		switch (Type)
		{
		case 3:
			if (Target != NULL) targetAngle = (Target->Position - Position).normalized();
			else if (AssignedDivision != NULL) targetAngle = AssignedDivision->getTargetAngle();
			break;
		default:
			if (AssignedDivision != NULL) targetAngle = AssignedDivision->getTargetAngle();
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
	SpeedPerformance = 0.0;
	TurningPerformance = 0.0;
	HealthPerformance = 0.0;
	Type = 0;
	if (AssignedDivision != NULL) AssignedDivision->leaveDivision(this);
	AssignedDivision = NULL;
	for (auto& turret : turrets)
		turret.Enabled = false;
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
	setUnitData();
	return true;
}

bool Unit::isSupplyUnit()
{
	if (Type == 2) return true;
	return false;
}