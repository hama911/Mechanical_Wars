#include"Turret.h"
#include"Graphics.h"
#include"Unit.h"

void Turret::set(int type,double x,double y) {
	Enabled = true;
	Type = type; 
	LocalPosition = Vec2(x, y);
	GlobalAngle = Vec2(1, 0);
	TargetAngle = Vec2(1, 0);
	ReloadCount = 0;
	setTurretData();
}

void Turret::setTurretData()
{
	switch (Type)
	{
	case 0:
		Range = 192.0;
		ReloadTime = 60;
		TurningPerformance = 0.09;
		BulletSpeed = 2.0;
		break;
	case 1:
		Range = 500.0;
		ReloadTime = 180;
		TurningPerformance = 0.02;
		BulletSpeed = 3.0;
		break;
	case 2:
		Range = 200.0;
		ReloadTime = 60;
		TurningPerformance = 0.04;
		BulletSpeed = 3.0;
		break;
	default:
		break;
	}
}

void Turret::drawTurret() const
{
	switch (Type)
	{
	case 0:
		TextureAsset(L"T-34_Turret")(0, 0, 30, 20).resize(30 * getZoom(), 20 * getZoom()).rotate(Vec2ToRadian(GlobalAngle)).draw(ConvertVec2ToPoint(getRealPosition() - Vec2(15.0, 10.0)));
		break;
	case 1:
		TextureAsset(L"Ratte_Turret")(0, 0, 60, 30).resize(60 * getZoom(), 30 * getZoom()).rotate(Vec2ToRadian(GlobalAngle)).draw(ConvertVec2ToPoint(getRealPosition() - Vec2(30.0, 15.0)));
		break;
	case 2:
		TextureAsset(L"Ratte_Turret2")(0, 0, 60, 30).resize(40 * getZoom(), 20 * getZoom()).rotate(Vec2ToRadian(GlobalAngle)).draw(ConvertVec2ToPoint(getRealPosition() - Vec2(20.0, 10.0)));
		break;
	default:
		break;
	}

}