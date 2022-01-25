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
    int _size = 0;
    
    DIRECTION _dir = DIRECTION::RIGHT;
    int _speed = 0;     // pixel per second

    // Get

    // Set
};

