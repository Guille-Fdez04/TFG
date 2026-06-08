/*
 * Listado de los tipos de mensajes empleados en la aplicación, así como definiciones de sus parámetros.
*/
#ifndef __USB_MESSAGES_TABLE_H
#define __USB_MESSAGES_TABLE_H

#include<stdint.h>

typedef enum {
    MENSAJE_NO_IMPLEMENTADO,
    MENSAJE_PING,
    MENSAJE_TEMP,
    MENSAJE_HR,
    MENSAJE_PRES,
    MENSAJE_ACELERACION,
    MENSAJE_ANGULOS,
    MENSAJE_APLICACION,
    MENSAJE_GIROSCOPIO,
    MENSAJE_CPU,
    MENSAJE_PRESION_ASL,
    MENSAJE_MAGNETO,

} messageTypes;



//#pragma pack(1)   //Con esto consigo que el alineamiento de las estructuras en memoria del PC (32 bits) no tenga relleno.
//Con lo de abajo consigo que el alineamiento de las estructuras en memoria del microcontrolador no tenga relleno
#define PACKED __attribute__ ((packed))

typedef struct {
    uint8_t message;
} PACKED PARAM_MENSAJE_NO_IMPLEMENTADO;

typedef struct{
    int32_t parte_entera;
    int32_t parte_fraccionaria;
} PACKED PARAM_MENSAJE_TEMP;

typedef struct{
    int32_t parte_entera;
    int32_t parte_fraccionaria;
} PACKED PARAM_MENSAJE_HR;

typedef struct{
    int32_t presion;
    int32_t parte_entera_altitud;
    uint32_t parte_fraccionaria_altitud;
} PACKED PARAM_MENSAJE_PRESION;

typedef struct{
    float ejeX;
    float ejeY;
    float ejeZ;
    float maximo;
} PACKED PARAM_MENSAJE_ACELERACION;

typedef struct{
    int32_t cabeceo;
    int32_t alabeo;

} PACKED PARAM_MENSAJE_ANGULOS;

typedef struct{
    uint8_t estado;
} PACKED PARAM_MENSAJE_APLICACION;

typedef struct{
    float ejeX;
    float ejeY;
    float ejeZ;
} PACKED PARAM_MENSAJE_GIROSCOPIO;

typedef struct{

    uint32_t cpu;

}PACKED PARAM_MENSAJE_CPU;

typedef struct{
    float presasl;
}PACKED PARAM_MENSAJE_PRES_ASL;

typedef struct{

    float ejex;
    float ejey;
    float ejez;

}PACKED PARAM_MENSAJE_MAGNETO;



//#pragma pack()    //...Pero solo para los mensajes que voy a intercambiar, no para el resto





#endif
