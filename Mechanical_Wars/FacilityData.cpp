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
	case 0:		//���퐻����
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
	case 0:		//���퐻����
		++Progress;
		if (Progress > 100)
		{
			units.push_back(Unit(IFF, 0, Position));
			Progress = 0;
		}
		break;
	default:
		break;
	}
}