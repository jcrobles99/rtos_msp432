 // FileName:        GPIO_MSP432.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP432P401R
 // Program version: CCS V8.3 TI
 // Driver version:  1.0
 // Company:         Texas Instruments
 // Description:     Definición de funciones del módulo GPIO para entradas y salidas.
 // Authors:         Alejandro Lerma Corral y Miguel Ángel Maldonado Villar
 // Updated:         11/2020

#include "system.h"     // Configuración del sistema.


/* Declaración del arreglo GPIO_PORT_TO_BASE
 * En el cual se encuentran las direcciones en donde comienzan
 * los registros de control para cada puerto.                   */
static const uint32_t GPIO_PORT_TO_BASE[] =
{   0x00,
    0x40004C00,
    0x40004C01,
    0x40004C20,
    0x40004C21,
    0x40004C40,
    0x40004C41,
    0x40004C60,
    0x40004C61,
    0x40004C80,
    0x40004C81,
    0x40004D20
};

/*****************************************************************************
 * Function: gpio_init
 * Preconditions: None.
 * Overview: Inicialización del módulo GPIO. Se configuran los pines de
 *          entrada y salida que corresponden a los LEDs y los switches
 *          en la tarjeta.
 * Input: None.
 * Output: None.
 *
 *****************************************************************************/

void gpio_init(void)
{
    // Configuracion de LEDS de la tarjeta como Salidas
    GPIO_CONFIG_OUTPUT(P1,B0); // Configura el pin como salida (LED1 - rojo)
    GPIO_CONFIG_OUTPUT(P2,B0); // Configura el pin como salida (LED_RGB - rojo)
    GPIO_CONFIG_OUTPUT(P2,B1); // Configura el pin como salida (LED_RGB - verde)
    GPIO_CONFIG_OUTPUT(P2,B2); // Configura el pin como salida (LED_RGB - azul)


    // Configuracion de BOTONES de la tarjeta como Entradas
    GPIO_CONFIG_INPUT(P1,B1); // Configura el pin como entrada (SW1)
    GPIO_CONFIG_INPUT(P1,B4); // Configura el pin como entrada (SW2)

    //Configuracion de las resistencias Pull-Up internas
    GPIO_PULLUP_ENABLE(P1,B1); // Habilita las resistencias de pullup del pin (SW1)
    GPIO_PULLUP_ENABLE(P1,B4); // Habilita las resistencias de pullup del pin (SW2)

    GPIO_OUTPUT_HIGH(P1,B1); // Alternativa para forzar el pin a tener las pull-up habilitadas.
    GPIO_OUTPUT_HIGH(P1,B4); // Alternativa para forzar el pin a tener las pull-up habilitadas.
}

/***************************************************************************
 * Function: gpio_configIO
 * Preconditions: None.
 * Overview: Configura un PIN como entrada o salida
 * Input: Puerto, Pin, salida (0) o entrada (1).
 * Output: None.
 *
 *****************************************************************************/

void gpio_configIO(uint_fast8_t Port, uint_fast16_t Pin, bool I_O)  // 0: Salida, // 1: Entrada.
{
    if(Port%2 == 0)  // Si el puerto es par.
    {
        if(!I_O)
            GPIO_CONFIG_OUTPUT(((DIO_PORT_Even_Interruptable_Type*) GPIO_PORT_TO_BASE[Port-1]), Pin);
        else
        {
            GPIO_CONFIG_INPUT(((DIO_PORT_Even_Interruptable_Type*) GPIO_PORT_TO_BASE[Port-1]), Pin);
            GPIO_PULLUP_ENABLE(((DIO_PORT_Even_Interruptable_Type*) GPIO_PORT_TO_BASE[Port-1]), Pin);
            GPIO_OUTPUT_HIGH(((DIO_PORT_Even_Interruptable_Type*) GPIO_PORT_TO_BASE[Port-1]), Pin);
        }
    }
    else                    // Si el puerto es impar.
    {
        if(!I_O)
            GPIO_CONFIG_OUTPUT(((DIO_PORT_Odd_Interruptable_Type*) GPIO_PORT_TO_BASE[Port]), Pin);
        else
        {
            GPIO_CONFIG_INPUT(((DIO_PORT_Odd_Interruptable_Type*) GPIO_PORT_TO_BASE[Port]), Pin);
            GPIO_PULLUP_ENABLE(((DIO_PORT_Odd_Interruptable_Type*) GPIO_PORT_TO_BASE[Port]), Pin);
            GPIO_OUTPUT_HIGH(((DIO_PORT_Odd_Interruptable_Type*) GPIO_PORT_TO_BASE[Port]), Pin);
        }
    }
}

