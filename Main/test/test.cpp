#include "test.h"

#include "unit_tests/VectorTest.h"
#include "unit_tests/CanvasTest.h"
#include "unit_tests/MatrixTest.h"
#include "unit_tests/GeometryTest.h"
#include "unit_tests/GraphicsTest.h"

#include "playing_tests/ProjectileTest.h"
#include "playing_tests/clockpositionsTest.h"
#include "playing_tests/DrawSphereTest.h"

void Test::UnitTest()
{
	VectorTest();
	MatrixTest();
	CanvasTest();
	GeometryTest();
	GraphicsTest();
}

void Test::PlayingTest()
{
	//ProjectileTest();
	//clockpositionsTest();
	//DrawSphereTest();
}
