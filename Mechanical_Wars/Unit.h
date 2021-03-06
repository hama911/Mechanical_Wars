#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

#define MAX_TURRET 10

class Platoon;

class Unit : public Calculation
{
public:
	Unit() { Enabled = false; }


	void update();	//������
	void draw() const;	//�`��

	void addDamege(double value);

	//������
	void mountTurret();

	void updatePlatoon();

	bool setUnit(int IFF_p, int type, Vec2 position = Vec2(Random(1024), Random(1024)));
	void reset();


	bool hitCheck(Vec2 pos);


public:	//�����f�[�^�ɃA�N�Z�X
	int getMotionType() const;

public:
	//�ʃf�[�^
	void updateUnit();
	void setUnitData();
	void drawUnit() const;


	//�ړ��n
	void moveForward(double length);	//����
	void moveBack(double length);		//����

	//��]�n
	void turnUpdate();	//�p�x

	//�U���n
	void shot();

	//����
	void limitMoving();

public:
	//�ϐ�
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetAngle;
	int IFF;	//���ʃR�[�h
	double Health;	//�ϋv
	double Speed;	//���݂̃X�s�[�h

	Platoon* MyPlatoon;

	//�Œ萔�l
	double SpeedPerformance;	//���x���\
	double TurningPerformance;	//���񐫔\
	double HealthPerformance;	//�ϋv���\
	int Type;

	//�⋋
	double Supply;	//�⋋��
	double Fuel;	//�R��
	double SupplyMax;
	double FuelMax;

	Turret turrets[MAX_TURRET];

};
