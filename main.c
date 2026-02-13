// main.c
#include <stdio.h>
#include <stdlib.h> // Para calloc (opcional, mas recomendado)
#include "lib_menu.h"

int main() {
    // --- MENU 1: SIMPLES ---
    char *opcoes1[] = {"Jogar", "Opcoes", "Sair"};

    MenuSimple m1 = {0}; // Usar m1
    m1.titulo = "MENU PRINCIPAL";
    m1.comando = "Use ENTER para selecionar";
    m1.opcoes = opcoes1;
    m1.n_opcoes = 3;
    m1.cor_texto_titulo = COR_PRETA; m1.cor_fundo_titulo = COR_BRANCA;
    m1.cor_texto_sel = COR_VERMELHA; m1.cor_fundo_sel = COR_PADRAO;
    m1.cor_texto_norm = COR_AZUL;    m1.cor_fundo_norm = COR_PADRAO;

    menu_simple(&m1);

    printf("\nSelecionado no Menu 1: %s\n\n", m1.opcoes[m1.n_opcao_selecionada]);

    // --- MENU 2: MÚLTIPLO ---
    char *opcoes2[] = {"Queijo", "Tomate", "Bacon", "Cebola"};
    
    // Precisamos de um array para guardar os X ou espaços.
    // Inicializamos tudo com espaço ' '.
    char selecoes_usuario[] = {' ', ' ', ' ', ' '}; 

    MenuMulti m2 = {0}; // Usar m2
    m2.titulo = "INGREDIENTES PIZZA";
    m2.comando = "Marque com ENTER e desca ate AVANCAR";
    m2.opcoes = opcoes2;
    m2.n_opcoes = 4;
    m2.selecoes = selecoes_usuario; // Passamos o array que criamos
    
    // Cores
    m2.cor_texto_titulo = COR_AMARELA; m2.cor_fundo_titulo = COR_PADRAO;
    m2.cor_texto_sel = COR_BRANCA;     m2.cor_fundo_sel = COR_PADRAO;
    m2.cor_texto_norm = COR_BRANCA;    m2.cor_fundo_norm = COR_PADRAO;

    menu_multi(&m2);

    printf("\nIngredientes escolhidos:\n");
    for(int i=0; i < m2.n_opcoes; i++){
        if(m2.selecoes[i] == 'X'){
            printf("- %s\n", m2.opcoes[i]);
        }
    }

    return 0;
}
