#pragma once
#include "Obj.h"

// �켱 Ÿ���� ���� �� ������ �ʴ´ٴ� ���� �Ͽ� ������

class Tile :
    public Obj
{
public:
    Tile(Core* pEngine);
    ~Tile();

public:
    bool Create(float offsetX, float offsetY, int gridX, int gridY, int size);
    virtual void Update() override;
    virtual void Render() override;



private:
    float _offsetX = 0.f;
    float _offsetY = 0.f;
    int _gridX = 0;
    int _gridY = 0;
    TILE_TYPE _type = TILE_TYPE::NONE;

    // Get
public:
    TILE_TYPE GetType() const { return _type; }

    // Set
public:
    void SetType(TILE_TYPE type) { _type = type; }
    

public:
    void TileColorUpdate();
};

