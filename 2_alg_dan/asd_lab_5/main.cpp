#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "catch.hpp"

int main(int argc, char* argv[] )
{
    int result = Catch::Session().run( argc, argv );	// -- пуск системы Catch --
    system("pause");			// -- для просмотра результатов --
    return result;
}
