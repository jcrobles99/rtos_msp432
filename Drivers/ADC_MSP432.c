 // FileName:        ADC_MSP432.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP432P401R
 // Program version: CCS V8.3 TI
 // Driver version:  1.0
// Company:         Texas Instruments
 // Description:     Definición de funciones del módulo ADC.
 // Authors:         Jesús Andrés Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         10/2020

#include "system.h"     // Configuración del sistema.


void ADC_init()
{
    //Utiliza el registro ADC14CTL0 para activar el modulo
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ON_OFS) = 1;

    //Aqui se configura el reloj, el preescaler y la division
    ADC14 -> CTL0 |= ADC14_CTL0_DIV__8 | ADC14_CTL0_SHT1__64 | ADC14_CTL0_SHT0__64;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SHP_OFS) = 1;

    //Aqui configuramos el modo en el que va a trabajar el conversor mediante el mismo registro ADC14CTL0
    ADC14 -> CTL0 |= ADC14_CTL0_CONSEQ_1;

    //Asigna la resolución de 14bits.
    ADC14 -> CTL1 = ADC14_CTL1_RES__14BIT ;

    //Se asigna un pin para cada canal a utilizar.
    ADC14 -> MCTL[0] = ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_0;
    ADC14 -> MCTL[1] = ADC14_MCTLN_VRSEL_0 | ADC14_MCTLN_INCH_1;

    /* Configura el CH1 como el canal final de la secuencia de conversión.
     * Es decir, cada que se dispare el módulo ADC, se llevará a cabo la
     * conversión para los canales CH0 hasta el CH1.                    */
    BITBAND_PERI(ADC14->MCTL[1], ADC14_MCTLN_EOS_OFS) = 1;

    gpio_setAsPeripheralModuleFunctionOutputPin(5, BIT4, 1);    // Establece como pin análogo.
    gpio_setAsPeripheralModuleFunctionOutputPin(5, BIT5, 1);    // Establece como pin análogo.

}

/*****************************************************************************
 * Function: ADC_Inicializar
 * Preconditions: None.
 * Overview: Inicialización y configuración del módulo para su uso posterior.
 *           Incluye la configuración de reloj y resolución.
 * Input: Parámetros de configuración de reloj y resolución.
 * Output: None.
 *
 *****************************************************************************/
void ADC_Inicializar(uint32_t RES, uint32_t CLK_div)
{
    //Utiliza el registro ADC14CTL0 para activar el modulo.
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ON_OFS) = 1;

    //Aqui se configura el reloj, el preescaler y la division
    ADC14 -> CTL0 |= CLK_div | ADC14_CTL0_SHT1__64 | ADC14_CTL0_SHT0__192;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SHP_OFS) = 1;

    // Aqui, con el registro ADC14CTL1 configuramos la resolucion a la que va a trabajar el conversor
    ADC14 -> CTL1 = RES ;
}

/*****************************************************************************
 * Function: ADC_Modo_Conversion
 * Preconditions: ADC_Initialize().
 * Overview: Configura el modo de conversión del ADC.
 * Input: uint32_t ConvertionMode.
 * Output: None.
 *
 *****************************************************************************/

void ADC_Modo_Conversion(uint32_t ConvertionMode)
{
    //Aqui configuramos  cual va a ser el modo de conversion mediante el registro ADC14CTL0
    ADC14 -> CTL0 |= ConvertionMode;
}

/*****************************************************************************
 * Function: ADC_Canal_Final
 * Preconditions: ADC_Initialize().
 * Overview: Configura el canal final de una secuencia de conversión del ADC.
 * Input: uint32_t CH.
 * Output: None.
 *
 *****************************************************************************/
void ADC_Canal_Final(uint32_t CH)
{
    //  Aqui elegimos cual es la direccion final del canal para el uso de modo secuencia
    BITBAND_PERI(ADC14->MCTL[CH], ADC14_MCTLN_EOS_OFS) = 1;
}

/*****************************************************************************
 * Function: ADC_Canal_Inicial
 * Preconditions: ADC_Initialize().
 * Overview: Configura el canal inicial de una secuencia de conversión del ADC.
 * Input: uint32_t CH.
 * Output: None.
 *
 *****************************************************************************/
void ADC_Canal_Inicial(uint32_t CH)
{
    //Caso contrario, este serpa la direccion inicial del canal para el uso de modo secuencia
    ADC14->CTL1 |= (CH<<ADC14_CTL1_CSTARTADD_OFS);
}

/*****************************************************************************
 * Function: ADC_Conversion_Simple
 * Preconditions: ADC_Initialize().
 * Overview: Configura el canal de una conversión simple del ADC.
 * Input: uint32_t CH.
 * Output: None.
 *
 *****************************************************************************/
void ADC_ConversionSimple(uint32_t CH)
{
    //Cuando utilizamos el modo de conversion simple, utilizamos solo una direccion de canal, la que será la inicial y la final y esto lo hacemos con el registro ADC14CTL1
    ADC14->CTL1 |= (CH<<ADC14_CTL1_CSTARTADD_OFS);
}

