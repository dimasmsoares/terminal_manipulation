// main.c
#include <stdio.h>
#include "lib_menu.h"

int main() {
    // Definindo as opções
    char *meus_itens[] = {
        "Iniciar Jogo",
        "Configuracoes",
        "Carregar",
        "Sair"
    };

    // Configurando a struct
    Menu meu_menu;
    meu_menu.opcoes = meus_itens;
    meu_menu.n_opcoes = 4;
    meu_menu.n_opcao_selecionada = 0; // Começa na primeira opção

    // Chama a biblioteca
    menu_simple(&meu_menu);

    // Mostra o resultado
    printf("\nVoce escolheu a opcao indice: %d -> %s\n", 
           meu_menu.n_opcao_selecionada, 
           meu_menu.opcoes[meu_menu.n_opcao_selecionada]);

    return 0;
}