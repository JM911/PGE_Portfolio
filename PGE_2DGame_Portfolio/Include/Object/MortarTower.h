#pragma once
#include "Tower.h"

class MortarTower :
    public Tower
{
public:
    MortarTower(Core* pEngine);
    virtual ~MortarTower();

public:
    void Setting(float range, float interval, olc::Pixel color = olc::BLUE);
    virtual void Update() override;
    virtual void Render() override;
};

