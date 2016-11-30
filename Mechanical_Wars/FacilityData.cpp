#include"Facility.h"
#include"Graphics.h"
#include"Unit.h"

extern Array<Unit> units;


void Facility::drawFacility() const
{
	switch (Type)
	{
	case 0:		//���퐻����
		Rect(ConvertVec2ToPoint(Position), Size(64 * getZoom(), 64 * getZoom())).draw(Palette::Chocolate);
		break;
	case 1:		//����������
		Line(ConvertVec2ToVec2(Position - Vec2(SupplyMax / 2, 43)), ConvertVec2ToVec2(Position - Vec2(-SupplyMax / 2, 43))).draw(3 * getZoom(), Palette::Black);
		Line(ConvertVec2ToVec2(Position - Vec2(SupplyMax / 2, 43)), ConvertVec2ToVec2(Position - Vec2(SupplyMax / 2 - Supply, 43))).draw(3 * getZoom(), Palette::Purple);
		Line(ConvertVec2ToVec2(Position - Vec2(FuelMax / 2, 40)), ConvertVec2ToVec2(Position - Vec2(-FuelMax / 2, 40))).draw(3 * getZoom(), Palette::Black);
		Line(ConvertVec2ToVec2(Position - Vec2(FuelMax / 2, 40)), ConvertVec2ToVec2(Position - Vec2(FuelMax / 2 - Fuel, 40))).draw(3 * getZoom(), Palette::Yellow);
		Rect(ConvertVec2ToPoint(Position - Vec2(32, 32)), Size(64 * getZoom(), 64 * getZoom())).draw(Palette::Red);
		break;
	default:
		break;
	}
}

void Facility::updateFacility()
{
	switch (Type)
	{
	case 0:		//���퐻����
		++Progress;
		if (Progress > 100)
		{
			for (auto& unit : units)
				if (unit.setUnit(IFF, 0, Position)) break;
			Progress = 0;
		}
		break;
	case 1:		//����������
		Fuel += 1.0;
		Supply += 1.0;
		if (Fuel > FuelMax) Fuel = FuelMax;
		if (Supply > SupplyMax) Supply = SupplyMax;
		++Progress;
		if(Progress>400)
		{
			for (auto& unit : units)
				if (unit.setUnit(IFF, 2, Position)) break;
			Progress = 0;
		}
		break;
	default:
		break;
	}
}

