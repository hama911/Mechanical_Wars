#include"Turret.h"
#include"Graphics.h"
#include"Unit.h"

void Turret::set(int type, double x, double y) {
	Enabled = true;
	Type = type;
	LocalPosition = Vec2(x, y);
	GlobalAngle = Vec2(1, 0);
	TargetAngle = Vec2(1, 0);
	ReloadCount = 0;
	setTurretData();
	ammo = 0;
}

void Turret::setTurretData()
{
	switch (Type)
	{
	case 0:
		Range = 512.0;
		TurningPerformance = 0.05;
		BulletSpeed = 5.0;
		break;
	case 1:
		Range = 500.0;
		TurningPerformance = 0.02;
		BulletSpeed = 3.0;
		break;
	case 2:
		Range = 200.0;
		TurningPerformance = 0.04;
		BulletSpeed = 3.0;
		break;
	case 3:	//�����e
		Range = 192.0;
		TurningPerformance = 0.1;
		BulletSpeed = 3.0;
		break;
	case 4:	//�ԍڋ@�֏e
		Range = 192.0;
		TurningPerformance = 0.1;
		BulletSpeed = 3.0;
		break;
	default:
		break;
	}
}

void Turret::drawTurret() const
{
	/*
	if(ReloadCount>0)
		Circle(ConvertVec2ToPoint(getRealPosition()), ReloadCount*0.1 * getZoom()).drawFrame(1*getZoom(), 0, Palette::Yellowgreen);
		*/
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
	case 3:
		TextureAsset(L"Rifle").resize(15 * getZoom(), 5 * getZoom()).rotate(Vec2ToRadian(GlobalAngle)).draw(ConvertVec2ToPoint(getRealPosition() - Vec2(7.5, 2.5)));
		break;
	case 4:
		//TextureAsset(L"Rifle").resize(15 * getZoom(), 5 * getZoom()).rotate(Vec2ToRadian(GlobalAngle)).draw(ConvertVec2ToPoint(getRealPosition() - Vec2(7.5, 2.5)));
		break;
	default:
		break;
	}

}