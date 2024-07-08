 // FileName:        Control_Plus.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Archivo que controla el control plus
 // Authors:         Jesús Andrés Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         04/12/2020

#include "system.h"

#if defined(CONTROL_PLUS)

/* Variables sobre las cuales se maneja el sistema. */
float TemperaturaActual=0;       // Temperatura.
float SetPoint = 25.0;         // Valor deseado.

char state[MAX_MSG_SIZE];      // Cadena a imprimir.

bool toggle = 0;               // Toggle para el heartbeat.
bool event = FALSE;            // Evento I/O que fuerza impresión inmediata.

bool FAN_LED_State = 0;                                     // Estado led_FAN.
const char* SysSTR[] = {"Cool","Off","Heat","Only Fan"};    // Control de los estados.

/**********************************************************************************
 * Function: INT_SWI
 * Preconditions: Interrupción habilitada, registrada e inicialización de módulos.
 * Overview: Función que es llamada cuando se genera
 *           la interrupción del botón SW1 o SW2.
 * Input: None.
 * Output: None.
 **********************************************************************************/
void INT_SWI(void)
{
    GPIO_WIPE_INT_BAND(P1,B1); // Limpia la bandera de la interrupción.
    GPIO_WIPE_INT_BAND(P1,B4); // Limpia la bandera de la interrupción.

    if(!gpio_input_state(SETPOINT_PORT,BIT(SP_UP)))        // Si se trata del botón para aumentar setpoint (SW1).
        HVAC_SetPointUp();
    else if(!gpio_input_state(SETPOINT_PORT,BIT(SP_DOWN))) // Si se trata del botón para disminuir setpoint (SW2).
        HVAC_SetPointDown();

    return;
}

/*FUNCTION******************************************************************************
*
* Function Name    : HVAC_ActualizarEntradas
* Returned Value   : None.
* Comments         :
*    Actualiza los variables indicadores de las entradas sobre las cuales surgirán
*    las salidas.
*
*END***********************************************************************************/
void HVAC_ActualizarEntradas(void)
{
    static bool ultimos_estados[] = {FALSE, FALSE, FALSE, FALSE, FALSE};

    TemperaturaActual = ADC_Obtener_Temp(CH0);                                // Averigua temperatura actual.

    if(gpio_input_state(FAN_PORT,BIT(FAN_ON)) != NORMAL_STATE_EXTRA_BUTTONS)   // Observa entradas.
    {
        EstadoEntradas.FanState = On;
        EstadoEntradas.SystemState = FanOnly;

        if(ultimos_estados[0] == FALSE)
            event = TRUE;

        ultimos_estados[0] = TRUE;
        ultimos_estados[1] = FALSE;
    }

    else if(gpio_input_state(FAN_PORT,BIT(FAN_AUTO)) != NORMAL_STATE_EXTRA_BUTTONS)    // No hay default para
    {                                                                                       // cuando no se detecta
        EstadoEntradas.FanState = Auto;                                                     // ninguna entrada activa.
        if(ultimos_estados[1] == FALSE)
            event = TRUE;

        ultimos_estados[1] = TRUE;
        ultimos_estados[0] = FALSE;

        if(gpio_input_state(SYSTEM_PORT,BIT(SYSTEM_COOL)))                             // Sistema en COOL.
        {
            EstadoEntradas.SystemState = Cool;
            if(ultimos_estados[2] == FALSE)
                event = TRUE;
            ultimos_estados[2] = TRUE;
            ultimos_estados[3] = FALSE;
            ultimos_estados[4] = FALSE;
        }
        else if(gpio_input_state(SYSTEM_PORT,BIT(SYSTEM_OFF)))                         // Sistema apagado.
        {
            EstadoEntradas.SystemState = Off;
            if(ultimos_estados[3] == FALSE)
                event = TRUE;
            ultimos_estados[2] = FALSE;
            ultimos_estados[3] = TRUE;
            ultimos_estados[4] = FALSE;
        }
        else if(gpio_input_state(SYSTEM_PORT,BIT(SYSTEM_HEAT)))                        // Sistema en HEAT.
        {
            EstadoEntradas.SystemState = Heat;
            if(ultimos_estados[4] == FALSE)
                event = TRUE;
            ultimos_estados[2] = FALSE;
            ultimos_estados[3] = FALSE;
            ultimos_estados[4] = TRUE;
        }
        else
        {
            EstadoEntradas.SystemState = Off;
            ultimos_estados[2] = FALSE;
            ultimos_estados[3] = FALSE;
            ultimos_estados[4] = FALSE;
        }                                                           // Este es solo un default en el caso de que
    }                                                               // el sistema no encuentre ningun estado de los 3
}                                                                   // activo (deberia ser un error debido a que debe
                                                                    // haber solo un botón activado siempre).