/******************************************************************************
 * Function: gpio_outputBIT
 * Preconditions: None.
 * Overview: Establece el valor de una salida.
 * Input: Puerto , Pin , estado.
 * Output: None.
 *
 *****************************************************************************/

void gpio_outputBIT(uint_fast8_t Port, uint_fast16_t Pin, bool state)
{
    if(Port%2 == 0)  // Si el puerto es par.
    {
        if(!state)
            GPIO_OUTPUT_LOW(((DIO_PORT_Even_Interruptable_Type*) GPIO_PORT_TO_BASE[Port-1]), Pin);
        else
            GPIO_OUTPUT_HIGH(((DIO_PORT_Even_Interruptable_Type*) GPIO_PORT_TO_BASE[Port-1]), Pin);
    }
    else                    // Si el puerto es impar.
    {
        if(!state)
            GPIO_OUTPUT_LOW(((DIO_PORT_Odd_Interruptable_Type*) GPIO_PORT_TO_BASE[Port]), Pin);
        else
            GPIO_OUTPUT_HIGH(((DIO_PORT_Odd_Interruptable_Type*) GPIO_PORT_TO_BASE[Port]), Pin);
    }
}

/******************************************************************************
 * Function: gpio_output_high
 * Preconditions: None.
 * Overview: Pone a 1 el pin
 * Input: Puerto, Pin
 * Output: None.
 *
 *****************************************************************************/
void gpio_output_high(uint_fast8_t Port,uint_fast16_t Pin)
{
    gpio_outputBIT(Port,Pin,HIGH);
}
/******************************************************************************
 * Function: gpio_output_low
 * Preconditions: None.
 * Overview: Pone a 0 el pin
 * Input: Puerto, Pin
 * Output: None.
 *
 *****************************************************************************/
void gpio_output_low(uint_fast8_t Port,uint_fast16_t Pin)
{
    gpio_outputBIT(Port,Pin,LOW);
}

/*****************************************************************************
 * Function: gpio_input_state
 * Preconditions: None.
 * Overview: Retorna el valor de entrada para un bit de un puerto en específico.
 * Input: uint_fast8_t selectedPort, uint_fast16_t selectedPins.
 * Output: None.
 *
 *****************************************************************************/
uint8_t gpio_input_state(uint_fast8_t Port, uint_fast16_t Pin)
{
    uint_fast16_t inputPinValue;

    // Identifica el puerto seleccionado.
    uint32_t baseAddress = GPIO_PORT_TO_BASE[Port];

    // Lee el registro que indica el valor de entrada de un pin.
    inputPinValue = HWREG16(baseAddress + OFS_PAIN) & (Pin);

    // Retorna el valor.
    if (inputPinValue > 0)
        return GPIO_INPUT_PIN_HIGH;
    return GPIO_INPUT_PIN_LOW;
}

/*****************************************************************************
 * Function: gpio_enable_INT
 * Preconditions: None.
 * Overview: Habilita la interrupción para un pin de un puerto en específico.
 * Input: Port,Pin
 * Output: None.
 *
 *****************************************************************************/
void gpio_enable_INT(uint_fast8_t Port, uint_fast16_t Pin)
{
    // Identifica el puerto seleccionado.
    uint32_t baseAddress = GPIO_PORT_TO_BASE[Port];
    // Modifica el bit del registro correspondiente para habilitar la interrupción.
    HWREG16(baseAddress + OFS_PAIE) |= Pin;
}

/*****************************************************************************
 * Function: gpio_disabled_INT
 * Preconditions: None.
 * Overview: Deshabilita la interrupción para un pin de un puerto en específico.
 * Input: uint_fast8_t selectedPort, uint_fast16_t selectedPins.
 * Output: None.
 *
 *****************************************************************************/
void gpio_disabled_INT(uint_fast8_t Port, uint_fast16_t Pin)
{
    //Identifica el puerto seleccionado.
    uint32_t baseAddress = GPIO_PORT_TO_BASE[Port];
    //Modifica el bit del registro correspondiente para deshabilitar la interrupción.
    HWREG16(baseAddress + OFS_PAIE) &= ~Pin;
}

/*****************************************************************************
 * Function: gpio_clearBINT
 * Preconditions: None..
 * Overview: Limpia el bit que indica que hubo una interrupción en el bit del puerto específicado.
 * Input:  uint_fast8_t selectedPort, uint_fast16_t selectedPins.
 * Output: None.
 *
 *****************************************************************************/
