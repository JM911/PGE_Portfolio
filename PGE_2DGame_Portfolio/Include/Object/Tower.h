#pragma once
#include "Obj.h"

class Bullet;
class Enemy;

class Tower :
    public Obj
{
public:
    Tower(Core* pEngine);
    virtual ~Tower();

public:
    bool Create(int gridX, int gridY);
    virtual void Update() override;
    virtual void Render() override;

    virtual void BulletRender() = 0;


    
protected:
    bool _enable = false;
    int _gridX = 0;
    int _gridY = 0;

    TOWER_TYPE _type = TOWER_TYPE::NORMAL;

    // Get
public:
    bool GetEnable() const { return _enable; }
    TOWER_TYPE GetType() const { return _type; }

    // Set
public:
    void SetEnable(bool enable) { _enable = enable; }



    // 공격 메커니즘 (공용)
protected:
    Enemy* _pTarget = nullptr;
    float _range = 0.f;

    float _timeTick = 0.f;
    float _interval = 100.f;

    // Get
public:
    Enemy* GetTarget() const { return _pTarget; }
    float GetRange() const { return _range; }
    float GetInterval() const { return _interval; }

    // Set
public:
    void SetTarget(Enemy* pTarget) { _pTarget = pTarget; }
    void SetRange(float range) { _range = range; }
    void SetInterval(float interval) { _interval = interval; }

    void TimeTickInc();
    bool CheckTargetInRange();
};

