/*  Implementa compactarHuecos(arr), que elimine los huecos de un array preservando el orden de
    los elementos definidos. Además, debe preservar el valor undefined si es un valor explícito
    almacenado en una posición existente (no un hueco).
    Implementa dos variantes de esta función:
    1.  Destructiva: compactación del mismo array original usando dos variables como punteros o
        iteradores. Si necesitas eliminar elementos al final del array, utiliza length pero evita delete
        para generar los huecos (no se recomienda su uso).
    2.  No destructiva: devuelve un nuevo array comprimido (el original no se modifica).
    Puedes utilizar el siguiente array de entrada: */
        const a = [];
        a[0] = 10;
        a[2] = undefined;
        a[5] = 30;
        delete a[5];
        a[7] = 40;
        a.extra = "meta"; 
/*  Pistas:
    •   Recuerda que for...in recorre claves presentes (y puede incluir propiedades que no sean
        índice), mientras que un bucle for por índices recorre 0..length-1. Para este ejercicio, se
        recomienda que utilices índices numéricos.
    •   delete deja huecos, pero evita su uso. splice reindexa y ajusta length.
    •   i in a dice si el índice existe
    Para probar tu código debes realizar, al menos, la siguiente prueba:
    •   Imprime length antes y después.
    •   Imprime los índices presentes con for (let i=0; i<a.length; i++)
        console.log(i in a, a[i]).
    •   Verifica que a.extra sigue existiendo como propiedad, pero no como elemento del array
        comprimido. */

console.log("=== ESTADO INICIAL ===");
console.log("Longitud:", a.length);
for (let i = 0; i < a.length; i++) {
    // i in a devuelve false si es un hueco
    console.log(`Índice ${i}: Presente=${i in a}, Valor=${a[i]}`);
}

const arr2 = a;

function compactarHuecosD(arr){
    let j=0;
    for(let i=0; i<arr.length; i++){
        if(i in arr){
            arr[j] = arr[i];
            j++;
        }
    }
    arr.length = j;
    return arr;
}

function compactarHuecosN(arr2){

    const ret = [];
    let j=0;

    for(let i=0; i<arr2.length; i++){
        if(i in arr2){
            ret[j] = arr2[i];
            j++;
        }
    }
    ret.length = j;
    return ret;
}

const dest = compactarHuecosD(a);
const node = compactarHuecosN(a);

console.log("\n=== TRAS COMPACTACIÓN DESTRUCTIVA ===");
console.log("Longitud:", dest.length);

for (let i = 0; i < dest.length; i++) {
    console.log(`Índice ${i}: Presente=${i in dest}, Valor=${dest[i]}`);
}

console.log("\n¿Sigue existiendo extra?:", dest.extra);

console.log("\n=== TRAS COMPACTACIÓN NO DESTRUCTIVA ===");
console.log("Longitud:", node.length);

for (let i = 0; i < node.length; i++) {
    console.log(`Índice ${i}: Presente=${i in node}, Valor=${node[i]}`);
}

console.log("\n¿Sigue existiendo extra?:", node.extra);