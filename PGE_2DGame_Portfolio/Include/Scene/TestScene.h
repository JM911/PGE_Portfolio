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


    // ���̺� ���� ��Ŀ���� (���߿� Wave Ŭ������ ����)
public:
    float _spawnTimeTick = 0.f;
    float _spawnInterval = 0.f;
    int _spawnIndex = 0;

    void SpawnWave(float elapsedTime);



    // ���� �޴� ��Ŀ����
public:
    int _playerHP = 0;
    float _finalX = 0.f;
    float _finalY = 0.f;

public:
    void CheckEnemyReach(Enemy* pEnemy);
};

