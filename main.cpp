//
// Created by Alejandro Azurdia on 26/08/22.
//


#include <iostream>
#include <pthread.h>
using namespace std;
/****

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
            cout << i << " ";
            cout << suma << endl;
        }
    }
    return suma;
}

void *sumarPrimos(void *hilos){
    struct infoHilo *info = (struct infoHilo *)hilos;
    info->sumaparcial = sumarPrimos(info->min, info->max);
    pthread_exit((void*)(info->sumaparcial));
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

    for (int i = 0 ; i < nhilos; i++) {

        //int min = n * i;
        //int max = min + n - 1;
        //hilo.n = n;




    }
}
    ****/

struct info{
    int max = 25;
    int threads = 5;
    int n;
    int sumaparcial;
    int mint;
    int maxt;

};




bool esPrimo(int n){
    if (n == 0 || n == 1 || n == 4 || n == 2) return false;
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

    cout << "digamos que aquí pasa lo de ingrese cantidad maxima" << endl;
    int sumatotal = 0;

    info infohilo;
    infohilo.n = infohilo.max/infohilo.threads;
    cout << "El valor de n es: " << infohilo.n << endl;

    for (int i = 0; i < infohilo.n; i++){
        cout << "/***********************************/" << endl;
        cout << "Hilo " << i << endl;

        infohilo.mint = infohilo.n * i;
        infohilo.maxt = infohilo.mint + infohilo.n - 1;

        pthread_t hilo;
        pthread_create(&hilo, NULL, sumarPrimos, (void*)&infohilo);
        pthread_join(hilo, NULL);
        sumatotal += infohilo.sumaparcial;


    }

    cout << "El valor de la suma total es: " << sumatotal << endl;



}

