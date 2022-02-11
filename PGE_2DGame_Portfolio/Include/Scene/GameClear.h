#pragma once
#include "Scene.h"
class GameClear :
    public Scene
{
public:
	GameClear(Core* pEngine);
	virtual ~GameClear();

public:
	virtual void Update() override;
	virtual void Render() override;
};

