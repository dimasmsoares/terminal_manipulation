#include <stdio.h>

typedef struct Veiculo Veiculo;

typedef struct VTVeiculos{
    void (*print_veiculo)(Veiculo *);
} VTVeiculos;

typedef struct Veiculo{
    int rodas;
    VTVeiculos *v_table;
} Veiculo;

void print(Veiculo *self){
    for(int i = 0; i < self->rodas; i++){
        printf("O");
    }
    printf("\n");
}

void print2(Veiculo *self){
    for(int i = 0; i < self->rodas; i++){
        printf("=");
    }
    printf("\n");
}

int main(){
    VTVeiculos vt_veiculos = {print};

    Veiculo v1 = {4, &vt_veiculos};
    Veiculo v2 = {2, &vt_veiculos};

    v1.v_table->print_veiculo(&v1);
    v2.v_table->print_veiculo(&v2);

    return 0;
}