/*FUNCTION******************************************************************************
*
* Function Name    : HVAC_ActualizarSalidas
* Returned Value   : None.
* Comments         :
*    Decide a partir de las entradas actualizadas las salidas principales,
*    y en ciertos casos, en base a una cuestión de temperatura, la salida del 'fan'.
*
*END***********************************************************************************/
void HVAC_ActualizarSalidas(void)
{
    // Cambia el valor de las salidas de acuerdo a entradas.

    if(EstadoEntradas.FanState == On)
    {
        FAN_LED_State = 1;
        gpio_outputBIT(FAN_LED_PORT,  FAN_LED,  1);
        gpio_outputBIT(HEAT_LED_PORT, HEAT_LED, 0);
        gpio_outputBIT(COOL_LED_PORT, COOL_LED, 0);
    }

    else if(EstadoEntradas.FanState == Auto)
    {
        switch(EstadoEntradas.SystemState)
        {
        case Off:   gpio_outputBIT(FAN_LED_PORT,  FAN_LED,  0);
                    gpio_outputBIT(HEAT_LED_PORT, HEAT_LED, 0);
                    gpio_outputBIT(COOL_LED_PORT, COOL_LED, 0);
                    FAN_LED_State = 0;
                    break;
        case Heat:  HVAC_Heat(); break;
        case Cool:  HVAC_Cool(); break;
        }
    }
}

/*FUNCTION******************************************************************************
*
* Function Name    : HVAC_Heat
* Returned Value   : None.
* Comments         :
*    Decide a partir de la temperatura actual y la deseada, si se debe activar el fan.
*    (La temperatura deseada debe ser mayor a la actual). El estado del fan debe estar
*    en 'auto' y este modo debe estar activado para entrar a la función.
*
*END***********************************************************************************/
void HVAC_Heat(void)
{
    gpio_outputBIT(HEAT_LED_PORT, HEAT_LED, 1);
    gpio_outputBIT(COOL_LED_PORT, COOL_LED, 0);

    if(TemperaturaActual < SetPoint)                    // El fan se debe encender si se quiere una temp. más alta.
    {
        gpio_outputBIT(FAN_LED_PORT,  FAN_LED,  1);
        FAN_LED_State = 1;
    }
    else
    {
        gpio_outputBIT(FAN_LED_PORT,  FAN_LED,  0);
        FAN_LED_State = 0;
    }
}

/*FUNCTION******************************************************************************
*
* Function Name    : HVAC_Cool
* Returned Value   : None.
* Comments         :
*    Decide a partir de la temperatura actual y la deseada, si se debe activar el fan.
*    (La temperatura deseada debe ser menor a la actual). El estado del fan debe estar
*    en 'auto' y este modo debe estar activado para entrar a la función.
*
*END***********************************************************************************/
void HVAC_Cool(void)
{
    TemperaturaActual = ADC_Obtener_Temp(CH0);
    gpio_outputBIT(HEAT_LED_PORT, HEAT_LED, 0);
    gpio_outputBIT(COOL_LED_PORT, COOL_LED, 1);

    if(TemperaturaActual > SetPoint)                    // El fan se debe encender si se quiere una temp. más baja.
    {
        gpio_outputBIT(FAN_LED_PORT,  FAN_LED,  1);
        FAN_LED_State = 1;
    }
    else
    {
        gpio_outputBIT(FAN_LED_PORT,  FAN_LED,  0);
        FAN_LED_State = 0;
    }

}

/*FUNCTION******************************************************************************
*
* Function Name    : HVAC_SetPointUp
* Returned Value   : None.
* Comments         :
*    Sube el valor deseado (set point). Llamado por interrupción a causa del SW1.
*
*END***********************************************************************************/
void HVAC_SetPointUp(void)
{
    SetPoint += 0.5;
    event = TRUE;
}

/*FUNCTION******************************************************************************
*
* Function Name    : HVAC_SetPointDown
* Returned Value   : None.
* Comments         :
*    Baja el valor deseado (set point). Llamado por interrupción a causa del SW2.
*
*END***********************************************************************************/
void HVAC_SetPointDown(void)
{
    SetPoint -= 0.5;
    event = TRUE;
}
#endif
