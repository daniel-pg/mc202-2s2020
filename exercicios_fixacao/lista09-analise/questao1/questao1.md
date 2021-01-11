# Questão 1

(a) Escreva as funções a seguir usando uma notação O adequada e mais simples:
* n<sup>5</sup> + 100000
* log<sub>35</sub> (n<sup>n</sup>)
* 2<sup>n−0.1</sup>
* 2<sup>log(n<sup>2</sup>)</sup>
* 1000<sup>1000n</sup> + n<sup>n</sup>

R:  
1. O(n<sup>5</sup>)
2. O(x⋅ln(x))
3. O(2<sup>n</sup>)
4. O(n<sup>2</sup>)
5. O(n<sup>n</sup>)

(b)  Prove ou desprove as afirmações:

2<sup>n</sup> = O(2<sup>n−0.001</sup>)  
2<sup>n</sup> = O(2<sup>0.999⋅n</sup>)  
n<sup>2</sup> = O(n<sup>1.999</sup>)  

1. Verdadeiro, pois podemos separar a exponencial na soma de outra exponencial com uma constante, que é descartada na notação do grande O.
1. Falso, não satisfaz a propriedade da notação O.
1. Falso, não satisfaz a propriedade da notação O.
