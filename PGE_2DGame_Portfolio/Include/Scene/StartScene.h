#pragma once
#include "Scene.h"

class StartScene :
    public Scene
{
public:
	StartScene(Core* pEngine);
	virtual ~StartScene();

public:
	virtual void Update() override;
	virtual void Render() override;

private:
	SCENE_MENU _menu = SCENE_MENU::START;

	int _cursorX = 200;
	int _cursorY = 202;

	// deco
private:
	float _cirX[10] = { 0.f, };
	float _cirY[10] = { 0.f, };

	int _cirSize[10] = { 0, };
	float _cirSpeed[10] = { 0.f, };
	olc::Pixel _cirColor[10] = { olc::WHITE, };

	int _curCirIdx = 0;

	float _timeTick = 0.f;
	float _interval = 0.f;

	void CreateRandomCircle();
	void UpdateRandomCircle();
	void RenderRandomCircle();
};

