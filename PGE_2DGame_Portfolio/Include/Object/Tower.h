#pragma once
#include "Obj.h"

class Bullet;
class Enemy;

class Tower :
    public Obj
{
public:
    Tower(Core* pEngine);
    virtual ~Tower();

public:
    bool Create(int gridX, int gridY);
    virtual void Update() override;
    virtual void Render() override;


    
protected:
    bool _enable = false;
    int _gridX = 0;
    int _gridY = 0;
    float _range = 0.f;

    TOWER_TYPE _type = TOWER_TYPE::NORMAL;

    // TODO: Ÿ��(Enemy ������ Ÿ��) ���� ����. (Ÿ�� ������ ��� Ÿ���� ��� ������ �Ÿ��� ����ؾ� �ϹǷ� ������)
    
    // Get
public:
    bool GetEnable() const { return _enable; }
    //int GetGridX() const { return _gridX; }
    //int GetGridY() const { return _gridY; }
    float GetRange() const { return _range; }
    TOWER_TYPE GetType() const { return _type; }

    // Set
public:
    void SetEnable(bool enable) { _enable = enable; }
    //void SetGridX(int gridX) { _gridX = gridX; }
    //void SetGridY(int gridY) { _gridY = gridY; }
    void SetRange(float range) { _range = range; }



    // ���� ��Ŀ���� (����)
protected:
    Enemy* _pTarget = nullptr;

    // Get
public:
    Enemy* GetTarget() const { return _pTarget; }

    // Set
public:
    void SetTarget(Enemy* pTarget) { _pTarget = pTarget; }
    bool CheckTargetInRange();
};

