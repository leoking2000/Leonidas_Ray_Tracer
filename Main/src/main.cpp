#include <iostream>
#include "test/test.h"

int main()
{
#ifndef NDEBUG
    Test::UnitTest();
#endif
    
    Test::PlayingTest();


    return 0;
}
