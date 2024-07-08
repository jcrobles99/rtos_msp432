 // FileName:        GPIO_MSP432.h
 // Dependencies:    None.
 // Processor:       MSP432
 // Board:           MSP432P401R
 // Program version: CCS V8.3 TI
 // Driver version:  1.1
 // Company:         Texas Instruments
 // Description:     Descripci�n general de constantes, macros y configuraciones del m�dulo GPIO.
 // Authors:         Juan Carlos Robles Ortega y Jes�s Andr�s Lara Acevedo.
 // Updated:         09/2020

#ifndef GPIO_MSP432_H_
#define GPIO_MSP432_H_

#define GPIO_HIGH_TO_LOW                                                 (0x01)
#define GPIO_LOW_TO_HIGH                                                 (0x00)

#define GPIO_INPUT_PIN_HIGH                                              (0x01)
#define GPIO_INPUT_PIN_LOW                                               (0x00)

#define GPIO_PRIMARY_MODULE_FUNCTION                                     (0x01)
#define GPIO_SECONDARY_MODULE_FUNCTION                                   (0x02)
#define GPIO_TERTIARY_MODULE_FUNCTION                                    (0x03)

// Bits.
#define B0    0
#define B1    1
#define B2    2
#define B3    3
#define B4    4
#define B5    5
#define B6    6
#define B7    7

// Definiciones I/O.
#define SET_OUTPUT  1
#define SET_INPUT   0
#define PULLUP_EN   1
#define PULLUP_DIS  0
#define HIGH        1
#define LOW         0
#define INT_EN      1
#define INT_DIS     0

/* Configurar un pin como entrada o salida. */
#define GPIO_CONFIG_OUTPUT(P,B)         (BITBAND_PERI(P->DIR, B) = SET_OUTPUT) //Configura el puerto como salida (escritura)
#define GPIO_CONFIG_INPUT(P,B)          (BITBAND_PERI(P->DIR, B) = SET_INPUT) //Configura el puerto como entrada (lectura)

/* Habilitar o deshabilitar resistencias de pullup en un pin de un puerto en espec�fico. */
#define GPIO_PULLUP_ENABLE(P,B)         (BITBAND_PERI(P->REN, B) = PULLUP_EN) //Resistencias PullUp habilitadas
#define GPIO_PULLUP_DISABLED(P,B)       (BITBAND_PERI(P->REN, B) = PULLUP_DIS)//Resitencias PullUp deshabilitadas

/* Cambiar estado de un pin de salida. */
#define GPIO_OUTPUT_HIGH(P,B)           (BITBAND_PERI(P->OUT, B) = HIGH) //Pone en alto el bit del puerto (escritura)
#define GPIO_OUTPUT_LOW(P,B)            (BITBAND_PERI(P->OUT, B) = LOW)  //Pone en bajo el bit del puerto (escritura)

/* Lectura de un pin. */
#define GPIO_INPUT_STATE(P,B)           (BITBAND_PERI(P->IN, B)) //Lee el estado del bit en el puerto

/* Habilitar o deshabilitar interrupci�n en un pin. */
#define GPIO_ENABLE_INT(P,B)            (BITBAND_PERI(P->IE, B) = INT_EN)
#define GPIO_DISABLED_INT(P,B)          (BITBAND_PERI(P->IE, B) = INT_DIS)

/* Limpiar una bandera de interrupci�n. */
#define GPIO_WIPE_INT_BAND(P,B)         (BITBAND_PERI(P->IFG, B) = LOW)


/* Funcion que marca un pin de un puerto como entrada o como salida. */
extern void gpio_configIO(uint_fast8_t Port, uint_fast16_t Pin, bool I_O);
/* Funci�n que establece un valor en un pin de salida. */
extern void gpio_outputBIT(uint_fast8_t Port, uint_fast16_t Pin, bool state);
/* Funci�n que inicializa el m�dulo GPIO. */
extern void gpio_init(void);
/* Funci�n para poner a 1 el pin */
extern void gpio_output_high(uint_fast8_t Port,uint_fast16_t Pin);
/* Funci�n para poner a 0 el pin */
extern void gpio_output_low(uint_fast8_t Port,uint_fast16_t Pin);
/* Funci�n que retorna el valor de entrada de un pin. */
extern uint8_t gpio_input_state(uint_fast8_t Port, uint_fast16_t Pin);
/* Funci�n que habilita una interrupci�n de GPIO. */
extern void gpio_enable_INT(uint_fast8_t Port, uint_fast16_t Pin);
/* Funci�n que deshabilita una interrupci�n de GPIO. */
extern void gpio_disabled_INT(uint_fast8_t Port, uint_fast16_t Pin);
/* Funci�n que limpia una bandera de interrupci�n de GPIO. */
extern void gpio_clearBINT(uint_fast8_t Port, uint_fast16_t Pin);
/* Funci�n que retorna el estado de una interrupci�n de GPIO. */
extern uint_fast16_t gpio_stateINT(uint_fast8_t Port, uint_fast16_t Pin);
/* Funci�n para seleccionar el tipo de flanco que provoca la interrupci�n de GPIO. */
extern void gpio_FlancoInt(uint_fast8_t Port, uint_fast16_t Pin, uint_fast8_t edgeSelect);
/* Funci�n para configurar la funci�n de salida de un pin. */
extern void gpio_setAsPeripheralModuleFunctionOutputPin(uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t mode);
/* Funci�n para configurar la funci�n de entrada de un pin. */
extern void gpio_setAsPeripheralModuleFunctionInputPin(uint_fast8_t selectedPort, uint_fast16_t selectedPins, uint_fast8_t mode);

#endif /* GPIO_MSP432_H_ */
