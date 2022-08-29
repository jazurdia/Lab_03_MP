//
// Created by Alejandro Azurdia on 26/08/22.
//


#include <iostream>
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

int main(){

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

