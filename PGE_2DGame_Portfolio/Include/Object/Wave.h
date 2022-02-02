#pragma once
#include "Obj.h"

class Enemy;

class Wave :
    public Obj
{
public:
    Wave(Core* pEngine);
    virtual ~Wave();

public:
    bool Create(int enemyNum,  float spawnStartTime, float spawnInterval);
    bool EnemyCreate(int spawnGridX, int spawnGridY, int size,
        int hp, int att, float speed, olc::Pixel color = olc::RED);
    virtual void Update() override;
    virtual void Render() override;


private:
    Enemy* _pEnemy[MAX_ENEMY_NUM] = { nullptr };
    int _enemyNum = 0;

    //int _spawnGridX = 0;
    //int _spawnGridY = 0;
    float _spawnStartTime = 0.f;
    float _spawnInterval = 0.f;

    bool _enable = false;

public:
    int GetEnemyNum() const { return _enemyNum; }
    bool GetEnable() const { return _enable; }

    void SetEnable(bool enable) { _enable = enable; }

public:
    void EnemyClear();
    void ChangeWaveDirAt(int gridX, int gridY, DIRECTION dir);
    Enemy** GetEnemyArr() { return _pEnemy; }   // 이렇게 쓰면 되는지?


    // Enemy 순차 생성 메커니즘
private:
    float _timeTickforStart = 0.f;
    float _timeTickforNext = 0.f;
    int _curEnemyIdx = 0;

    void SpawnEnemy();



    // 적 공격 메커니즘
public:
    int CheckReachedEnemy(int finalGridX, int finalGridY);
    // Enemy 도착 시 해당 enemy 죽음 + 하나라도 죽으면 true 반환
    // => 이렇게 하면 동시에 둘 이상 도착할 때 버그가능... 일단은 신경X


    // 모든 적 죽었는지 체크
public:
    bool IsAllEnemyDead();
};

