const entrada = [1, "2", true, null, undefined, NaN, "tres"];
const dificil = [ "10", " 3.5 ", "-2e3", "", "42px", NaN, Infinity, false ];


function isValid( data , item ){

  const n = Number(item);
  const isNan = (Number.isNaN(n));
  const isInfinity = !(Number.isFinite(n));
  
  if( !isNan && !isInfinity){
    data.decisiones.push({original: item,
                          convertido: n,
                          razon: "Es incluido porque Number(original) no retorna NaN ni Infinity"});
    data.incluidos++;
    data.suma+=n;
  }
  else if( isNan ){
    data.decisiones.push({original: item,
              convertido: null,
              razon: "No es incluido porque Number(original) retorna NaN"});
    data.excluidos++;
  } 
  else{
    data.decisiones.push({original: item,
            convertido: null,
            razon: "No es incluido porque Number(original) retorna Infinity o -Infinity"});
    data.excluidos++;
  }
}

function sumaRobusta(arr){

  const data = {
    suma: 0,
    incluidos: 0,
    excluidos: 0,
    decisiones: []
  }

  for( let i = 0; i < arr.length; ++i){

    isValid(data, arr[i]);

  }

  return data;
}

console.log(sumaRobusta(entrada));
console.log(sumaRobusta(dificil));