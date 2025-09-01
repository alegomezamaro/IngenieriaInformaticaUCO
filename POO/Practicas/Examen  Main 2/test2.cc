#include "computer.h"
#include "cart.h"
#include "gtest/gtest.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

TEST(Cart, Constructor)
{
	Cart c(1);
	EXPECT_EQ(1,c.getId());
	EXPECT_EQ(0,c.getN());

	Cart c2(2);
	EXPECT_EQ(2,c2.getId());
	EXPECT_EQ(0,c2.getN());
}

TEST(Cart,addComputer)
{
	Cart c(1);

	EXPECT_EQ(0,c.getN());

	Computer c1("MacBook Pro","Apple",1500);
	c.addComputer(c1);
	EXPECT_EQ(1,c.getN());

	Computer c2("MacBook Air","Apple",1000);
	c.addComputer(c2);
	EXPECT_EQ(2,c.getN());

	Computer c3("iMac","Apple",2500);
	c.addComputer(c3);
	EXPECT_EQ(3,c.getN());
}

TEST(Cart,print)
{
	Cart c(1);
	Computer c1("PC1","PV1");
	Computer c2("PC2","PV2");
	Computer c3("PC3","PV3");
	c.addComputer(c1);
	c.addComputer(c2);
	c.addComputer(c3);
	c.print();
}

TEST(Cart,write)
{
	Cart c(1);
	Computer c1("PC1","PV1");
	Computer c2("PC2","PV2");
	Computer c3("PC3","PV3");
	c.addComputer(c1);
	c.addComputer(c2);
	c.addComputer(c3);
	c.write();
	ifstream f("salida.txt");
	if(f)
	{
		string dato;
		string num,nombre,modelo;
		while(getline(f,dato,','))
		{
			num = dato;
			getline(f,dato,',');
			nombre = dato;
			getline(f,dato,'\n');
			modelo = dato;
			cout << num << "," << nombre << "," << modelo << endl;
		}
		f.close();
	}
}