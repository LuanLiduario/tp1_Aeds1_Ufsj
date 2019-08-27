#include "tp.h"
//CONfERIR carregarProduto, novoProduto, realizar venda
void main (){
    ListaProduto *estoque = NULL;
    int qtd_prod = 0, opcao = showMenu();
    estoque = carregarProdutos(&qtd_prod);
    ListaProduto *aux = estoque;
    while(opcao != 0){
        if(opcao== 1){
            estoque = novoProduto(estoque, &qtd_prod);
        }
        if(opcao == 2){
            realizarVenda(estoque);

        }
        opcao = showMenu();
    }
    gravarProdutos(estoque, qtd_prod);
    system("pause");
    return;
}

