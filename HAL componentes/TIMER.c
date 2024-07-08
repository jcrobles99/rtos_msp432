 // FileName:        TIMER.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Archivo que inicializa el TIMER
 // Authors:         Jesús Andrés Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         04/12/2020

#include "system.h"

/*FUNCTION******************************************************************************
*
* Function Name    : Iniciar_Timer()
* Returned Value   : None.
* Comments         : Inicilaiza el TIMER
*
*END***********************************************************************************/
void Iniciar_Timer()
{
    timer_config(TIMER32_OneShotMode, TIMER32_PrescaleDiv_1,TIMER32_32BitSize,1);   //Configura el timer como Modo de disparo único, tamaño de 32 bits y preescaler de 1.
    Int_registerInterrupt(INT_T32_INT1, Timer32_INT1);  //Registra la interrupción deseada
    Int_enableInterrupt(INT_T32_INT1);      //Habilita la interrupcion deseada
}

/*FUNCTION******************************************************************************
*
* Function Name    : Tiempo_ms()
* Returned Value   : None.
* Comments         : Activar Timer
*
*END***********************************************************************************/
void Tiempo_ms(uint32_t time)
{
    timer_enable(1); //Habilita el timer
    timer_enableINT(1); //Habilita la interrupcion del timer
    timer_setValue(time*(SYSTEM_CLOCK/1000),1);    //Carga el valor en milisegundos y mediante la formula, calculará un numero para contar y que esto dure 2 segundos
}

/*FUNCTION******************************************************************************
*
* Function Name    : Timer32_INT1()
* Returned Value   : None.
* Comments         : Interrupción cuando el timer finaliza
*
*END***********************************************************************************/
void Timer32_INT1(void)
{
    timer_clearINT(1); //Se limpia la bandera del timer para poder hacer uso de ella de nuevo
    door=0;  //Se cambia variable para cerrar puerta
}
