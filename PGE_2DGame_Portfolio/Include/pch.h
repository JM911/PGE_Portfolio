#pragma once

// аж©Д include
#include "olcPixelGameEngine.h"
#include "Flag.h"

using namespace std;

#define MAP_WIDTH		12
#define MAP_HEIGHT		9

#define MAP_POS_X		170
#define MAP_POS_Y		40
#define TILE_SIZE		25

#define TOWER_SIZE		10

#define MAX_ENEMY_NUM	50
#define MAX_WAVE_NUM	10
#define MAX_BULLET_NUM	50


// Macro
#define SAFE_DELETE(p)	if(p) { delete p; p = nullptr;}