#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algoritmo.h"
#include "func.h"
#include "utils.h"

#define DEFAULT_RUNS	30  //Numero de vezes que corre o programa antes de fechar

// Função para preencher a estrutura
struct info preencherInfo(struct info infoPop) {
    infoPop.popsize = 100;
    infoPop.pm = 0.001;
    infoPop.pr = 0.7;
	infoPop.tsize = 2;
	infoPop.ro = 0.0;
    infoPop.numGenerations = 2500;

    // Retorna a estrutura preenchida
    return infoPop;
}

int main(int argc, char *argv[])
{
    FILE *f;
    int runs = DEFAULT_RUNS;
    struct info infoPop;
    ind best_run, best_ever;
    pind pop = NULL, parents = NULL;
    char name_file[100];
    int ger_atual,inv,i,r,j,count,count2,c;
    float moedas_disp[MAX_OBJ][2];
	float mbf = 0.0;
	count = count2 = 0;
	best_ever.fitness = MAX_OBJ*MAX_OBJ;

    printf("Ficheiro: \n");
    gets(name_file);

	f=fopen(name_file, "r");
	if(!f)
	{
		printf("Erro abrir ficheiro\n");
		exit(1);
	}

    infoPop = preencherInfo(infoPop);

	fscanf(f, "%d %f", &infoPop.num_moedas, &infoPop.valor_total);


	for(i=0; i<infoPop.num_moedas; i++){
        best_ever.p[i] = 10000;
	}

	for (int i = 0; i < infoPop.num_moedas; i++) {
        if (fscanf(f, "%f", &moedas_disp[i][1]) != 1) {
            fprintf(stderr, "Erro ao ler o valor %d da segunda linha\n", i + 1);
            fclose(f);
            return 0;
        }
    }

    // Faz um ciclo com o número de execuções definidas
	for (r=0; r<runs; r++)
	{
        init_rand();
        // Geração da população inicial
		pop = init_pop(infoPop);

        // Avalia a população inicial
		Avalia(pop, infoPop, moedas_disp);

        // Aplicação do algoritmo trepa colinas para refinar a população inicial
        trepa_colinas(pop, infoPop, moedas_disp);

		// Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
		best_run = pop[0];

        // Encontra-se a melhor solução dentro de toda a população
		best_run = get_best(pop, infoPop, best_run);

        // Reserva espaço para os pais da população seguinte
		parents = malloc(sizeof(ind)*infoPop.popsize);
        // Caso não consiga fazer a alocação, envia aviso e termina o programa
		if (parents==NULL)
		{
			printf("Erro na alocacao de memoria\n");
			exit(1);
		}

		// Ciclo de optimização
		ger_atual = 1;
		while (ger_atual <= infoPop.numGenerations)
		{
            // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
			tournament(pop, infoPop, parents);

//            tournament_geral(pop, infoPop, parents);

            genetic_operators(parents, infoPop, pop);

            // Avalia a nova população (a dos filhos)
			Avalia(pop, infoPop, moedas_disp);
            //trepa_colinas(pop, infoPop, moedas_disp);

            // Actualiza a melhor solução encontrada
			best_run = get_best(pop, infoPop, best_run);
			ger_atual++;
		}
        // Aplicação do algoritmo trepa colinas para refinar a população final
        //trepa_colinas(pop, infoPop, moedas_disp);

        best_run = get_best(pop, infoPop, best_run);

		// Contagem das soluções inválidas
		for (inv=0, i=0; i<infoPop.popsize; i++){
			if (pop[i].valido == 0)
				inv++;
		}

		printf("\nRepeticao %d:", r+1);
		write_best(best_run, infoPop);

		printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/infoPop.popsize);
		mbf += best_run.fitness;

                for(j=0; j<infoPop.num_moedas; j++){
                            count += best_run.p[j];
                            if(best_ever.p[j] == 0){
                                count2 = count2;
                            }
                            else{
                                count2 += best_ever.p[j];
                            }
                    }

		if (r==0 || best_run.valido == 1 && (best_run.fitness*100) <= (best_ever.fitness*100)){
                if(best_run.fitness == best_ever.fitness && count < count2){
                    best_ever = best_run;
                }
                else if(best_run.fitness < best_ever.fitness){
                    best_ever = best_run;
                }
		}

		count = count2 = 0;

		free(parents);
        parents = NULL;
		free(pop);
        pop = NULL;
	}

	// Escreve resultados globais
	printf("\n\nMBF: %f\n", mbf/r);
	printf("\nMelhor solucao encontrada");
	write_best(best_ever, infoPop);
    return 0;
}
