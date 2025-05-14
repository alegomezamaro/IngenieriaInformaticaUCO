#include "computer.h"
#include "laptop.h"
#include "gtest/gtest.h"
#include <string>

using namespace std;

TEST(Laptop, Constructor)
{
	Laptop l(17,"MacBook Pro",1500);
	EXPECT_EQ(17,l.getPulgadas());
	EXPECT_EQ("MacBook Pro",l.getModelo());
	EXPECT_EQ("Laptop",l.getNombre());
	EXPECT_EQ(1500,l.getPrecio());

	Laptop l2(0,"",-5);
	EXPECT_EQ(1,l2.getPulgadas());
	EXPECT_EQ("Ninguno",l2.getModelo());
	EXPECT_EQ("Laptop",l2.getNombre());
	EXPECT_EQ(0,l2.getPrecio());
}

TEST(Laptop,setPulgadas)
{
	Laptop l(17,"MacBook Pro",1500);
	EXPECT_TRUE(l.setPulgadas(34));
	EXPECT_FALSE(l.setPulgadas(0));
}

TEST(Laptop,getInfo)
{
	Laptop l(17,"MacBook Pro",1500);
	EXPECT_EQ("Laptop de 17 pulgadas modelo MacBook Pro precio 1500",l.getInfo());

	Laptop l2(18,"PV3",300);
	EXPECT_EQ("Laptop de 18 pulgadas modelo PV3 precio 300",l2.getInfo());

}