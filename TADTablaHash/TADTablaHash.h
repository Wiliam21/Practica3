/*
LIBRERIA: Cabecera de el TAD TABLA HASH
AUTOR: Andrew Wiliam Huerta Puente Noviembre 2020
VERSIÓN: 1.0

DESCRIPCIÓN: TAD Tabla Hash.
Estructura de datos en la que se cumple:
Uso de una funcion de Hash para indexar elementos
Insertar elementos con una clave y un valor
Poder obtener un elemento solo con la clave

OBSERVACIONES: Hablamos de una Estructura de datos dinámica 
cuando se le asigna memoria a medida que es necesitada, 
durante la ejecución del programa. 
Se diferencia las mayusculas de minusculas
*/

#include "../TADLista/TADListaDL.h"

#define TAM 101

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct TablaHash
{
    Lista listas[TAM];
    int numElements;
}TablaHash;

int Hash(Key key);
void InitializeTable(TablaHash *tabla);
void DestroyTable(TablaHash *tabla);
void AddElement(TablaHash *tabla, Elemento elemento,boolean debug);
Elemento SearchBykey(TablaHash *tabla,Key key,boolean debug);
void DeleteByKey(TablaHash *tabla,Key key,boolean debug);
void ModifyByKey(TablaHash *tabla,Key key, Elemento elemento,boolean debug);
void ShowStats(TablaHash *tabla);
void KeyStartWith(TablaHash *tabla, char c);
void DeftWith(TablaHash *tabla, Definition def);