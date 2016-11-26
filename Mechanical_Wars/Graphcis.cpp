#include"Graphics.h"

double zoom;
double targetZoom;
Vec2 drawPos;


void drawInit()
{
	zoom = 1.0;
	targetZoom = 1.0;
	drawPos = Mouse::Pos();
}

void drawUpdate()
{
	//読み取る地点の座標をdrawPosとする
	if (!Input::MouseL.pressed)drawPos += Mouse::Delta();
	zoom /= (Mouse::Wheel() / 20.0) + 1.0;
	drawPos *= ((zoom - targetZoom)*0.1 + targetZoom) / targetZoom;
	targetZoom += (zoom - targetZoom)*0.1;
}

Vec2 ConvertVec2ToVec2(Vec2 pos)
{
	return (pos*targetZoom - drawPos + Mouse::Pos());
	
}

Point ConvertVec2ToPoint(Vec2 pos)
{
	pos = (pos*targetZoom - drawPos + Mouse::Pos());
	return{ int(pos.x), int(pos.y) };
}

double getZoom()
{
	return targetZoom;
}