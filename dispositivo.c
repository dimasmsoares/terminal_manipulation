#include <stdio.h>
#include <stdlib.h>

// TIPO ("CLASSE") BASE
typedef struct Dispositivo Dispositivo;

typedef struct {
    void (*executar)(Dispositivo *);
    void (*print_infos)(Dispositivo *);
} VT_Dispositivo;

struct Dispositivo{
    const VT_Dispositivo *vtable;
    const char *nome;
};

// TIPOS ("CLASSES") DERIVADAS ("HERDADAS")
/*** SENSOR TEMPERATURA ***/
typedef struct SensorTemperatura{
    Dispositivo dispositivo;
    float temperatura_atual;
} SensorTemperatura;

void st_init(SensorTemperatura *, float);
void print_st(Dispositivo *dispositivo);
void ler_temperatura(Dispositivo *dispositivo);

/*** SENSOR PRESSÃO ***/
typedef struct SensorPressao{
    Dispositivo dispositivo;
    float pressao_atual;
} SensorPressao;

void sp_init(SensorPressao *, float);
void print_sp(Dispositivo *dispositivo);
void ler_pressao(Dispositivo *dispositivo);

/*** MOTOR ***/
typedef struct Motor{
    Dispositivo dispositivo;
    int status;
} Motor;
void motor_init(Motor *, int);
void print_status(Dispositivo *dispositivo);
void mudar_status(Dispositivo *dispositivo);

// VTABLES
static const VT_Dispositivo vt_sensor_temperatura = {
    .executar = ler_temperatura,
    .print_infos = print_st
};

static const VT_Dispositivo vt_sensor_pressao = {
    .executar = ler_pressao,
    .print_infos = print_sp
};

static const VT_Dispositivo vt_motor = {
    .executar = mudar_status,
    .print_infos = print_status
};

int main(){
    
    SensorTemperatura *st = malloc(sizeof(SensorTemperatura));
    st_init(st, 24.4);

    SensorPressao *sp = malloc(sizeof(SensorPressao));
    sp_init(sp, 105.1);

    Motor *m = malloc(sizeof(Motor));
    motor_init(m, 0);
    
    Dispositivo *sistema[3] = {(Dispositivo *)st, (Dispositivo *)sp, (Dispositivo *)m};

    for(int i = 0; i < 3; i++){
        sistema[i]->vtable->print_infos(sistema[i]);
        sistema[i]->vtable->executar(sistema[i]);
        sistema[i]->vtable->print_infos(sistema[i]);
    }

    free(st);
    free(sp);
    free(m);

    return 0;
}

// "CONSTRUTORES"
void st_init(SensorTemperatura *st, float temp_init){
    st->dispositivo.vtable = &vt_sensor_temperatura;
    st->dispositivo.nome = "Sensor de Temperatura";
    st->temperatura_atual = temp_init;
}

void sp_init(SensorPressao *sp, float pressao_init){
    sp->dispositivo.vtable = &vt_sensor_pressao;
    sp->dispositivo.nome = "Sensor de Pressão";
    sp->pressao_atual = pressao_init;
}

void motor_init(Motor *m, int status_init){
    m->dispositivo.vtable = &vt_motor;
    m->dispositivo.nome = "Motor";
    m->status = status_init;
}


void ler_temperatura(Dispositivo *dispositivo){
    SensorTemperatura *st = (SensorTemperatura *)dispositivo;
    st->temperatura_atual += 0.2;
}

void ler_pressao(Dispositivo *dispositivo){
    SensorPressao *sp = (SensorPressao *)dispositivo;
    sp->pressao_atual += 5;
}

void mudar_status(Dispositivo *dispositivo){
    Motor *m = (Motor *)dispositivo;
    if(m->status == 0) m->status = 1;
    else m->status = 0;
}

void print_st(Dispositivo *dispositivo){
    SensorTemperatura *st = (SensorTemperatura *)dispositivo;
    printf("Dispositivo: %s\n", st->dispositivo.nome);
    printf("Valor atual: %f\n", st->temperatura_atual);
}

void print_sp(Dispositivo *dispositivo){
    SensorPressao *sp = (SensorPressao *)dispositivo;
    printf("Dispositivo: %s\n", sp->dispositivo.nome);
    printf("Valor atual: %f\n", sp->pressao_atual);
}

void print_status(Dispositivo *dispositivo){
    Motor *m = (Motor *)dispositivo;
    printf("Dispositivo: %s\n", m->dispositivo.nome);
    printf("Valor atual: %d\n", m->status);
}