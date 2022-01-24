#pragma once

enum class TILE_TYPE
{
	NONE,		// 미정
	PATH,		// 적이 지나가는 길
	ABLE,		// 타워를 세울 수 있는 타일
	UNABLE,		// 타워를 세울 수 없는 타일

	END,
};