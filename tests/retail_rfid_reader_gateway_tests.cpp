#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>

TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
    CHECK(true);
}

int main (int argc, char ** argv)
{
   return RUN_ALL_TESTS(argc, argv);
}
