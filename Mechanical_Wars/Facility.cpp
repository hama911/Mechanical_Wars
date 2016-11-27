#include"Facility.h"

Facility::Facility(Vec2 position,int IFF_p,int type)
{
	Enabled = true;
	Position = position;
	Type = type;
	IFF = IFF_p;
	Progress = 0;
}

Facility::~Facility()
{
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