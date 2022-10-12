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

void listarSecuenciaw(vector<char> cod, int &aux)
{
    int cont = 0, cont2 = 0;
    vector<char> codigos = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 'B', 'D', 'H', 'V', 'N', 'X', '-'};
    for (int i = 0; i < codigos.size(); i++)
    {
        vector<char>::iterator it = cod.begin();
        while (it != cod.end())
        {
            if (*it == codigos[i])
            {
                cont++;
            }
            if (*it == '-')
            {
                cont2++;
            }
            it++;
        }

        if (cont != 0 && cont2 != 0 && codigos[i] != '-')
        {
            aux -= cont;
            cout << codigos[i] << " Contiene: " << cont << " bases" << endl;
        }
        else if (cont != 0 && cont2 == 0 && codigos[i] != '-')
        {
            aux += cont;
            cout << codigos[i] << " Contiene: " << cont << " bases" << endl;
        }
        cont = 0;
        cont2 = 0;
    }
}

void listarSecuencias(list<Secuencia> lista)
{    
    int cont = 0;
    // Cuantas veces cada codigo aparece en la secuencia por cada codigo genetico
    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        vector<char> secuencias;
        for (int i = 0; i < it->getSecuencia().size(); i++)
        {
            secuencias.push_back(it->getSecuencia()[i]);
        }
        vector<char>::iterator it2 = secuencias.begin();

        // it2 vacio
        if (it2 == secuencias.end())
        {
            break;
        }
        else
        {
            cout << it->getNombre_sec() << endl;
            listarSecuenciaw(secuencias, cont);
            if (cont < 1)
            {
                cout << "Esta secuencia contiene al menos " << cont * -1 << " bases" << endl;
            }
            else
            {
                cout << "Esta secuencia contiene " << cont << " bases" << endl;
            }
            cont = 0;
        }
        for (int i = 0; i < secuencias.size(); i++)
        {
            cout << secuencias[i];
        }
        secuencias.clear();
        system("pause");
    }
}

void cuantos(string sub, vector<char> aux, int &cont2)
{
    char cadena[MAX_LENGHT];
    char subcadena[MAX_LENGHT];
    char *busqueda = NULL;
    strcpy(subcadena, sub.c_str());
    // cout<<subcadena<<endl;
    // copiar aux.secuencia a cadena
    for (int i = 0; i < aux.size(); i++)
    {
        cadena[i] = aux[i];
    } /*
     for (int i=0; i< sizeof(cadena); i++)
     {
         cout<<cadena[i];
     }    */
    busqueda = strstr(cadena, subcadena);
    if (busqueda == NULL)
    {
        cout << "La secuencia dada no existe." << endl;
    }
    while (busqueda != NULL)
    {
        cont2++;
        busqueda = strstr(busqueda + 1, subcadena);
    }
}

void sub_secuencia(string sub, list<Secuencia> lista)
{
    int cont = 0;
    // cout << sub << endl;

    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {

        // cout << "   " << it->nombre_sec << endl;
        vector<char> secuencias;
        secuencias.clear();
        for (int i = 0; i < it->getSecuencia().size(); i++)
        {
            secuencias.push_back(it->getSecuencia()[i]);
        }
        vector<char>::iterator it2 = secuencias.begin();
        cuantos(sub, secuencias, cont);
        secuencias.clear();
        // cout<<endl<<endl;
    }
    cout << endl
         << endl;
    cout << "La subsecuencia " << sub << " aparece " << cont << " veces" << endl;

    // es_subsecuencia CAACATCACCAATCA
}

void cambiarValorPorX(string sub, vector<char> &aux)
{
    // cout<<cadena<<endl;
    // cambiar valor por X donde este la secuencia completa
    int cont = sub.size();
    for (int i = 0; i < aux.size(); i++)
    {
        if (aux[i] == sub[0])
        {
            for (int j = 0; j < sub.size(); j++)
            {
                if (aux[i + j] == sub[j])
                {
                    cont--;
                }
            }
            if (cont == 0)
            {
                for (int j = 0; j < sub.size(); j++)
                {
                    aux[i + j] = 'X';
                }
            }
            cont = sub.size();
        }
    }
}

void enmascarar(string sub, list<Secuencia> &lista)
{
    vector<char> secuencias;
    string aux;
    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        vector<char>::iterator it2 = secuencias.begin();
        for (int i = 0; i < it->getSecuencia().size(); i++)
        {
            secuencias.push_back(it->getSecuencia()[i]);
        }
        cambiarValorPorX(sub, secuencias);
        for (int i = 0; i < secuencias.size(); i++)
        {
            aux += secuencias[i];
        }
        it->setSecuencia(aux);

        secuencias.clear();
        aux.clear();
    }

    // listar secuencias
    for (list<Secuencia>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        cout << it->getNombre_sec() << endl;
        cout <<"Ancho: " <<it->getTamano() << endl;
        cout << it->getSecuencia() << endl;
        
    }
}