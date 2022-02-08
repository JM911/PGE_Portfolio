#pragma once
#include "Obj.h"

// 방향전환, 소멸판정은 모두 씬에서

class Bullet;
class InGameScene;

class Enemy :
    public Obj
{
public:
    Enemy(Core* pEngine, InGameScene* pScene);
    virtual ~Enemy();

public:
    bool Create(int genGridX, int genGridY, int size, int hp, int att, 
        float speed, int reward, olc::Pixel color = olc::RED);
    virtual void Update() override;
    virtual void Render() override;



private:
    InGameScene* _pScene = nullptr;

    int _genGridX = 0;      // 생성위치
    int _genGridY = 0;

    bool _alive = false;
    int _HP = 0;
    int _maxHP = 0;
    int _ATT = 0;

    int _reward = 0;
    
    DIRECTION _dir = DIRECTION::RIGHT;
    float _speed = 0.f;     // pixel per second

    // Get
public:
    int GetGenGridX() const { return _genGridX; }
    int GetGenGridY() const { return _genGridY; }

    bool GetAlive() const { return _alive; }
    int GetHP() const { return _HP; }
    int GetATT() const { return _ATT; }
    int GetReward() const { return _reward; }

    DIRECTION GetDir() const { return _dir; }
    float GetSpeed() const { return _speed; }

    // Set
public:
    void SetGenGridX(int x) { _genGridX = x; }
    void SetGenGridY(int y) { _genGridY = y; }

    void SetAlive(bool alive) { _alive = alive; }
    void SetHP(int hp) { _HP = hp; }
    void SetATT(int att) { _ATT = att; }

    void SetDir(DIRECTION dir) { _dir = dir; }
    void SetSpeed(float speed) { _speed = speed; }




public:
    void ChangeDirAt(int gridX, int gridY, DIRECTION dir);
    void BeDamaged(int att);



    // 디버프 관련
private:
    bool _debuffEnable = false;
    float _slowRate = 0.f;
    float _timeTickforDebuff = 0.f;
    float _debuffDuration = 0.f;

public:
    void SetSlowDebuff(float slowRate, float duration);
};

