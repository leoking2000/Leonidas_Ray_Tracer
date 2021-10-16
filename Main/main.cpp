#include "../Tests/test.h"
#include "examples/DrawSphereTest.h"

int main()
{
#ifndef NDEBUG
    Test::UnitTest();
#endif

    DrawSphereTest();

    return 0;
}
