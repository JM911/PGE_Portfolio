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

public:
	void SetScene(Scene* pScene);
	void ReleaseScene();
};

