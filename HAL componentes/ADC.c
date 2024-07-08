 // FileName:        ADC.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Archivo que inicializa el ADC
 // Authors:         Jesús Andrés Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         04/12/2020

#include "system.h"

/*FUNCTION******************************************************************************
*
* Function Name    : Iniciar_ADC
* Returned Value   : None.
* Comments         : Función que inicializa el ADC
*
*END***********************************************************************************/

void Iniciar_ADC()
{
    ADC_Inicializar(Resolucion14bits, CLKDiv8);  //Definir la resolución del ADC (8 bits) así como las divisiones de reloj (8)
    ADC_Modo_Conversion(SequenceOfChannels);       //Definir el modo de conversión del ADC (Secuencia de canales)
    ADC_Configura_Pin(CH2,AN6,VCC_VSS);            //Configuración de los canales y de los puertos a utilizar, así como la referencia a utilizar
    ADC_Configura_Pin(CH1,AN8,VCC_VSS);
    CanalesADC(CH0, CH2);                       //Definir el canal de termino de la secuencia de canales
}

#if defined(CONTROL_PLUS)
/*FUNCTION******************************************************************************
*
* Function Name     : Iniciar_ADC_Plus
* * Returned Value  : None.
* Comments          : Función que inicializa lo necesario para ADC en el control plus
*
*END***********************************************************************************/

void Iniciar_ADC_Plus(void)
{
    ADC_Habilita_Temp_Sensor(CH0);                          // Se configura el sensor en el canal 0.
}
#endif
