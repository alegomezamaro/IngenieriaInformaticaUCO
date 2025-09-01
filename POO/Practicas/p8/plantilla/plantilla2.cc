#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

template <class T> class MiClase{
    private:
        T x_;
        T y_;

    public:
        MiClase (T x, T y){
            x_ = x;
            y_ = y;
        };
        inline T GetX(){return x_;}
        inline T GetY(){return y_;}
        inline T Div(){return x_/y_;};
};

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Introduce ./plantilla <Tipo de vector: int (I) o floats (F)> <Numero dividendo> <Numero divisor>\n";
        return 0;
    }
    std::string tipo = argv[1];
    if (tipo == "I") {
        MiClase <int> i(atoi(argv[2]), atoi(argv[3]));
        std::cout << "Division entera :\n" << i.GetX()  << " : " << i.GetY() << " = " << i.Div() << "\n";
    }
    else if (tipo == "F") {
        MiClase <float> f(atof(argv[2]), atof(argv[3]));
        std::cout << "Division floats :\n" << f.GetX()  << " : " << f.GetY() << " = " << f.Div() << "\n";
    }
    else {
        std::cout << "Orden no válido. Introduce 'I' o 'D'.\n";
    }
    return 0;
}