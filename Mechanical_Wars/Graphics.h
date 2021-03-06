#pragma once

#include<Siv3D.hpp>

//描画位置変更を行う関数群
void drawInit();

void drawUpdate();

Vec2 ConvertVec2ToVec2(Vec2 pos);

Point ConvertVec2ToPoint(Vec2 pos);

Vec2 DisConvertVec2ToVec2(Vec2 pos);

double getSoundVolume(Vec2 pos);

double getZoom();