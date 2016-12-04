#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Mission;
class Facility : public Calculation
{
public:
	Facility() { Enabled = false; }

	void update();
	void draw() const;
	void reset();
	bool set(Mission *mission, int type);
	void drawFacility() const;
	void updateFacility();
public:


	bool Enabled;
	Mission* LocatedMission;
	int Type;
	int Progress;
	double Supply;
	double Fuel;
	double SupplyMax;
	double FuelMax;

};