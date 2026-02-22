const inv = [];
inv[0] = 100;
inv[2] = undefined;
inv[5] = 300;
delete inv[5];
inv[7] = null;
inv.extra = "metadato";
console.log("OG\n", inv);

function detectarTipo(item){

  const t = typeof item;
 
  if(t === "undefined") return {"__undefined__" : true};
  else return item;
  
}

function toJSONDenso(arr){

  const newArr = [];

  for ( let i = 0; i< arr.length; ++i){

    if( !(i in arr) )
      newArr[i] = {"__gap__" : true};
    else
      newArr[i] = detectarTipo(arr[i]);

  }

  return JSON.stringify(newArr);

}

function fromJSONDenso(strArr){

  const ogArr = JSON.parse(strArr);

  const newArr = [];

  for(let i = 0; i<ogArr.length; ++i){

    const val = ogArr[i];

    if( val && typeof val === "object" && val.__gap__ === true)
      continue;
    else if( val && typeof val === "object" && val.__undefined__ === true)
      newArr[i] = undefined;
    else newArr[i] = val;

  }

  return newArr;

}

const jsonStr = toJSONDenso(inv)

console.log("Stringify()\n", jsonStr);

const jsonArr =fromJSONDenso(jsonStr)

console.log("REVAMPED\n", jsonArr);