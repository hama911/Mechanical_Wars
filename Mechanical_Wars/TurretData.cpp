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
		BulletSpeed = 1.0;
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
		Circle(ConvertVec2ToVec2(getRealPosition()), 5 * getZoom()).draw(HSV(BaseUnit->getIFF(), 1, 0.5));
		Line(ConvertVec2ToVec2(getRealPosition()), ConvertVec2ToVec2(getRealPosition()) + GlobalAngle * 10 * getZoom()).draw(2 * getZoom(), HSV(BaseUnit->getIFF(), 1, 0.5));
		break;
	case 1:
		Circle(ConvertVec2ToVec2(getRealPosition()), 10 * getZoom()).draw(HSV(BaseUnit->getIFF(), 1, 0.5));
		Line(ConvertVec2ToVec2(getRealPosition()), ConvertVec2ToVec2(getRealPosition()) + GlobalAngle * 20 * getZoom()).draw(5 * getZoom(), HSV(BaseUnit->getIFF(), 1, 0.5));
		break;
	default:
		break;
	}

}