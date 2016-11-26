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
	//ì«Ç›éÊÇÈínì_ÇÃç¿ïWÇdrawPosÇ∆Ç∑ÇÈ
	if (!Input::MouseL.pressed)drawPos += Mouse::Delta();
	zoom /= (Mouse::Wheel() / 20.0) + 1.0;
	drawPos *= ((zoom - targetZoom)*0.1 + targetZoom) / targetZoom;
	targetZoom += (zoom - targetZoom)*0.1;
}

Vec2 ConvertVec2ToVec2(Vec2 pos)
{
	return (pos*targetZoom - drawPos + Mouse::Pos());
	
}
Vec2 DisConvertVec2ToVec2(Vec2 pos)
{
	return (pos - Mouse::Pos() + drawPos) / targetZoom;
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

double getSoundVolume(Vec2 pos)
{
	double distance = Vec3(pos.x, pos.y, 0.0).distanceFrom(Vec3(DisConvertVec2ToVec2(Window::Size()/2).x, DisConvertVec2ToVec2(Mouse::Pos()).y, 500.0/getZoom()))*0.01;
	return 0.1 / (distance*distance);
}