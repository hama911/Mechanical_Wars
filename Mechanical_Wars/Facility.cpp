#include"Facility.h"


void Facility::reset()
{
	Enabled = false;
	Position = Vec2(0, 0);
	Type = 0;
	IFF = 0;
	Progress = 0;
	Supply = 0;
	Fuel = 0;
	SupplyMax = 0;
	FuelMax = 0;
}

bool Facility::set(int iff, double x, double y, int type)
{
	if (Enabled) return false;
	Enabled = true;
	Position = Vec2(x, y);
	Type = type;
	IFF = iff;
	Supply = 0;
	Fuel = 0;
	Progress = 0;
	switch (Type)
	{
	case 0:
		break;
	case 1:
		SupplyMax = 100;
		FuelMax = 100;
		break;
	default:
		break;
	}
	return true;
}

void Facility::update()
{
	if (!Enabled) return;
	updateFacility();
}
void Facility::draw() const
{
	if (!Enabled) return;
	drawFacility();
}