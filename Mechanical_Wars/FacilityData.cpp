#include"Facility.h"
#include"Graphics.h"
#include"Unit.h"

extern Array<Unit> units;

void Facility::setFacilityData()
{
	switch (Type)
	{
	default:
		break;
	}
}

void Facility::drawFacility() const
{
	switch (Type)
	{
	case 0:		//•ºŠí»‘¢‹Ç
		Rect(ConvertVec2ToPoint(Position), Size(64*getZoom(), 64*getZoom())).draw(Palette::White);
		break;
	default:
		break;
	}
}

void Facility::updateFacility()
{
	switch (Type)
	{
	case 0:		//•ºŠí»‘¢‹Ç
		++Progress;
		if (Progress > 100)
		{
			for (auto& unit : units)
			{
				if (!unit.getEnabled())
				{

					unit.resetUnit(IFF, 0, Position);
					break;
				}
			}
			Progress = 0;
		}
		break;
	default:
		break;
	}
}