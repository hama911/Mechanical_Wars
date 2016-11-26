#pragma once

#include <Siv3D.hpp>


class Turret;
class Unit;

class Bullet
{
public:

	void update();		//trueで消去
	void draw()	const;

	//内部データにアクセス
	Vec2 getPosition() const;
	int getType() const;
	bool getEnabled() const;

	Bullet(Turret* turret);
	~Bullet();

private:

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

