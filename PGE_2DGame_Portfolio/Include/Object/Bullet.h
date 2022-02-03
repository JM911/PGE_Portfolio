#pragma once
#include "Obj.h"

class Enemy;

class Bullet :
    public Obj
{
public:
    Bullet(Core* pEngine);
    virtual ~Bullet();

public:
    void Create(float x, float y, Enemy* pTarget);
    void Setting(int size, float speed, int att, olc::Pixel color = olc::BLACK);
    virtual void Update() override;
    virtual void Render() override;



protected:
    float _dirX = 0.f;
    float _dirY = 0.f;
    float _speed = 0.f;
    int _ATT = 0;

    bool _enable = false;

    Enemy* _pTarget = nullptr;

    // Get
public:
    float GetSpeed() const { return _speed; }
    int GetATT() const { return _ATT; }
    Enemy* GetTarget() const { return _pTarget; }
    bool GetEnable() const { return _enable; }

    // Set
public:
    void SetSpeed(float speed) { _speed = speed; }
    void SetATT(int att) { _ATT = att; }
    void SetTarget(Enemy* pTarget) { _pTarget = pTarget; }
    void SetEnable(bool enable) { _enable = enable; }




};