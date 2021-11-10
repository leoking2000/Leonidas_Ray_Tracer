#include "gtest/gtest.h"

#include "Tests/MathTest.h"
#include "Tests/CanvasTest.h"
#include "Tests/GeometryTest.h"
#include "Tests/GraphicsTest.h"
#include "Tests/DefaultWorldTest.h"

#include "examples/ProjectileTest.h"
#include "examples/clockpositionsTest.h"
#include "examples/DrawSphereTest.h"

#define RUN_EXAMPLES 0

int main(int argc, char** argv) 
{
	::testing::InitGoogleTest(&argc, argv);

	int r = RUN_ALL_TESTS();

#if RUN_EXAMPLES
	ProjectileTest();
	clockpositionsTest();
	DrawSphereTest();
#endif


	return r;
}