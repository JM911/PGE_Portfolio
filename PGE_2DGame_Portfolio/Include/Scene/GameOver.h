#pragma once
#include "Scene.h"

class GameOver :
    public Scene
{
public:
	GameOver(Core* pEngine);
	virtual ~GameOver();

public:
	virtual void Update() override;
	virtual void Render() override;

private:
	SCENE_MENU _menu = SCENE_MENU::START;

	int _cursorX = 180;
	int _cursorY = 202;
};

