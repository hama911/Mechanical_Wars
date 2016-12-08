#pragma once
#include<Siv3D.hpp>


//パワーを管理するシステム。
//１つのIFFに対し１つのパワーが用意される
class Power
{
public:
	Power(int iff) { IFF = iff; Enabled = false; }
	void update();
	void draw() const;
	void FindNeedUnits();
public:
	bool FreeMission;
	int NeedUnits[3];
	int IFF;
	bool Enabled = true;
};