#include "test.h"

#include "unit_tests/FloatEqualTest.h"
#include "unit_tests/VectorTest.h"
#include "unit_tests/CanvasTest.h"

#include "playing_tests/ProjectileTest.h"

void Test::Test()
{
	FloatEqualTest();
	VectorTest();
	CanvasTest();

	ProjectileTest();
}
