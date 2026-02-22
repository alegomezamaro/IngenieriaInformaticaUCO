// Cree una función llamada crearObjeto que tome como argumentos un nombre y una edad, y
// devuelva un objeto con:
// 1. Una propiedad nombre con el valor pasado como argumento.
// 2. Una propiedad edad con el valor pasado como argumento.
// 3. Un método actualizarEdad que reciba un número y actualice la propiedad edad.
// Demuestre su uso actualizando la edad de un objeto creado.

function crearObjeto(nombre, edad){

    return{
        nombre: nombre,
        edad: edad,
        actualizarEdad: function (n){
            this.edad = n;
        }
    }
}

const obj = crearObjeto("Javi", 22);

console.log(obj);
obj.actualizarEdad(18);
console.log(obj);