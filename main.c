#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADTablaHash\TADTablaHash.h"

int MostrarMenu();
void CargarArchivo(TablaHash *tabla);
void AgregarPalabra(TablaHash *tabla);
void BuscarPalabra(TablaHash *tabla);
void BuscarPalabraPorLetra(TablaHash *tabla);
void BuscarDefinicion(TablaHash *tabla);
void ModificarPalabra(TablaHash *tabla);
void EliminarPalabra(TablaHash *tabla);
void MostrarEstadisticas(TablaHash *tabla);
void ExportarTabla(TablaHash *tabla);
void ExportarElemento(Elemento elemento);
void ExportarElementos(Lista *lista);

#define DEBUG TRUE

int main()
{
    TablaHash tabla;
    InitializeTable(&tabla);
    int exit = 0, op;
    do
    {
        op = MostrarMenu();
        system("cls");
        switch (op)
        {
        case 1:
            CargarArchivo(&tabla);
            break;
        case 2:
            AgregarPalabra(&tabla);
            break;
        case 3:
            BuscarPalabra(&tabla);
            break;
        case 4:
            BuscarPalabraPorLetra(&tabla);
            break;
        case 5:
            BuscarDefinicion(&tabla);
            break;
        case 6:
            ModificarPalabra(&tabla);
            break;
        case 7:
            EliminarPalabra(&tabla);
            break;
        case 8:
            MostrarEstadisticas(&tabla);
            break;
        case 9:
            ExportarTabla(&tabla);
            break;
        case 0:
            exit = 1;
            break;
        default:
            printf("\nOpcion invalida, ingresa una opcion valida\n");
            system("pause");
            break;
        }
    } while (exit == 0);
    DestroyTable(&tabla);
}

int MostrarMenu()
{
    int op;
    system("cls");
    printf("DICCIONARIO Hash\n");
    printf("\n1) Cargar un archivo de definiciones");
    printf("\n2) Agregar una palabra y su definicion");
    printf("\n3) Buscar una palabra y ver definicion");
    printf("\n4) Buscar palabras que empiecen con una letra");
    printf("\n5) Buscar definiciones que contengan una palabra");
    printf("\n6) Modificar una definicion");
    printf("\n7) Eliminar una palabra");
    printf("\n8) Ver estadisticas hash");
    printf("\n9) Exportar difiniciones a un archivo de texto");
    printf("\n0) Salir");
    printf("\nIngresa una opcion: ");
    scanf("%d", &op);
    return op;
}

void CargarArchivo(TablaHash *tabla)
{
    printf("\tCargar datos de un archivo\n\n");
    char dir[100];
    printf("Ingresa la la ruta del archivo (en caso de estar en la misma carpeta que el programa solo ingresa el nombre):\n");
    printf("Archivo: ");
    fflush(stdin);
    scanf("%[^\n]", dir);
    getchar();
    if (strstr(dir, ".txt") == NULL)
    {
        strcat(dir, ".txt");
    }
    FILE *file;
    if ((file = fopen(dir, "r")) == NULL)
    {
        printf("\nNo se ha encontrado el archivo\n");
        system("pause");
    }
    else
    {
        system("cls");
        Elemento temp;
        while (!feof(file))
        {
            fscanf(file, "%[^:]", temp.key.key);
            if (fgetc(file) == EOF)
            {
                fclose(file);
                break;
            }
            fscanf(file, "%[^\n]", temp.definition.definition);
            printf("%s:%s\n", temp.key.key, temp.definition.definition);
            fgetc(file);
            AddElement(tabla, temp, FALSE);
            memset(temp.definition.definition, '\0', 251);
            memset(temp.key.key, '\0', 101);
        }

        printf(ANSI_COLOR_GREEN "\n\nDiccionario cargado\n" ANSI_COLOR_RESET);
        system("pause");
    }
    fclose(file);
}

void AgregarPalabra(TablaHash *tabla)
{
    printf("\tAgregar una nueva palabra\n\n");
    Elemento temp;
    printf("Ingresa la palabra: ");
    fflush(stdin);
    scanf("%[^\n]", temp.key.key);
    getchar();
    printf("Ingresa la definicion: ");
    fflush(stdin);
    scanf("%[^\n]", temp.definition.definition);
    getchar();
    AddElement(tabla, temp, DEBUG);
    system("pause");
}

