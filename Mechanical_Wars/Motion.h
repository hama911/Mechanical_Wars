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

	Motion(Bullet* bullet);
	Motion(Unit* unit);
	~Motion();

private:
	bool Enabled;
	int Count;
	Vec2 Position;
	int Type;
};