#include <gtest/gtest.h>
#include "estudiante.h"

// Caso de prueba para el constructor vacío
TEST(EstudianteTest, ConstructorVacio)
{
    Estudiante estudiante;
    EXPECT_EQ(estudiante.getNombre(), "Sin nombre");
    EXPECT_EQ(estudiante.getEdad(), 0);
    EXPECT_EQ(estudiante.getDNI(), "Sin dni");
}

// Caso de prueba para el constructor parametrizado
TEST(EstudianteTest, ConstructorParametrizado)
{
    Estudiante estudiante("12345678A", "Juan", 20);
    EXPECT_EQ(estudiante.getNombre(), "Juan");
    EXPECT_EQ(estudiante.getEdad(), 20);
    EXPECT_EQ(estudiante.getDNI(), "12345678A");
}

// Caso de prueba para el constructor parametrizado con valores por defecto
TEST(EstudianteTest, ConstructorParametrizadoValoresPorDefecto)
{
    Estudiante estudiante("98765432B");
    EXPECT_EQ(estudiante.getNombre(), "Sin nombre");
    EXPECT_EQ(estudiante.getEdad(), 0);
    EXPECT_EQ(estudiante.getDNI(), "98765432B");
}

// Caso de prueba para el constructor parametrizado con valores por defecto y valores personalizados
TEST(EstudianteTest, ConstructorParametrizadoValoresPersonalizados)
{
    Estudiante estudiante("", "Ana", -5);
    EXPECT_EQ(estudiante.getNombre(), "Ana");
    EXPECT_EQ(estudiante.getEdad(), 0);
    EXPECT_EQ(estudiante.getDNI(), "Sin dni");
}

/*// Caso de prueba para el método getInfo
TEST(EstudianteTest, GetInfo)
{
    Estudiante estudiante("56789012C", "Pedro", 25);
    EXPECT_EQ(estudiante.getInfo(), "El alumno con nombre Pedro tiene 25 años y su DNI es 56789012C.");
}*/

// Caso de prueba para los modificadores
TEST(EstudianteTest, Modificadores)
{
    Estudiante estudiante;
    estudiante.setNombre("Luisa");
    estudiante.setEdad(30);
    estudiante.setDNI("34567890D");

    EXPECT_EQ(estudiante.getNombre(), "Luisa");
    EXPECT_EQ(estudiante.getEdad(), 30);
    EXPECT_EQ(estudiante.getDNI(), "34567890D");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
