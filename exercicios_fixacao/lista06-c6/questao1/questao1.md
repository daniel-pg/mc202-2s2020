# Questão 1

* É possível determinar a saída do programa (ou parte dela)? Qual?  

O trecho de código apresentado tem tantos problemas que certamente seria
possível determinar a saída do programa: um terrível e assustador Segmentation Fault.
Primeiramente, um erro menos importante que podemos notar é o fato de que a função
f() não tem efeito nenhum, pois não altera nenhum valor nem retorna nada. Até aí tudo
bem, nada que dê Segmentation Fault. A coisa piora quando tentamos acessar uma região
inválida da memória `d[1]` e alocar um outro bloco de memória nesse endereço, o que causa
comportamento indefinido, isso fora o fato da função g() não devolver nem alterar nenhum
valor também. Após isso, outro erro grave é cometido: tentamos dereferenciar um ponteiro
não inicializado, que pode apontar pra qualquer lugar, e depois tentamos guardar
o valor `100` nesse endereço. Por fim, liberamos o ponteiro `d` sem antes liberar os
conteúdos armazenados na região apontada por ele.

* Existe _memory leak_?  

Sim. A memória alocada pela função g() não foi liberada corretamente.

*  Modifique para que toda memória alocada seja liberada e a saída seja a esperada: 2, 3, 100.

Feito no arquivo `codigo_corrigido.c`.