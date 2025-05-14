#include "jugador.h"
#include "gtest/gtest.h"
#include <string>
using namespace std;

TEST(Jugador, Constructores)
{
	Jugador j("Nombre 1", "pivot");
	EXPECT_EQ(j.getNombre(), "Nombre 1");
	EXPECT_EQ(j.getDireccion(), "XX");
	EXPECT_EQ(j.getDNI(), "XX");
	EXPECT_EQ(j.getPuesto(), "pivot");
	Jugador j2("Nombre 1", "Banquillo");
	EXPECT_EQ(j2.getNombre(), "Nombre 1");
	EXPECT_EQ(j2.getDireccion(), "XX");
	EXPECT_EQ(j2.getDNI(), "XX");
	EXPECT_EQ(j2.getPuesto(), "Ninguno");
	Jugador j3("Nombre 1", "alero", "Dir 1", "DNI 1");
	EXPECT_EQ(j3.getNombre(), "Nombre 1");
	EXPECT_EQ(j3.getDireccion(), "Dir 1");
	EXPECT_EQ(j3.getDNI(), "DNI 1");
	EXPECT_EQ(j3.getPuesto(), "alero");
}

TEST(Jugador, Modificador)
{
	Jugador j("Nombre 1", "pivot");
	EXPECT_TRUE(j.setPuesto("ala-pivot"));
	EXPECT_EQ(j.getPuesto(), "ala-pivot");
	EXPECT_FALSE(j.setPuesto("ala"));
	EXPECT_EQ(j.getPuesto(), "ala-pivot");
}

TEST(Jugador,Operadores)
{
 	Jugador j("Nombre 1","alero","Dir 1", "DNI 1");
 	Jugador j2("Nombre 1","Banquillo");
 	j2=j;
 	EXPECT_EQ(j.getNombre(),j2.getNombre());
 	EXPECT_EQ(j.getDireccion(),j2.getDireccion());
 	EXPECT_EQ(j.getDNI(),j2.getDNI());
 	EXPECT_EQ(j.getPuesto(),j2.getPuesto());
 	cout << j << endl;
}