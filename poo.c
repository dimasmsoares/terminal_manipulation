#include <stdio.h>

typedef struct Numero Numero;

typedef struct Numero{
    int valor;

    void (*imprimir)(Numero *self);
    void (*incrementar)(Numero *self);
    void (*decrementar)(Numero *self);
} Numero;

void incrementar_numero(Numero *self){
    ++self->valor;
}

void decrementar_numero(Numero *self){
    --self->valor;
}

void imprimir_numero(Numero *self){
    printf("%d\n", self->valor);
}

int main(){
    Numero x = {
        .valor = 24,
        .incrementar = incrementar_numero,
        .decrementar = decrementar_numero,
        .imprimir = imprimir_numero,
    };

    x.imprimir(&x);
    x.incrementar(&x);
    x.imprimir(&x);
    x.decrementar(&x);
    x.decrementar(&x);
    x.imprimir(&x);

    return 0;
}