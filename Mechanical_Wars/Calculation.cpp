#include"Calculation.h"

double Calculation::Vec2ToRadian(Vec2 pos) const
{
	return Atan2(pos.y, pos.x);
}