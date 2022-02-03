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
    void Setting(int size, float range, float interval, olc::Pixel color = olc::WHITE);
    virtual void Update() override;
    virtual void Render() override;



    
private:
    bool _enable = false;
    int _gridX = 0;
    int _gridY = 0;

    float _range = 0.f;

    // TODO: 타겟(Enemy 포인터 타입) 변수 제작. (타겟 설정은 모든 타워와 모든 몹간의 거리를 계산해야 하므로 씬에서)
    
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



    /* 공격 메커니즘 */

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
    void TimeTickInc();
    void CreateBullet();

    bool CheckTargetInRange();
    void Attack();
};

