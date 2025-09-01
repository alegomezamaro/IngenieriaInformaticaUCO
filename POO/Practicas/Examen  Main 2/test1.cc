#include "computer.h"
#include "gtest/gtest.h"
#include <string>
using namespace std;

TEST(Computer, Constructores)
{
	Computer c1("MacBook Pro","Apple",1500);
	EXPECT_EQ(c1.getNombre(),"MacBook Pro");
	EXPECT_EQ(c1.getModelo(),"Apple");
	EXPECT_EQ(c1.getPrecio(),1500);

	Computer c2("MacBook Air","Apple");
	EXPECT_EQ(c2.getNombre(),"MacBook Air");
	EXPECT_EQ(c2.getModelo(),"Apple");
	EXPECT_EQ(c2.getPrecio(),0);

	Computer c3("MacBook Pro","Apple",-100);
	EXPECT_EQ(c3.getNombre(),"MacBook Pro");
	EXPECT_EQ(c3.getModelo(),"Apple");
	EXPECT_EQ(c3.getPrecio(),0);
}

TEST(Computer,Modificadores)
{
	Computer c1("MacBook Pro","Apple",1500);

	EXPECT_FALSE(c1.setNombre(""));
	EXPECT_EQ(c1.getNombre(),"MacBook Pro");

	EXPECT_TRUE(c1.setNombre("MacBook Pro 2"));
	EXPECT_EQ(c1.getNombre(),"MacBook Pro 2");

	EXPECT_FALSE(c1.setModelo(""));
	EXPECT_EQ(c1.getModelo(),"Apple");

	EXPECT_TRUE(c1.setModelo("Apples"));
	EXPECT_EQ(c1.getModelo(),"Apples");

	EXPECT_FALSE(c1.setPrecio(-2));
	EXPECT_EQ(c1.getPrecio(),1500);
	EXPECT_FALSE(c1.setPrecio(-2));
	EXPECT_EQ(c1.getPrecio(),1500);
}

TEST(Computer,getNombreYModelo)
{
	Computer c1("MacBook Pro","Apple",1500);
	EXPECT_EQ(c1.getNombreYModelo(),"MacBook Pro; Apple");
}