#include"Unit.h"
#include"Graphics.h"



void Unit::setUnitData()
{
	switch (Type)
	{
	case 0:
		/*
		type 89 ã@ìÆêÌé‘
		*/

		SpeedPerformance = 0.5;
		TurningPerformance = 0.03;
		HealthPerformance = 10;

		turrets[0].setLocalPosition(Vec2(4, 0));
		turrets[0].setType(0);

		break;
	case 1:
		/*
		t500 èdó§è„ëïçbäÕ
		*/

		SpeedPerformance = 0.2;
		TurningPerformance = 0.01;
		HealthPerformance = 100;

		turrets[0].setLocalPosition(Vec2(5, 0));
		turrets[0].setType(1);
		turrets[1].setLocalPosition(Vec2(-12, 6));
		turrets[1].setType(0);
		turrets[2].setLocalPosition(Vec2(-12, -6));
		turrets[2].setType(0);
		break;
	default:
		break;
	}
	Enabled = true;
	Position.x = Random(1024.0);
	Position.y = Random(1024.0);
	TargetAngle = Vec2(1, 0).rotated(Random(TwoPi));
	Health = HealthPerformance;
	Angle = TargetAngle;
}

void Unit::drawUnit() const
{
	switch (Type)
	{
	case 0:
		Rect(ConvertVec2ToPoint(Position - Vec2(15.0, 7.5)), Point(30 * getZoom(), 15 * getZoom())).rotated(Vec2ToRadian(Angle)).draw(HSV(IFF));
		break;
	case 1:
		Rect(ConvertVec2ToPoint(Position - Vec2(30.0, 15)), Point(60 * getZoom(), 30 * getZoom())).rotated(Vec2ToRadian(Angle)).draw(HSV(IFF, 1, 0.9));
		Rect(ConvertVec2ToPoint(Position - Vec2(20.0, 10)), Point(40 * getZoom(), 20 * getZoom())).rotated(Vec2ToRadian(Angle)).draw(HSV(IFF));
		break;
	default:
		break;
	}
}