 // FileName:        Imprimir.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Archivo que imprime los estados del control no plus y el
 //                  control plus
 // Authors:         Jesús Andrés Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         04/12/2020

#include "system.h"

/*FUNCTION******************************************************************************
*
* Function Name    : Imprimir
* Returned Value   : None.
* Comments         : Función para imprimir el estado del control no plus
*END***********************************************************************************/
#if defined(CONTROL_NOPLUS)
void Imprimir()
{
    iteracion_imp++;
    if(iteracion_imp==100)
    {
        if(sistema==1)
        {
            putsf_UART(MAIN_UART, "\n\rSistema: On\n\r");
                sprintf(robles, "Cupo máximo: %d  ",cupo);
                putsf_UART(MAIN_UART, robles);
                sprintf(lara, "Personas: %s  \n\r",juan);
                putsf_UART(MAIN_UART, lara);
                if(select==1)
                {
                    putsf_UART(MAIN_UART, "Puerta: ");
                    if(door==1)
                    {
                        putsf_UART(MAIN_UART, "Abierta\n\r");
                    }
                    else
                    {
                        putsf_UART(MAIN_UART, "Cerrada\n\r");
                        sprintf(jesus, "--\n\r\n\r");
                    }
                }
                if(select==0)
                {
                    putsf_UART(MAIN_UART, "PERSONA ENFERMA\n\r");
                    x++;
                    if(x==5)
                    {
                        select=1;
                        x=0;
                    }
                }
                putsf_UART(MAIN_UART, "Temperatura: ");
                putsf_UART(MAIN_UART, jesus);
            }
        else
        {
            putsf_UART(MAIN_UART, "\n\rSistema: Off");
        }
        iteracion_imp=0;
    }
}
#endif

#if defined(CONTROL_PLUS)
/*FUNCTION******************************************************************************
*
* Function Name    : Imprimir_Plus
* Returned Value   : None.
* Comments         : Función para imprimir el estado del control plus
*END***********************************************************************************/
void Imprimir_Plus(void)
{
    iteracion_imp++;
    if(iteracion_imp==100)
    {
        if(sistema==1)
        {
            putsf_UART(MAIN_UART, "\n\rSistema: On\n\r");
                sprintf(robles, "Cupo máximo: %d  ",cupo);
                putsf_UART(MAIN_UART, robles);
                sprintf(lara, "Personas: %s  \n\r",juan);
                putsf_UART(MAIN_UART, lara);
                if(select==1)
                {
                    putsf_UART(MAIN_UART, "Puerta: ");
                    if(door==1)
                    {
                        putsf_UART(MAIN_UART, "Abierta\n\r");
                    }
                    else
                    {
                        putsf_UART(MAIN_UART, "Cerrada\n\r");
                        sprintf(jesus, "--\n\r\n\r");
                    }
                }
                if(select==0)
                {
                    putsf_UART(MAIN_UART, "PERSONA ENFERMA\n\r");
                    x++;
                    if(x==5)
                    {
                        select=1;
                        x=0;
                    }
                }

                putsf_UART(MAIN_UART, "Temperatura: ");
                putsf_UART(MAIN_UART, jesus);
                sprintf(state,"Fan: %s, System: %s, SetPoint: %0.2f\n\r",
                EstadoEntradas.FanState == On? "On":"Auto",
                SysSTR[EstadoEntradas.SystemState],
                SetPoint);
                putsf_UART(MAIN_UART,state);
                sprintf(state,"Temperatura Actual: %0.2f°C %0.2f°F  Fan: %s\n\r\n\r",
                TemperaturaActual,
                ((TemperaturaActual*9.0/5.0) + 32),
                FAN_LED_State?"On":"Off");
                putsf_UART(MAIN_UART,state);
            }
        else
        {
            putsf_UART(MAIN_UART, "\n\rSistema: Off");
        }
        iteracion_imp=0;

    }
}
#endif
