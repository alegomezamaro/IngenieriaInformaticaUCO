#include <gtest/gtest.h>
#include "estudianteGraduado.h"

TEST(EstudianteGraduadoTest, ConstructorVacio) {
    EstudianteGraduado estudianteGraduado;
    EXPECT_EQ(estudianteGraduado.getNombre(), "Sin nombre");
    EXPECT_EQ(estudianteGraduado.getEdad(), 0);
    EXPECT_EQ(estudianteGraduado.getDNI(), "Sin dni");
    EXPECT_EQ(estudianteGraduado.getEspecialidad(), "Sin indicar");
    EXPECT_EQ(estudianteGraduado.getAnioGraduacion(), 2011);
}

TEST(EstudianteGraduadoTest, ConstructorParametrizado) {
    EstudianteGraduado estudianteGraduado("12345678A", "Mención en Computación", 2015, "Juan", 25);
    EXPECT_EQ(estudianteGraduado.getNombre(), "Juan");
    EXPECT_EQ(estudianteGraduado.getEdad(), 25);
    EXPECT_EQ(estudianteGraduado.getDNI(), "12345678A");
    EXPECT_EQ(estudianteGraduado.getEspecialidad(), "Mención en Computación");
    EXPECT_EQ(estudianteGraduado.getAnioGraduacion(), 2015);
}

TEST(EstudianteGraduadoTest, SetEspecialidadInvalida) {
    EstudianteGraduado estudianteGraduado;
    EXPECT_FALSE(estudianteGraduado.setEspecialidad("Ingeniería"));
    EXPECT_EQ(estudianteGraduado.getEspecialidad(), "Sin indicar");
}

TEST(EstudianteGraduadoTest, SetAnioGraduacionInvalido) {
    EstudianteGraduado estudianteGraduado;
    EXPECT_FALSE(estudianteGraduado.setAnioGraduacion(2010));
    EXPECT_EQ(estudianteGraduado.getAnioGraduacion(), 2011);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
