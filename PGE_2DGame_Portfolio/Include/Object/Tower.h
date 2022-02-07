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


    
protected:
    bool _enable = false;
    int _gridX = 0;
    int _gridY = 0;
    float _range = 0.f;

    TOWER_TYPE _type = TOWER_TYPE::NORMAL;

    // TODO: 타겟(Enemy 포인터 타입) 변수 제작. (타겟 설정은 모든 타워와 모든 몹간의 거리를 계산해야 하므로 씬에서)
    
    // Get
public:
    bool GetEnable() const { return _enable; }
    //int GetGridX() const { return _gridX; }
    //int GetGridY() const { return _gridY; }
    float GetRange() const { return _range; }
    TOWER_TYPE GetType() const { return _type; }

    // Set
public:
    void SetEnable(bool enable) { _enable = enable; }
    //void SetGridX(int gridX) { _gridX = gridX; }
    //void SetGridY(int gridY) { _gridY = gridY; }
    void SetRange(float range) { _range = range; }



    // 공격 메커니즘 (공용)
protected:
    Enemy* _pTarget = nullptr;

    // Get
public:
    Enemy* GetTarget() const { return _pTarget; }

    // Set
public:
    void SetTarget(Enemy* pTarget) { _pTarget = pTarget; }
    bool CheckTargetInRange();
};

