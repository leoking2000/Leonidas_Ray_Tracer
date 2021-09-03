#include <iostream>
#include "test/test.h"

int main()
{

#ifndef NDEBUG
    Test::Test();
#endif

    std::cout << "Leonidas Ray Tracer!!!" << std::endl;



    return 0;
}
