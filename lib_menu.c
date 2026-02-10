// lib_menu.c
#include "lib_menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

const char *codigos_texto[] = {"30", "31", "32", "33", "34", "35", "36", "37", "39"};
const char *codigos_fundo[] = {"40", "41", "42", "43", "44", "45", "46", "47", "49"};

void aplicar_cor(Cor texto, Cor fundo) {
    printf("\033[%s;%sm", codigos_texto[texto], codigos_fundo[fundo]);
}

void resetar_cor() {
    printf("\033[0m");
}

int get_key_press() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// ... (Sua função menu_simple original estava ok, mantive omitida para focar na multi) ...
void menu_simple(MenuSimple *menu) {
    // ... (Copie sua lógica do menu_simple aqui, ela estava 90% correta)
    // Apenas certifique-se de usar menu->titulo no printf inicial
     printf("\033[?25l");
    while (1) {
        system("clear");
        if(menu->titulo){
            aplicar_cor(menu->cor_texto_titulo, menu->cor_fundo_titulo);
            printf("### %s ###\n\t%s\n\n", menu->titulo, menu->comando);
            resetar_cor();
        }
        for (int i = 0; i < menu->n_opcoes; i++) {
            if (menu->n_opcao_selecionada == i) {
                aplicar_cor(menu->cor_texto_sel, menu->cor_fundo_sel);
                printf(" > [%s] \n", menu->opcoes[i]);
                resetar_cor();
            } else {
                aplicar_cor(menu->cor_texto_norm, menu->cor_fundo_norm);
                printf("   %s \n", menu->opcoes[i]);
                resetar_cor();
            }
        }
        int ch = get_key_press();
        if (ch == 10) break;
        if (ch == 27) {
            ch = get_key_press();
            if (ch == 91) {
                ch = get_key_press();
                if (ch == 65) { if(menu->n_opcao_selecionada > 0) menu->n_opcao_selecionada--; }
                else if (ch == 66) { if(menu->n_opcao_selecionada < menu->n_opcoes - 1) menu->n_opcao_selecionada++; }
            }
        }
    }
    printf("\033[?25h");
}


void menu_multi(MenuMulti *menu) {
    int pos_cursor = 0;
    // O cursor pode ir de 0 até n_opcoes.
    // Se pos_cursor == n_opcoes, significa que está no botão "AVANÇAR"
    
    printf("\033[?25l");

    while (1) {
        system("clear");

        // 1. Título
        if(menu->titulo){
            aplicar_cor(menu->cor_texto_titulo, menu->cor_fundo_titulo);
            printf("### %s ###\n\t%s\n\n", menu->titulo, menu->comando);
            resetar_cor();
        }

        // 2. Opções (Checkboxes)
        for (int i = 0; i < menu->n_opcoes; i++) {
            // Verifica se este item está selecionado pelo cursor
            if(pos_cursor == i){
                aplicar_cor(menu->cor_texto_sel, menu->cor_fundo_sel);
            } else {
                aplicar_cor(menu->cor_texto_norm, menu->cor_fundo_norm);
            }

            // Imprime [X] ou [ ] baseado no estado salvo
            printf(" %c [%c] %s ", (pos_cursor == i ? '>' : ' '), menu->selecoes[i], menu->opcoes[i]);
            
            resetar_cor();
            printf("\n");
        }

        printf("\n"); // Espaço antes do botão

        // 3. Botão AVANÇAR
        if(pos_cursor == menu->n_opcoes){ // Cursor está no botão
            aplicar_cor(menu->cor_texto_sel, menu->cor_fundo_sel);
            printf("   [ AVANÇAR ]   ");
        } else {
            aplicar_cor(menu->cor_texto_norm, menu->cor_fundo_norm);
            printf("     AVANÇAR     ");
        }
        resetar_cor();
        printf("\n");

        // 4. Input
        int ch = get_key_press();

        if (ch == 27) { // Setas
            ch = get_key_press();
            if (ch == 91) {
                ch = get_key_press();
                switch(ch) {
                    case 65: // Cima
                        if (pos_cursor > 0) pos_cursor--;
                        else pos_cursor = menu->n_opcoes; // Loop volta para o botão Avançar
                        break;
                    case 66: // Baixo
                        if (pos_cursor < menu->n_opcoes) pos_cursor++;
                        else pos_cursor = 0; // Loop volta para o topo
                        break;
                }
            }
        }
        else if (ch == 10) { // ENTER
            if (pos_cursor == menu->n_opcoes) {
                // Se pressionou Enter no botão AVANÇAR, sai do menu
                break; 
            } else {
                // Se pressionou Enter numa opção, alterna (Toggle)
                if(menu->selecoes[pos_cursor] == ' ') 
                    menu->selecoes[pos_cursor] = 'X';
                else 
                    menu->selecoes[pos_cursor] = ' ';
            }
        }
    }
    printf("\033[?25h");
}