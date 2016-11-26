#include"Turret.h"
#include"Graphics.h"
#include"Unit.h"

void Turret::setTurretData()
{
	Enabled = true;
	switch (Type)
	{
	case 0:
		//120mm ‚‘¬“Ob’e
		Range = 200.0;
		ReloadTime = 60;
		TurningPerformance = 0.09;
		BulletSpeed = 3.0;
		break;
	case 1:
		//200mm žÖ’e–C“ƒ
		Range = 500.0;
		ReloadTime = 180;
		TurningPerformance = 0.02;
		BulletSpeed = 3.0;
		break;
	case 2:
		//120mm ‚‘¬“Ob’e
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
		//Circle(ConvertVec2ToVec2(getRealPosition()), 5 * getZoom()).draw(HSV(BaseUnit->getIFF(), 1, 0.5));
		//Line(ConvertVec2ToVec2(getRealPosition()), ConvertVec2ToVec2(getRealPosition()) + GlobalAngle * 10 * getZoom()).draw(2 * getZoom(), HSV(BaseUnit->getIFF(), 1, 0.5));
		TextureAsset(L"T-34_Turret")(0, 0, 30, 20).resize(30 * getZoom(), 20 * getZoom()).rotate(Vec2ToRadian(GlobalAngle)).draw(ConvertVec2ToPoint(getRealPosition() - Vec2(15.0, 10.0)));

		break;
	case 1:
		//Circle(ConvertVec2ToVec2(getRealPosition()), 10 * getZoom()).draw(HSV(BaseUnit->getIFF(), 1, 0.5));
		//Line(ConvertVec2ToVec2(getRealPosition()), ConvertVec2ToVec2(getRealPosition()) + GlobalAngle * 20 * getZoom()).draw(5 * getZoom(), HSV(BaseUnit->getIFF(), 1, 0.5));
		TextureAsset(L"Ratte_Turret")(0, 0, 60, 30).resize(60 * getZoom(), 30 * getZoom()).rotate(Vec2ToRadian(GlobalAngle)).draw(ConvertVec2ToPoint(getRealPosition() - Vec2(30.0, 15.0)));

		break;
	case 2:
		//Circle(ConvertVec2ToVec2(getRealPosition()), 10 * getZoom()).draw(HSV(BaseUnit->getIFF(), 1, 0.5));
		//Line(ConvertVec2ToVec2(getRealPosition()), ConvertVec2ToVec2(getRealPosition()) + GlobalAngle * 20 * getZoom()).draw(5 * getZoom(), HSV(BaseUnit->getIFF(), 1, 0.5));
		TextureAsset(L"Ratte_Turret2")(0, 0, 60, 30).resize(40 * getZoom(), 20 * getZoom()).rotate(Vec2ToRadian(GlobalAngle)).draw(ConvertVec2ToPoint(getRealPosition() - Vec2(20.0, 10.0)));

		break;
	default:
		break;
	}

}