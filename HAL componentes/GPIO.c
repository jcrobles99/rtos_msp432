 // FileName:        GPIO.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Archivo que inicializa el GPIO
 // Authors:         Jesús Andrés Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         04/12/2020

#include "system.h"

/*FUNCTION******************************************************************************
*
* Function Name    : Iniciar_GPIO
* Returned Value   : None.
* Comments         : Controla los preparativos para poder usar las entradas y salidas GPIO
*
*END***********************************************************************************/

// Funcion donde se van a inicializar los leds como salida y como va a ser su estado inicial (Encendido/apagado)
void Iniciar_GPIO(void)
{
    gpio_init();
    gpio_outputBIT(PUERTO_LED1,  BIT_LED1,  0);  //Led1 Rojo, inicia encendido
    gpio_outputBIT(PUERTO_LED2,  BIT_LED2,  1);  //Led2 rgb, rojo inicia apagado
    gpio_outputBIT(PUERTO_LED3,  BIT_LED3,  1);  //Led2 rgb, verde inicia apagado
    gpio_outputBIT(PUERTO_LED4,  BIT_LED4,  1);  //Led2 rgb, azul inicia apagado
    putsf_UART(MAIN_UART, "\n\rEquipo No.2\n\r");
    putsf_UART(MAIN_UART, "\n\rBIENVENIDOS A LARA BOOLE INC\n\r");

    /*Seleccionar flanco de las interrupciones a utilizar*/
    gpio_FlancoInt(5,B1,GPIO_HIGH_TO_LOW);
    gpio_FlancoInt(3,B5,GPIO_HIGH_TO_LOW);
    gpio_FlancoInt(6,B7,GPIO_HIGH_TO_LOW);

    /*Preparativos de interrupción (limpiar las banderas de interrupción asi como la habilitación de los pines utilizar*/
    GPIO_WIPE_INT_BAND(P5,B1);
    GPIO_WIPE_INT_BAND(P3,B5);
    GPIO_WIPE_INT_BAND(P6,B7);
    GPIO_ENABLE_INT(P5,B1);
    GPIO_ENABLE_INT(P3,B5);
    GPIO_ENABLE_INT(P6,B7);

    /* Uso del módulo Interrupt para generar la interrupción general y registro de esta en una función
    *  que se llame cuando la interrupción se active.                                                   */
    Int_registerInterrupt(INT_PORT5, INT_1);
    Int_enableInterrupt(INT_PORT5);
    Int_registerInterrupt(INT_PORT3, INT_2);
    Int_enableInterrupt(INT_PORT3);
    Int_registerInterrupt(INT_PORT6, INT_3);
    Int_enableInterrupt(INT_PORT6);

    /*Inicialización de los pines conectados a los Leds para la secuencia*/
    GPIO_CONFIG_OUTPUT(P5,B0); //LED 1
    GPIO_CONFIG_OUTPUT(P5,B2); //LED 2
    GPIO_OUTPUT_LOW(P5,B0);   //LED 1
    GPIO_OUTPUT_HIGH(P5,B2);   //LED 2
}

#if defined(CONTROL_PLUS)
/*FUNCTION******************************************************************************
*
* Function Name    : HVAC_InicialiceIO
* Returned Value   : None.
* Comments         : Controla los preparativos para poder usar las entradas y salidas GPIO del control plus.
*
*END***********************************************************************************/
void Iniciar_GPIO_Plus(void)
{
    // Modo de interrupción de los botones principales.
    gpio_FlancoInt(1,BIT(SP_UP),   GPIO_HIGH_TO_LOW);
    gpio_FlancoInt(1,BIT(SP_DOWN), GPIO_HIGH_TO_LOW);

    // Preparativos de interrupción.
    GPIO_WIPE_INT_BAND(P1,B1);
    GPIO_WIPE_INT_BAND(P1,B4);
    GPIO_ENABLE_INT(P1,B1);
    GPIO_ENABLE_INT(P1,B4);

    // Se necesitan más entradas, se usarán las siguientes:
    gpio_configIO(2, FAN_ON, ENTRADA);
    gpio_configIO(2, FAN_AUTO, ENTRADA);
    gpio_configIO(SYSTEM_PORT, SYSTEM_COOL, ENTRADA);
    gpio_configIO(SYSTEM_PORT, SYSTEM_OFF, ENTRADA);
    gpio_configIO(SYSTEM_PORT, SYSTEM_HEAT, ENTRADA);
    gpio_configIO(SETPOINT_PORT, SP_UP, ENTRADA);
    gpio_configIO(SETPOINT_PORT, SP_DOWN, ENTRADA);

    /* Uso del módulo Interrupt para generar la interrupción general y registro de esta en una función
    *  que se llame cuando la interrupción se active.                                                   */
    Int_registerInterrupt(INT_PORT1, INT_SWI);
    Int_enableInterrupt(INT_PORT1);
}
#endif
