#pragma once

enum class TILE_TYPE
{
	NONE,		// ����
	PATH,		// ���� �������� ��
	ABLE,		// Ÿ���� ���� �� �ִ� Ÿ��
	UNABLE,		// Ÿ���� ���� �� ���� Ÿ��
	OCCUPIED,	// Ÿ���� ������ �ִ� Ÿ��

	END,
};

enum class DIRECTION
{
	RIGHT,
	DOWN,
	LEFT,
	UP,
};

enum class ENEMY_TYPE
{
	NORMAL,

	END,
};