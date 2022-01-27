#include "Map.h"
#include "Tile.h"

Map::Map(Core* pEngine)	:
	Obj(pEngine)
{
	_x = MAP_POS_X;
	_y = MAP_POS_Y;
	_tileSize = TILE_SIZE;

	// 타일 동적 할당
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			_pTile[i][j] = new Tile(_pEngine);
			_pTile[i][j]->Create(_x, _y, j, i, _tileSize);
		}
	}
}

Map::~Map()
{
	// 타일 메모리 해제
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			SAFE_DELETE(_pTile[i][j]);
		}
	}

}

void Map::Update()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			_pTile[i][j]->Update();
		}
	}
}

void Map::Render()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			_pTile[i][j]->Render();
		}
	}
}

TILE_TYPE Map::GetTileType(int x, int y)
{
	return _pTile[y][x]->GetType();
}

void Map::SetTileType(int x, int y, TILE_TYPE type)
{
	_pTile[y][x]->SetType(type);
}

void Map::SetTileTypeNum(int arr[][MAP_WIDTH])
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (!_pTile[i][j])
				continue;

			switch (arr[i][j])
			{
			case 0:
				_pTile[i][j]->SetType(TILE_TYPE::NONE);
				break;
			case 1:
				_pTile[i][j]->SetType(TILE_TYPE::PATH);
				break;
			case 2:
				_pTile[i][j]->SetType(TILE_TYPE::ABLE);
				break;
			case 3:
				_pTile[i][j]->SetType(TILE_TYPE::UNABLE);
				break;
			}

			_pTile[i][j]->TileColorUpdate();
		}
	}
}
