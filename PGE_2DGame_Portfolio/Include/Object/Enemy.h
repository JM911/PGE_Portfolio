#pragma once
#include "Obj.h"

// 방향전환, 소멸판정은 모두 씬에서

class Enemy :
    public Obj
{
public:
    Enemy();
    virtual ~Enemy();

public:
    virtual void Update(Core* pEngine) override;
    virtual void Render(Core* pEngine) override;



private:
    int _genGridX = 0;      // 생성위치
    int _genGridY = 0;

    int _HP = 0;
    
    DIRECTION _dir = DIRECTION::RIGHT;
    float _speed = 0.f;     // pixel per second

    // Get
public:
    int GetGenGridX() const { return _genGridX; }
    int GetGenGridY() const { return _genGridY; }
    int GetHP() const { return _HP; }
    DIRECTION GetDir() const { return _dir; }
    float GetSpeed() const { return _speed; }

    // Set
public:
    void SetGenGridX(int x) { _genGridX = x; }
    void SetGenGridY(int y) { _genGridY = y; }
    void SetHP(int hp) { _HP = hp; }
    void SetDir(DIRECTION dir) { _dir = dir; }
    void SetSpeed(float speed) { _speed = speed; }




public:
    void ChangeDirUDAt(int gridX, DIRECTION dir);
    void ChangeDirLRAt(int gridY, DIRECTION dir);
    void ChangeDirAt(int gridX, int gridY, DIRECTION dir);
};

