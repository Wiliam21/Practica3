#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TADTablaHash.h"

/*
Funcion de hash para obtener el indice de una llave
Recive: La llave sobre la que se usara la funcion
Regresa: El indice de la tabla
*/
int Hash(Key key)
{
    int i, sum = 0, length = strlen(key.key);
    for (i = 0; i < length; i++)
    {
        sum += key.key[i] * (i + 1);
    }
    return sum % TAM;
}

/*
int Hash(Key key)
{
    int i,  length = strlen(key.key);
    long sum = 1;
    for (i = 0; i < length; i++)
    {
        sum *= key.key[i];
    }
    return sum % TAM;
}
*/

/*
Inicializa la tabla para su correcto uso
Recive: Un apuntador a la tabla
*/
void InitializeTable(TablaHash *tabla)
{
    int i;
    tabla->numElements = 0;
    for (i = 0; i < TAM; i++)
    {
        Initialize(&(tabla->listas[i]));
    }
}

/*
Borra los datos de la tabla
Recive: Un apuntador a la tabla
Observaciones: La tabla debe estar inicializada
*/
void DestroyTable(TablaHash *tabla)
{
    int i;
    tabla->numElements = 0;
    for (i = 0; i < TAM; i++)
    {
        Destroy(&(tabla->listas[i]));
    }
}

/*
Agrega un elemento en la tabla
Recive: Un apuntador a la tabla hash y el elemento que se agregara
Observaciones: La tabla debe estar inicializada
*/
void AddElement(TablaHash *tabla, Elemento elemento, boolean debug)
{
    int valorHash = Hash(elemento.key);
    Elemento temp = SearchBykey(tabla, elemento.key, FALSE);
    if (temp.key.key[0] == '\0')
    {
        Add(&(tabla->listas[valorHash]), elemento);
        if (debug)
        {
            printf(ANSI_COLOR_CYAN "\nAgregado en lista: %d Coliciones: %d\n" ANSI_COLOR_RESET, valorHash, Size(&(tabla->listas[valorHash]) - 1));
        }
    }
    else
    {
        printf(ANSI_COLOR_RED "\n\tYa existe \"%s\"\n" ANSI_COLOR_RESET,elemento.key.key);
    }
}

/*
Busca un elemento en la tabla a partir de la llave del elemento
Recive: Un apuntador a la tabla donde se buscara el elemento y la llave del elemento
Regresa: El elemento que haya coincidido con la llave
Observaciones: La tabla debe estar inicializada, en caso de no encontrar el elemento regresa uno con valores nulos
*/
Elemento SearchBykey(TablaHash *tabla, Key key, boolean debug)
{
    Elemento elemento;
    int i, pasos = 1, valorHash = Hash(key);
    Posicion pos = First(&(tabla->listas[valorHash]));
    int listLenght = Size(&(tabla->listas[valorHash]));
    for (i = 1; i <= listLenght; i++)
    {
        pasos += 2;
        elemento = Position(&(tabla->listas[valorHash]), pos);
        if (strcmp(key.key, elemento.key.key) == 0)
        {
            if (debug)
            {
                printf(ANSI_COLOR_CYAN "\nLista: %d Pasos: %d Colisiones: %d\n" ANSI_COLOR_RESET, valorHash, pasos, listLenght - 1);
            }
            return elemento;
        }
        pos = Following(&(tabla->listas[valorHash]), pos);
    }
    memset(elemento.definition.definition, '\0', 251);
    memset(elemento.key.key, '\0', 101);
    return elemento;
}

