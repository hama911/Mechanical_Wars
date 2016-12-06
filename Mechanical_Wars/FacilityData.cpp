#include"Facility.h"
#include"Graphics.h"
#include"Unit.h"
#include"Power.h"
#include"Mission.h"
extern Array<Power> powers;
extern Array<Unit> units;


void Facility::drawFacility() const
{
	switch (Type)
	{
	case 0:		//•ºŠí»‘¢‹Ç
		TextureAsset(L"fact1").resize(100 * getZoom(), 70 * getZoom()).draw(ConvertVec2ToPoint(LocatedMission->Position - Vec2(50.0, 35.0)));
		Rect(ConvertVec2ToPoint(LocatedMission->Position - Vec2(50, 35)), Size(100 * getZoom(), 70 * getZoom())).draw(Color(HSV(LocatedMission->IFF), 128)).drawFrame(5 * getZoom(), 0, Palette::Gray);

		break;
	case 1:		//•¨Ž‘»‘¢‹Ç
		Line(ConvertVec2ToVec2(LocatedMission->Position - Vec2(SupplyMax / 2, 43)), ConvertVec2ToVec2(LocatedMission->Position - Vec2(-SupplyMax / 2, 43))).draw(3 * getZoom(), Palette::Black);
		Line(ConvertVec2ToVec2(LocatedMission->Position - Vec2(SupplyMax / 2, 43)), ConvertVec2ToVec2(LocatedMission->Position - Vec2(SupplyMax / 2 - Supply, 43))).draw(3 * getZoom(), Palette::Purple);
		Line(ConvertVec2ToVec2(LocatedMission->Position - Vec2(FuelMax / 2, 40)), ConvertVec2ToVec2(LocatedMission->Position - Vec2(-FuelMax / 2, 40))).draw(3 * getZoom(), Palette::Black);
		Line(ConvertVec2ToVec2(LocatedMission->Position - Vec2(FuelMax / 2, 40)), ConvertVec2ToVec2(LocatedMission->Position - Vec2(FuelMax / 2 - Fuel, 40))).draw(3 * getZoom(), Palette::Yellow);
		//Rect(ConvertVec2ToPoint(LocatedMission->Position - Vec2(32, 32)), Size(64 * getZoom(), 64 * getZoom())).draw(Palette::Red);
		TextureAsset(L"fact0").resize(100 * getZoom(), 70 * getZoom()).draw(ConvertVec2ToPoint(LocatedMission->Position - Vec2(50.0, 35.0)));
		Rect(ConvertVec2ToPoint(LocatedMission->Position - Vec2(50, 35)), Size(100 * getZoom(), 70 * getZoom())).draw(Color(HSV(LocatedMission->IFF), 128)).drawFrame(5 * getZoom(), 0, Palette::Gray);

		break;
	default:
		break;
	}
}

void Facility::updateFacility()
{
	if (LocatedMission->BAL == 0) return;
	switch (Type)
	{
	case 0:		//•ºŠí»‘¢‹Ç
		++Progress;
		while (Progress > 0 && powers[LocatedMission->IFF].NeedUnits[2] > 0)
		{
			for (auto& unit : units)
				if (unit.setUnit(LocatedMission->IFF, 2, LocatedMission->Position)) break;
			Progress -= 50;
			--powers[LocatedMission->IFF].NeedUnits[2];
		}
		while (Progress > 0 && powers[LocatedMission->IFF].NeedUnits[0] > 0)
		{
			for (auto& unit : units)
				if (unit.setUnit(LocatedMission->IFF, 3 * (RandomBool(0.7)), LocatedMission->Position)) break;
			Progress -= 80;
			--powers[LocatedMission->IFF].NeedUnits[0];
		}
		break;
	case 1:		//•¨Ž‘»‘¢‹Ç
		Fuel += 1.0;
		Supply += 1.0;
		if (Fuel > FuelMax) Fuel = FuelMax;
		if (Supply > SupplyMax) Supply = SupplyMax;
		break;
	default:
		break;
	}
}

