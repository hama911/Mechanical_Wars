#pragma once
#include<Siv3D.hpp>

class Unit;
class Bullet;

class Motion
{
public:

	void update();
	void draw() const;

	bool getEnabled() const;

	void reset();

	Motion() { Enabled = false; }

	bool setFromBullet(Bullet* bullet);

	bool setFromUnit(Unit* unit);

private:
	bool Enabled;
	int Count;
	Vec2 Position;
	int Type;
};