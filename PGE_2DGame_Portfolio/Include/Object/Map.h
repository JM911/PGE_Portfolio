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
    // ���� �� ũ�⵵ �������� �Ѵٸ� 1���� �迭�� ���̸� ���ڷ� �ޱ�



    // TODO: ���� �޴� ��Ŀ���� 
    // => ������ Ÿ�� ��ǥ ������ ����, Enemy* ���� �޾Ƽ� ���� üũ �� bool ��ȯ �Լ�
};

