// lib_menu.c
#include "lib_menu.h"
#include <stdio.h>      // Necessário para printf
#include <stdlib.h>     // Necessário para system
#include <termios.h>    // Necessário para struct termios
#include <unistd.h>     // Necessário para STDIN_FILENO

int get_key_press() {
    struct termios oldt, newt;
    int ch;
    
    // Pega configurações atuais
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    
    // Desabilita buffer de linha e eco
    newt.c_lflag &= ~(ICANON | ECHO);
    
    // Aplica novas configurações
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    
    // Restaura configurações originais
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}

void menu_simple(Menu *menu) {
    // Esconde o cursor no início
    printf("\033[?25l");

    while (1) {
        system("clear"); 

        // --- Lógica de Impressão Corrigida ---
        for (int i = 0; i < menu->n_opcoes; i++) {
            if (menu->n_opcao_selecionada == i) {
                // Item selecionado: Mostra seta e destaque (opcionalmente cor)
                printf(" > [%s]\n", menu->opcoes[i]);
            } else {
                // Item não selecionado: Espaço em branco para alinhar
                printf("   %s\n", menu->opcoes[i]);
            }
        }

        int ch = get_key_press();

        // --- Lógica de Navegação ---
        if (ch == 27) { // ESC
            // O get_key_press é bloqueante, então chamamos novamente para pegar o resto da sequência
            // Sequência de seta: ESC (27) -> [ (91) -> A/B (65/66)
            
            ch = get_key_press(); 
            if (ch == 91) { 
                ch = get_key_press();
                
                switch(ch) {
                    case 65: // Seta Cima (A)
                        if (menu->n_opcao_selecionada > 0)
                            menu->n_opcao_selecionada--;
                        else
                            menu->n_opcao_selecionada = menu->n_opcoes - 1; // Loop para o final
                        break;
                        
                    case 66: // Seta Baixo (B)
                        if (menu->n_opcao_selecionada < menu->n_opcoes - 1)
                            menu->n_opcao_selecionada++;
                        else
                            menu->n_opcao_selecionada = 0; // Loop para o início
                        break;
                }
            }
        }
        else if (ch == 10) { // ENTER
            break; // Sai do loop e mantém a seleção salva na struct
        }
    }
    
    // Restaura o cursor antes de sair
    printf("\033[?25h");
}