#pragma once

#include<Siv3D.hpp>

class Calculation
{
public:
	double Vec2ToRadian(Vec2 pos) const;
	Vec2 calculateDeviation(Vec2 pos1, Vec2 pos2, double v1, Vec2 v2);
	double calculateCollisionTime(Vec2 pos1, Vec2 pos2, double v1, Vec2 v2);
private:

};