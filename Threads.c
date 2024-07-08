 // FileName:        Threads.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Activa las funciones del hilo System_Thread.
 //                  Main del proyecto.
 // Authors:         Juan Carlos Robles Ortega y Jesús Andrés Lara Acevedo.
 // Updated:         03/12/2020

#include "system.h"

extern void *Control_Thread(void *arg0);   // Funciones de threads que arrancarán inicialmente.

#if defined (CONTROL_PLUS)
extern void *Control_Plus_Thread(void *arg0);
#endif

int main(void)
{
    pthread_attr_t      pAttrs;
    struct sched_param  priParam;
    int                 retc;
    int                 detachState;

   pthread_attr_init(&pAttrs);                                  /* Reinicio de parámetros. */

   detachState = PTHREAD_CREATE_DETACHED;                       // Los recursos se liberarán después del término del thread.
   retc = pthread_attr_setdetachstate(&pAttrs, detachState);    // Además, al hilo no se le puede unir otro (join).
   if (retc != 0) { while (1); }

   /**********************
   ** Thread principal. **
   **********************/

   priParam.sched_priority = 2;                                         // Prioridad de la tarea principal.
   retc |= pthread_attr_setstacksize(&pAttrs, THREADSTACKSIZE1);        // Así se determinaría el tamaño del stack.
   if (retc != 0) { while (1); }
   pthread_attr_setschedparam(&pAttrs, &priParam);
   retc = pthread_create(&control_thread, &pAttrs, Control_Thread, NULL); // Creación del thread.
   if (retc != 0) { while (1); }

#if defined(CONTROL_PLUS)
   /**********************
   ** Thread secundario. **
   **********************/

   priParam.sched_priority = 1;                                         // Prioridad de la tarea principal.
   retc |= pthread_attr_setstacksize(&pAttrs, THREADSTACKSIZE1);        // Así se determinaría el tamaño del stack.
   if (retc != 0) { while (1); }
   pthread_attr_setschedparam(&pAttrs, &priParam);
   retc = pthread_create(&control_plus_thread, &pAttrs, Control_Plus_Thread, NULL); // Creación del thread.
   if (retc != 0) { while (1); }
#endif


   /* Arranque del sistema. */
   BIOS_start();
   return (0);
}
