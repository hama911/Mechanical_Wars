#include"Unit.h"
#include"Graphics.h"
#include"Facility.h"
#include"Mission.h"

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
		turrets[1].set(4, 4, 0);
		break;
	case 1:
		Supply = 0;
		Fuel = 0;
		SupplyMax = 10;
		FuelMax = 10;
		SpeedPerformance = 0.3;
		TurningPerformance = 0.02;
		HealthPerformance = 100;
		turrets[0].set(2, -19, -7);
		turrets[1].set(2, -19, 7);
		turrets[2].set(1, 8, 0);
		break;
	case 2:	//ï‚ããópÉgÉâÉbÉN
		Supply = 0;
		Fuel = 50;
		SupplyMax = 100;
		FuelMax = 100;
		SpeedPerformance = 1.0;
		TurningPerformance = 0.2;
		HealthPerformance = 5;
		break;
	case 3:	//ï‡ï∫
		Supply = 0;
		Fuel = 5;
		SupplyMax = 5;
		FuelMax = 0;
		SpeedPerformance = 1;
		TurningPerformance = 0.1;
		HealthPerformance = 50;
		turrets[0].set(3, 0, 3);
	default:
		break;
	}
	Enabled = true;
	TargetPosition = Position;
	Health = HealthPerformance;
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
	case 3:
		if (pos2.x < -5) flag = false;
		if (pos2.x > 5) flag = false;
		if (pos2.y < -7.5) flag = false;
		if (pos2.y > 7.5) flag = false;
		break;
	default:
		flag = false;
		break;
	}
	return flag;
}

void Unit::drawUnit() const
{
	//Circle(ConvertVec2ToVec2(Position), 15 * getZoom()).draw(Color(HSV(IFF), 64));
	switch (Type)
	{
	case 0:
		TextureAsset(L"T-34_Chassis")(0, 0, 30, 20).resize(30 * getZoom(), 20 * getZoom()).rotate(Vec2ToRadian(Angle)).draw(ConvertVec2ToPoint(Position - Vec2(15.0, 10.0)));
		break;
	case 1:
		//ëœãvÉQÅ[ÉW
		Line(ConvertVec2ToVec2(Position - Vec2(HealthPerformance / 2, 20)), ConvertVec2ToVec2(Position - Vec2(-HealthPerformance / 2, 20))).draw(3 * getZoom(), Palette::Red);
		Line(ConvertVec2ToVec2(Position - Vec2(HealthPerformance / 2, 20)), ConvertVec2ToVec2(Position - Vec2(HealthPerformance / 2 - Health, 20))).draw(3 * getZoom(), Palette::Green);

		TextureAsset(L"Ratte_Chassis")(0, 0, 60, 30).resize(60 * getZoom(), 30 * getZoom()).rotate(Vec2ToRadian(Angle)).draw(ConvertVec2ToPoint(Position - Vec2(30.0, 15.0)));
		break;
	case 2:
		//îRóøÉQÅ[ÉW
		Line(ConvertVec2ToVec2(Position - Vec2(10, 26)), ConvertVec2ToVec2(Position - Vec2(-10, 26))).draw(3 * getZoom(), Palette::Black);
		Line(ConvertVec2ToVec2(Position - Vec2(10, 26)), ConvertVec2ToVec2(Position - Vec2(10 - (Fuel / FuelMax) * 20, 26))).draw(3 * getZoom(), Palette::Purple);

		//ï®éëÉQÅ[ÉW
		Line(ConvertVec2ToVec2(Position - Vec2(10, 23)), ConvertVec2ToVec2(Position - Vec2(-10, 23))).draw(3 * getZoom(), Palette::Black);
		Line(ConvertVec2ToVec2(Position - Vec2(10, 23)), ConvertVec2ToVec2(Position - Vec2(10 - (Supply / SupplyMax) * 20, 23))).draw(3 * getZoom(), Palette::Yellow);

		TextureAsset(L"Supply_Truck")(0, 0, 15, 10).resize(15 * getZoom(), 10 * getZoom()).rotate(Vec2ToRadian(Angle)).draw(ConvertVec2ToPoint(Position - Vec2(7.5, 5.0)));
		break;
	case 3:		//ï‡ï∫
		//ëœãvÉQÅ[ÉW
		//Line(ConvertVec2ToVec2(Position - Vec2(HealthPerformance / 2, 20)), ConvertVec2ToVec2(Position - Vec2(-HealthPerformance / 2, 20))).draw(3 * getZoom(), Palette::Red);
		//Line(ConvertVec2ToVec2(Position - Vec2(HealthPerformance / 2, 20)), ConvertVec2ToVec2(Position - Vec2(HealthPerformance / 2 - Health, 20))).draw(3 * getZoom(), Palette::Green);

		TextureAsset(L"Soldier").resize(10 * getZoom(), 15 * getZoom()).rotate(Vec2ToRadian(Angle)).draw(ConvertVec2ToPoint(Position - Vec2(5.0, 7.5)));
		break;
	default:
		break;
	}
}