void BuscarPalabra(TablaHash *tabla)
{
    printf("\tBuscar una palabra\n\n");
    Key key;
    printf("Ingresa la palabra a buscar: ");
    fflush(stdin);
    scanf("%[^\n]", key.key);
    getchar();
    Elemento temp = SearchBykey(tabla, key, DEBUG);
    int op;
    if (temp.definition.definition[0] != '\0')
    {
        printf("\nDefinicion: %s\n", temp.definition.definition);
        printf("\nDeseas exportar esta palabra y su definicion a un archivo\n1) Si\n2) No\n");
        printf("Ingresa la opcion: ");
        scanf("%d", &op);
        if (op == 1)
        {
            ExportarElemento(temp);
        }
    }
    else
    {
        printf(ANSI_COLOR_RED "\nEl elemento no existe\n" ANSI_COLOR_RESET);
        system("pause");
    }
}

void ModificarPalabra(TablaHash *tabla)
{
    printf("\tModificar una palabra\n\n");
    Elemento temp;
    printf("Ingresa la palabra: ");
    fflush(stdin);
    scanf("%[^\n]", temp.key.key);
    getchar();
    printf("Ingresa la nueva definicion: ");
    fflush(stdin);
    scanf("%[^\n]", temp.definition.definition);
    getchar();
    ModifyByKey(tabla, temp.key, temp, DEBUG);
    system("pause");
}

void EliminarPalabra(TablaHash *tabla)
{
    printf("\tEliminar una palabra\n\n");
    Key key;
    printf("Ingresa la palabra a eliminar: ");
    fflush(stdin);
    scanf("%[^\n]", key.key);
    getchar();
    DeleteByKey(tabla, key, DEBUG);
    system("pause");
}

void MostrarEstadisticas(TablaHash *tabla)
{
    ShowStats(tabla);
    system("pause");
}

void ExportarTabla(TablaHash *tabla)
{
    printf("\tExportar diccionario\n\n");
    char dir[100];
    printf("\nIngresa el nombre que tendra el archivo (En caso de ya exitir se sobre escribe en este)\n");
    printf("Archivo: ");
    fflush(stdin);
    scanf("%[^\n]", dir);
    getchar();
    if (strstr(dir, ".txt") == NULL)
    {
        strcat(dir, ".txt");
    }

    FILE *file;
    file = fopen(dir, "w");
    int i, j;
    Elemento temp;
    for (i = 0; i < TAM; i++)
    {
        for (j = 1; j <= Size(&(tabla->listas[i])); j++)
        {
            temp = Element(&(tabla->listas[i]), j);
            fprintf(file, "%s:%s\n", temp.key.key, temp.definition.definition);
        }
    }
    printf(ANSI_COLOR_GREEN "\nDatos exportados\n" ANSI_COLOR_RESET);
    fclose(file);
    system("pause");
}

void ExportarElemento(Elemento elemento)
{
    char dir[100], c;
    printf("\nIngresa el nombre del archivo (En caso de ya exitir se agrega al final, si no se crea el archivo)\n");
    printf("Archivo: ");
    fflush(stdin);
    scanf("%[^\n]", dir);
    getchar();
    if (strstr(dir, ".txt") == NULL)
    {
        strcat(dir, ".txt");
    }

    FILE *file;
    fpos_t pos;
    file = fopen("temp.txt", "a+");
    fprintf(file, " ");
    fgetpos(file, &pos);
    pos = pos - 2;
    fsetpos(file, &pos);
    c = fgetc(file);
    fclose(file);
    file = fopen("temp.txt", "r+");
    pos = pos + 1;
    fsetpos(file, &pos);
    if (c == '\n' || pos < 3)
    {
        fprintf(file, "%s:%s\n", elemento.key.key, elemento.definition.definition);
    }
    else
    {
        fprintf(file, "\n%s:%s\n", elemento.key.key, elemento.definition.definition);
    }
    fclose(file);
    printf(ANSI_COLOR_GREEN "\nDatos exportados\n" ANSI_COLOR_RESET);
    system("pause");
}

