#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Inicio d
typedef struct{
    char *nome;
    float valor;
}Produto;

typedef struct{
    Produto produto;
    int qtd;
}ItemVenda;

typedef struct ListaProduto{
    Produto produto;
    struct ListaProduto *proximo;
}ListaProduto;

void imprimeLinha(char, int);

void imprimeAEsquerda(char *, char, int);

void imprimeADireita(char *, char, int);

void imprimeItemVenda(ItemVenda);

ListaProduto* novoProduto(ListaProduto*, int*);

int showMenu();

float calculaTotal(ItemVenda[], int);

void notaFiscal (ItemVenda[], int);

ListaProduto *carregarProdutos(int*);

void gravarProdutos (ListaProduto*, int);

Produto* buscarProduto (ListaProduto*, char *);

void realizarVenda(ListaProduto*);
