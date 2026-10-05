#include <stdio.h>
#include <math.h>
#include "algoritmo.h"
#include "func.h"
#include "utils.h"

#define ITER_TC  1000
#define MAX_OBJ 1000

// Calcula a qualidade de uma solução com penalização
float eval_individual_penalizado(int sol[], struct info d, float moedas_disp[][2], int *v)
{
	int     i,k;
	float   sum_weight, sum_profit,penalty, ro_aux;

    d.ro = -1;
	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i=0; i < d.num_moedas; i++)
	{
        // Verifica se o objecto i esta no troco
		if (sol[i] > 0)
		{
            // Actualiza o peso total
			sum_weight += sol[i];
            // Actualiza o lucro total
			sum_profit += (sum_weight * moedas_disp[i][1]);
            // Obtem o melhor ro
            ro_aux = moedas_disp[i][1]/(float)sol[i];
            if (ro_aux < d.ro)
                d.ro = ro_aux;
		}
	}
	if (sum_profit > d.valor_total)
	{
        // Solução Válida
		*v = 1;
		return sum_profit;
	}
	else
	{
        // Solução Inválida
        *v = 0;
        return (d.valor_total - sum_profit) + 1000;
	}
}

// Calcula a qualidade de uma solução com reparação aleatória
float eval_individual_reparado1(int sol[], struct info d, float moedas_disp[][2], int *v)
{
	int i, r = 0;
	float sum_weight, sum_profit;

	sum_profit = 0;
	sum_weight = 0;

	// Percorre todos os objetos
	for (i = 0; i < d.num_moedas; i++) {
		// Verifica se o objeto i está no troco
		if (sol[i] > 0) {
			// Atualiza o peso total
			sum_weight += sol[i];

			// Atualiza o lucro total
			sum_profit += (sum_weight * moedas_disp[i][1]);
			sum_weight = 0;
		}
	}

	// Processo de reparação
	while (fabs((d.valor_total)-(sum_profit)) > 0.001) {
        i = random_l_h(0, d.num_moedas-1);

		if (sum_profit > d.valor_total) {
				if (sol[i] > 0) {
					sol[i]--;
					sum_profit -= moedas_disp[i][1];
				}
		}
		else {
                sol[i]++;
                sum_weight += 1;
                sum_profit += moedas_disp[i][1];
		}
		d.valor_total = roundf(d.valor_total * 1000) / 1000;
		sum_profit = roundf(sum_profit * 1000) / 1000;
	}

    *v = 1;

	return sum_profit;
}


// Avaliacao da população
void Avalia(pind pop, struct info d, float moedas_disp[][2])
{
	int i;

	for (i=0; i<d.popsize; i++){
        pop[i].fitness = 0;
		pop[i].fitness = eval_individual_reparado1(pop[i].p, d, moedas_disp, &pop[i].valido);
	}
}

void gera_vizinho(int sol[], int solViz[], int num_moedas)
{
    int i;

    // Copia a solução para a solução vizinha
    for (i=0; i < num_moedas; i++)
        solViz[i] = sol[i];

    // escolhe um objeto aleatoriamente
    i = random_l_h(0, num_moedas-1);

    solViz[i] = solViz[i] + 1;
}

void gera_vizinho2(int sol[], int solViz[], int num_moedas)
{
    int i;

    // Copia a solução para a solução vizinha
    for (i=0; i < num_moedas; i++)
        solViz[i] = sol[i];

    // escolhe um objeto aleatoriamente
    i = random_l_h(0, num_moedas-1);

    solViz[i] = solViz[i] + 2;
}

void trepa_colinas(pind pop, struct info d, float moedas_disp[][2])
{
    int     i, j;
    ind   vizinho;

    for (i=0; i<d.popsize; i++)
    {
        for (j=0; j<ITER_TC; j++)
        {
              gera_vizinho2(pop[i].p, vizinho.p, d.num_moedas);
              vizinho.fitness = eval_individual_reparado1(vizinho.p, d, moedas_disp, &vizinho.valido);
              if (vizinho.fitness >= pop[i].fitness)
                pop[i] = vizinho;
        }
    }
}
