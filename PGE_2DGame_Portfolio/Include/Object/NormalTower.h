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




    /* ���� ��Ŀ���� */

private:
    Bullet* _pBullet = nullptr;

    // Get
public:
    //Bullet* GetBullet() const { return _pBullet; }
    float GetInterval() const { return _interval; }

    // Set
public:
    void SetInterval(float interval) { _interval = interval; }

public:
    void CreateBullet();

    void Attack();
};

