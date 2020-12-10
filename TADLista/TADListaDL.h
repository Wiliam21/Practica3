/*
LIBRERIA: Cabecera de el TAD LISTA DOBLE ENLAZADA
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
*/

#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;

typedef struct Key
{
   char key[101];
}Key;

typedef struct Definition
{
    char definition[251];
}Definition;

typedef struct Elemento
{
    Key key;
    Definition definition;
}Elemento;

typedef struct Nodo
{
    Elemento elemento;
    struct Nodo *siguiente;
    struct Nodo *anterior;
}Nodo;

typedef Nodo *Posicion;

typedef struct Lista
{
    int tam;
    Posicion frente;
    Posicion final;
}Lista;

void Initialize(Lista *lista);
void Destroy(Lista *lista);
Posicion Final(Lista *lista);
Posicion First(Lista *lista);
Posicion Following(Lista *lista, Posicion posicion);
Posicion Previuos(Lista *lista, Posicion posicion);
Posicion Search(Lista *lista,Elemento elemento);
Elemento Position (Lista *lista,Posicion posicion);
boolean ValidatePosition (Lista *lista,Posicion posicion);
Posicion ElementPosition(Lista *lista, int n);
Elemento Element(Lista *lista, int n);
int Size (Lista *lista);
boolean Empty (Lista *lista);
void Insert (Lista * lista, Posicion posicion, Elemento elemento, boolean b);
void Add (Lista *lista,Elemento elemento);
void Remove (Lista *lista,Posicion posicion);
void Replace (Lista *lista,Posicion posicion, Elemento elemento);