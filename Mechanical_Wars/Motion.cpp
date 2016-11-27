#include"Motion.h"
#include"Graphics.h"
#include"Bullet.h"
#include"Unit.h"

void Motion::update()
{
	if (Enabled)
	{
		++Count;
		Enabled = Count < 60;
	}
}

void Motion::draw() const
{
	if (Enabled)
	{
		switch (Type)
		{
		case 0:
			//Circle(ConvertVec2ToVec2(Position), (Count / 4 + 2) * getZoom()).draw(Color(255, 128, 0, 240 - Count * 12));
			TextureAsset(L"Effect2")((Count) * 32, 0, 32, 32).resize(16 * getZoom(), 16 * getZoom()).draw(ConvertVec2ToPoint(Position - Vec2(8.0, 8.0)));
			break;
		case 1:
			//Circle(ConvertVec2ToVec2(Position), (Count + 8) * getZoom()).draw(Color(255, 128, 0, 240 - Count * 12));
			TextureAsset(L"Effect1")((Count) * 64, 0,64, 64).resize(32 * getZoom(), 32 * getZoom()).draw(ConvertVec2ToPoint(Position - Vec2(16.0, 16.0)));
			break;
		case 3:
			TextureAsset(L"Effect1")((Count) * 64, 0, 64, 64).resize(64 * getZoom(), 64 * getZoom()).draw(ConvertVec2ToPoint(Position - Vec2(32.0, 32.0)));
			break;
		case 4:
			TextureAsset(L"Effect1")((Count) * 64, 0, 64, 64).resize(128 * getZoom(), 128 * getZoom()).draw(ConvertVec2ToPoint(Position - Vec2(64.0, 64.0)));

			break;
		default:
			break;
		}
	}
}

bool Motion::getEnabled() const
{
	return Enabled;
}

Motion::Motion(Bullet* bullet)
{
	Enabled = true;
	Count = 0;
	Position = bullet->getPosition();
	Type = bullet->getType();
	if (Type == 2) Type = 0;
	if (Type == 1) SoundAsset(L"explosive2").playMulti(getSoundVolume(Position) * 10);
	else SoundAsset(L"explosive1").playMulti(getSoundVolume(Position));
}

Motion::~Motion()
{
}


Motion::Motion(Unit* unit)
{
	Enabled = true;
	Count = 0;
	Position = unit->getPosition();
	Type = unit->getMotionType();
	if (Type == 2) Type = 0;
	if (Type == 1 || Type == 3 || Type == 4 ) SoundAsset(L"explosive2").playMulti(getSoundVolume(Position) * 10);
	else SoundAsset(L"explosive1").playMulti(getSoundVolume(Position));
}