/*
IMPLEMENTACION DE LA LIBRERIA DEL TAD LISTA DOBLE ENLAZADA (TADListaDL.h)
AUTOR: Andrew Wiliam Huerta Puente Noviembre 2020
VERSIÓN: 1.0

DESCRIPCIÓN: TAD lista o List.
Estructura de datos en la que se cumple:
Insertar elementos en cualquier posicion
Eliminar cualquier elemento de la lista
Acceder y modicar cualquier elemento de la lista
Se puede desplazar hacia adelante y hacia atras en los elementos de la lista

OBSERVACIONES: Hablamos de una Estructura de datos dinámica 
cuando se le asigna memoria a medida que es necesitada, 
durante la ejecución del programa. 

COMPILACIÓN PARA GENERAR EL CÓDIGO OBJETO: gcc -c TADListaDL.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADListaDL.h"

void Initialize(Lista *lista)
{
    lista->final = NULL;
    lista->frente = NULL;
    lista->tam = 0;
}

void Destroy(Lista *lista)
{
    Nodo *aux;
    while (lista->frente != NULL)
    {
        aux = lista->frente;
        lista->frente = lista->frente->siguiente;
        free(aux);
    }
    lista->final = NULL;
    lista->tam = 0;
    return;
}

Posicion Final(Lista *lista)
{
    return lista->final;
}

Posicion First(Lista *lista)
{
    return lista->frente;
}

Posicion Following(Lista *lista, Posicion posicion)
{
    if (ValidatePosition(lista, posicion))
    {
        return posicion->siguiente;
    }
}

Posicion Previuos(Lista *lista, Posicion posicion)
{
    if (ValidatePosition(lista, posicion))
    {
        return posicion->anterior;
    }
}

Posicion Search(Lista *lista, Elemento elemento)
{
    Posicion aux = lista->frente;
    while (aux != NULL)
    {
        if (memcmp(&(aux->elemento), &elemento, sizeof(Elemento)) == 0)
        {
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

Elemento Position(Lista *lista, Posicion posicion)
{
    if (ValidatePosition(lista, posicion))
    {
        return posicion->elemento;
    }
    exit(1);
}

boolean ValidatePosition(Lista *lista, Posicion posicion)
{
    Posicion aux = lista->frente;
    while (aux != NULL)
    {
        if (aux == posicion)
        {
            return TRUE;
        }
        aux = aux->siguiente;
    }
    return FALSE;
}

Posicion ElementPosition(Lista *lista, int n)
{
    int i;
    if (n > 0 && n < Size(lista))
    {
        Posicion aux = lista->frente;
        for (i = 1; i < n; i++)
        {
            aux = aux->siguiente;
        }
        return aux;
    }
    else
    {
        return NULL;
    }
}

Elemento Element(Lista *lista, int n)
{
    int i;
    if (n > 0 && n <= Size(lista))
    {
        Posicion aux = lista->frente;
        for (i = 2; i <= n; i++)
        {
            aux = aux->siguiente;
        }
        return aux->elemento;
    }
    else
    {
        exit(1);
    }
}

int Size(Lista *lista)
{
    return lista->tam;
}

boolean Empty(Lista *lista)
{
    return (lista->tam == 0) ? TRUE : FALSE;
}

void Insert(Lista *lista, Posicion posicion, Elemento elemento, boolean b)
{
    Nodo *aux;
    aux = malloc(sizeof(Nodo));
    aux->elemento = elemento;
    aux->siguiente = NULL;
    aux->anterior = NULL;
    if (!Empty(lista) && ValidatePosition(lista, posicion))
    {
        if (b)
        {
            if (posicion == lista->frente)
            {
                aux->siguiente = lista->frente;
                lista->frente = aux;
                lista->tam++;
                return;
            }
            else
            {
                aux->siguiente = posicion;
                aux->anterior = posicion->anterior;
                posicion->anterior->siguiente = aux;
                lista->tam++;
                return;
            }
        }
        else
        {
            if (posicion == lista->final)
            {
                Add(lista, elemento);
                return;
            }
            else
            {
                aux->siguiente = posicion->siguiente;
                aux->anterior = posicion;
                posicion->siguiente = aux;
                lista->tam++;
                return;
            }
        }
    }
    else
    {
        aux->siguiente = lista->frente;
        lista->frente = aux;
        lista->tam++;
        return;
    }
}

void Add(Lista *lista, Elemento elemento)
{
    Nodo *aux;
    aux = malloc(sizeof(Nodo));
    aux->elemento = elemento;
    aux->siguiente = NULL;
    aux->anterior = NULL;
    if (lista->tam == 0)
    {
        lista->frente = aux;
        lista->final = aux;
    }
    else
    {
        aux->anterior = lista->final;
        lista->final->siguiente = aux;
        lista->final = aux;
    }
    lista->tam++;
}

void Remove(Lista *lista, Posicion posicion)
{
    if (!Empty(lista) && ValidatePosition(lista, posicion))
    {
        if (Size(lista)==1)
        {
            Initialize(lista);
        }
        else if (posicion == lista->frente)
        {
            lista->frente = lista->frente->siguiente;
            lista->frente->anterior = NULL;
            free(posicion);
            lista->tam--;
            return;
        }
        else if (posicion == lista->final)
        {
            lista->final = lista->final->anterior;
            lista->final->siguiente = NULL;
            free(posicion);
            lista->tam--;
            return;
        }
        else
        {
            posicion->anterior->siguiente = posicion->siguiente;
            posicion->siguiente->anterior = posicion->anterior;
            free(posicion);
            lista->tam--;
            return;
        }
    }
}

void Replace(Lista *lista, Posicion posicion, Elemento elemento)
{
    if (!Empty(lista) && ValidatePosition(lista, posicion))
    {
        posicion->elemento = elemento;
    }
}