void gpio_clearBINT(uint_fast8_t Port, uint_fast16_t Pin)
{
    // Identifica el puerto seleccionado.
    uint32_t baseAddress = GPIO_PORT_TO_BASE[Port];
    // Modifica el bit del registro correspondiente para limpiar la bandera de interrupcion.
    HWREG16(baseAddress + OFS_PAIFG) &= ~Pin;
}

/*****************************************************************************
 * Function: gpio_stateINT
 * Preconditions: GPIO_init().
 * Overview: Retorna el valor que indica el estado de la interrupción de un bit del puerto en específico.
 * Input: uint_fast8_t selectedPort, uint_fast16_t selectedPins.
 * Output: None.
 *
 *****************************************************************************/
uint_fast16_t gpio_stateINT(uint_fast8_t Port, uint_fast16_t Pin)
{
    // Identifica el puerto seleccionado.
    uint32_t baseAddress = GPIO_PORT_TO_BASE[Port];
    // Retorna el valor del registro que indica el estado de una interrupción.
    return HWREG16(baseAddress + OFS_PAIFG) & Pin;
}

/*****************************************************************************
 * Function: gpio_FlancoInt
 * Preconditions: None.
 * Overview: Selecciona el evento en que se dará la interrupción para un bit de un puerto en específico.
 * Input: uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t edgeSelect.
 * Output: None.
 *
 *****************************************************************************/
void gpio_FlancoInt(uint_fast8_t Port, uint_fast16_t Pin, uint_fast8_t edgeSelect)
{
    // Identifica el puerto seleccionado.
    uint32_t baseAddress = GPIO_PORT_TO_BASE[Port];

    // Modifica el bit del registro correspondiente para seleccionar el flanco que provoca la interrupción.
    if (GPIO_LOW_TO_HIGH == edgeSelect)
        HWREG16(baseAddress + OFS_PAIES) &= ~Pin;
    else
        HWREG16(baseAddress + OFS_PAIES) |= Pin;
}

/**********************************************************************************
 * Function: GPIO_setAsPeripheralModuleFunctionOutputPin
 * Preconditions: GPIO_init().
 * Overview: Especifica la función de salida de un bit de un puerto en específico.
 * Input: uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t mode.
 * Output: None.
 *
 **********************************************************************************/
void gpio_setAsPeripheralModuleFunctionOutputPin(uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t mode)
{
    // Identifica el puerto seleccionado.
    uint32_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    HWREG16(baseAddress + OFS_PADIR) |= selectedPins;
    switch (mode)
    {
    case GPIO_PRIMARY_MODULE_FUNCTION:
        HWREG16(baseAddress + OFS_PASEL0) |= selectedPins;
        HWREG16(baseAddress + OFS_PASEL1) &= ~selectedPins;
        break;
    case GPIO_SECONDARY_MODULE_FUNCTION:
        HWREG16(baseAddress + OFS_PASEL0) &= ~selectedPins;
        HWREG16(baseAddress + OFS_PASEL1) |= selectedPins;
        break;
    case GPIO_TERTIARY_MODULE_FUNCTION:
        HWREG16(baseAddress + OFS_PASEL0) |= selectedPins;
        HWREG16(baseAddress + OFS_PASEL1) |= selectedPins;
        break;
    }
}

/**********************************************************************************
 * Function: setAsPeripheralModuleFunctionInputPin
 * Preconditions: GPIO_init().
 * Overview: Especifica la función de entrada de un bit de un puerto en específico.
 * Input: uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t mode.
 * Output: None.
 *
 **********************************************************************************/
void gpio_setAsPeripheralModuleFunctionInputPin(uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t mode)
{
    // Identifica el puerto seleccionado.
    uint32_t baseAddress = GPIO_PORT_TO_BASE[selectedPort];

    HWREG16(baseAddress + OFS_PADIR) &= ~selectedPins;
    switch (mode)
    {
    case GPIO_PRIMARY_MODULE_FUNCTION:
        HWREG16(baseAddress + OFS_PASEL0) |= selectedPins;
        HWREG16(baseAddress + OFS_PASEL1) &= ~selectedPins;
        break;
    case GPIO_SECONDARY_MODULE_FUNCTION:
        HWREG16(baseAddress + OFS_PASEL0) &= ~selectedPins;
        HWREG16(baseAddress + OFS_PASEL1) |= selectedPins;
        break;
    case GPIO_TERTIARY_MODULE_FUNCTION:
        HWREG16(baseAddress + OFS_PASEL0) |= selectedPins;
        HWREG16(baseAddress + OFS_PASEL1) |= selectedPins;
        break;
    }
}
