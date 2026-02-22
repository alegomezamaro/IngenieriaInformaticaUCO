/*
Sobrescribe el método toString del prototipo de Array para que devuelva una cadena con los
elementos del array separados por | (carácter barra horizontal) en lugar de la coma por defecto.
Demuestra el resultado con el array [10, 20, 30]
*/

const arr = [10, 20, 30];
arr.extra = "hey";

console.log(arr.toString());

Array.prototype.toString = function () {
  return this.join("|");
};


console.log(arr.toString());