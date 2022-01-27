#pragma once
#include "Obj.h"

class Tile;

class Map :
    public Obj
{
public:
    Map(Core* pEngine);
    virtual ~Map();

public:
    virtual void Update() override;
    virtual void Render() override;



private:
    int _tileSize = 0;
    Tile* _pTile[MAP_HEIGHT][MAP_WIDTH] = { nullptr, };
    //int _tileTypeNum[MAP_HEIGHT][MAP_WIDTH] = { {0,}, };

    // Get
public:
    int GetTileSize() const { return _tileSize; }
    TILE_TYPE GetTileType(int x, int y);
    //int GetTileTypeNum(int x, int y) { return _tileTypeNum[y][x]; }

    // Set
public:
    void SetTileSize(int size) { _tileSize = size; }
    void SetTileType(int x, int y, TILE_TYPE type);
    //void SetTileTypeNum(int x, int y, int t) { _tileTypeNum[y][x] = t; }
    void SetTileTypeNum(int arr[][MAP_WIDTH]);
    // 만약 맵 크기도 가변으로 한다면 1차원 배열과 길이를 인자로 받기



    // TODO: 공격 받는 메커니즘 
    // => 마지막 타일 좌표 변수로 저장, Enemy* 변수 받아서 범위 체크 후 bool 반환 함수
};

