#pragma once
#include "Scene.h"

class Tile;

class TestScene :
    public Scene
{
public:
    TestScene();
    virtual ~TestScene();

public:
    virtual void Update(class Core* pEngine) override;

    // Test
public:
    Tile* testTile = nullptr;
};

