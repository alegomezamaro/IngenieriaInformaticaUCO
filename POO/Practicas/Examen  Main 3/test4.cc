#include "equipo.h"
#include "jugador.h"
#include "gtest/gtest.h"
using namespace std;

TEST(Equipo, addJugador)
{
	Equipo e1;

	Jugador j1("nombre 1", "pivot", "direccion 1", "dni 1");
	Jugador j2("nombre 2", "pivot", "direccion 2", "dni 2");
	Jugador j3("nombre 3", "pivot", "direccion 3", "dni 3");
	Jugador j4("nombre 4", "pivot", "direccion 4", "dni 4");

	EXPECT_TRUE(e1.addJugador(j1));
	EXPECT_TRUE(e1.addJugador(j2));
	EXPECT_TRUE(e1.addJugador(j3));
	EXPECT_TRUE(e1.addJugador(j4));
	EXPECT_FALSE(e1.addJugador(j1));
}

TEST(Equipo, Constructor)
{
	Equipo e1;

	Jugador j1("nombre 1", "pivot", "direccion 1", "dni 1");
	Jugador j2("nombre 2", "pivot", "direccion 2", "dni 2");
	Jugador j3("nombre 3", "pivot", "direccion 3", "dni 3");
	Jugador j4("nombre 4", "pivot", "direccion 4", "dni 4");

	EXPECT_TRUE(e1.addJugador(j1));
	EXPECT_TRUE(e1.addJugador(j2));
	EXPECT_TRUE(e1.addJugador(j3));
	EXPECT_TRUE(e1.addJugador(j4));
	EXPECT_FALSE(e1.addJugador(j1));

	Equipo e2(e1);

	EXPECT_EQ(e1.size(), e2.size());
}

TEST(Equipo, Operador)
{
 	Equipo e1;

 	Jugador j1("nombre 1","pivot","direccion 1","dni 1");
 	Jugador j2("nombre 2","pivot","direccion 2","dni 2");
 	Jugador j3("nombre 3","pivot","direccion 3","dni 3");
 	Jugador j4("nombre 4","pivot","direccion 4","dni 4");

 	EXPECT_TRUE(e1.addJugador(j1));
 	EXPECT_TRUE(e1.addJugador(j2));
 	EXPECT_TRUE(e1.addJugador(j3));
 	EXPECT_TRUE(e1.addJugador(j4));
 	EXPECT_FALSE(e1.addJugador(j1));

 	EXPECT_TRUE(e1[0].getNombre()==j1.getNombre());
	EXPECT_TRUE(e1[1].getNombre()==j2.getNombre());
 	EXPECT_TRUE(e1[2].getNombre()==j3.getNombre());
 	EXPECT_TRUE(e1[3].getNombre()==j4.getNombre());
 }

TEST(Equipo, Ordenar)
{
	Equipo e1;

	Jugador j1("A", "pivot", "direccion 1", "dni 1");
	Jugador j2("B", "pivot", "direccion 2", "dni 2");
	Jugador j3("C", "pivot", "direccion 3", "dni 3");
	Jugador j4("D", "pivot", "direccion 4", "dni 4");

	EXPECT_TRUE(e1.addJugador(j4));
	EXPECT_TRUE(e1.addJugador(j3));
	EXPECT_TRUE(e1.addJugador(j2));
	EXPECT_TRUE(e1.addJugador(j1));

	e1.ordenar();

	EXPECT_TRUE(e1[3].getNombre() == j4.getNombre());
	EXPECT_TRUE(e1[2].getNombre() == j3.getNombre());
	EXPECT_TRUE(e1[1].getNombre() == j2.getNombre());
	EXPECT_TRUE(e1[0].getNombre() == j1.getNombre());
}