void BuscarPalabraPorLetra(TablaHash *tabla)
{
    printf("\tBuscar las palabras que inicie con una letra\n");
    char c;
    int i, op;
    Lista *lista;
    printf("\nIngresa la letra con que deben iniciar las palabras: ");
    fflush(stdin);
    scanf("%c", &c);
    system("cls");
    lista = KeyStartWith(tabla, c);
    if (Size(lista) == 0)
    {
        printf(ANSI_COLOR_YELLOW "\nNo se ha encontrado ninguna palabra que inicie con %c\n" ANSI_COLOR_RESET, c);
    }
    else
    {
        Elemento temp;
        printf("Palabras que inician con %c\n", c);
        for (i = 1; i <= Size(lista); i++)
        {
            temp = Element(lista, i);
            printf("\n%s:%s\n", temp.key.key, temp.definition.definition);
        }

        printf(ANSI_COLOR_GREEN "\nTotal de palabras encontradas: %d\n" ANSI_COLOR_RESET, Size(lista));
        printf("\nDeseas exportar esta lista de palabras y su definicion a un archivo\n1) Si\n2) No\n");
        printf("Ingresa la opcion: ");
        scanf("%d", &op);
        if (op == 1)
        {
            ExportarElementos(lista);
        }
    }
    system("pause");
}

void BuscarDefinicion(TablaHash *tabla)
{
    printf("\tBuscar las definiciones que contengan una frase o palabra\n");
    Definition def;
    int i, op;
    printf("\nPalabra o frase: ");
    fflush(stdin);
    scanf("%[^\n]", def.definition);
    system("cls");
    Lista *lista;
    lista = DeftWith(tabla, def);
    if (Size(lista) == 0)
    {
        printf(ANSI_COLOR_YELLOW "\nNo se ha encontrado ninguna palabra que contengan \"%s\"\n" ANSI_COLOR_RESET, def.definition);
    }
    else
    {
        Elemento temp;
        printf("Palabras que contienen \"%s\"\n", def.definition);
        for (i = 1; i <= Size(lista); i++)
        {
            temp = Element(lista, i);
            printf("\n%s:%s\n", temp.key.key, temp.definition.definition);
        }
        printf(ANSI_COLOR_GREEN "\nTotal de palabras encontradas: %d\n" ANSI_COLOR_RESET, Size(lista));
        printf("\nDeseas exportar esta lista de palabras y su definicion a un archivo\n1) Si\n2) No\n");
        printf("Ingresa la opcion: ");
        scanf("%d", &op);
        if (op == 1)
        {
            ExportarElementos(lista);
        }
    }
    system("pause");
}

void ExportarElementos(Lista *lista)
{
    int cont = 1;
    char dir[100], c;
    Elemento temp;
    printf("\nIngresa el nombre del archivo (En caso de ya exitir se agrega al final, si no se crea el archivo)\n");
    printf("Archivo: ");
    fflush(stdin);
    scanf("%[^\n]", dir);
    getchar();
    if (strstr(dir, ".txt") == NULL)
    {
        strcat(dir, ".txt");
    }

    FILE *file;
    fpos_t pos;
    Posicion listPos = First(lista);
    file = fopen("temp.txt", "a+");
    fprintf(file, " ");
    fgetpos(file, &pos);
    pos = pos - 2;
    fsetpos(file, &pos);
    c = fgetc(file);
    fclose(file);
    file = fopen("temp.txt", "r+");
    pos = pos + 1;
    fsetpos(file, &pos);
    temp = Position(lista, listPos);
    if (c == '\n' || pos < 3)
    {
        fprintf(file, "%s:%s\n", temp.key.key, temp.definition.definition);
    }
    else
    {
        fprintf(file, "\n%s:%s\n", temp.key.key, temp.definition.definition);
    }

    listPos = Following(lista, listPos);
    while (listPos != NULL)
    {
        temp = Position(lista, listPos);
        fprintf(file, "%s:%s\n", temp.key.key, temp.definition.definition);
        listPos = Following(lista, listPos);
    }

    fclose(file);
    printf(ANSI_COLOR_GREEN "\nDatos exportados\n" ANSI_COLOR_RESET);
}