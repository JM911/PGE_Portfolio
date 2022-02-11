#pragma once
#include "pch.h"

class Scene;

class Core : public olc::PixelGameEngine
{
public:
	Core();
	~Core();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:
	Scene* _pScene = nullptr;
	Scene* _pNextScene = nullptr;

public:
	void SetScene(Scene* pScene);
	void SetNextScene(Scene* pScene) { _pNextScene = pScene; }


	// 게임 종료용
private:
	bool _bExit = false;

public:
	void Exit() { _bExit = true; }
};

