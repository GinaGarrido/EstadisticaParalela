#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <math.h>

using namespace std;

void participante();
             
vector<int> obtenerPuntajes(std::string linea);

void leeGuarda(std::string filename);
double prom(std::vector<double> valor);
void moda(std::vector<double> valor);
void mediana(std::vector<double> valor);
void desviacion(std::vector<double> valor, double prom);

int main(int argc, char** argv) {
    if (argc > 1) {
        std::string ruta(argv[1]);
        leeGuarda(ruta);
    } else {
        participante();
    }
    return EXIT_SUCCESS;
}

void leeGuarda(std::string filename){
    std::ifstream entrada(filename);
    //std::ofstream salida("promedio.csv");
    std::vector<double> nem;
    std::vector<double> ranking;
    std::vector<double> matematica;
    std::vector<double> lenguaje;
    std::vector<double> ciencias;
    std::vector<double> historia;
    
    if (entrada){
        for (std::string linea; getline(entrada, linea);) {  
            vector<int> puntajes = obtenerPuntajes(linea);
            if (puntajes.size() >= 6) {
                nem.push_back(puntajes.at(1));
                ranking.push_back(puntajes.at(2));
                matematica.push_back(puntajes.at(3));
                lenguaje.push_back(puntajes.at(4));
                ciencias.push_back(puntajes.at(5));
                historia.push_back(puntajes.at(6));
                }
            puntajes.clear();
            }
        
#pragma omp parallel 
        {
#pragma omp single 
            {
#pragma omp task 
                {
                    std::cout << std::endl << "=== Nem ==" << std::endl;
                    double promnem=prom(nem);
                    moda(nem);
                    mediana(nem);
                    desviacion(nem,promnem);
                }
            }
#pragma omp single 
            {            
#pragma omp task 
                {
                    std::cout << std::endl << "=== Ranking ==" << std::endl;
                    double promrank=prom(ranking);
                    moda(ranking);
                    mediana(ranking);
                    desviacion(ranking,promrank);
                }
            }
#pragma omp single 
            {  
#pragma omp task 
                {
                    std::cout << std::endl << "=== Matemática ==" << std::endl;
                    double promat=prom(matematica);
                    moda(matematica);
                    mediana(matematica);
                    desviacion(matematica,promat);

                }
            }
#pragma omp single 
            {  
#pragma omp task 
                {
                    std::cout << std::endl << "=== lenguaje ==" << std::endl;
                    double promleng=prom(lenguaje);
                    moda(lenguaje);
                    mediana(lenguaje);
                    desviacion(lenguaje,promleng);
                }
            }
#pragma omp single 
            { 
#pragma omp task 
                {
                    std::cout << std::endl << "=== ciencias ==" << std::endl;
                    double promcien=prom(ciencias);
                    moda(ciencias);
                    mediana(ciencias);
                    desviacion(ciencias,promcien);
                }
            }
#pragma omp single 
            {
#pragma omp task 
                {
                    std::cout << std::endl << "=== historia ==" << std::endl;
                    double promhist=prom(historia);
                    moda(historia);
                    mediana(historia);
                    desviacion(historia,promhist);
                }
            }
        }
    }
}

double prom(std::vector<double> valor){
    
    double valorprom=0;
    
    for (std::size_t i=0; i< valor.size(); i++){
        valorprom+=valor[i];
        }
    
    valorprom=valorprom/valor.size();
    std::cout << std::endl << " Promedio: "<< valorprom << std::endl;
    return valorprom;
}

void moda(std::vector<double> valor){
    int punt=0, frec=0;
    map<double,int> datoMap;
    
    for (std::size_t i=0; i< valor.size()-1; i++){
        datoMap[valor[i]]++;
        }
    
    for( map<double,int>::iterator maximo=datoMap.begin(); maximo!=datoMap.end();maximo++){
        if ((maximo->second) > frec){
            frec=maximo->second;
            punt=maximo->first;
        }
    }
    std::cout << std::endl<< " Moda: "<< punt << std::endl;
}

void mediana(std::vector<double> valor){
    int suma=0;
    double median;
    int posMedio=valor.size()/2;
    map<double,int> datoMap;
    
    for (std::size_t i=0; i< valor.size()-1; i++){
        datoMap[valor[i]]++;
    }
    for(map<double,int>::iterator maximo=datoMap.begin(); maximo!=datoMap.end();maximo++){
        suma+=maximo->second;
        if (suma>=posMedio){
            median= maximo->first;
            break;
        }
    }
    std::cout << std::endl<< " Mediana: "<<median<< std::endl;
}

void desviacion(std::vector<double> valor, double prom){
    double varianza=0;
    for (std::size_t i=0; i< valor.size(); i++){
        varianza = varianza + pow((valor[i]-prom),2);
    }
    double std= sqrt(varianza/(valor.size()-1));
    std::cout << std::endl<< " Desviación: "<< std << std::endl;
    
}

void participante() {
    std::cout << std::endl << "=== Taller 1 ===" << std::endl;
    std::cout << std::endl << "Gina Geinse Garrido Cabezas" << std::endl; 
}

vector<int> obtenerPuntajes(std::string linea) {
    vector<int> arreglo;
    std::stringstream ss(linea);
    std::string item;

    while (std::getline(ss, item, ';')) {
        int valor = atoi(item.c_str());
        arreglo.push_back(valor);
        
    }

    return arreglo;
}
