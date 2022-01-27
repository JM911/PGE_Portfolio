#pragma once
#include "Scene.h"
#include "../pch.h"

#define ENEMY_NUM 10

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

    Enemy* _pArrEnemy[ENEMY_NUM] = { nullptr, };


    // 웨이브 스폰 메커니즘 (나중에 Wave 클래스로 변경)
public:
    float _spawnTimeTick = 0.f;
    float _spawnInterval = 0.f;
    int _spawnIndex = 0;

    void SpawnWave(float elapsedTime);



    // 공격 받는 메커니즘
public:
    int _playerHP = 0;
    float _finalX = 0.f;
    float _finalY = 0.f;

public:
    void CheckEnemyReach(Enemy* pEnemy);
};

