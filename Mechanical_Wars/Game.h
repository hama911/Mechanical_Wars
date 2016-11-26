#pragma once

#include"Main.h"


class Game : public MyApp::Scene
{
public:

	void update() override;

	void draw() const override;

	void init() override;	//‰Šú‰»

	void updateFadeIn(double) override;

	void refreshArray();

private:

};