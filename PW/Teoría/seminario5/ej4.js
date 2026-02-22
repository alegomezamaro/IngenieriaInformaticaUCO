const datos = [];
datos[0] = 10;
datos[1] = undefined;
datos[5] = 30;
datos[6] = 10;
datos[9] = undefined;
datos.extra = "metadato que no debe contarse";

// SUPONGO QUE UNDEFINED == 0;

function addMedia( item , media , nx ){

  const type = typeof item;

  if(type === "number"){
    media += item;
    ++nx;
  }
  else if(type === "undefined"){
    media += 5;
    ++nx;
  }

  return {media, nx};

}

function calcMediana(oldArr){

  let mediana, pos=0;
  const arr = []

  for( let i = 0; i<oldArr.length; ++i){

    if( i in oldArr ) arr[pos++] = oldArr[i];

  }

  const len = arr.length;
  if (len % 2 == 0){

    pos1 = len/2;
    pos2 = (len/2) - 1;

    let a = arr[len/2];
    let b = arr[(len/2)-1];

    if ( pos1 in arr && typeof a === "undefined" ) a = 0;
    if ( pos2 in arr && typeof b === "undefined" ) b = 0;

    mediana = (a+b) / 2;
  }
  else{

    pos1 = Math.round(len/2) - 1;

    let a = arr[pos1];

    console.log(a, pos1);

    if ( pos1 in arr && typeof a === "undefined" ) a = 0;

    mediana = a;
  }

  return mediana;
}

function updModa( m, item ){

  if ( !m.has(item) )
    m.set(item, 1);
  else
    m.set(item, m.get(item)+1);

  return m;

}

function calcularEstadística(arr){

  let media = 0, mediana = 0;
  const moda = [];
  let m = new Map();
  let nx = 0;

  mediana = calcMediana(arr);

  for( let i = 0; i<arr.length; ++i){

    const isHueco = !(i in arr);
    if( isHueco ) continue;
  
    ({media, nx} = addMedia(arr[i] , media, nx));
    m = updModa( m, arr[i] );

  }

  let max = 0;
  for (const [key,value] of m){
    console.log(key, value);
    if( value > max ){
      moda.splice(0, moda.length);
      moda.push(key);
      max = value;
    }
    else if(value === max) moda.push(key);
  }

  data = {
    media: media/nx,
    mediana: mediana,
    moda: (moda.length == 1) ? moda[0] : moda,
    n_elementos: nx
  }

  return data;
}

const obj = calcularEstadística(datos);

console.log(obj);



