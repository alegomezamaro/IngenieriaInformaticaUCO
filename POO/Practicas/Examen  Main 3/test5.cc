#include "dato.h"
#include "gtest/gtest.h"
using namespace std;

TEST(Dato, Constructor)
{
	int id;
	Dato <int> d(1,3);
	d.getId(id);
	int dato;
	d.getDato(dato);
	EXPECT_EQ(1,id);
	EXPECT_EQ(3,dato);
	Dato <float> d2(2,3.5);
	d2.getId(id);
	float dato2;
	d2.getDato(dato2);
	EXPECT_EQ(2,id);
	EXPECT_EQ(3.5,dato2);
	Dato <string> d3(3,"hola");
	d3.getId(id);
	string dato3;
	d3.getDato(dato3);
	EXPECT_EQ(3,id);
	EXPECT_EQ("hola",dato3);
}

TEST(Dato,Operadores)
{
	Dato < string > d (1,"hola");
	Dato < float > d2 (2,3);
	Dato < string > d3 (3,"adios");
	Dato < string > d4 (3,"hola");
	Dato < float > d5 (2,4);
	Dato < float > d6 (2,3);
	EXPECT_TRUE(d==d4);
	EXPECT_TRUE(d2==d6);
	EXPECT_FALSE(d2!=d6);
	EXPECT_FALSE(d==d3);
	EXPECT_TRUE(d!=d3);
	EXPECT_TRUE(d2!=d5);
}