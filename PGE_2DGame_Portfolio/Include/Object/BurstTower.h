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




    /* ���� ��Ŀ���� */

private:
    Bullet* _pBullet[MAX_BULLET_NUM] = { nullptr };

    int _curIdx = 0;
    int _maxBurstNum = 0;           // ���� 1�ֱ� �Ѿ� ����
    float _burstInterval = 0.1f;    // ���� �� �Ѿ� �߻� ����

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

