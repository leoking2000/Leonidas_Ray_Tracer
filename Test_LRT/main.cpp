#include "gtest/gtest.h"

//#include "Tests/MathTest.h"
#include "Tests/CanvasTest.h"
//#include "Tests/GeometryTest.h"
//#include "Tests/GraphicsTest.h"
//#include "Tests/DefaultWorldTest.h"
//#include "Tests/PattenTest.h"

//#include "examples/ProjectileTest.h"
//#include "examples/clockpositionsTest.h"
//#include "examples/DrawSphereTest.h"
#include "examples/TableTest.h"

#define RUN_TESTS 0
#define RUN_EXAMPLES 1

int main(int argc, char** argv) 
{
	int r = 0;

#if RUN_TESTS
	::testing::InitGoogleTest(&argc, argv);
	r = RUN_ALL_TESTS();
#endif

#if RUN_EXAMPLES
	//ProjectileTest();
	//clockpositionsTest();
	//DrawSphereTest();
	TableTest();
#endif


	return r;
}