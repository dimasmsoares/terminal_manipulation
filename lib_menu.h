// lib_menu.h
#ifndef LIB_MENU_H
#define LIB_MENU_H

typedef struct {
    int n_opcoes;            // Tamanho do array
    int n_opcao_selecionada; // Índice atual
    char **opcoes;           // Ponteiro para ponteiro (Array de strings)
} Menu;

void menu_simple(Menu *menu);
int get_key_press();

#endif