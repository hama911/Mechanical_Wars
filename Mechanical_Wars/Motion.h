#pragma once
#include<Siv3D.hpp>

class Unit;
class Bullet;

class Motion
{
public:

	void update();
	void draw() const;

	void reset();

	Motion() { Enabled = false; }

	bool setFromBullet(Bullet* bullet);
	bool setFromBulletLine(Vec2 pos1, Vec2 pos2);
	bool setFromUnit(Unit* unit);

public:
	bool Enabled;
	int Count;
	Vec2 Position;
	Vec2 Position2;
	int Type;
};