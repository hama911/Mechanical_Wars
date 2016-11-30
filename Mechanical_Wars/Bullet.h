#pragma once

#include <Siv3D.hpp>


class Turret;
class Unit;

class Bullet
{
public:

	void update();		//true‚ÅÁ‹
	void draw()	const;

	Bullet() { Enabled = false; }

	void reset();

	bool set(Turret* turret);




public:
	//ŒÂ•Êƒf[ƒ^
	void setBulletData();
	void drawBullet() const;

	//“à•”ŠÖ”
	Unit* serchEnemyUnit();	//õ“G
	Unit* hitCheck();	//”»’è


	//•Ï”
	bool Enabled;
	int IFF;
	Vec2 Position;
	Vec2 Angle;
	int Count;
	int Type;
	double SpeedPerformance;

};

