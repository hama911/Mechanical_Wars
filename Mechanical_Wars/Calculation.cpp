#include"Calculation.h"

double Calculation::Vec2ToRadian(Vec2 pos) const
{
	return Atan2(pos.y, pos.x);
}

Vec2 Calculation::calculateDeviation(Vec2 pos1, Vec2 pos2, double v1, Vec2 v2)
{
	return (pos2 + v2*calculateCollisionTime(pos1, pos2, v1, v2) - pos1).normalized();
}

double Calculation::calculateCollisionTime(Vec2 pos1, Vec2 pos2, double v1, Vec2 v2)
{
	if (v2.length() == 0) return pos2.distanceFrom(pos1) / v1;
	const double cosA = (pos1 - pos2).dot(v2) / ((pos1 - pos2).length()*v2.length());
	const double a = v1;
	const double b = v2.length();
	Println((pos1 - pos2).length() / ((2 * b*cosA + sqrt(4 * b*b*cosA*cosA - 4 * (b*b - a*a))) / 2));
	return (pos1 - pos2).length()/((2 * b*cosA + sqrt(4 * b*b*cosA*cosA - 4 * (b*b - a*a))) / 2);
}

