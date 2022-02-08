#pragma once
#include "Tower.h"

class BurstTower :
    public Tower
{
public:
    BurstTower(Core* pEngine);
    virtual ~BurstTower();

public:
    void Setting(int maxBurstNum, float range, float interval, olc::Pixel color = olc::YELLOW);
    virtual void Update() override;
    virtual void Render() override;




    /* 공격 메커니즘 */

private:
    Bullet* _pBullet[MAX_BULLET_NUM] = { nullptr };

    int _curIdx = 0;
    int _maxBurstNum = 0;           // 연사 1주기 총알 개수
    float _burstInterval = 0.1f;    // 연사 중 총알 발사 간격

    // Get
public:
    float GetInterval() const { return _interval; }

    // Set
public:
    void SetInterval(float interval) { _interval = interval; }

public:
    void CreateBullet();

    void Attack();
};

