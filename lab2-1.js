function isInteger(num ){
    return Number.isInteger(num);
}
console.log(isInteger(1));//true
console.log(isInteger(1.5));//false
console.log(isInteger(-0.5))//false

function isPrime(num){
    for(let i=2, max=Math.sqrt(num);i<=max;i++){
        if(num%i===0) return false
    }
    return num > 1;
}
console.log(isPrime(4));

