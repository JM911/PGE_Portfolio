#pragma once
#include "Tower.h"

class NormalTower :
    public Tower
{
public:
    NormalTower(Core* pEngine);
    virtual ~NormalTower();

public:
    void Setting(float range, float interval, olc::Pixel color = olc::WHITE);
    virtual void Update() override;
    virtual void Render() override;

    virtual void BulletRender() override;


    /* 공격 메커니즘 */

private:
    Bullet* _pBullet = nullptr;
    int _ATT = 0;

public:
    void CreateBullet();

    void Attack();
    void SetAttack(int att) { _ATT = att; }
};

