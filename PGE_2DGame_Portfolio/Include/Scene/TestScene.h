#pragma once
#include "Scene.h"
#include "../pch.h"

class Core;
class Map;
class Tower;
class Enemy;

class TestScene :
    public Scene
{
public:
    TestScene();
    virtual ~TestScene();

public:
    virtual void Update(Core* pEngine) override;
    virtual void Render(Core* pEngine) override;

    // Test
public:
    Map* _pTestMap = nullptr;
    int _curX = 0;
    int _curY = 0;
    int _curGridX = 0;
    int _curGridY = 0;

    Tower* _pTower[MAP_HEIGHT][MAP_WIDTH] = { nullptr, };

    Enemy* _pTestEnemy = nullptr;
};

