#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

// Inicialização do gerador de números aleatórios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Simula o lançamento de uma moeda, retornando o valor 0 ou 1
int flip()
{
	if ((((float)rand()) / RAND_MAX) < 0.5)
		return 0;
	else
		return 1;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
pind init_pop(struct info d)
{
	int     i, j;
	pind  indiv;

	indiv = malloc(sizeof(ind)*d.popsize);

	if (indiv==NULL)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
	for (i=0; i<d.popsize; i++)
	{
		for (j=0; j<d.num_moedas; j++){
			indiv[i].p[j] = random_l_h(0, d.popsize-1);
		}
	}
	return indiv;
}

// Actualiza a melhor solução encontrada
ind get_best(pind pop, struct info d, ind best)
{
	int i,j;
	int count,count2;
	count = count2 = 0;

	for (i=0; i<d.popsize; i++)
	{
	    for(j=0; j<d.num_moedas; j++){
            count += pop[i].p[j];
            if(best.p[j] == 0){
                count2 = count2;
            }
            else{
                count2 += best.p[j];
            }
	    }

        if(pop[i].valido == 1 && (best.fitness*10000) <= (pop[i].fitness*10000)){
                if(best.fitness == pop[i].fitness && count < count2 ){
                    best=pop[i];
                }
                else if(pop[i].fitness < best.fitness){
                    best=pop[i];
                }
        }
        count = count2 = 0;
	}
	return best;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}

// Escreve uma solução na consola
void write_best(ind x, struct info d)
{
	int i;

	printf("\nBest individual: %4.2f\n", x.fitness);
	for (i=0; i<d.num_moedas; i++)
		printf("%d ", x.p[i]);
	putchar('\n');
}
