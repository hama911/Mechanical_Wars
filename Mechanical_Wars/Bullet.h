#pragma once

#include <Siv3D.hpp>


class Turret;
class Unit;

class Bullet
{
public:

	void update();		//true�ŏ���
	void draw()	const;

	Bullet() { Enabled = false; }

	void reset();

	bool set(Turret* turret);




public:
	//�ʃf�[�^
	void setBulletData();
	void drawBullet() const;

	//�����֐�
	Unit* serchEnemyUnit();	//���G
	Unit* hitCheck();	//����


	//�ϐ�
	bool Enabled;
	int IFF;
	Vec2 Position;
	Vec2 Angle;
	int Count;
	int Type;
	double SpeedPerformance;

};

