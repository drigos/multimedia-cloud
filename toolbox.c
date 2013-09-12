#include "toolbox.h"

// Imprime um número em binário
void bprint(long int var, int size) {
	int i;
	for (i = size ; i >= 0 ; i--)
   fprintf(stdout, "%ld", (var >> i) % 2);
}

// Os 53 primeiros números primos
// Usados no algoritmo gerador de número aleatório
int prime_numbers[53] = {
   2,31,73,127,179,233,37,79,131,
   181,239,3,83,137,191,241,5,41,
   139,193,7,43,89,149,197,11,47,
   97,199,13,53,101,151,17,59,103,
   157,211,61,107,163,223,19,109,
   167,227,23,67,173,229,29,71,113};
// Índice para array primeNumbers
int ind = 0;

int get_rand(int min, int max) {
   // Recebe o número gerado
   int chosen;
   // o intervalo entre max e min é deslocado para o zero e atribuído ao max
   max -= min;
   // Calcula o valor de clock() multiplicado pelo quadrado de Pi e um valor da array de números primos
   // Depois executa o mod do valor máximo deslocado para zero, mais um pois senão nunca geraria o próprio número max
   // Adiciona o min como uma correção de offset deslocando para o intervalo original
   chosen = (int) ((unsigned int)((clock()+time(NULL)) * PI_SQR * prime_numbers[ind]) % (max+1)+min);

   //printf("((%ld+%ld) * %f * %d) %% (%d + 1) + %d = %d", clock(), time(NULL), pi_sqr, prime_numbers[ind], max, min, chosen);

   // A variável index é incrementada para que na próxima execução o valor seja diferente mesmo que o número gerado por clock() seja igual ao anterior
   ind++;
   // Garante que o valor de index sempre vai estar dentro dos limites da array primeNumbers
   ind %= 53;

   return chosen;
}
