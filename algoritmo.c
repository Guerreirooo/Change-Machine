#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
void tournament(pind pop, struct info d, pind parents)
{
	int i, x1, x2;
    x1 = x2 = 0;
	// Realiza popsize torneios
	for (i=0; i<d.popsize;i++)
	{
		x1 = random_l_h(0, d.popsize-1);
		do
			x2 = random_l_h(0, d.popsize-1);
		while (x1==x2);
		if (pop[x1].fitness < pop[x2].fitness)		// Problema de minimização
			parents[i] = pop[x1];
		else
			parents[i] = pop[x2];
	}
}

// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario
void tournament_geral(pind pop, struct info d, pind parents)
{
	int i, j, k, sair, best, *pos;

	pos = malloc(d.tsize*sizeof(int));
	// Realiza torneios
	for(i=0; i<d.popsize;i++)
	{
	    // Seleciona tsize soluções diferentes para entrarem em torneio de seleção
		for(j=0; j<d.tsize; j++)
        {
            do
            {
                pos[j] = random_l_h(0, d.num_moedas-1);
                // Verifica se a nova posição escolhida é igual a alguma das outras posições escolhidas
                sair = 0;
                for (k=0; k<j; k++)
                {
                    if (pos[k]==pos[j])
                        sair = 1;
                }
            }
            while (sair);
            // Guarda a posição da melhor solução de todas as que entraram em torneio
            if (j==0 || pop[pos[j]].fitness < pop[pos[best]].fitness)		// Problema de minimização
                best = j;
        }
        parents[i] = pop[pos[best]];
	}
	free(pos);
}

// Operadores geneticos a usar na geração dos filhos
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void genetic_operators(pind parents, struct info d, pind offspring)
{
	// Recombinação com dois pontos de corte
//	recombinacao_dois_pontos_corte(parents, d, offspring);
	// Recombinação uniforme
//	recombinacao_uniforme(parents, d, offspring);
	// Mutação binária
//    mutation(offspring, d);
    // Mutação por troca
	mutacao_por_troca(offspring, d);
}

// Mutação binária com vários pontos de mutação
void mutation(pind offspring, struct info d)
{
	int i, j;

	for (i=0; i<d.popsize; i++)
		for (j=0; j<d.num_moedas; j++)
			if (rand_01() < d.pm)
				offspring[i].p[j] = random_l_h(0,9);
}

// Mutação por troca
void mutacao_por_troca(pind offspring, struct info d)
{
	int i, pos1, pos2, aux;

	if(d.num_moedas == 1){
        printf("Mutacao por troca so funciona quando num_moedas > 1");
        return 0;
	}

	for (i=0; i<d.popsize; i++){
        if (rand_01() < d.pm)
        {
            pos1 = random_l_h(0, d.num_moedas-1);
            pos2 = random_l_h(0, d.num_moedas-1);

            aux = offspring[i].p[pos1];
            offspring[i].p[pos1] = offspring[i].p[pos2];
            offspring[i].p[pos2] = aux;
        }
	}
}

// Preenche o vector descendentes com o resultado da operação de recombinação com dois pontos de corte
void recombinacao_dois_pontos_corte(pind parents, struct info d, pind offspring)
{
    int i, j, point1, point2;
    if((d.popsize%2)==0){
        point1 = point2 = i = j = 0;

        for (i = 0; i < d.popsize; i+=2) // A população é iterada em pares
        {
            if (rand_01() < d.pr) // Realiza a recombinação com probabilidade definida
            {
                // Gera dois pontos de corte garantindo a ordem correta e limites válidos
                point1 = random_l_h(0, d.num_moedas - 2);
                point2 = random_l_h(point1, d.num_moedas - 1);

                // Copia os genes antes do primeiro ponto de corte
                for (j = 0; j < point1; j++)
                {
                    offspring[i].p[j] = parents[i].p[j];
                    offspring[i + 1].p[j] = parents[i + 1].p[j];
                }

                // Faz a troca de genes entre os pontos de corte
                for (j = point1; j < point2; j++)
                {
                    offspring[i].p[j] = parents[i + 1].p[j];
                    offspring[i + 1].p[j] = parents[i].p[j];
                }

                // Copia os genes após o segundo ponto de corte
                for (j = point2; j < d.num_moedas; j++)
                {
                    offspring[i].p[j] = parents[i].p[j];
                    offspring[i + 1].p[j] = parents[i + 1].p[j];
                }
            }
            else
            {
                // Se não houver recombinação, os descendentes são cópias dos pais
                offspring[i] = parents[i];
                offspring[i + 1] = parents[i + 1];
            }
        }
    }
    else{
        printf("Recombinacao apenas funciona com a quantidade de solucoes par");
    }
}


// Preenche o vector descendentes com o resultado da operação de recombinação uniforme
void recombinacao_uniforme(pind parents, struct info d, pind offspring)
{
	int i, j;
     if((d.popsize%2)==0){
        for(i=0; i<d.popsize; i+=2)
        {
            if(rand_01() < d.pr)
            {
                for(j=0; j<d.num_moedas; j++)
                {
                    if (flip() == 1)
                    {
                        offspring[i].p[j] = parents[i].p[j];
                        offspring[i+1].p[j] = parents[i+1].p[j];
                    }
                    else
                    {
                        offspring[i].p[j] = parents[i+1].p[j];
                        offspring[i+1].p[j] = parents[i].p[j];
                    }
                }
            }
            else
            {
                offspring[i] = parents[i];
                offspring[i+1] = parents[i+1];
            }
        }
    }
    else{
        printf("Recombinacao apenas funciona com a quantidade de solucoes par");
    }
}
