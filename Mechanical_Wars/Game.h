#pragma once

#include"Main.h"

#define GROUND_LIMIT_MIN_X 0
#define GROUND_LIMIT_MAX_X 2048
#define GROUND_LIMIT_MIN_Y 0
#define GROUND_LIMIT_MAX_Y 1024


class Game : public MyApp::Scene
{
public:

	void update() override;

	void draw() const override;

	void init() override;	//èâä˙âª

	void updateFadeIn(double) override;

	void refreshArray();


private:

	Texture ground;


};