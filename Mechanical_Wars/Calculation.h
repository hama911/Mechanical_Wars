#pragma once

#include<Siv3D.hpp>

class Calculation
{
public:
	double Vec2ToRadian(Vec2 pos) const;
	Vec2 calculateDeviation(Vec2 pos1, Vec2 pos2, double v1, Vec2 v2);	//ë¨ìxv2Ç≈ìÆÇ≠pos2Ç…pos1Ç©ÇÁë≈ÇøèoÇµÇΩë¨ìxv1ÇÃÇ‡ÇÃÇñΩíÜÇ≥ÇπÇÈ
	double calculateCollisionTime(Vec2 pos1, Vec2 pos2, double v1, Vec2 v2);
private:

};