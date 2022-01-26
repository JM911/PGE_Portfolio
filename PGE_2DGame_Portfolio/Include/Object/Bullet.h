#pragma once
#include "Obj.h"

class Enemy;

class Bullet :
    public Obj
{
public:
    Bullet();
    virtual ~Bullet();

public:
    virtual void Update(Core* pEngine) override;
    virtual void Render(Core* pEngine) override;



protected:
    float _dirX = 0.f;
    float _dirY = 0.f;
    float _speed = 0.f;
    float _ATT = 0.f;

    bool _enable = false;

    Enemy* _pTarget = nullptr;

public:
    Enemy* GetTarget() const { return _pTarget; }
    bool GetEnable() const { return _enable; }

public:
    void SetTarget(Enemy* pTarget) { _pTarget = pTarget; }
    void SetEnable(bool enable) { _enable = enable; }
};

