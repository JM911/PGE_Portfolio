#pragma once
#include "Obj.h"

class Tower :
    public Obj
{
public:
    Tower(int gridX, int gridY);
    virtual ~Tower();

public:
    virtual void Update(Core* pEngine) override;
    virtual void Render(Core* pEngine) override;



    
private:
    bool _enable = false;
    int _gridX = 0;
    int _gridY = 0;
    //olc::Pixel _color = olc::BLACK;

    int _range = 0;

    // TODO: Ÿ��(Enemy ������ Ÿ��) ���� ����. (Ÿ�� ������ ��� Ÿ���� ��� ������ �Ÿ��� ����ؾ� �ϹǷ� ������)
    
    // Get
public:
    bool GetEnable() const { return _enable; }
    int GetGridX() const { return _gridX; }
    int GetGridY() const { return _gridY; }
    //olc::Pixel GetColor() const { return _color; }
    int GetRange() const { return _range; }

    // Set
public:
    void SetEnable(bool enable) { _enable = enable; }
    void SetGridX(int gridX) { _gridX = gridX; }
    void SetGridY(int gridY) { _gridY = gridY; }
    //void SetColor(olc::Pixel color) { _color = color; }
    void SetRange(int range) { _range = range; }
};

