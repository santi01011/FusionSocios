#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED

typedef struct
{
    int dia, mes, anio;
}t_fecha;

typedef struct
{
    long dni;
    char apyn[30];
    t_fecha fecha_inscripcion;
}t_socio;

#endif // TIPOS_H_INCLUDED
