#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

/*PROTOTIPOS*/
int get_key_press();
void edit_entry(Entry *e);
int print_form (Form *f);

typedef struct {
    char *label;
    char value[101];   // buffer real
    int max_len;
} Entry;

typedef struct {
    char *label;
    char **options;   // vetor de strings - ponteiro para ponteiros = array de char *
    int n_options;
    int selected;     // pra navegação
} Droplist;

typedef struct{
    Entry entry_name;
    Droplist droplist_cargo;
    Droplist droplist_nivel;
} Form;

int main(){

    Entry nome = {
        .label = "Nome Completo",
        .max_len = 100
    }
    strcpy(nome.value, "");

    char *opcoes_cargo[] = {"Auxiliar", "Técnico", "Analista", "Consultor"};
    Droplist cargo = {
        .label = "Cargo",
        .options = opcoes_cargo,
        .n_options = 4,
        .selected = 0
    };

    char *opcoes_nivel[] = {"A1", "A2", "A3", "A4", "B5", "B6", "B7", "B8", "Especial 9", "Especial 10"};
    Droplist nivel = {
        .label = "Nivel",
        .options = opcoes_nivel,
        .n_options = 10,
        .selected = 0
    };

    Form formulario = {nome, cargo, nivel};

    int selecionado = 0;

    while(1){
        system("clear");
        printf("\033[?25l");

        for(int i = 0; i < form.n_opcoes; i++){
            if(selecionado == i){
                printf(">\t%s%s\n", form.campos[i], form.valores[i]);
            }
            else{
                printf("\t%s%s\n", form.campos[i], form.valores[i]);
            }
        }

        int ch = get_key_press();
        /*Quando pressionamos uma tecla que não pertence a tabela ASCII, o computador envia não um, mas 3 bytes em sequência para
        para nosso programa:
        27 (ESC): É o caractere "Escape". Ele serve como um alerta.
        91 ([): Na tabela ASCII, o 91 é o abre colchetes. Nos padrões de terminal (ANSI/VT100), o ESC seguido de [ inicia a maioria 
        dos comandos de movimentação de cursor.
        XX (): Um byte, que especifica o comando. Ex: (66) = seta para baixo ↓ | (65) = seta para cima ↑*/

        // Verifica se é uma seta de es uma seta "↑" "↓" ou "ENTER".
        if(ch == 27){   // Escape (ESC)
            ch = get_key_press();
            if(ch == 91){
                ch = get_key_press();
                if(ch == 65){   // Seta para cima
                    if(selecionado > 0){
                        selecionado --;
                    }
                    else{
                        selecionado = form.n_opcoes - 1;
                    }
                } // if(ch == 65)
                else if(ch == 66){  // Seta para baixo
                    if(selecionado < (form.n_opcoes -1)){
                        selecionado ++;
                    }
                    else{
                        selecionado = 0;
                    }
                } // else if(ch == 66)
            } // if(ch == 91)
        } // if(ch == 27)

        if(ch == 10){   // ENTER
            printf("\n%d\n", selecionado);
            break;
        }
    }

    printf("\033[?25h");

    return 0;
}

int get_key_press(){
    /*No Linux/Unix, a função _getch() existente no Windows não existe por padrão. O terminal funciona em modo "canônico" 
    (espera uma linha inteira e o "Enter"). Para simular o comportamento do Windows, precisamos manipular as configurações 
    do terminal manualmente usando a estrutura "termios".*/

    // Cria duas variáveis para guardar as configurações do terminal: oldt (configuração antiga/original) e newt (nova 
    // configuração que vamos criar).
    struct termios oldt, newt;  
    
    // Variável para armazenar o caractere pressionado
    int ch;
    
    // Pega (get) os atributos atuais do terminal e salva em oldt. Esses atributos definem o comportamento do terminal.
    // Ex: (ICANON) Esperar o ENTER para a execução do comando | (ECHO) Mostra na tela o caractere da tecla pressionada.
    tcgetattr(STDIN_FILENO, &oldt);
    
    // Copia as configurações originais para a variável newt. Vamos modificar essa cópia.
    newt = oldt;
    
    // Desligando duas "bandeiras" (flags) de configuração usando operações bit a bit:
    newt.c_lflag &= ~(ICANON | ECHO);
    
    // Aplica (set) as novas configurações ao terminal agora (TCSANOW). A partir deste momento, o terminal para de 
    // esperar o Enter e de mostrar letras.
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    // Lê o caractere pressionado e guarda na variável ch. 
    ch = getchar();

    // Restaura as configurações originais (oldt)
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // Retorna o caractere lido para quem chamou a função.
    return ch;
}   // END FUCTION get_key_press

void edit_entry(Entry *e){
    int ch;
    int pos = strlen(e->value);

    // garante que não estoure se vier algo estranho
    if(pos > e->max_len) pos = e->max_len;

    printf("\033[?25h"); // mostra cursor

    while(1){
        ch = get_key_press();

        /* ENTER → termina edição */
        if(ch == 10){
            break;
        }

        /* BACKSPACE (Linux: 127 | alguns terminais: 8) */
        if(ch == 127 || ch == 8){
            if(pos > 0){
                pos--;
                e->value[pos] = '\0';

                /* apaga visualmente */
                printf("\b \b");
                fflush(stdout);
            }
        }
        /* caracteres imprimíveis */
        else if(ch >= 32 && ch <= 126){
            if(pos < e->max_len){
                e->value[pos++] = ch;
                e->value[pos] = '\0';

                putchar(ch);
                fflush(stdout);
            }
        }
    }

    printf("\033[?25l"); // esconde cursor
}

int print_form (Form *f){
    int selecionado = 0;
    while(1){
        system("clear");

    } // END WHILE
}