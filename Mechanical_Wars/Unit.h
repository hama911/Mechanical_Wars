#pragma once

# include <Siv3D.hpp>
#include"Turret.h"

class Unit
{
public:
	Unit();
	Unit(int IFF_p);
	~Unit();

	bool update();	//������
	void draw() const;	//�`��

	void addDamege(double value);

	//������
	void mountTurret();

	Vec2 getPosition();
	Vec2 getAngle();
	int getIFF();
	double getSpeedPerformance();


private:

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
	int Heat;	//�ˌ��N�[���_�E��
	Vec2 Position;
	Vec2 Angle;
	Vec2 TargetAngle;
	int IFF;	//���ʃR�[�h
	double Health;	//�̗�

	//�Œ萔�l
	double SpeedPerformance;	//���x���\
	double TurningPerformance;	//���񐫔\

	Array<Turret> turrets;

};
