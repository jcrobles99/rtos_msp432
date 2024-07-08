 // FileName:        system_Threads.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Definición de las funciones de los threads System_Threads().
 // Authors:         Jesús Andrés Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         04/12/2020


/* EXPLICACION DEL PROGRAMA DE LA PLANTILLA.
 *  Sistema de control de entradas a un establecimiento, consiste un ir contando
 *  las personas que ingresar y salen del mismo cuidando el cupo máximo permitido,
 *  además de que se toma la temperatura de cada persona que va a ingresar y en caso
 *  de que se alta no se le permitirá el acceso.
 *  Al sistema plus se le agrega un control de temperatura ambiente. HVAC.
 */

#include "system.h"

void *Control_Thread(void *arg0);
#if defined (CONTROL_PLUS)
void *Control_Plus_Thread(void *arg0);
#endif

/*********************************THREAD*************************************
 * Function: Control_Thread
 * Preconditions: None.
 * Input:  Apuntador vacío que puede referenciarse a cualquier tipo de dato.
 * Output: None.
 *
 *****************************************************************************/

void *Control_Thread(void *arg0)
{
//Funciones de inicialización de componentes
   Iniciar_UART ();
   Iniciar_ADC();
   Iniciar_Timer();
   Iniciar_GPIO();

   /* Inicia el sistema (función predeterminada). */
   SystemInit();

   /* Máquina de estados sincronizada. */
   while(TRUE)
   {
       Checar_entradas();
#if defined(CONTROL_NOPLUS)
       Imprimir();
#endif
       usleep(10000);
   }
}

/*********************************THREAD*************************************
 * Function: Control_Plus_Thread
 * Preconditions: None.
 * Input:  Apuntador vacío que puede referenciarse a cualquier tipo de dato.
 * Output: None.
 *
 *****************************************************************************/
#if defined(CONTROL_PLUS)
void *Control_Plus_Thread(void *arg0)
{
    Iniciar_GPIO_Plus();
    Iniciar_ADC_Plus();
   /* Máquina de estados sincronizada. */
   while(TRUE)
   {
       HVAC_ActualizarEntradas();
       HVAC_ActualizarSalidas();
       Imprimir_Plus();
       usleep(10000);
   }
}
#endif