/*****************************************************************************
 * Function: ADC_Configura_Pin
 * Preconditions: ADC_Initialize().
 * Overview: Configura el pin análogo para un canal ADC.
 * Input: uint32_t CH, uint32_t.
 * Output: None.
 *
 *****************************************************************************/
void ADC_Configura_Pin(uint32_t CH, uint32_t AN, uint32_t VRef)
{
    //Aqui se configura el pin analogo por donde tendremos la entrada del voltaje
    ADC14 -> MCTL[CH] = VRef | AN;
}

/*****************************************************************************
 * Function: ADC_Temp_Sensor
 * Preconditions: ADC_Initialize().
 * Overview: Habilita el sensor de temperatura interno.
 * Input: uint32_t CH.
 * Output: None.
 *
 *****************************************************************************/
void ADC_Habilita_Temp_Sensor(uint32_t CH)
{
    // Configura lo necesario del módulo REF_A (v(R+)=2.5V).
    REF_A->CTL0|=REF_A_CTL0_VSEL_3;
    BITBAND_PERI(REF_A->CTL0 , REF_A_CTL0_ON_OFS) = 1;
    BITBAND_PERI(REF_A->CTL0 , REF_A_CTL0_TCOFF_OFS) = 0;
    // Habilita el sensor de temperatura.
    BITBAND_PERI(ADC14 -> CTL1, ADC14_CTL1_TCMAP_OFS) = 1;
    ADC_Configura_Pin(CH, (AN_MAX-1), VREF_VSS);
}
/*****************************************************************************
 * Function: ADC_Obtener_Temp
 * Preconditions: ADC_Initialize().
 * Overview: Obtiene la temperatura actual de acuerdo a constantes
 *           y el valor del canal.
 * Input: uint32_t CH.
 * Output: uint32_t valor en Celsius.
 *
 *****************************************************************************/
float ADC_Obtener_Temp(uint16_t CH)
{
    float   temp = 0.0;
    uint16_t cal30 = TLV->ADC14_REF2P5V_TS30C;
    uint16_t cal85 = TLV->ADC14_REF2P5V_TS85C;
    float calDiff = cal85 - cal30;
    ADC_Activar(); while(ADC_Ocupado());
    temp =  ((((ADC_resultado(CH) - cal30) * 55) / calDiff) + 30.0f);
    return temp;
}

/*****************************************************************************
 * Function: ADC_Activar
 * Preconditions: ADC_init().
 * Overview: Se inicia la conversión ADC.
 * Input: None.
 * Output: None.
 *
 *****************************************************************************/
void ADC_Activar(void)
{
    // Funcion bandera que activa la conversion y pone en alto la bandera de ocupado
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 1;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SC_OFS) = 1;
}

/*****************************************************************************
 * Function: ADC_Ocupado
 * Preconditions: ADC_init().
 * Overview: Indica si hay una conversión en curso o no.
 * Input: None.
 * Output: Valor booleano.
 *
 *****************************************************************************/
bool ADC_Ocupado(void)
{
    /*BAndera de ocupado, la cual se activa mientras se está realizando una conversion
     * (0) si no se está llevando a cabo una conversión.
     * (1) si hay una conversión en curso.               */
    return BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_BUSY_OFS);
}

/*****************************************************************************
 * Function: ADC_resultado
 * Preconditions: ADC_init().
 * Overview: Retorna el valor de la conversión ADC para el canal "channel" dado.
 * Input: uint16_t channel.
 * Output: uint16_t con el valor de la conversión del canal "channel".
 *
 *****************************************************************************/
uint16_t ADC_resultado(uint16_t channel)
{
    /* Retorna el valor de la conversión ADC para el canal "channel" dado.
     * Los valores de las conversiones se almancenan en el arreglo MEM       */
    return ADC14->MEM[channel];
}





//------------------------------------------------------------------------------------------------------------------------------------------------------
/*****************************************************************************
 * Function: InicializarADC8
 * Preconditions: None.
 * Overview: Inicialización y configuración del módulo para su uso posterior.
 *           Incluye la configuración de reloj y resolución en 8 bits.
 * Input: Parámetros de configuración de reloj.
 * Output: None.
 *
 *****************************************************************************/
void InicializarADC8(uint32_t CLK_div)
{
    //Utiliza el registro ADC14CTL0 para activar el modulo.
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ON_OFS) = 1;

    //Aqui se configura el reloj, el preescaler y la division
    ADC14 -> CTL0 |= CLK_div | ADC14_CTL0_SHT1__64 | ADC14_CTL0_SHT0__192;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SHP_OFS) = 1;

    // Aqui, con el registro ADC14CTL1 configuramos la resolucion a la que va a trabajar el conversor
    ADC14 -> CTL1 = ADC14_CTL1_RES__8BIT;
}

