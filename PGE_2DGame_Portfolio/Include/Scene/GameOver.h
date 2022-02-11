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
	SCENE_MENU _menu = START;
};

