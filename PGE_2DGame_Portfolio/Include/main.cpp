#define OLC_PGE_APPLICATION
#include "Core.h"

int main()
{
	Core demo;
	if (demo.Construct(640, 360, 2, 2))
		demo.Start();
	return 0;
}