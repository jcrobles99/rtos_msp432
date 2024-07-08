  // FileName:        ADC_MSP432.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP432P401R
 // Program version: CCS V8.3 TI
 // Driver version:  1.0
// Company:         Texas Instruments
 // Description:     Definici�n de funciones del m�dulo ADC.
 // Authors:         Jes�s Andr�s Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         10/2020


#ifndef ADC_MSP432_H_
#define ADC_MSP432_H_

enum Analog_pin
{
    AN0,  AN1,  AN2,  AN3,  AN4,  AN5,  AN6,  AN7,
    AN8,  AN9,  AN10, AN11, AN12, AN13, AN14, AN15,
    AN16, AN17, AN18, AN19, AN20, AN21, AN22, AN23,
    AN24, AN25, AN26, AN27, AN28, AN29, AN30, AN31, AN_MAX=23,
};

enum Channel
{
    CH0,  CH1,  CH2,  CH3,  CH4,  CH5,  CH6,  CH7,
    CH8,  CH9,  CH10, CH11, CH12, CH13, CH14, CH15,
    CH16, CH17, CH18, CH19, CH20, CH21, CH22, CH23,
    CH24, CH25, CH26, CH27, CH28, CH29, CH30, CH31, CH_MAX=31,
};

/* Definici�n de constantes para el m�dulo ADC. */

#define PreDiv1             ADC14_CTL0_PDIV__1
#define PreDiv4             ADC14_CTL0_PDIV__4
#define PreDiv32            ADC14_CTL0_PDIV__32
#define PreDiv64            ADC14_CTL0_PDIV__64

#define CLKDiv1             ADC14_CTL0_DIV__1
#define CLKDiv2             ADC14_CTL0_DIV__2
#define CLKDiv3             ADC14_CTL0_DIV__3
#define CLKDiv4             ADC14_CTL0_DIV__4
#define CLKDiv5             ADC14_CTL0_DIV__5
#define CLKDiv6             ADC14_CTL0_DIV__6
#define CLKDiv7             ADC14_CTL0_DIV__7
#define CLKDiv8             ADC14_CTL0_DIV__8

// Re-definiciones para resoluciones posibles.
#define Resolucion8bits              ADC14_CTL1_RES__8BIT
#define Resolucion10bits             ADC14_CTL1_RES__10BIT
#define Resolucion12bits             ADC14_CTL1_RES__12BIT
#define Resolucion14bits             ADC14_CTL1_RES__14BIT

// Re-definiciones para modos de conversion.
#define SingleChannel               ADC14_CTL0_CONSEQ_0
#define SequenceOfChannels          ADC14_CTL0_CONSEQ_1
#define SingleChannelRepeat         ADC14_CTL0_CONSEQ_2
#define SequenceOfChannelsRepeat    ADC14_CTL0_CONSEQ_3

// Re-definiciones para voltajes de referencia.
#define VCC_VSS                     ADC14_MCTLN_VRSEL_0
#define VREF_VSS                    ADC14_MCTLN_VRSEL_1
#define VeREF_VeREF                 ADC14_MCTLN_VRSEL_14
#define VeREFBuf_VeREF              ADC14_MCTLN_VRSEL_15

/* Valor m�ximo de la conversi�n ADC con una resoluci�n de 14 bits. */
#define MAX_VALUE 16383 // (2 ^14 bits)

/* Funci�n que inicializa el m�dulo, de ella dependen las dem�s. */
extern void ADC_init(void);
/* Funci�n que inicializa el m�dulo, de ella dependen las dem�s. */
extern void ADC_Inicializar(uint32_t RES, uint32_t CLK_div);
/* Funci�n que configura el modo de conversi�n del ADC. */
extern void ADC_Modo_Conversion(uint32_t ConvertionMode);
/* Funci�n que configura el canal final de secuencia de conversi�n. */
extern void ADC_Canal_Final(uint32_t CH);
/* Funci�n que configura el canal inicial de secuencia de conversi�n. */
extern void ADC_Canal_Inicial(uint32_t CH);
/* Funci�n que configura el canal de conversi�n. */
extern void ADC_ConversionSimple(uint32_t CH);
/* Funci�n que configura el pin analogo para un canal ADC. */
extern void ADC_Configura_Pin(uint32_t CH, uint32_t AN, uint32_t VRef);
/* Funci�n que retorna el valor del sensor de temperatura en Celsius. */
extern float ADC_Obtener_Temp(uint16_t CH);
/* Funci�n que dispara la conversi�n ADC. */
extern void ADC_Activar(void);
/* Funci�n que indica si hay una conversi�n en curso o no. */
extern bool ADC_Ocupado(void);
/* Funci�n que retorna el valor de la conversi�n ADC de un canal en espec�fico. */
extern uint16_t ADC_resultado(uint16_t channel);
/* Funci�n que habilita y configura el sensor de temperatura en un canal espec�fico. */
extern void ADC_Habilita_Temp_Sensor(uint32_t CH);

//Funciones creadas por nosotros
//--------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion que inicializa el m�dulo con una resolucion de 8 bits
extern void InicializarADC8(uint32_t CLK_div);
// Funcion que inicializa el m�dulo con una resolucion de 10 bits
void InicializarADC10(uint32_t CLK_div);
// Funcion que inicializa el m�dulo con una resolucion de 12 bits
void InicializarADC12(uint32_t CLK_div);
// Funcion que inicializa el m�dulo con una resolucion de 14 bits
extern void InicializarADC14(uint32_t CLK_div);
//Funci�n que configura el modo de conversion del m�dulo ADC
extern void ModoConversionADC(uint32_t ConvertionMode);
//Funci�n que configura el canal inicial y final del m�dulo ADC
extern void CanalesADC(uint32_t CH, uint32_t CH1);
//Funci�n que dispara la conversi�n ADC e indica si hay una conversi�n en curso o no
extern void DisparoADC(void);
//Funci�n para obtener el valor de la conversi�n ADC de un canal
extern uint16_t ResultadoADC(uint16_t channel);

#endif /* ADC_MSP432_H_ */
