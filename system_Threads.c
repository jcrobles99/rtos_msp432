 // FileName:        system_Threads.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Definici�n de las funciones de los threads System_Threads().
 // Authors:         Jes�s Andr�s Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         04/12/2020


/* EXPLICACION DEL PROGRAMA DE LA PLANTILLA.
 *  Sistema de control de entradas a un establecimiento, consiste un ir contando
 *  las personas que ingresar y salen del mismo cuidando el cupo m�ximo permitido,
 *  adem�s de que se toma la temperatura de cada persona que va a ingresar y en caso
 *  de que se alta no se le permitir� el acceso.
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
 * Input:  Apuntador vac�o que puede referenciarse a cualquier tipo de dato.
 * Output: None.
 *
 *****************************************************************************/

void *Control_Thread(void *arg0)
{
//Funciones de inicializaci�n de componentes
   Iniciar_UART ();
   Iniciar_ADC();
   Iniciar_Timer();
   Iniciar_GPIO();

   /* Inicia el sistema (funci�n predeterminada). */
   SystemInit();

   /* M�quina de estados sincronizada. */
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
 * Input:  Apuntador vac�o que puede referenciarse a cualquier tipo de dato.
 * Output: None.
 *
 *****************************************************************************/
#if defined(CONTROL_PLUS)
void *Control_Plus_Thread(void *arg0)
{
    Iniciar_GPIO_Plus();
    Iniciar_ADC_Plus();
   /* M�quina de estados sincronizada. */
   while(TRUE)
   {
       HVAC_ActualizarEntradas();
       HVAC_ActualizarSalidas();
       Imprimir_Plus();
       usleep(10000);
   }
}
#endif
