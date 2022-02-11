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
	SCENE_MENU _menu = START;
};

