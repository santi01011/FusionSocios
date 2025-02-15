//agregar los include que considere necesarios
#include "../include/socios.h"

/**
Para su resolución puede ayudarse de las siguientes funciones provistas.
--------------------------------------------
int cmp_socios_res(const void *v1, const void *v2)

//compara dos estructuras t_socio, en este caso por dni, devolviendo:
< 0  --->  v1  < v2
  0  --->  v1 == v2
> 0  --->  v1  > v2

--------------------------------------------

int leer_registro_arch_socios_b_res(FILE* arch, t_socio* socio)
//lee un registro del archivo de texto que contiene los socios del club B y arma una estructura t_socio con estos datos

--------------------------------------------
int compara_fechas_res(const t_fecha *f1, const t_fecha *f2)

//compara dos estructuras t_fecha, devolviendo:
FECHA_MENOR  --->  f1  < f2
FECHA_IGUAL  --->  f1 == f2
FECHA_MAYOR  --->  f1  > f2

 **/
void printSocio(void *elem){
    t_socio* a = (t_socio*)elem;
    printf("%lu|%s|%d/%d/%d\n", a->dni, a->apyn, a->fecha_inscripcion.dia, a->fecha_inscripcion.mes, a->fecha_inscripcion.anio);
}

//int compara_fechas(const t_fecha *f1, const t_fecha *f2){
//    if(f1->anio == f2->anio && f1->mes == f2->mes && f1->dia == f2->dia)
//        return 0;
//    if(f1->anio > f2->anio)
//        return 1;
//
//    return 1;
//}

int cmp_socios(const void *v1, const void *v2){
    t_socio* s1 = (t_socio*)v1;
    t_socio* s2 = (t_socio*)v2;
    return s1->dni - s2->dni;
}

int leerArchGen(const char* nombreArch, size_t tamElem, printStruct printSocio){
    FILE* pf = fopen(nombreArch, "rb");
    void* elem = malloc(tamElem);
    if(!pf)
        return 0;
    if(!elem){
        fclose(pf);
        return 0;
    }
    printf("Archivo: %s\n", nombreArch);
    while(fread(elem, tamElem, 1, pf))
        printSocio(elem);
    puts("Fin archivo\n");
    fclose(pf);
    return 1;
}

void menu(){
    char opc;
    do{
        if(strchr("abfs", opc) == 0)
            printf("Seleccione una opcion valida\n");
        printf("\n[a]ver socios del club a\n[b]ver socios del club b\n[f]fusionar clubes\n[s]salir."
            "\n\nSeleccione una opcion: ");
        fflush(stdin);
        opc = getchar();
        if(opc == 'a')
            leerArchGen("../Archivos/socios_a.bin", sizeof(t_socio), printSocio);
        if(opc == 'b')
            mostrar_archivo_socios_b("../Archivos/socios_b.txt");
        if(opc == 'f'){
            printf("\n[a]Conservar antiguedad mayor\n[b]Conservar antiguedad menor\n[c]Resetear antiguedad a fecha actual\n");
            fflush(stdin);
            opc = getchar();
            if(opc == 'a')
                unificar_clubes("../Archivos/socios_a.bin", "../Archivos/socios_b.txt", "../Archivos/fusion_mayor.txt", sizeof(t_socio), 1);
            if(opc == 'b')
                unificar_clubes("../Archivos/socios_a.bin", "../Archivos/socios_b.txt", "../Archivos/fusion_menor.txt", sizeof(t_socio), 2);
            if(opc == 'c')
                unificar_clubes("../Archivos/socios_a.bin", "../Archivos/socios_b.txt", "../Archivos/fusion_cero.txt", sizeof(t_socio), 3);

        }
    }while(opc != 's');
    return;
}


