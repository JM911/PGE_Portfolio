#include "Map.h"
#include "Tile.h"

Map::Map()
{
	_x = MAP_POS_X;
	_y = MAP_POS_Y;

	// 타일 동적 할당
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			_pTile[i][j] = new Tile();
			_pTile[i][j]->SetSize(TILE_SIZE);
			_pTile[i][j]->SetX(_x + j * TILE_SIZE);
			_pTile[i][j]->SetY(_y + i * TILE_SIZE);
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
			if (_pTile)
			{
				delete _pTile[i][j];
				_pTile[i][j] = nullptr;
			}
		}
	}

}

void Map::Update(Core* pEngine)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			_pTile[i][j]->Update(pEngine);
		}
	}
}

void Map::Render(Core* pEngine)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			_pTile[i][j]->Render(pEngine);
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

void Map::SyncTileType()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (_tileTypeNum[i][j])
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
		}
	}
}