/*****************************************************************************
 * Function: InicializarADC10
 * Preconditions: None.
 * Overview: Inicialización y configuración del módulo para su uso posterior.
 *           Incluye la configuración de reloj y resolución en 10 bits.
 * Input: Parámetros de configuración de reloj.
 * Output: None.
 *
 *****************************************************************************/
void InicializarADC10(uint32_t CLK_div)
{
    //Utiliza el registro ADC14CTL0 para activar el modulo.
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ON_OFS) = 1;

    //Aqui se configura el reloj, el preescaler y la division
    ADC14 -> CTL0 |= CLK_div | ADC14_CTL0_SHT1__64 | ADC14_CTL0_SHT0__192;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SHP_OFS) = 1;

    // Aqui, con el registro ADC14CTL1 configuramos la resolucion a la que va a trabajar el conversor
    ADC14 -> CTL1 = ADC14_CTL1_RES__10BIT;
}

/*****************************************************************************
 * Function: InicializarADC12
 * Preconditions: None.
 * Overview: Inicialización y configuración del módulo para su uso posterior.
 *           Incluye la configuración de reloj y resolución en 12 bits.
 * Input: Parámetros de configuración de reloj.
 * Output: None.
 *
 *****************************************************************************/
void InicializarADC12(uint32_t CLK_div)
{
    //Utiliza el registro ADC14CTL0 para activar el modulo.
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ON_OFS) = 1;

    //Aqui se configura el reloj, el preescaler y la division
    ADC14 -> CTL0 |= CLK_div | ADC14_CTL0_SHT1__64 | ADC14_CTL0_SHT0__192;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SHP_OFS) = 1;

    // Aqui, con el registro ADC14CTL1 configuramos la resolucion a la que va a trabajar el conversor
    ADC14 -> CTL1 = ADC14_CTL1_RES__12BIT;
}

/*****************************************************************************
 * Function: InicializarADC14
 * Preconditions: None.
 * Overview: Inicialización y configuración del módulo para su uso posterior.
 *           Incluye la configuración de reloj y resolución en 14 bits.
 * Input: Parámetros de configuración de reloj.
 * Output: None.
 *
 *****************************************************************************/
void InicializarADC14(uint32_t CLK_div)
{
    //Utiliza el registro ADC14CTL0 para activar el modulo.
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ON_OFS) = 1;

    //Aqui se configura el reloj, el preescaler y la division
    ADC14 -> CTL0 |= CLK_div | ADC14_CTL0_SHT1__64 | ADC14_CTL0_SHT0__192;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SHP_OFS) = 1;

    // Aqui, con el registro ADC14CTL1 configuramos la resolucion a la que va a trabajar el conversor
    ADC14 -> CTL1 = ADC14_CTL1_RES__14BIT;
}

/*****************************************************************************
 * Function: ModoConversionADC
 * Preconditions: InicilizarADCx().
 * Overview: Configura el modo de conversión del ADC.
 * Input: uint32_t ConvertionMode.
 * Output: None.
 *
 *****************************************************************************/
void ModoConversionADC(uint32_t ConvertionMode)
{
    //Aqui configuramos  cual va a ser el modo de conversion mediante el registro ADC14CTL0
    ADC14 -> CTL0 |= ConvertionMode;
}

/*****************************************************************************
 * Function: CanalesADC
 * Preconditions: InicializarADCx().
 * Overview: Configura el canal inicial y final de una secuencia de conversión del ADC.
 * Input: uint32_t CH.
 * Output: None.
 *
 *****************************************************************************/
void CanalesADC(uint32_t CH, uint32_t CH1)
{
    //Caso contrario, este serpa la direccion inicial del canal para el uso de modo secuencia
    ADC14->CTL1 |= (CH<<ADC14_CTL1_CSTARTADD_OFS);
    //  Aqui elegimos cual es la direccion final del canal para el uso de modo secuencia
    BITBAND_PERI(ADC14->MCTL[CH1], ADC14_MCTLN_EOS_OFS) = 1;
}

/*****************************************************************************
 * Function: DisparoADC
 * Preconditions: InicializarADCx().
 * Overview: Se inicia la conversión ADC y se cicla en un while hasta que la termine.
 * Input: None.
 * Output: None.
 *
 *****************************************************************************/
void DisparoADC(void)
{
    // Funcion bandera que activa la conversion y pone en alto la bandera de ocupado
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_ENC_OFS) = 1;
    BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_SC_OFS) = 1;
    /*BAndera de ocupado, la cual se activa mientras se está realizando una conversion
     * (0) si no se está llevando a cabo una conversión.
     * (1) si hay una conversión en curso.               */
      while(BITBAND_PERI(ADC14->CTL0, ADC14_CTL0_BUSY_OFS));
}

/*****************************************************************************
 * Function: ResultadoADC
 * Preconditions: InicializarADCx().
 * Overview: Retorna el valor de la conversión ADC para el canal "channel" dado.
 * Input: uint16_t channel.
 * Output: uint16_t con el valor de la conversión del canal "channel".
 *
 *****************************************************************************/
uint16_t ResultadoADC(uint16_t channel)
{
    return ADC14->MEM[channel];
}
