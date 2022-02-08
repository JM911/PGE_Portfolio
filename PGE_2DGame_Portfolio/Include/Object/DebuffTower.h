#pragma once
#include "Tower.h"

class DebuffTower :
    public Tower
{
public:
    DebuffTower(Core* pEngine);
    virtual ~DebuffTower();

public:
    void Setting(float range, float interval, olc::Pixel color = olc::BLUE);
    virtual void Update() override;
    virtual void Render() override;




    /* 공격 메커니즘 */

private:
    bool _attEnable = false;
    float _curRadius = 0.f;
    float _attSpeed = 150.f;

    float _slowRate = 0.3f;     // 이속 30% 감소 (=평소 이속의 70%)
    float _debuffDuration = 2.f;    // 디버프 지속시간
    // => 위 두 요소는 여차하면 세팅으로 넣자

public:
    bool GetAttEnable() const { return _attEnable; }
    float GetRadius() const { return _curRadius; }
    
    float GetSlowRate() const { return _slowRate; }
    float GetDuration() const { return _debuffDuration; }

public:
    void SetAttEnable(bool enable) { _attEnable = enable; }
        
private:
    void Attack();
};

