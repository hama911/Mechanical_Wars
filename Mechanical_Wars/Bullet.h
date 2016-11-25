#pragma once

#include <Siv3D.hpp>

#include"Unit.h"
#include"Turret.h"



class Bullet
{
public:

	bool update();		//true�ŏ���
	void draw()	const;

	//�����f�[�^�ɃA�N�Z�X
	Vec2 getPosition();

	Bullet();
	~Bullet();

private:

	//�����֐�
	Unit* serchEnemyUnit();	//���G
	Unit* hitCheck();	//����


	//�ϐ�
	int IFF;
	Vec2 Position;
	Vec2 Angle;
	int Count;
};

