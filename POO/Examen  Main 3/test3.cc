#include "dado.h"
#include "gtest/gtest.h"
using namespace std;

TEST(Dado, Constructor)
{
	Dado d;
	EXPECT_EQ(1, d.get());
	Dado d2(9);
	EXPECT_EQ(1, d2.get());
	Dado d3(5);
	EXPECT_EQ(5, d3.get());
	Dado d4(-2);
	EXPECT_EQ(1, d4.get());
}

TEST(Dado, Modificador)
{
	Dado d;
	EXPECT_EQ(1, d.get());
	EXPECT_FALSE(d.set(9));
	EXPECT_EQ(1, d.get());
	EXPECT_TRUE(d.set(5));
	EXPECT_EQ(5, d.get());
	EXPECT_FALSE(d.set(-2));
	EXPECT_EQ(5, d.get());
}

TEST(Dado, Operador)
{
 	Dado d,d2;
 	srand(time(NULL));
 	for (int i = 0; i < 100; ++i)
 	{
 		int v1 = (rand() % 6) + 1;
 		int v2 = (rand() % 6) + 1;
 		d.set(v1);
 		d2.set(v2);
 		EXPECT_EQ(v1+v2,d+d2);
 	}
}