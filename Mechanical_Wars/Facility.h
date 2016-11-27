#pragma once
#include<Siv3D.hpp>
#include"Calculation.h"

class Facility : public Calculation
{
public:
	Facility(Vec2 facility,int IFF_p,int type);
	~Facility();

	void update();
	void draw() const;

	void setFacilityData();
	void drawFacility() const;
	void updateFacility();
private:


	bool Enabled;
	Vec2 Position;
	int Type;
	int IFF;

	int Progress;

};