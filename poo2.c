#include <stdio.h>
typedef struct Data Data;

typedef struct Data{
    int d;
    int m;
    int y;

    void (*add_dias)(Data *, int);
    void (*mostrar_data)(Data *);
} Data;

void adicionar_dias(Data *data, int dias){
    if(data->y % 4 == 0){
	if(data->y % 100 == 0){
        //não bissexto
	}
	else if(data->y % 400 == 0){
	}
    }
     data->d += dias;
}

void print_data(Data *data){
    printf("%02d/%02d/%02d\n", data->d, data->m, data->y);
}

Data __init__(int d, int m, int y){
    Data data;
    
    data.d = d;
    data.m = m;
    data.y = y;

    data.add_dias = adicionar_dias;
    data.mostrar_data = print_data;
    return data;
}

int main(){
    Data data = __init__(1,1,2026);
    
    data.mostrar_data(&data);

    data.add_dias(&data, 20);

    data.mostrar_data(&data);

    return 0;
}
