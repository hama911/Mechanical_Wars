#pragma once

#include <Siv3D.hpp>


class Turret;
class Unit;

class Bullet
{
public:

	bool update();		//true�ŏ���
	void draw()	const;

	//�����f�[�^�ɃA�N�Z�X
	Vec2 getPosition();
	int getType();

	Bullet(Turret* turret);
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
	int Type;
};

