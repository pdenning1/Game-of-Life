#include "test1.h"

Test::Test(int x) : _x(x)
{}


void Test::TestPrint()
{
    std::cout << "x = " << _x << std::endl;
}