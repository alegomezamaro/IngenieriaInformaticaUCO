/*
Una cadena de producción en una fábrica de tecnología necesita controlar la calidad de los productos
ensamblados. Sus datos están organizados en un array de objetos, donde cada objeto representa un
producto que cuenta con los siguientes atributos:
• id: Identificador único del producto.
• components: Un array con los componentes del producto. Cada componente es representado
por un objeto con:
o type: tipo del componente ("chip", "sensor", "case", etc.).
o status: estado del componente ("OK", "DAMAGED" o "MISSING").
El sistema debe verificar si el producto está defectuoso (esto es, si al menos uno de sus componentes tiene
estado "DAMAGED" o "MISSING") o es válido (estado "OK"). Escriba una función en JavaScript que reciba el
array de productos y devuelva un array con los identificadores (id) de los productos defectuosos. No está
permitido el uso del bucle for clásico (for (..;..;..)), ni de métodos map(), reduce() o filter(),
en caso de conocerlos)
*/


const products = [
  { id: "P001",
    components: [
      { type: "chip", status: "OK" },
      { type: "sensor", status: "DAMAGED" }
    ]
  },
  { id: "P002",
    components: [
      { type: "chip", status: "OK" },
      { type: "sensor", status: "OK" },
      { type: "case", status: "OK" }
    ]
  },
  { id: "P003",
    components: [
      { type: "chip", status: "MISSING" },
      { type: "sensor", status: "OK" }
    ]
 }
];

function findProductosDefectuosos(products){

  const pDef = [];

  products.forEach( (item) => {

    let isOk = true;
    const {id: a, components: b} = item;

    b.forEach( (comp) => {
      
      const {status: c} = comp;
      if (c !== "OK"){
        isOk = false;
        // Podría hacerlo con for ..of para usar break; aquí
      }

    });

    if(!isOk) pDef.push(a);
  });

  return pDef;

}

const productosDefectuosos = findProductosDefectuosos(products);
console.log(productosDefectuosos);