void ModifyByKey(TablaHash *tabla, Key key, Elemento elemento, boolean debug)
{
    Elemento temp;
    int i, pasos = 1, valorHash = Hash(key);
    Posicion pos = First(&(tabla->listas[valorHash]));
    int listLenght = Size(&(tabla->listas[valorHash]));
    for (i = 1; i <= listLenght; i++)
    {
        pasos += 2;
        temp = Position(&(tabla->listas[valorHash]), pos);
        if (strcmp(key.key, temp.key.key) == 0)
        {
            Replace(&(tabla->listas[valorHash]), pos, elemento);
            if (debug)
            {
                printf(ANSI_COLOR_CYAN "\nLista: %d Pasos: %d Colisiones: %d\n" ANSI_COLOR_RESET, valorHash, pasos, listLenght - 1);
            }
            return;
        }
        pos = Following(&(tabla->listas[valorHash]), pos);
    }
    printf(ANSI_COLOR_RED "\nEl elemento no existe\n" ANSI_COLOR_RESET);
}

void DeleteByKey(TablaHash *tabla, Key key, boolean debug)
{
    Elemento temp;
    int i, pasos = 1, valorHash = Hash(key);
    Posicion pos = First(&(tabla->listas[valorHash]));
    int listLenght = Size(&(tabla->listas[valorHash]));
    for (i = 1; i <= listLenght; i++)
    {
        pasos += 2;
        temp = Position(&(tabla->listas[valorHash]), pos);
        if (strcmp(key.key, temp.key.key) == 0)
        {
            Remove(&(tabla->listas[valorHash]), pos);
            if (debug)
            {
                printf(ANSI_COLOR_CYAN "\nLista: %d Pasos: %d Colisiones: %d\n" ANSI_COLOR_RESET, valorHash, pasos, listLenght - 1);
            }
            return;
        }
        pos = Following(&(tabla->listas[valorHash]), pos);
    }
    printf(ANSI_COLOR_RED "\nEl elemento no existe\n" ANSI_COLOR_RESET);
}

void ShowStats(TablaHash *tabla)
{
    int i, col, size, elementos = 0, totalcol = 0, contVacias = 0,max=0;
    for (i = 0; i < TAM; i++)
    {
        size = Size(&(tabla->listas[i]));
        if (!Empty(&(tabla->listas[i])))
        {
            col = size - 1;
        }
        else
        {
            col = 0;
            contVacias++;
        }
        if (size > 0)
        {
            printf(ANSI_COLOR_CYAN "\nLista: %d, Elementos: %d, Colisiones: %d" ANSI_COLOR_RESET, i, size, col);
            totalcol += col;
            elementos += size;
            if (size>max)
            {
                max=size;
            }
        }
    }
    printf(ANSI_COLOR_CYAN "\nTotal de elementos: %d\nTotal de colisiones: %d\nListas vacias: %d\nEl coste maximo es O(%d)\n" ANSI_COLOR_RESET, elementos, totalcol, contVacias,max);
}

Lista* KeyStartWith(TablaHash *tabla, char c)
{
    int i, cont = 0;
    Lista *lista;
    lista=(Lista *)malloc(sizeof(Lista));
    Initialize(lista);
    Posicion pos;
    Elemento temp;
    for (i = 0; i < TAM; i++)
    {
        pos = First(&(tabla->listas[i]));
        while (pos != NULL)
        {
            temp = Position(&(tabla->listas[i]), pos);
            if (temp.key.key[0] == c)
            {
                Add(lista,temp);
            }
            pos = Following(&(tabla->listas[i]), pos);
        }
    }
    return lista;
}

Lista* DeftWith(TablaHash *tabla, Definition def)
{
    int i, cont = 0;
    Posicion pos;
    Elemento temp;
    Lista *lista;
    lista=(Lista *)malloc(sizeof(Lista));
    Initialize(lista);
    for (i = 0; i < TAM; i++)
    {
        pos = First(&(tabla->listas[i]));
        while (pos != NULL)
        {
            temp = Position(&(tabla->listas[i]), pos);
            if (strstr(temp.definition.definition, def.definition) != NULL)
            {
                Add(lista,temp);
            }
            pos = Following(&(tabla->listas[i]), pos);
        }
    }
    return lista;
}