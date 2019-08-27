#include "tp.h"

void imprimeLinha(char c, int x){
    for (int i=0; i<x; i++){
        printf("%c", c);
    }
}

void imprimeAEsquerda(char *s, char c, int x){
    printf("%s", s);
    for(int i=0; i< (x -(strlen(s))); i++){//tirando \0
        printf("%c", c);
    }
}

void imprimeADireita(char *s, char c, int x){
    for(int i=0; i< (x -(strlen(s))); i++){
        printf("%c", c);
    }
    printf("%s", s);
}

void imprimeItemVenda(ItemVenda x){
    imprimeAEsquerda(x.produto.nome, ' ', 30);
    char *vQtd = (char*)malloc(sizeof(char)*12); //string para valor e quantidade
    sprintf(vQtd, "%.2f", x.produto.valor);
    strcat(vQtd, " x ");
    char *qtd= (char*)malloc(sizeof(char)*7);
    itoa(x.qtd, qtd, 10);
    strcat(vQtd, qtd);
    strcat(vQtd, " =");
    imprimeAEsquerda(vQtd, ' ', 12);
    float subTotal = x.produto.valor * (float)x.qtd;
    char *sTotal = (char*)malloc(sizeof(char)*9);
    sprintf(sTotal, "%.2f", subTotal);
    imprimeADireita(sTotal, ' ', 8);
    free(sTotal);
    free(vQtd);
    free(qtd);
}

ListaProduto* novoProduto(ListaProduto *estoque, int *produtosCadastrados){
    Produto p;
    p.nome = (char*) malloc(sizeof(char)*30);
    fflush(stdin);
    printf("Digite o nome do produto: ");
    fflush(stdin);
    gets(p.nome);
    printf("\nDigite o valor do produto: ");
    scanf("%f", &p.valor);
    fflush(stdin);
    ListaProduto *novo = (ListaProduto*) malloc(sizeof(ListaProduto));
    novo->produto = p;
    novo->proximo = estoque;
    estoque = novo;
    (*produtosCadastrados)++;
    return estoque;
}

int showMenu(){
    int op;
    printf("\n");
    imprimeLinha('*', 50);
    printf("\n");
    imprimeADireita("MENU DE OPCOES", ' ', 34);
    printf("\n");
    imprimeLinha('*', 50);
    printf("\n0 - SAIR \n1 - CADASTRAR NOVO PRODUTO \n2 - REALIZAR VENDA \n");
    imprimeLinha('*', 50);
    printf("\nINFORME SUA OPCAO: ");
    scanf("%d", &op);
    return op;
}

float calculaTotal(ItemVenda v[], int qtdItens){
    float total = 0.0;
    for(int i=0; i<qtdItens; i++){
        total += v[i].produto.valor * v[i].qtd;
    }
    return total;
}

void notaFiscal(ItemVenda v[], int qtdItens){
    printf("\n");
    imprimeLinha('*', 50);
    printf("\n");
    imprimeADireita("NOTA FISCAL", ' ', 30);
    printf("\n");
    imprimeLinha('*', 50);
    printf("\n");
    for(int i=0; i<qtdItens; i++){
        imprimeItemVenda(v[i]);
        printf("\n");
    }
    imprimeLinha('*', 50);
    printf("\n");
    float total= calculaTotal(v,qtdItens);
    int i= (int)total;
    int tam=0;
    while(i>0){
        i=i/10;
        tam++;
    }
    imprimeADireita("TOTAL = ",' ', 47-tam);
    printf("%.2f",total);
    printf("\n");
    imprimeLinha('*', 50);
    printf("\n \n \n");
}

ListaProduto* carregarProdutos(int *qtdProdCad){
    FILE *arq = fopen("produtosCadastrados.txt", "rb");
    ListaProduto *estoque = NULL;
    fread(qtdProdCad,sizeof(int),1, arq);
    for(int i=0;i<*qtdProdCad; i++){
        Produto p;
        int tamString;
        fread(&tamString,sizeof(int),1, arq);
        p.nome = (char*) malloc(sizeof(char)*(tamString+1));
        fread(p.nome, sizeof(char), tamString, arq);
        p.nome[tamString] = '\0';
        fread(&p.valor, sizeof(float), 1, arq);
        ListaProduto *novo = (ListaProduto*) malloc(sizeof(ListaProduto));
        novo->produto = p;
        novo->proximo = estoque;
        estoque = novo;
    }
    fclose(arq);
    return estoque;
}

void gravarProdutos(ListaProduto *estoque, int qtdProd){
    int t;
    if (estoque == NULL) {
        printf("\nESTOQUE VAZIO\n");
        return;
    }
    FILE *arq = fopen("produtosCadastrados.txt","wb");
    if(arq==NULL){
        printf("erro");
        exit(1);
    }
    ListaProduto *aux = estoque;
    fwrite(&qtdProd, sizeof(int),1, arq);
    for(int i = 0; i<qtdProd; i++){
        t = strlen(aux->produto.nome);
        fwrite(&t, sizeof(int),1, arq);
        fwrite(aux->produto.nome, sizeof(char), t, arq);
        fwrite(&aux->produto.valor, sizeof(float), 1, arq);
        aux = aux->proximo;
    }
    fclose(arq);
}

Produto* buscarProduto(ListaProduto *estoque, char *nomePesq){
    ListaProduto *aux = estoque;
    while(aux != NULL){
        if(strcmp(aux->produto.nome, nomePesq) == 0){
            return &aux->produto;
        }
        aux = aux->proximo;
    }
    return NULL;
}

void realizarVenda(ListaProduto *produtos){
    Produto *p = (Produto*) malloc(sizeof(Produto));
    char *nome = (char*) malloc(sizeof(char) * 30);
    ItemVenda venda[100];
    int posicaoVenda =0;
    int qtdVendida = 0;
    fflush(stdin);
    while(1){
        printf("\nDigite o nome do produto: ");
        fflush(stdin);
        fgets(nome, 30, stdin);
        fflush(stdin);
        if(strcmp(nome, "\n\0") == 0){
                break;
        }else{
        nome[strlen(nome)-1] = '\0';
        p = buscarProduto(produtos, nome);
        if(p != NULL){
                printf("\nInforme a quantidade: ");
                scanf("%d", &qtdVendida);
                venda[posicaoVenda].produto = *p;
                venda[posicaoVenda].qtd = qtdVendida;
                posicaoVenda++;

        }else{
                printf("\nProduto não encontrado\n");
            }
        }
    }
    notaFiscal(venda, posicaoVenda);
}




