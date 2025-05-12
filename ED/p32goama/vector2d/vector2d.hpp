/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <iostream>
#include <memory>

/**
 * @brief Models a vector in the plane.
 *
 * A tiny model to practice several c++ concepts:
 * - C++ templates.
 * - typename keyword.
 * - Shared references.
 * - Static class method.
 * - Implement the "Design by Contract" paradigm in c++
 *
 * The specification to implement is:
 *
 * Makers:
 *
 * create() //Default constructor. Return a reference to a zero vector.
 *   - post-c: x()==0 and y()==0
 * create(x:T, y:T) //return a reference to a vector given its ordinates.
 *   - post-c: x()==x and y()==y
 *
 * Observers:
 *
 * x():T // the x ordinate.
 * y():T // the y ordinate.
 *
 * Modifiers:
 *
 * set_x(T x) //set the x ordinate.
 *   - post-c: x==x()
 * set_y(T y) //set the y ordinate.
 *   - post-c: y==y()
 * add(Vector2D o) // add the vector o to this.
 *   - post-c: x()==old.x()+o.x()
 *   - post-c: y()==old.y()+o.y()
 *
 *
 * @tparam T represent the number type for the ordinates.
 */

// TODO: define the interface for the proposed ADT.
// Remember: here we want interfaces not implementations.

template <class T>
class Vector2D
{
public:
    /** @name Public types.*/

    /** @name Life cycle.*/
    /** @{*/
    Vector2D();
    Vector2D(T const &x_v, T const &y_v);
    ~Vector2D();
    /** @}*/

    /** @name Observers.*/
    /** @{*/
    T const &x() const;
    T const &y() const;
    /** @}*/

    /** @name Modifiers.*/
    /** @{*/
    void set_x(T const &x_v);
    void set_y(T const &y_v);
    void add(const Vector2D<T> &o);
    /** @}*/

protected:
    // The representation.
    // TODO: choose one.
    T x_; // The x ordinate.
    T y_; // The y ordinate.
    //
};

//

#include <vector2d_imp.hpp>