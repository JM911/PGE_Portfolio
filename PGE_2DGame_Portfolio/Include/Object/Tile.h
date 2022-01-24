#pragma once
#include "Obj.h"
#include "../pch.h"

class Core;

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
    int _size = 0;

    // Get
public:
    TILE_TYPE GetType() const { return _type; }
    int GetSize() const { return _size; }

    // Set
public:
    void SetType(TILE_TYPE type) { _type = type; }
    void SetSize(int size) { _size = size; }
};

