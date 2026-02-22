/*
Desarrolle una función mapaDeHuecos que reciba un array disperso y devuelva un objeto donde las
claves sean los índices de inicio de los huecos consecutivos y los valores, la longitud de cada secuencia
de huecos.
Por ejemplo, para [1, , , 4, , , , 5, 6, ,], debe retornar {1: 2, 4: 3, 9: 1}
*/

const arr = [1, , , 4, , , , 5, 6, ,];

function mapaDeHuecos (arr){

    const ret = {};
    let esp=0;
    let pos=0
    for(let i=0; i<arr.length; i++){
        if(!(i in arr)){
            pos=i;
            while((!(i in arr)) && (i<arr.length)){
                esp++;
                i++
            }
            ret[pos]=esp;
            esp=0;
        }
    }
    return ret;
}

console.log(arr);

const data = mapaDeHuecos(arr);
console.log(data);