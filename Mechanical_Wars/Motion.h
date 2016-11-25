#pragma once
#include<Siv3D.hpp>
#include"Bullet.h"

class Motion
{
public:

	bool update();
	void draw() const;

	Motion(Bullet* bullet);
	~Motion();

private:
	int Count;
	Vec2 Position;

};