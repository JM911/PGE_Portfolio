#pragma once
#include "Tower.h"

class MortarTower :
    public Tower
{
public:
    MortarTower(Core* pEngine);
    virtual ~MortarTower();

public:
    void Setting(float range, float interval, olc::Pixel color = olc::VERY_DARK_GREEN);
    virtual void Update() override;
    virtual void Render() override;

    virtual void BulletRender() override;



    /* 공격 메커니즘 */

private:
    int _cannonBallRad = 0;
    float _cannonBallSpeed = 0.f;
    float _aoeRange = 0.f;
    int _ATT = 0;

    bool _cannonEnable = false;
    float _cannonBallX = 0.f;
    float _cannonBallY = 0.f;

    float _targetX = 0.f;
    float _targetY = 0.f;

    bool _isAttacking = false;
    bool _isAttackRendering = false;
    float _timeTickforAOE = 0.f;

public:
    bool GetAttacking() { return _isAttacking; }
    float GetAOERange() { return _aoeRange; }
    int GetATT() { return _ATT; }

    float GetCannonX() { return _cannonBallX; }
    float GetCannonY() { return _cannonBallY; }

    void FinishAttacking() { _isAttacking = false; }

public:
    void CreateCannon();

    void Attack();
};

