#include"Unit.h"
#include"Graphics.h"

void Unit::setUnitData()
{
	switch (Type)
	{
	case 0:
		SpeedPerformance = 0.5;
		TurningPerformance = 0.03;
		HealthPerformance = 10;
		turrets[0].set(0, 4, 0);
		break;
	case 1:
		SpeedPerformance = 0.2;
		TurningPerformance = 0.005;
		HealthPerformance = 100;
		turrets[0].set(2, -19, -7);
		turrets[1].set(2, -19, 7);
		turrets[2].set(1, 8, 0);
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
		TextureAsset(L"T-34_Chassis")(0,0,30,20).resize(30*getZoom(), 20*getZoom()).rotate(Vec2ToRadian(Angle)).draw(ConvertVec2ToPoint(Position - Vec2(15.0, 10.0)));
		break;
	case 1:
		TextureAsset(L"Ratte_Chassis")(0, 0, 60, 30).resize(60 * getZoom(), 30 * getZoom()).rotate(Vec2ToRadian(Angle)).draw(ConvertVec2ToPoint(Position - Vec2(30.0, 15.0)));
		break;
	default:
		break;
	}
}