#pragma once

#include <Siv3D.hpp>


class Turret;
class Unit;

class Bullet
{
public:

	void update();		//true�ŏ���
	void draw()	const;

	//�����f�[�^�ɃA�N�Z�X
	Vec2 getPosition() const;
	int getType() const;
	bool getEnabled() const;

	Bullet(Turret* turret);
	~Bullet();

private:

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

