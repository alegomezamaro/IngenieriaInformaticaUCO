#include "persona.h"
#include "gtest/gtest.h"
#include <string>
using namespace std;

TEST(Persona, Constructores)
{
	Persona p("Nombre 1");
	EXPECT_EQ(p.getNombre(),"Nombre 1");
	EXPECT_EQ(p.getDireccion(),"XX");
	EXPECT_EQ(p.getDNI(),"XX");
	Persona p2("Nombre 2","Cordoba","1234A");
	EXPECT_EQ(p2.getNombre(),"Nombre 2");
	EXPECT_EQ(p2.getDireccion(),"Cordoba");
	EXPECT_EQ(p2.getDNI(),"1234A");
	Persona p3(p2);
	EXPECT_EQ(p3.getNombre(),"Nombre 2");
	EXPECT_EQ(p3.getDireccion(),"Cordoba");
	EXPECT_EQ(p3.getDNI(),"1234A");
}

TEST(Persona,Modificadores)
{
	Persona p("Nombre 1");
	EXPECT_EQ(p.getNombre(),"Nombre 1");
	EXPECT_FALSE(p.setNombre(""));
	EXPECT_EQ(p.getNombre(),"Nombre 1");
	EXPECT_TRUE(p.setNombre("Nombre 2"));
	EXPECT_EQ(p.getNombre(),"Nombre 2");
	EXPECT_EQ(p.getDireccion(),"XX");
	EXPECT_FALSE(p.setDireccion(""));
	EXPECT_EQ(p.getDireccion(),"XX");
	EXPECT_TRUE(p.setDireccion("Cordoba"));
	EXPECT_EQ(p.getDireccion(),"Cordoba");
	EXPECT_EQ(p.getDNI(),"XX");
	EXPECT_FALSE(p.setDNI(""));
	EXPECT_EQ(p.getDNI(),"XX");
	EXPECT_TRUE(p.setDNI("1234A"));
	EXPECT_EQ(p.getDNI(),"1234A");
}

/*TEST(Persona,getDatos)
{
	Persona p("Pepe","Cordoba","12345678Z");
	string datos;
	p.getDatos(datos);
	EXPECT_EQ(datos,"Pepe con DNI 12345678Z vive en Cordoba");
}*/