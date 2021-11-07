#include "test.h"

#include "unit_tests/VectorTest.h"
#include "unit_tests/CanvasTest.h"
#include "unit_tests/MatrixTest.h"
//#include "unit_tests/GeometryTest.h"
//#include "unit_tests/GraphicsTest.h"

void Test::UnitTest()
{
	VectorTest();
	MatrixTest();
	CanvasTest();
	//GeometryTest();
	//GraphicsTest();
}

