#pragma once
#include<Siv3D.hpp>
#include"Bullet.h"

class Motion
{
public:

	void update();
	void draw() const;

	bool getEnabled() const;

	Motion(Bullet* bullet);
	~Motion();

private:
	bool Enabled;
	int Count;
	Vec2 Position;
	int Type;
};