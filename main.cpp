//
// Created by Alejandro Azurdia on 26/08/22.
//

#include <iostream>
#include <pthread.h>
using namespace std;

struct infoHilo{
    int max;
    int min;
    int n;
    int sumaparcial;
};

// subrutina que comprueba si es primo
bool esPrimo(int n){
    if (n == 0 || n == 1 || n == 4) return false;
    for (int x = 2; x < n / 2; x++) {
        if (n % x == 0) return false;
    }
    return true;
}

// subrutina que suma todos los primos en un rango
int sumarPrimos(int min, int max){
    int suma = 0;
    for (int i = min; i <= max; i++){
        if(esPrimo(i)){
            suma += i;
        }
    }
    return suma;
}

void *sumarPrimos(void *hilos){
    struct infoHilo *info = (struct infoHilo *)hilos;
    info->sumaparcial = sumarPrimos(info->min, info->max);
    pthread_exit((void*)(info->sumaparcial));
}

// subrutina que encuentra los rangos para sumarPrimos.
int *encontrarRango(int n, int iteracion){
    int min = n * iteracion;
    int max = min + n - 1 ;

    int arr[2] = {min, max};

    return arr;

}


int main(){

    infoHilo hilo;
    int maxTotal = 0;
    int nhilos = 0;
    int n = 0;
    int hilo_id = 0;

    cout << "Ingrese cantidad máxima" << endl;
    cin >> maxTotal;

    cout << "Ingrese cantidad de hilos" << endl;
    cin >> nhilos;

    n = maxTotal/nhilos; // asegurar de que no sea punto decimal.
    cout << "El valor de n es: " << n << endl;

    for (int i = 0 ; i < nhilos; i++){
        int *rango = encontrarRango(n, i);
        hilo.max = rango[1];
        hilo.min = rango[0];
        hilo.n = n;

        pthread_t hilo_id;
        pthread_create(&hilo_id, NULL, sumarPrimos, (void *)&hilo);



    }













}