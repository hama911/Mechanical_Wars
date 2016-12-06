#include"Motion.h"
#include"Graphics.h"
#include"Bullet.h"
#include"Unit.h"

void Motion::update()
{
	if (!Enabled) return;
	switch (Type)
	{
	case 5:
		--Count;
		if (Count < 0) Enabled = false;
		break;
	default:
		++Count;
		Enabled = Count < 60;
		break;
	}
}

void Motion::draw() const
{
	if (Enabled)
	{
		switch (Type)
		{
		case 0:
			TextureAsset(L"Effect2")((Count) * 32, 0, 32, 32).resize(16 * getZoom(), 16 * getZoom()).draw(ConvertVec2ToPoint(Position - Vec2(8.0, 8.0)));
			break;
		case 1:
			TextureAsset(L"Effect1")((Count) * 64, 0, 64, 64).resize(32 * getZoom(), 32 * getZoom()).draw(ConvertVec2ToPoint(Position - Vec2(16.0, 16.0)));
			break;
		case 3:
			TextureAsset(L"Effect1")((Count) * 64, 0, 64, 64).resize(64 * getZoom(), 64 * getZoom()).draw(ConvertVec2ToPoint(Position - Vec2(32.0, 32.0)));
			break;
		case 4:
			TextureAsset(L"Effect1")((Count) * 64, 0, 64, 64).resize(128 * getZoom(), 128 * getZoom()).draw(ConvertVec2ToPoint(Position - Vec2(64.0, 64.0)));
			break;
		case 5:
			Line(ConvertVec2ToVec2(Position), ConvertVec2ToVec2(Position2)).draw(1 * getZoom(), Color(255, 255, 255, Count));
			break;
		default:
			break;
		}
	}
}


bool Motion::setFromBullet(Bullet* bullet)
{
	if (Enabled) return false;
	Enabled = true;
	Count = 0;
	Position = bullet->Position;
	Type = bullet->Type;
	switch (Type)
	{
	case 0:
		SoundAsset(L"explosive1").playMulti(getSoundVolume(Position));
		break;
	case 1:
		SoundAsset(L"explosive2").playMulti(getSoundVolume(Position) * 10);
		break;
	case 2:
		Type = 0;
		SoundAsset(L"explosive1").playMulti(getSoundVolume(Position));
		break;
	case 3:
		Enabled = false;
		break;
	default:
		break;
	}
	return true;
}

bool Motion::setFromBulletLine(Vec2 pos1, Vec2 pos2)
{
	if (Enabled) return false;
	Enabled = true;
	Count = 64;
	Position = pos1;
	Position2 = pos2;
	Type = 5;
	return true;
}



bool Motion::setFromUnit(Unit* unit)
{
	if (Enabled) return false;
	Enabled = true;
	Count = 0;
	Position = unit->Position;
	Type = unit->getMotionType();
	switch (Type)
	{
	case 1:
		SoundAsset(L"explosive2").playMulti(getSoundVolume(Position) * 10);
		break;
	case 2:
		SoundAsset(L"explosive2").playMulti(getSoundVolume(Position) * 10);
		break;
	case 3:
		SoundAsset(L"explosive2").playMulti(getSoundVolume(Position) * 10);
		break;
	default:
		Enabled = false;
		break;
	}
	return true;
}

void Motion::reset()
{
	Enabled = false;
	Count = 0;
	Position = Vec2(0, 0);
	Type = 0;
}