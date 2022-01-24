#define OLC_PGE_APPLICATION
#include "Core.h"

int main()
{
	Core demo;
	if (demo.Construct(1280, 720, 1, 1))
		demo.Start();
	return 0;
}