 // FileName:        Control.c
 // Dependencies:    system.h
 // Processor:       MSP432
 // Board:           MSP43P401R
 // Program Version: CCS V8.3 TI
 // Company:         Texas Instruments
 // Description:     Archivo que controla el control no plus
 // Authors:         Jesús Andrés Lara Acevedo y Juan Carlos Robles Ortega
 // Updated:         04/12/2020

#include "system.h"

/*Variables utilizadas en el programa*/
 float temperatura;
 int E1=0, S1=0, door=0, select=0, x=0, sistema=0, personas=0, iteracion_imp=0;
 char juan[10]={'0'};
 char robles[10]={};
 char lara[10]={};
 char jesus[10]={"--\n\r\n\r"};

/*FUNCTION******************************************************************************
*
* Function Name    : INT_1
* Returned Value   : None.
* Comments         : Función utilizada cuando ocurre una interrupción en el puerto 5. En
*                    este caso es para mostrar que una persona ha ingresado al establecimiento
*
*END***********************************************************************************/
void INT_1()
{
    GPIO_WIPE_INT_BAND(P5,B1);
    E1=1;
}

/*FUNCTION******************************************************************************
*
* Function Name    : INT_2
* Returned Value   : None.
* Comments         : Funcion utilizada cuando ocurre una interrupcion en el puerto 3. En
*                    este caso para mostrar que una persona ha salido del establecimiento
*
*END***********************************************************************************/
void INT_2 ()
{
    GPIO_WIPE_INT_BAND(P3,B5);
    if(personas>0)
    {
    personas--;
    sprintf(juan, "%d",personas);
    }
}

/*FUNCTION******************************************************************************
*
* Function Name    : INT_1
* Returned Value   : None.
* Comments         : Funcion utilizada cuando ocurre una interrupcion en el puerto 6. En
*                    este caso para activar o desactivar el sistema
*END***********************************************************************************/
void INT_3 ()
{
    GPIO_WIPE_INT_BAND(P6,B7);
    if(sistema==0)
    {
        sistema=1;
        GPIO_OUTPUT_HIGH(P5,B0);
        GPIO_OUTPUT_LOW(P5,B2);
    }
    else
    {
        sistema=0;
        GPIO_OUTPUT_HIGH(P5,B2);
        GPIO_OUTPUT_LOW(P5,B0);
    }

}

/*FUNCTION******************************************************************************
*
* Function Name    : Checar_entradas
* Returned Value   : None.
* Comments         : Función utilizada para hacer el control de entradas al establecimiento
*END***********************************************************************************/
void Checar_entradas(void)
{
    if(personas<cupo)
    {
        if(E1==1)
        {
            temperatura=Temperatura();
            if(temperatura<37)
            {
                personas++;
                door=1;
                Tiempo_ms(5000);
                sprintf(juan, "%d",personas);
            }
            else
            {
                select=0;
            }
            E1=0;
        }
        sprintf(jesus, "%.01f\n\r\n\r",temperatura);
    }
    else
    {
        sprintf(juan, " LLENO ");
    }
}

/*FUNCTION******************************************************************************
*
* Function Name    : Temperatura
* Returned Value   : temp1
* Comments         : Función utilizada para checar la temperatura corporal
*END***********************************************************************************/
float Temperatura()
{
    uint32_t temp1=0;
    DisparoADC();
    temp1=(ResultadoADC(2)*10/16380)+30;
    return temp1;
}
