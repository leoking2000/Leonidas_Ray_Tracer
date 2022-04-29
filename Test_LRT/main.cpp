#include "gtest/gtest.h"

#include "Tests/CanvasTest.h"
#include "Tests/GeometryTest.h"

#include "examples/ParallelMirrorTest.h"
#include "examples/TableTest.h"

#define RUN_TESTS 1
#define RUN_EXAMPLES 0

int main(int argc, char** argv) 
{
	int r = 0;

#if RUN_TESTS
	::testing::InitGoogleTest(&argc, argv);
	r = RUN_ALL_TESTS();
#endif

#if RUN_EXAMPLES
	ParallelMirrorTest();
	TableTest();
#endif


	return r;
}