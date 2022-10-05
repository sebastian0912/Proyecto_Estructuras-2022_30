#include "Secuencia.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <iterator>

#define MAX_LENGHT 1000

// Constructor
Secuencia::Secuencia() {}

Secuencia::~Secuencia() {}

void Secuencia::guardar(list<Secuencia> &lista, string nombre_archivo)
{
    char *str = new char[800];
    string datos;
    ifstream fe(nombre_archivo);
    int cont = 0, aux = 0;
    // Comprobar si el archivo esta vacio y luego leeerlo
    if (fe.is_open())
    {
        string sec;
        while (!fe.eof())
        {
            fe.getline(str, MAX_LENGHT);
            if (str[0] == '>')
            {
                if (sec != "")
                {
                    Secuencia secuencia;
                    secuencia.setNombre_sec(datos);
                    secuencia.setSecuencia(sec);

                    secuencia.setTamano(cont);

                    lista.push_back(secuencia);
                    sec = "";
                    datos = "";
                    cont = 0;
                }
                datos = str;
            }
            else
            {
                // copiar solo la primera secuencia
                if (aux == 0)
                {
                    sec = str;
                    cont = strlen(str);
                    aux++;
                }
                else
                {
                    sec += str;
                }
            }
        }
        Secuencia secuencia;
        secuencia.setNombre_sec(datos);
        secuencia.setSecuencia(sec);

        lista.push_back(secuencia);
        sec = "";
        aux=0;
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
    cout << "Secuencias guardadas" << endl;
    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        cout << "   " << it->nombre_sec << endl;
        cout << "   " << it->tamano << endl;
        cout << "   " << it->secuencia << endl;
    }
    cout << "Tamaño de la lista: " << lista.size() << endl;
    fe.close();
}

