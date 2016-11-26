#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

#define MAX_TURRET 10


class Unit : public Calculation
{
public:
	Unit(int IFF_p,int type);
	~Unit();

	void update();	//������
	void draw() const;	//�`��

	void addDamege(double value);

	//������
	void mountTurret();

	Vec2 getPosition() const;
	Vec2 getAngle() const;
	int getIFF() const;
	bool getEnabled() const;
	double getSpeedPerformance() const;


private:
	//�ʃf�[�^
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

	//�ϐ�
	bool Enabled;
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetAngle;
	int IFF;	//���ʃR�[�h
	double Health;	//�ϋv

	//�Œ萔�l
	double SpeedPerformance;	//���x���\
	double TurningPerformance;	//���񐫔\
	double HealthPerformance;	//�ϋv���\
	int Type;

	Turret turrets[MAX_TURRET];

};
