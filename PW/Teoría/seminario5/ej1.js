/*  Dispones de un array que representa un inventario, donde el índice es la “posición física” en el
    almacén y el valor es el id del producto. El array puede ser disperso (con huecos) y contener
    distintos valores (números, null, undefined, etc.).
    Para comenzar, crea este array: */
        const inventario = [];
        inventario[0] = 101;
        inventario[2] = undefined;
        inventario[5] = 104;
        delete inventario[5];
        inventario[7] = null;
        inventario.extra = "metadato";
/*  Implementa una función condensarInventario(arr) que devuelva un array denso de longitud
    arr.length, cumpliendo:
    • Si el índice no existe en arr (hueco), en la salida pon { id: null, estado: 'hueco' }.
    • Si el índice existe y el valor es:
    o número ⇒ { id: valor, estado: 'ok' }
    o undefined ⇒ { id: undefined, estado: 'indefinido' }
    o null ⇒ { id: null, estado: 'nulo' }
    o cualquier otro ⇒ { id: valor, estado: 'otro' }
    Para implementar esta función, no utilices delete (para “crear” huecos). Ten en cuenta que
    forEach ignoran huecos. También puedes usar el operador in para distinguir hueco de
    undefined.
    Finalmente, comprueba cómo funciona cada bucle de la siguiente forma: sobre el inventario
    original y sobre el inventario denso de condensarInventario(arr):
    • forEach → muestra por consola cada par (índice, valor) visitado.
    • for...of → muestra por consola los valores que produce (fíjate en los huecos).
    • for...in → muestra por consola las claves que visita (fíjate si aparece extra). */

inventario.forEach( (item) => {
    console.log(item);
})

function detectarTipo(item){
    const map = {
        "number":{ id: item, estado: 'ok' },
        "undefined":{ id: undefined, estado: 'indefinido' },
        "null":{ id: null, estado: 'nulo' },
        "other":{ id: item, estado: 'otro' },   
    }
    const type = typeof item;
    if(item === null) return map["null"];
    return map[type] || map["other"];
}

    function condensarInventario(arr){
    let ret = [];
    for(let i=0; i<arr.length; i++){
        if(!(i in arr)) ret[i]={ id: null, estado: 'hueco' };
        else ret[i] = detectarTipo(arr[i]);
    }
    return ret;
}

inventarioDenso = condensarInventario(inventario);
inventarioDenso.forEach((item) => {
  console.log(item);
})