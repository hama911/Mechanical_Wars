#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

#define MAX_TURRET 10


class Unit : public Calculation
{
public:
	Unit(int IFF_p, int type,Vec2 position = Vec2(Random(1024), Random(1024)));
	~Unit();

	void update();	//‰Šú‰»
	void draw() const;	//•`‰æ

	void addDamege(double value);

	//‰Šú‰»
	void mountTurret();

	Vec2 getPosition() const;
	Vec2 getAngle() const;
	int getIFF() const;
	bool getEnabled() const;
	double getSpeedPerformance() const;
	int getMotionType() const;
	
	bool hitCheck(Vec2 pos);


private:
	//ŒÂ•Êƒf[ƒ^
	void setUnitData();
	void drawUnit() const;


	//ˆÚ“®Œn
	void moveForward(double length);	//‹——£
	void moveBack(double length);		//‹——£

	//‰ñ“]Œn
	void turnUpdate();	//Šp“x

	//UŒ‚Œn
	void shot();

	//§ŒÀ
	void limitMoving();

	//•Ï”
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetAngle;
	int IFF;	//¯•ÊƒR[ƒh
	double Health;	//‘Ï‹v

	//ŒÅ’è”’l
	double SpeedPerformance;	//‘¬“x«”\
	double TurningPerformance;	//ù‰ñ«”\
	double HealthPerformance;	//‘Ï‹v«”\
	int Type;

	Turret turrets[MAX_TURRET];

};
