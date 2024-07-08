 // FileName:        TIMER32_MSP432.c
 // Dependencies:    System.h
 // Processor:       MSP432
 // Board:           MSP432P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Definici�n de funciones del m�dulo timer32.
 // Authors:         Alejandro Lerma Corral y Miguel �ngel Maldonado Villar
 // Updated:         11/2020

#include "system.h"

// Encendido del m�dulo timer32_1.
void timer_init(int timer)
{
    if(timer==1)
        timer_config( TIMER32_PeriodicMode, TIMER32_PrescaleDiv_1, TIMER32_32BitSize,1 );
    if(timer==2)
        timer_config( TIMER32_PeriodicMode, TIMER32_PrescaleDiv_1, TIMER32_32BitSize,2 );
}

// Habilita la interrupci�n del m�dulo timer32_1.
void timer_enableINT(int timer)
{
    if(timer==1)
        BITBAND_PERI( TIMER32_1->CONTROL, TIMER32_CONTROL_IE_OFS ) = 1;
    if(timer==2)
        BITBAND_PERI( TIMER32_2->CONTROL, TIMER32_CONTROL_IE_OFS ) = 1;

}

// Deshabilita la interrupci�n del m�dulo timer32_1.
void timer_disabledIN(int timer)
{
    if(timer==1)
        BITBAND_PERI( TIMER32_1->CONTROL, TIMER32_CONTROL_IE_OFS ) = 0;
    if(timer==2)
        BITBAND_PERI( TIMER32_2->CONTROL, TIMER32_CONTROL_IE_OFS ) = 0;
}

// Configura el modo, divisor de tiempo y tama�o del m�dulo timer32_1.
void timer_config(uint32_t Mode, uint32_t Prescale, uint32_t Size, int timer)
{
    if(timer==1)
        TIMER32_1->CONTROL |= (Mode | Prescale | Size);
    if(timer==2)
        TIMER32_2->CONTROL |= (Mode | Prescale | Size);
}

// Brinda el valor al que debe cargarse el modulo del timer32_1.
void timer_setValue(uint32_t LoadValue, int timer)
{
    if(timer==1)
        TIMER32_1->LOAD = LoadValue;
    if(timer==2)
        TIMER32_2->LOAD = LoadValue;
}

// Habilita el m�dulo timer32_1.
void timer_enable(int timer)
{
    if(timer==1)
        BITBAND_PERI( TIMER32_1->CONTROL, TIMER32_CONTROL_ENABLE_OFS ) = 1;
    if(timer==2)
        BITBAND_PERI( TIMER32_2->CONTROL, TIMER32_CONTROL_ENABLE_OFS ) = 1;
}

// Deshabilita el m�dulo timer32_1.
void timer_disabled(int timer)
{
    if(timer==1)
        BITBAND_PERI( TIMER32_1->CONTROL, TIMER32_CONTROL_ENABLE_OFS ) = 0;
    if(timer==2)
        BITBAND_PERI( TIMER32_2->CONTROL, TIMER32_CONTROL_ENABLE_OFS ) = 0;
}

// Limpia la bandera de interrupci�n del m�dulo timer32_1.
void timer_clearINT(int timer)
{
    if(timer==1)
        TIMER32_1->INTCLR = 0x00000000;
    if(timer==2)
        TIMER32_2->INTCLR = 0x00000000;
}
