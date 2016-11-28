#pragma once

#include <Siv3D.hpp>


class Turret;
class Unit;

class Bullet
{
public:

	void update();		//trueで消去
	void draw()	const;

	Bullet() { Enabled = false; }

	void reset();

	bool set(Turret* turret);


	//Get/Set関数
public:
	Vec2 getPosition() const { return Position; }
	int getType() const { return Type; }
	bool getEnabled() const { return Enabled; }
	void setCount(int count) { Count = count; }


private:
	//個別データ
	void setBulletData();
	void drawBullet() const;

	//内部関数
	Unit* serchEnemyUnit();	//索敵
	Unit* hitCheck();	//判定


	//変数
	bool Enabled;
	int IFF;
	Vec2 Position;
	Vec2 Angle;
	int Count;
	int Type;
	double SpeedPerformance;

};

