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
    Enemy** GetEnemyArr() { return _pEnemy; }   // �̷��� ���� �Ǵ���?


    // Enemy ���� ���� ��Ŀ����
private:
    float _timeTickforStart = 0.f;
    float _timeTickforNext = 0.f;
    int _curEnemyIdx = 0;

    void SpawnEnemy();



    // �� ���� ��Ŀ����
public:
    int CheckReachedEnemy(int finalGridX, int finalGridY);
    // Enemy ���� �� �ش� enemy ���� + �ϳ��� ������ true ��ȯ
    // => �̷��� �ϸ� ���ÿ� �� �̻� ������ �� ���װ���... �ϴ��� �Ű�X


    // ��� �� �׾����� üũ
public:
    bool IsAllEnemyDead();
};

