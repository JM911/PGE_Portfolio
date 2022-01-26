#pragma once
#include "Obj.h"

class Bullet;
class Enemy;

class Tower :
    public Obj
{
public:
    Tower(int gridX, int gridY);
    virtual ~Tower();

public:
    virtual void Update(Core* pEngine) override;
    virtual void Render(Core* pEngine) override;



    
private:
    bool _enable = false;
    int _gridX = 0;
    int _gridY = 0;

    float _range = 0.f;

    // TODO: Ÿ��(Enemy ������ Ÿ��) ���� ����. (Ÿ�� ������ ��� Ÿ���� ��� ������ �Ÿ��� ����ؾ� �ϹǷ� ������)
    
    // Get
public:
    bool GetEnable() const { return _enable; }
    int GetGridX() const { return _gridX; }
    int GetGridY() const { return _gridY; }
    float GetRange() const { return _range; }

    // Set
public:
    void SetEnable(bool enable) { _enable = enable; }
    void SetGridX(int gridX) { _gridX = gridX; }
    void SetGridY(int gridY) { _gridY = gridY; }
    void SetRange(float range) { _range = range; }



    /* ���� ��Ŀ���� */

private:
    Enemy* _pTarget = nullptr;
    Bullet* _pBullet = nullptr;

    float _timeTick = 0.f;
    float _interval = 100.f;

    // Get
public:
    Enemy* GetTarget() const { return _pTarget; }
    Bullet* GetBullet() const { return _pBullet; }
    float GetInterval() const { return _interval; }

    // Set
public:
    void SetTarget(Enemy* pTarget) { _pTarget = pTarget; }
    void SetInterval(float interval) { _interval = interval; }

public:
    void TimeTickInc(Core* pEngine);
    void CreateBullet();
    void ReleaseBullet();

    bool CheckTargetInRange();
    void Attack();
};

