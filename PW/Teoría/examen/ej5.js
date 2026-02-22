/*
Defina un objeto como función constructora, Counter, que de alguna forma encapsule un contador
privado y proporcione un método único que, al ser invocado, devuelva un objeto con dos métodos:
increment() y getValue(). El método increment() debe incrementar el contador privado, y
getValue() debe retornar el valor actual del contador. La peculiaridad es que cada invocación al
método que expone increment() y getValue() debe devolver nuevos invocadores
independientes que mantengan su propio estado del contador.
*/


function Counter() {

  this.getCounterMethods = function (){
    let count = 0;

    return {
      increment: function(){ count++; },
      getValue: function(){ return count;}
    }
  }

}

// new Counter().getCounterMethods().increment()
// new Counter().getCounterMethods().getValue()
const myCounter = new Counter();
const counterMethods = myCounter.getCounterMethods();
counterMethods.increment();
counterMethods.increment();
const counterMethods2 = myCounter.getCounterMethods();
counterMethods2.increment();
console.log("1: " + counterMethods.getValue()); // 1: 2
console.log("2: " + counterMethods2.getValue()); // 2: 1