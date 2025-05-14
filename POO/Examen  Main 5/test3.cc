#include "gtest/gtest.h"
#include "matriculaAsignatura.h"

// Test para el constructor parametrizado
TEST(MatriculaAsignaturaTest, ConstructorParametrizado) {
    MatriculaAsignatura matricula("Programación", 30);
    EXPECT_EQ(matricula.getAsignatura(), "Programación");
    EXPECT_EQ(matricula.getMaxAlumnos(), 30);
}

// Test para el método addAlumno
TEST(MatriculaAsignaturaTest, AddAlumno) {
    MatriculaAsignatura matricula("Matemáticas", 25);

    // Agregar alumnos
    EXPECT_TRUE(matricula.addAlumno("Juan"));
    EXPECT_TRUE(matricula.addAlumno("Maria"));
    EXPECT_TRUE(matricula.addAlumno("Pedro"));

    // Intentar agregar un alumno ya existente
    EXPECT_FALSE(matricula.addAlumno("Maria"));

    // Intentar agregar más alumnos que el límite
    for (int i = 0; i < 21; ++i) {
        matricula.addAlumno("Alumno" + std::to_string(i));
    }
    EXPECT_TRUE(matricula.addAlumno("NuevoAlumno"));  // Aún hay espacio
    EXPECT_FALSE(matricula.addAlumno("UltimoAlumno"));  // Límite alcanzado
}

// Test para el método getN
TEST(MatriculaAsignaturaTest, GetN) {
    MatriculaAsignatura matricula("Física", 20);

    // Agregar algunos alumnos
    matricula.addAlumno("Estudiante1");
    matricula.addAlumno("Estudiante2");
    matricula.addAlumno("Estudiante3");

    EXPECT_EQ(matricula.getN(), 3);

    // Agregar más alumnos
    for (int i = 0; i < 15; ++i) {
        matricula.addAlumno("Alumno" + std::to_string(i));
    }

    EXPECT_EQ(matricula.getN(), 18);
}

// Ejecutar los tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
