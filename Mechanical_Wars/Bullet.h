#pragma once

#include <Siv3D.hpp>


class Turret;
class Unit;

class Bullet
{
public:

	bool update();		//trueで消去
	void draw()	const;

	//内部データにアクセス
	Vec2 getPosition();
	int getType();

	Bullet(Turret* turret);
	~Bullet();

private:

	//内部関数
	Unit* serchEnemyUnit();	//索敵
	Unit* hitCheck();	//判定


	//変数
	int IFF;
	Vec2 Position;
	Vec2 Angle;
	int Count;
	int Type;
};