int unificar_clubes(const char* nombreArchA, const char* nombreArchB, const char* nombreArchFin, size_t tamElem, int flag){
    int res;
    t_socio *auxB, auxA;
    auxB = malloc(sizeof(t_socio));
    FILE* pfA;
    FILE* pfB;
    FILE* pfF;
    pfB = fopen(nombreArchB, "rt");
    if(!pfB)
        return 0;

    pfA = fopen(nombreArchA, "rb");
    if(!pfA){
        fclose(pfB);
        return 0;
    }
    pfF = fopen(nombreArchFin, "wt");
    if(!pfA){
        fclose(pfB);
        fclose(pfA);
        return 0;
    }

    leer_registro_arch_socios_b_res(pfB, auxB);
    fread(&auxA, tamElem, 1, pfA);
    if(flag == 1){  //mayorAntig
        while(!feof(pfB) && !feof(pfA)){
            res = cmp_socios_res(&auxA, auxB);
            if(res == 0){
                res = compara_fechas_res(auxB->fecha_inscripcion, &auxA.fecha_inscripcion);
                if(res > 0){
                    fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxB->dni, auxB->apyn, auxB->fecha_inscripcion.dia, auxB->fecha_inscripcion.mes, auxB->fecha_inscripcion.anio);
                    leer_registro_arch_socios_b_res(pfB, auxB);
                    fread(&auxA, tamElem, 1, pfA);
                }else{
                    fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxA.dni, auxA.apyn, auxA.fecha_inscripcion.dia, auxA.fecha_inscripcion.mes, auxA.fecha_inscripcion.anio);
                    fread(&auxA, tamElem, 1, pfA);
                    leer_registro_arch_socios_b_res(pfB, auxB);
                }
            }
            else{
                fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxB->dni, auxB->apyn, auxB->fecha_inscripcion.dia, auxB->fecha_inscripcion.mes, auxB->fecha_inscripcion.anio);
                fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxA.dni, auxA.apyn, auxA.fecha_inscripcion.dia, auxA.fecha_inscripcion.mes, auxA.fecha_inscripcion.anio);
                leer_registro_arch_socios_b_res(pfB, auxB);
                fread(&auxA, tamElem, 1, pfA);
            }
        }
    }
    if(flag == 2){//menorAntig
        while(!feof(pfB) && !feof(pfA)){
            res = cmp_socios_res(&auxA, auxB);
            if(res == 0){
                res = compara_fechas_res(auxB->fecha_inscripcion, &auxA.fecha_inscripcion);
                if(res < 0){
                    fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxB->dni, auxB->apyn, auxB->fecha_inscripcion.dia, auxB->fecha_inscripcion.mes, auxB->fecha_inscripcion.anio);
                    leer_registro_arch_socios_b_res(pfB, auxB);
                    fread(&auxA, tamElem, 1, pfA);
                }else{
                    fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxA.dni, auxA.apyn, auxA.fecha_inscripcion.dia, auxA.fecha_inscripcion.mes, auxA.fecha_inscripcion.anio);
                    fread(&auxA, tamElem, 1, pfA);
                    leer_registro_arch_socios_b_res(pfB, auxB);
                }
            }
            else{
                fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxB->dni, auxB->apyn, auxB->fecha_inscripcion.dia, auxB->fecha_inscripcion.mes, auxB->fecha_inscripcion.anio);
                fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxA.dni, auxA.apyn, auxA.fecha_inscripcion.dia, auxA.fecha_inscripcion.mes, auxA.fecha_inscripcion.anio);
                leer_registro_arch_socios_b_res(pfB, auxB);
                fread(&auxA, tamElem, 1, pfA);
            }
        }
    }
    if(flag == 3){//antig = 0
       t_fecha fechaActual;
       fechaActual.anio = 2024;
       fechaActual.dia = 5;
       fechaActual.mes = 12;
        while(!feof(pfB) && !feof(pfA)){
            res = cmp_socios_res(&auxA, auxB);
            if(res == 0){
                    fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxB->dni, auxB->apyn, fechaActual.dia, fechaActual.mes, fechaActual.anio);
                    leer_registro_arch_socios_b_res(pfB, auxB);
                    fread(&auxA, tamElem, 1, pfA);
                }
            else{
                fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxB->dni, auxB->apyn, fechaActual.dia, fechaActual.mes, fechaActual.anio);
                fprintf(pfF, "%lu|%s|%d/%d/%d\n", auxA.dni, auxA.apyn, fechaActual.dia, fechaActual.mes, fechaActual.anio);
                leer_registro_arch_socios_b_res(pfB, auxB);
                fread(&auxA, tamElem, 1, pfA);
            }
        }
    }
    fclose(pfA);
    fclose(pfB);
    fclose(pfF);
    return 1;
}

