 // FileName:        TIMER32_MSP432.h
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:		     MSP432P401R
 // Program Version: CCS V8.3 TI
 // Driver Version:  1.0
 // Company:         Texas Instruments
 // Description:     Descripci�n general de constantes, macros y configuraciones del m�dulo TIMER32.
 // Authors:         Jes�s Andr�s Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         09/2020

#ifndef TIMER32_MSP432_H_
#define TIMER32_MSP432_H_

/* Definici�n de macros. */

// Modos de funcionamiento.
#define TIMER32_FreeRunningMode     ((uint32_t)0x00000000)
#define TIMER32_PeriodicMode        ((uint32_t)0x00000040)
#define TIMER32_OneShotMode         ((uint32_t)0x00000001)

// Tipos de prescaler (divisor de tiempos).
#define TIMER32_PrescaleDiv_1       ((uint32_t)0x00000000)
#define TIMER32_PrescaleDiv_16      ((uint32_t)0x00000004)
#define TIMER32_PrescaleDiv_256     ((uint32_t)0x00000008)

// Tama�o del timer.
#define TIMER32_16BitSize           ((uint32_t)0x00000000)
#define TIMER32_32BitSize           ((uint32_t)0x00000002)

// Encendido o apagado.
#define TIMER32_Enabled             1
#define TIMER32_Disabled            0

// Encendido del m�dulo timer32_1.
extern void timer_init(int timer);

// Habilita la interrupci�n del m�dulo timer32_1.
extern void timer_enableINT(int timer);

// Deshabilita la interrupci�n del m�dulo timer32_1.
extern void timer_disabledINT(int timer);

// Configura el modo, divisor de tiempo y tama�o del m�dulo timer32_1.
extern void timer_config(uint32_t Mode, uint32_t Prescale, uint32_t Size, int timer);

// Brinda el valor al que debe cargarse el modulo del timer32_1.
extern void timer_setValue(uint32_t LoadValue, int timer);

// Habilita el m�dulo timer32_1.
extern void timer_enable(int timer);

// Deshabilita el m�dulo timer32_1.
extern void timer_disabled(int timer);

// Limpia la bandera de interrupci�n del m�dulo timer32_1.
extern void timer_clearINT(int timer);


#endif /* TIMER32_MSP432_H_ */
