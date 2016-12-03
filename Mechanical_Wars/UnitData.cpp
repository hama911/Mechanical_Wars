#include"Unit.h"
#include"Graphics.h"
#include"Facility.h"

extern Array<Facility> facilities;
void Unit::setUnitData()
{
	switch (Type)
	{
	case 0:
		Supply = 10;
		Fuel = 10;
		SupplyMax = 10;
		FuelMax = 10;
		SpeedPerformance = 1.0;
		TurningPerformance = 0.03;
		HealthPerformance = 10;
		turrets[0].set(0, 4, 0);
		break;
	case 1:
		Supply = 10;
		Fuel = 10;
		SupplyMax = 10;
		FuelMax = 10;
		SpeedPerformance = 0.3;
		TurningPerformance = 0.02;
		HealthPerformance = 100;
		turrets[0].set(2, -19, -7);
		turrets[1].set(2, -19, 7);
		turrets[2].set(1, 8, 0);
		break;
	case 2:	//�⋋�p�g���b�N
		Supply = 100;
		Fuel = 100;
		SupplyMax = 100;
		FuelMax = 100;
		SpeedPerformance = 1.0;
		TurningPerformance = 0.2;
		HealthPerformance = 5;
		break;
	default:
		break;
	}
	Enabled = true;
	TargetAngle = Vec2(1, 0).rotated(Random(TwoPi));
	Health = HealthPerformance;
	Angle = TargetAngle;
}

bool Unit::hitCheck(Vec2 pos)
{
	bool flag = true;
	Vec2 pos2 = (pos - Position).rotate(-Vec2ToRadian(Angle));
	switch (Type)
	{
	case 0:
		if (pos2.x < -15) flag = false;
		if (pos2.x > 15) flag = false;
		if (pos2.y < -10) flag = false;
		if (pos2.y > 10) flag = false;
		break;
	case 1:
		if (pos2.x < -30) flag = false;
		if (pos2.x > 30) flag = false;
		if (pos2.y < -15) flag = false;
		if (pos2.y > 15) flag = false;
		break;
	case 2:
		if (pos2.x < -7.5) flag = false;
		if (pos2.x > 7.5) flag = false;
		if (pos2.y < -5) flag = false;
		if (pos2.y > 5) flag = false;
		break;
	default:
		flag = false;
		break;
	}
	return flag;
}

void Unit::drawUnit() const
{
	switch (Type)
	{
	case 0:
		TextureAsset(L"T-34_Chassis")(0, 0, 30, 20).resize(30 * getZoom(), 20 * getZoom()).rotate(Vec2ToRadian(Angle)).draw(ConvertVec2ToPoint(Position - Vec2(15.0, 10.0)));
		break;
	case 1:
		TextureAsset(L"Ratte_Chassis")(0, 0, 60, 30).resize(60 * getZoom(), 30 * getZoom()).rotate(Vec2ToRadian(Angle)).draw(ConvertVec2ToPoint(Position - Vec2(30.0, 15.0)));
		break;
	case 2:
		TextureAsset(L"Supply_Truck")(0, 0, 15, 10).resize(15 * getZoom(), 10 * getZoom()).rotate(Vec2ToRadian(Angle)).draw(ConvertVec2ToPoint(Position - Vec2(7.5, 5.0)));
		break;
	default:
		break;
	}
}

void Unit::updateUnit()
{
	switch (Type)
	{
	case 2:
		if (Fuel <= 50 || Supply <= 1)
		{
			double distance = 10000;
			Facility *supplyFacility = NULL;
			for (auto& facility : facilities)
			{
				if (facility.Enabled && facility.IFF == IFF && facility.Type == 1 && facility.Position.distanceFrom(Position) < distance)
				{
					distance = facility.Position.distanceFrom(Position);
					supplyFacility = &facility;
				}
			}
			if (supplyFacility == NULL) return;
			if (supplyFacility->Position.distanceFrom(Position) > 16)
			{
				TargetAngle = (supplyFacility->Position - Position).normalized();
				Speed = SpeedPerformance;
			}
			else
			{
				supplyFacility->Fuel -= FuelMax - Fuel;
				supplyFacility->Supply -= SupplyMax - Supply;
				Fuel = FuelMax;
				Supply = SupplyMax;
			}
		}
		break;
	default:
		break;
	}
}