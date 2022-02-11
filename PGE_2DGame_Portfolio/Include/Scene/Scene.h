#pragma once
#include "../pch.h"

class Core;

class Scene
{
public:
	Scene(Core* pEngine);
	virtual ~Scene();

public:
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	Core* _pEngine;
};
