#pragma once
#include "Obj.h"

class Tile :
    public Obj
{
public:
    Tile();
    ~Tile();

public:
    void Update(Core* pEngine) override;
    void Render(Core* pEngine) override;



private:
    TILE_TYPE _type = TILE_TYPE::NONE;

    // Get
public:
    TILE_TYPE GetType() const { return _type; }

    // Set
public:
    void SetType(TILE_TYPE type) { _type = type; }
};

