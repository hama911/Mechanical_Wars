#include"Facility.h"
#include"Power.h"
#include"Mission.h"

extern Array<Power> powers;

void Facility::reset()
{
	Enabled = false;
	Type = 0;
	Progress = 0;
	Supply = 0;
	Fuel = 0;
	SupplyMax = 0;
	FuelMax = 0;
	LocatedMission = NULL;
}

bool Facility::set(Mission *mission, int type)
{
	if (Enabled) return false;
	Enabled = true;
	Type = type;
	LocatedMission = mission;
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
	if (!Enabled || !powers[LocatedMission->IFF].Enabled) return;
	updateFacility();
}
void Facility::draw() const
{
	if (!Enabled) return;
	drawFacility();
}