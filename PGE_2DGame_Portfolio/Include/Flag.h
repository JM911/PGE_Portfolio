#pragma once

enum class TILE_TYPE
{
	NONE,		// ����
	PATH,		// ���� �������� ��
	ABLE,		// Ÿ���� ���� �� �ִ� Ÿ��
	UNABLE,		// Ÿ���� ���� �� ���� Ÿ��

	END,
};

enum class DIRECTION
{
	RIGHT,
	DOWN,
	LEFT,
	UP,
};