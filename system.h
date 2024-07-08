 // FileName:        system.h
 // Dependencies:    None
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Incluye librerías, define ciertas macros y significados así como llevar un control de versiones.
 // Authors:         Jesús Andrés Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         04/12/2020

#ifndef _system_h_
#define _system_h_

//Definiciones para controlar si el sistema es No Plus o Plus
#define CONTROL_PLUS
//#define CONTROL_NOPLUS

//Definición para controlar el cupo máximo
#define cupo 10

#pragma once

#define __MSP432P401R__
#define  __SYSTEM_CLOCK    48000000 // Frecuencias funcionales recomendadas: 12, 24 y 48 Mhz.

/* Librerias a usar (paquete predeterminado). */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Archivos fuente POSIX. */
#include <pthread.h>
#include <semaphore.h>
#include <ti/posix/tirtos/_pthread.h>
#include <ti/sysbios/knl/Task.h>

/* Archivos fuente RTOS. */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Event.h>

/* Incluye Board Support Package. */
#include "Drivers/BSP.h"

/*Declaracion del apuntador del hilo de control*/
pthread_t          control_thread;
/*Declaracion del apuntador del hilo de control plus*/
#if defined (CONTROL_PLUS)
pthread_t          control_plus_thread;
#endif

/* Definiciones para el thread principal. */
#define THREADSTACKSIZE1            1500

/* Definiciones del estado 'normal' de los botones externos a la tarjeta (solo hay dos botones). */
#define GND 0
#define VCC 1

/* Definición del estado 'normal' de los botones que ya existen en la tarjeta y de los que son externos. */
#define ESTADO_NORMAL_DEL_BOTON  VCC  // Esto no se cambia.
#define NORMAL_STATE_EXTRA_BUTTONS GND  // Aqui se coloca GND o VCC (varía dependiendo de la implementación deseada).

/* Funciones de inicialización */
extern void Iniciar_UART (void);
extern void Iniciar_GPIO(void);
extern void Iniciar_ADC(void);
extern void Iniciar_Timer(void);


/* Funcion especial que imprime el mensaje asegurando que no habrá interrupciones y por ende,
 * asegure funcionamiento óptimo.                                                           */
extern void print(char* message);

/*Activa el ADC*/
extern void Dispara_ADC(void);
//Declaración de la función TIMER32_INT1
extern void Timer32_INT1 (void);
//Declaración de la función Delay_ms
extern void Tiempo_ms(uint32_t time);

//Función que checa entradas al sistema
extern void Checar_entradas(void);

#if defined(CONTROL_NOPLUS)
//Función imprime estados control no plus
extern void Imprimir(void);
#endif

//Funcion para leer la temperatura corporal del cliente
extern float Temperatura(void);

/*Funcion de interrupcion del puerto 5, utilizada para entradas*/
extern void INT_1(void);
/*Funcion de interrupcion del puerto 3, utilizada para salidas*/
extern void INT_2(void);
/*Funcion de interrupcion del puerto 6, utilizada para encender y apagar sistema*/
extern void INT_3(void);

/*Variables utilizadas en el programa*/

#define SYSTEM_CLOCK 48000000   //Define a SYSTEM_CLOCK con el valor de 48000000


extern float temperatura;           //variable donde se guarda la temperautura corporal
extern int E1, S1, door, select, x, sistema, personas, iteracion_imp;               //Variables del sistema
//Variables utilizadas para guardar cadenas para impresión
extern char juan[10];
extern char robles[10];
extern char lara[10];
extern char jesus[10];

//Declaraciones del Control Plus
/* Enumeradores para la descripción del sistema. */
#if defined(CONTROL_PLUS)
enum FAN        // Para el fan (abanico).
{
    On,
    Auto,
};

enum SYSTEM     // Para el sistema cuando FAN está en auto (cool, off y heat, o no considerar ninguno y usar fan only).
{
    Cool,
    Off,
    Heat,
    FanOnly,
};

struct EstadoEntradas
{
    uint8_t  SystemState;
    uint8_t     FanState;
}   EstadoEntradas;

// Definiciones Básicas.
#define ENTRADA 1
#define SALIDA 0

// Re-definición de los bits y puertos de entrada a utilizar.
#define FAN_ON      B3
#define FAN_AUTO    B4
#define SYSTEM_COOL B5
#define SYSTEM_OFF  B6
#define SYSTEM_HEAT B7
#define SP_UP       B1
#define SP_DOWN     B4

#define FAN_PORT        2
#define SYSTEM_PORT     2
#define SETPOINT_PORT   1
#define FAN_PORTT        P2
#define SYSTEM_PORTT     P2
#define SETPOINT_PORTT   P1

#define TEMP_CH         CH0
#define HEARTBEAT_CH    CH1
#define POT_PIN         AN1

// Re-definición de los bits y puertos de salida a utilizar.
#define FAN_LED     BSP_LED1
#define HEAT_LED    BSP_LED2
#define HBeatLED    BSP_LED3
#define COOL_LED    BSP_LED4

#define FAN_LED_PORT    BSP_LED1_PORT
#define HEAT_LED_PORT   BSP_LED2_PORT
#define HB_LED_PORT     BSP_LED3_PORT
#define COOL_LED_PORT   BSP_LED4_PORT

// Definiciones del estado 'normal' de los botones externos a la tarjeta (solo hay dos botones).
#define GND 0
#define VCC 1
#define NORMAL_STATE_EXTRA_BUTTONS GND  // Aqui se coloca GND o VCC.

// Definiciones del sistema.
#define MAX_MSG_SIZE 64
#define MAX_ADC_VALUE 16383             // (2 ^14 bits) es la resolución default.
#define MAIN_UART (uint32_t)(EUSCI_A0)
#define DELAY 20000

// Definición para el RTOS.
#define THREADSTACKSIZE1 1500

/* Función de interrupción para botones de setpoint. */
extern void INT_SWI(void);

extern void Iniciar_GPIO_Plus(void);
extern void Iniciar_ADC_Plus(void);

/* Funciones principales. */
extern void HVAC_ActualizarEntradas(void);
extern void HVAC_ActualizarSalidas(void);
extern void Imprimir_Plus(void);

// Funciones para los estados Heat y Cool.
extern void HVAC_Heat(void);
extern void HVAC_Cool(void);

// Funciones para incrementar o disminuir setpoint.
extern void HVAC_SetPointUp(void);
extern void HVAC_SetPointDown(void);

/* Variables sobre las cuales se maneja el sistema. */
extern float TemperaturaActual;       // Temperatura.
extern float SetPoint;         // Valor deseado.

extern char state[MAX_MSG_SIZE];      // Cadena a imprimir.

extern bool toggle;               // Toggle para el heartbeat.
extern bool event;            // Evento I/O que fuerza impresión inmediata.

extern bool FAN_LED_State;                                     // Estado led_FAN.
extern const char* SysSTR[];    // Control de los estados.

#endif

#endif
