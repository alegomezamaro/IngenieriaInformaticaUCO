/**
 * @file ip_utils.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include "ip_utils.hpp"
#include <sstream>
#include <string>
#include <algorithm>

IP::IP() : bytes({0, 0, 0, 0})
{
}
IP::IP(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
    : bytes({a, b, c, d})
{
}

bool IP::operator==(IP const &b) const
{
    return bytes == b.bytes;
}

bool IP::operator<(IP const &b) const
{
    return bytes < b.bytes;
}

std::ostream &
operator<<(std::ostream &out, const IP &ip)
{
    // TODO
    // Remember: we want to output the ascii code, not the char.

    out << static_cast<int>(ip.bytes[0]) << "." << static_cast<int>(ip.bytes[1]) << "." << static_cast<int>(ip.bytes[2]) << "."
    << static_cast<int>(ip.bytes[3]); //Salida de la dirección IP en formato decimal

    //
    return out;
}

std::istream &
operator>>(std::istream &in, IP &ip) noexcept(false)
{
    // TODO
    // Hint: you can use a std::istringstream to convert from text to uint8_t.
    // Hint: you can use the std::replace algorithm to replace '.' by ' '.
    // Remember: if a wrong format is detected, throw an runtime_error exception.

    std::string input; //Variable para almacenar la cadena de entrada
    in >> input; //Leemos la cadena de entrada
    std::replace(input.begin(), input.end(), '.', ' '); //Reemplazamos los '.' por espacios para poder leer los números
    std::istringstream iss(input); //Creamos un istringstream para poder leer los números separados por espacios
    int a, b, c, d; //Variables para almacenar los números leídos
     
    if (!(iss >> a >> b >> c >> d) || a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255) { //Comprobamos que los números leídos son válidos sino muestra un error
        throw std::runtime_error("Ip: wrong input format."); //Lanzamos una excepción si el formato es incorrecto
    }
     
     // Convertimos los números a uint8_t
     ip.bytes[0] = static_cast<uint8_t>(a); //Convertimos el número a uint8_t
     ip.bytes[1] = static_cast<uint8_t>(b); //Convertimos el número a uint8_t
     ip.bytes[2] = static_cast<uint8_t>(c); //Convertimos el número a uint8_t
     ip.bytes[3] = static_cast<uint8_t>(d); //Convertimos el número a uint8_t

    //
    return in;
}

std::uint64_t
ip_to_int(const IP &ip)
{
    std::uint64_t ret_val = 0l;
    // TODO
    // Remember: casting to 64 bits unsigned integer to do not loss bits.
    // Hint: mult by 2^n means shift to left n bits.

    ret_val = (static_cast<std::uint64_t>(ip.bytes[0]) << 24) + (static_cast<std::uint64_t>(ip.bytes[1]) << 16) +
              (static_cast<std::uint64_t>(ip.bytes[2]) << 8) + (static_cast<std::uint64_t>(ip.bytes[3])); //Convertimos la dirección IP a un número entero de 64 bits sin signo

    //
    return ret_val;
}
