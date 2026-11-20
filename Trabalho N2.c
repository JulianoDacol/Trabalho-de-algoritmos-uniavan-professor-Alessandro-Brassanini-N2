 /*
 * Trabalho da N2 - Algoritmos I
 * Professor: Alessandro Joao Brassanini
 * Tema: simulacao de um dia de vendas de uma loja.
 *
 * Equipe (preencher com os nomes completos antes da entrega):
 * Integrante 1: JULIANO DACOL HENQUEMAIER
 *
 * O codigo usa somente recursos do C padrao ANSI (C89).
 * Os textos estao sem acentos para facilitar o uso em terminais diversos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PRODUTOS 200
#define CLIENTES 50
#define PRECO_MINIMO 5
#define PRECO_MAXIMO 100

/* Retorna um numero aleatorio entre 0 e limite - 1.
 * Todas as chamadas usam limite maior que zero.
 */
int sortear(int limite)
{
    return rand() % limite;
}

int main(void)
{
    int npro;
    int ncli;
    int i;
    int produto;
    int maisVendido;
    int compra[CLIENTES];
    int quantidadeVendida[PRODUTOS];
    float preco[PRODUTOS];
    float total;

    srand((unsigned int) time(NULL));

    /* Sorteia de 1 a 200 produtos e de 1 a 50 clientes. */
    npro = 1 + sortear(PRODUTOS);
    ncli = 1 + sortear(CLIENTES);

    /* Cada produto recebe um preco fixo para todo o dia.
     * Assim como no exemplo do enunciado, os precos sao sorteados
     * em reais inteiros: 5, 6, ..., 100, exibidos com duas casas.
     */
    for (i = 0; i < npro; i++) {
        preco[i] = (float) (PRECO_MINIMO
                   + sortear(PRECO_MAXIMO - PRECO_MINIMO + 1));
        quantidadeVendida[i] = 0;
    }

    /* compra[i] guarda o indice do produto comprado pelo cliente i.
     * Um mesmo produto pode ser comprado por diferentes clientes,
     * pois o enunciado nao estabelece limite de estoque.
     */
    total = 0.0f;
    for (i = 0; i < ncli; i++) {
        compra[i] = sortear(npro);
        produto = compra[i];
        quantidadeVendida[produto]++;
        total += preco[produto];
    }

    printf("==================================================\n");
    printf("          LOJA SORTE & CIA - VENDAS DO DIA\n");
    printf("==================================================\n");
    printf("Simulacao para:\n");
    printf("  %d produtos\n", npro);
    printf("  %d clientes\n\n", ncli);
    printf("Os codigos de clientes e produtos comecam em zero.\n\n");
    printf("Cliente       Produto          Valor (R$)\n");
    printf("--------------------------------------------------\n");

    /* O valor de compra[i] e usado como indice no vetor preco.
     * Seus valores ficam entre 0 e npro - 1, dentro do vetor.
     */
    for (i = 0; i < ncli; i++) {
        printf("%7d       %7d          %10.2f\n",
               i, compra[i], preco[compra[i]]);
    }

    printf("--------------------------------------------------\n");
    printf("TOTAL DE VENDAS: R$ %.2f\n", total);

    /* Resumo adicional: valor medio gasto e produtos mais vendidos.
     * ncli e sempre pelo menos 1, evitando divisao por zero.
     */
    printf("Valor medio por cliente: R$ %.2f\n", total / ncli);

    maisVendido = 0;
    for (i = 1; i < npro; i++) {
        if (quantidadeVendida[i] > quantidadeVendida[maisVendido]) {
            maisVendido = i;
        }
    }

    /* Exibe todos os produtos empatados na maior quantidade vendida. */
    printf("\nProduto(s) mais vendido(s):\n");
    for (i = 0; i < npro; i++) {
        if (quantidadeVendida[i] == quantidadeVendida[maisVendido]) {
            printf("  Produto %d: %d venda(s), preco R$ %.2f\n",
                   i, quantidadeVendida[i], preco[i]);
        }
    }
    printf("==================================================\n");

    return 0;
}
