#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Facility : public Calculation
{
public:
	Facility() { Enabled = false; }

	void update();
	void draw() const;
	void reset();
	bool set(int iff, double x, double y, int type);
	void drawFacility() const;
	void updateFacility();
private:


	bool Enabled;
	Vec2 Position;
	int Type;
	int IFF;
	int Progress;
	double Supply;
	double Fuel;
	double SupplyMax;
	double FuelMax;

};