#include <stdio.h>

typedef struct Forma Forma;

typedef struct VT_Forma{
    double (*area)(Forma *);
} VT_Forma;

typedef struct Forma{
    VT_Forma *v_table;
} Forma;

typedef struct Circulo{
    Forma forma;
    double raio;
} Circulo;

typedef struct Retangulo{
    Forma forma;
    double largura;
    double altura;
} Retangulo;

double area_circulo(Forma *self){
    Circulo *c = (Circulo *)self;
    return 3.14159*(c->raio)*(c->raio);
}

double area_retagulo(Forma *self){
    Retangulo *r = (Retangulo *)self;
    return (r->altura)*(r->largura);
}

int main(){
    VT_Forma vt_circulo = {area_circulo};
    VT_Forma vt_retangulo = {area_retagulo};

    Circulo c;
    Retangulo r;

    c.forma.v_table = &vt_circulo;
    c.raio = 5;
    r.forma.v_table = &vt_retangulo;
    r.largura = 2;
    r.altura =5;

    Forma *formas[2] = {(Forma *)&c, (Forma *)&r};

    for(int i = 0; i < 2; i++){
        double x = formas[i]->v_table->area(formas[i]);
        printf("%f\n", x);
    }

    return 0;
}