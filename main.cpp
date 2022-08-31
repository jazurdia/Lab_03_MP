//
// Created by Alejandro Azurdia on 26/08/22.
//


/*******************************************************************************
 * Inicio de la parte A del laboratorio 3 de Programación de Microprocesadores.
 * Fecha de entrega: 29 de agosto de 2022.
***/


#include <iostream>
#include <pthread.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


using namespace std;

struct info{
    int max;
    int threads;
    int n;
    int sumaparcial;
    int mint;
    int maxt;

};

bool esPrimo(int n){
    if (n == 0 || n == 1 || n == 4 ) return false;
    for (int x = 2; x < n / 2; x++) {
        if (n % x == 0) return false;
    }
    return true;
}


void *sumarPrimos(void* info){
    struct info *infoHilo = (struct info *)info;
    int suma = 0;
    for (int i = infoHilo->mint; i <= infoHilo->maxt; i++){
        cout << "cheking " << i << "   ";
        if(esPrimo(i)){
            suma += i;
            cout << i << "  es primo. ";
        }
        cout << endl;
    }
    infoHilo->sumaparcial = suma;
    pthread_exit((void*)(infoHilo->sumaparcial));

}

int mainA(){

    int sumatotal = 0;

    info infohilo;

    cout << "Ingrese el numero maximo: " << endl;
    cin >> infohilo.max;

    cout << "Ingrese el numero de hilos: " << endl;
    cin >> infohilo.threads;


    infohilo.n = infohilo.max/infohilo.threads;
    cout << "El valor de n es: " << infohilo.n << endl;

    for (int i = 0; i < infohilo.threads; i++){

        if(i == infohilo.threads - 1){

            cout << "/***********************************/" << endl;
            cout << "Hilo " << i << endl;

            infohilo.mint = i * infohilo.n + 1;
            infohilo.maxt = infohilo.max;

            pthread_t hilo;
            pthread_create(&hilo, NULL, sumarPrimos, (void*)&infohilo);
            pthread_join(hilo, NULL);
            sumatotal += infohilo.sumaparcial;

        } else {
            cout << "/***********************************/" << endl;
            cout << "Hilo " << i << endl;

            infohilo.mint = infohilo.n * i;
            infohilo.maxt = infohilo.mint + infohilo.n - 1;

            pthread_t hilo;
            pthread_create(&hilo, NULL, sumarPrimos, (void*)&infohilo);
            pthread_join(hilo, NULL);
            sumatotal += infohilo.sumaparcial;
        }

    }

    cout << "El valor de la suma total es: " << sumatotal << endl;

}

/***
* Inicio de la parte B del laboratorio 3 de Programación de Microprocesadores.
* Fecha de entrega: 31 de agosto de 2022.
*/

// funcion para p_threads que evalua n en la sumatoria.
void *sumatoria(void *arg){
    float *n;
    n = (float *)arg;
    float *resultado;
    resultado = (float *)malloc(sizeof(float));
    *resultado = 1/((*n)*((*n)-1));
    return (void *)resultado;
}

int mainB(){
    float n;
    cout << "Ingrese el numero n: " << endl;
    cin >> n;
    float resSumatoria = 0;

    for (int i = 2; i < n; i++) {
        pthread_t hilo;
        pthread_attr_t attr;

        float v = (float) i;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        void *exit_value;
        pthread_create(&hilo, &attr, sumatoria, (void *) &v);
        pthread_join(hilo, &exit_value);
        float res = *((float *) exit_value);
        free(exit_value);

        resSumatoria += res;
    }

    cout << "El valor de la sumatoria es: " << resSumatoria << endl;

    return 0;

}


/***
* Main para elegir que parte del laboratorio 3 de Programación de Microprocesadores ejecutar.
*/


int main(){

    bool flag = true;
    while(flag){
        cout << endl;
        cout << "Elige la parte a ejecutar: " << endl;
        cout << "1. Parte A" << endl;
        cout << "2. Parte B" << endl;
        cout << "3. Salir" << endl;
        int opcion;
        cin >> opcion;
        switch (opcion){
            case 1:
                mainA();
                break;
            case 2:
                mainB();
                break;
            case 3:
                flag = false;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }
}