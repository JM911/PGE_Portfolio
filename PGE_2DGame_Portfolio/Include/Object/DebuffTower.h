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




    /* ���� ��Ŀ���� */

private:
    bool _attEnable = false;
    float _curRadius = 0.f;
    float _attSpeed = 150.f;

    float _slowRate = 0.3f;     // �̼� 30% ���� (=��� �̼��� 70%)
    float _debuffDuration = 2.f;    // ����� ���ӽð�
    // => �� �� ��Ҵ� �����ϸ� �������� ����

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

