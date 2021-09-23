#include "test.h"

#include "unit_tests/VectorTest.h"
#include "unit_tests/CanvasTest.h"
#include "unit_tests/MatrixTest.h"
#include "unit_tests/RayTest.h"

#include "playing_tests/ProjectileTest.h"
#include "playing_tests/clockpositionsTest.h"
#include "playing_tests/DrawSphereTest.h"

void Test::UnitTest()
{
	VectorTest();
	CanvasTest();
	MatrixTest();
	RayTest();
}

void Test::PlayingTest()
{
	//ProjectileTest();
	//clockpositionsTest();
	DrawSphereTest();
}
