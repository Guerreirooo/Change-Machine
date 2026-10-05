#define MAX_OBJ 1000

// Estrutura para armazenar parametros
struct info
{
    int popsize;
    // Tamanho da população (numero de moedas do troco)
    int     num_moedas;
    // Probabilidade de mutação
    float   pm;
    // Probabilidade de recombinação
    float   pr;
    // Tamanho do torneio para seleção do pai da próxima geração
	int     tsize;
	// Constante para avaliação com penalização
	float   ro;
	// Valor que é suposto obter (V do enunciado)
	float     valor_total;
	// Número de gerações
    int     numGenerations;

};

typedef struct individual ind, *pind;

struct individual
{
    // Solução (numero quantitativo de cada moeda)
    int     p[MAX_OBJ];
    // Valor da qualidade da solução
	float   fitness;
    // 1 se for uma solução válida e 0 se não for
	int     valido;
};

void tournament(pind, struct info, pind);

void tournament_geral(pind, struct info, pind);

void genetic_operators(pind, struct info, pind);

void mutation(pind, struct info);

void mutacao_por_troca(pind, struct info);
