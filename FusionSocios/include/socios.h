#ifndef ACTAS_H_INCLUDED
#define ACTAS_H_INCLUDED

#include "tipos.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM_LINEA 250
typedef void(*printStruct)(void*);
typedef int(*Cmp)(const void*, const void*);

void crear_archivo_socios_a(const char * path);
void mostrar_archivo_socios_a(const char * path);
void mostrar_archivo_socios_b(const char * path);
void mostrar_archivo_socios_final(const char * path);


//FUNCIONES DE ALUMNO

void menu();
int validarOpc(char opc, char* stro);
int leerArchGen(const char* nombreArch, size_t tamElem, printStruct printSocio);
void printSocio(void *elem);
int cmp_socios(const void *v1, const void *v2);
int unificar_clubes(const char* nombreArchA, const char* nombreArchB, const char* nombreArchFin, size_t tamElem, int flag);


#endif // BANCO_H_INCLUDED
