 //FileName:        system_msp432p401r.c
 //Dependencies:    system.h
 //Processor:       MSP432
 //Board:           MSP432P401R
 //Compiler:        CCS V8.3 TI
 //Company:         Texas Instruments
 //Description:     Definición del sistema como constantes, configuraciones, etc.


/*--------------------- Configuration Instructions ----------------------------
   1. If you prefer to halt the Watchdog Timer, set __HALT_WDT to 1:
   #define __HALT_WDT       1
   2. Insert your desired CPU frequency in Hz at:
   #define __SYSTEM_CLOCK   12000000
   3. If you prefer the DC-DC power regulator (more efficient at higher
       frequencies), set the __REGULATOR to 1:
   #define __REGULATOR      1
 *---------------------------------------------------------------------------*/

/*--------------------- Watchdog Timer Configuration ------------------------*/
//  Halt the Watchdog Timer
//     <0> Do not halt the WDT
//     <1> Halt the WDT

#include "system.h"


#define __HALT_WDT         1

/*--------------------- CPU Frequency Configuration -------------------------*/
//  CPU Frequency
//     <1500000> 1.5 MHz
//     <3000000> 3 MHz
//     <12000000> 12 MHz
//     <24000000> 24 MHz
//     <48000000> 48 MHz
#ifndef __SYSTEM_CLOCK
#define __SYSTEM_CLOCK 48000000
#endif

/*--------------------- Power Regulator Configuration -----------------------*/
//  Power Regulator Mode
//     <0> LDO
//     <1> DC-DC
#define __REGULATOR        0

/*----------------------------------------------------------------------------
   Define clocks, used for SystemCoreClockUpdate()
 *---------------------------------------------------------------------------*/
#define __VLOCLK           10000
#define __MODCLK           24000000
#define __LFXT             32768
#define __HFXT             48000000

/*----------------------------------------------------------------------------
   Clock Variable definitions
 *---------------------------------------------------------------------------*/
uint32_t SystemCoreClock = __SYSTEM_CLOCK;  /*!< System Clock Frequency (Core Clock)*/

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */


void Power_idleFunc(void)
{

}


void SystemCoreClockUpdate(void)
{
    uint32_t source = 0, divider = 0, dividerValue = 0, centeredFreq = 0, calVal = 0;
    int16_t dcoTune = 0;
    float dcoConst = 0.0;

    divider = (CS->CTL1 & CS_CTL1_DIVM_MASK) >> CS_CTL1_DIVM_OFS;
    dividerValue = 1 << divider;
    source = CS->CTL1 & CS_CTL1_SELM_MASK;

    switch(source)
    {
    case CS_CTL1_SELM__LFXTCLK:
        if(BITBAND_PERI(CS->IFG, CS_IFG_LFXTIFG_OFS))
        {
            // Clear interrupt flag
            CS->KEY = CS_KEY_VAL;
            CS->CLRIFG |= CS_CLRIFG_CLR_LFXTIFG;
            CS->KEY = 1;

            if(BITBAND_PERI(CS->IFG, CS_IFG_LFXTIFG_OFS))
            {
                if(BITBAND_PERI(CS->CLKEN, CS_CLKEN_REFOFSEL_OFS))
                {
                    SystemCoreClock = (128000 / dividerValue);
                }
                else
                {
                    SystemCoreClock = (32000 / dividerValue);
                }
            }
            else
            {
                SystemCoreClock = __LFXT / dividerValue;
            }
        }
        else
        {
            SystemCoreClock = __LFXT / dividerValue;
        }
        break;
    case CS_CTL1_SELM__VLOCLK:
        SystemCoreClock = __VLOCLK / dividerValue;
        break;
    case CS_CTL1_SELM__REFOCLK:
        if (BITBAND_PERI(CS->CLKEN, CS_CLKEN_REFOFSEL_OFS))
        {
            SystemCoreClock = (128000 / dividerValue);
        }
        else
        {
            SystemCoreClock = (32000 / dividerValue);
        }
        break;
    case CS_CTL1_SELM__DCOCLK:
        dcoTune = (CS->CTL0 & CS_CTL0_DCOTUNE_MASK) >> CS_CTL0_DCOTUNE_OFS;
    
        switch(CS->CTL0 & CS_CTL0_DCORSEL_MASK)
        {
        case CS_CTL0_DCORSEL_0:
            centeredFreq = 1500000;
            break;
        case CS_CTL0_DCORSEL_1:
            centeredFreq = 3000000;
            break;
        case CS_CTL0_DCORSEL_2:
            centeredFreq = 6000000;
            break;
        case CS_CTL0_DCORSEL_3:
            centeredFreq = 12000000;
            break;
        case CS_CTL0_DCORSEL_4:
            centeredFreq = 24000000;
            break;
        case CS_CTL0_DCORSEL_5:
            centeredFreq = 48000000;
            break;
        }

        if(dcoTune == 0)
        {
            SystemCoreClock = centeredFreq;
        }
        else
        {

            if(dcoTune & 0x1000)
            {
                dcoTune = dcoTune | 0xF000;
            }

            if (BITBAND_PERI(CS->CTL0, CS_CTL0_DCORES_OFS))
            {
                dcoConst = *((volatile const float *) &TLV->DCOER_CONSTK_RSEL04);
                calVal = TLV->DCOER_FCAL_RSEL04;
            }
            /* Internal Resistor */
            else
            {
                dcoConst = *((volatile const float *) &TLV->DCOIR_CONSTK_RSEL04);
                calVal = TLV->DCOIR_FCAL_RSEL04;
            }

            SystemCoreClock = (uint32_t) ((centeredFreq)
                               / (1
                                    - ((dcoConst * dcoTune)
                                            / (8 * (1 + dcoConst * (768 - calVal))))));
        }
        break;
    case CS_CTL1_SELM__MODOSC:
        SystemCoreClock = __MODCLK / dividerValue;
        break;
    case CS_CTL1_SELM__HFXTCLK:
        if(BITBAND_PERI(CS->IFG, CS_IFG_HFXTIFG_OFS))
        {
            // Clear interrupt flag
            CS->KEY = CS_KEY_VAL;
            CS->CLRIFG |= CS_CLRIFG_CLR_HFXTIFG;
            CS->KEY = 1;

            if(BITBAND_PERI(CS->IFG, CS_IFG_HFXTIFG_OFS))
            {
                if(BITBAND_PERI(CS->CLKEN, CS_CLKEN_REFOFSEL_OFS))
                {
                    SystemCoreClock = (128000 / dividerValue);
                }
                else
                {
                    SystemCoreClock = (32000 / dividerValue);
                }
            }
            else
            {
                SystemCoreClock = __HFXT / dividerValue;
            }
        }
        else
        {
            SystemCoreClock = __HFXT / dividerValue;
        }
        break;
    }
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *
 * Performs the following initialization steps:
 *     1. Enables the FPU
 *     2. Halts the WDT if requested
 *     3. Enables all SRAM banks
 *     4. Sets up power regulator and VCORE
 *     5. Enable Flash wait states if needed
 *     6. Change MCLK to desired frequency
 *     7. Enable Flash read buffering
 */
void SystemInit(void)
{
    // Enable FPU if used
    #if (__FPU_USED == 1)                                  // __FPU_USED is defined in core_cm4.h
    SCB->CPACR |= ((3UL << 10 * 2) |                       // Set CP10 Full Access
                   (3UL << 11 * 2));                       // Set CP11 Full Access
    #endif

    #if (__HALT_WDT == 1)
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;            // Halt the WDT
    #endif

    SYSCTL->SRAM_BANKEN = SYSCTL_SRAM_BANKEN_BNK7_EN;      // Enable all SRAM banks

    #if (__SYSTEM_CLOCK == 1500000)                        // 1.5 MHz
    // Default VCORE is LDO VCORE0 so no change necessary

    // Switches LDO VCORE0 to DCDC VCORE0 if requested
    #if __REGULATOR
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_4;
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    #endif

    // No flash wait states necessary

    // DCO = 1.5 MHz; MCLK = source
    CS->KEY = CS_KEY_VAL;                                  // Unlock CS module for register access
    CS->CTL0 = CS_CTL0_DCORSEL_0;                          // Set DCO to 1.5MHz
    CS->CTL1 = (CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK)) | CS_CTL1_SELM__DCOCLK;  
	                                                       // Select MCLK as DCO source
    CS->KEY = 0;

    // Set Flash Bank read buffering
    FLCTL->BANK0_RDCTL = FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_BUFD | FLCTL_BANK0_RDCTL_BUFI);
    FLCTL->BANK1_RDCTL = FLCTL->BANK1_RDCTL & ~(FLCTL_BANK1_RDCTL_BUFD | FLCTL_BANK1_RDCTL_BUFI);

    #elif (__SYSTEM_CLOCK == 3000000)                      // 3 MHz
    // Default VCORE is LDO VCORE0 so no change necessary

    // Switches LDO VCORE0 to DCDC VCORE0 if requested
    #if __REGULATOR
    while(PCM->CTL1 & PCM_CTL1_PMR_BUSY);
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_4;
    while(PCM->CTL1 & PCM_CTL1_PMR_BUSY);
    #endif

    // No flash wait states necessary

    // DCO = 3 MHz; MCLK = source
    CS->KEY = CS_KEY_VAL;                                  // Unlock CS module for register access
    CS->CTL0 = CS_CTL0_DCORSEL_1;                          // Set DCO to 1.5MHz
    CS->CTL1 = (CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK)) | CS_CTL1_SELM__DCOCLK;  
	                                                       // Select MCLK as DCO source
    CS->KEY = 0;

    // Set Flash Bank read buffering
    FLCTL->BANK0_RDCTL = FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_BUFD | FLCTL_BANK0_RDCTL_BUFI);
    FLCTL->BANK1_RDCTL = FLCTL->BANK1_RDCTL & ~(FLCTL_BANK1_RDCTL_BUFD | FLCTL_BANK1_RDCTL_BUFI);

    #elif (__SYSTEM_CLOCK == 12000000)                     // 12 MHz
    // Default VCORE is LDO VCORE0 so no change necessary

    // Switches LDO VCORE0 to DCDC VCORE0 if requested
    #if __REGULATOR
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_4;
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    #endif

    // No flash wait states necessary

    // DCO = 12 MHz; MCLK = source
    CS->KEY = CS_KEY_VAL;                                  // Unlock CS module for register access
    CS->CTL0 = CS_CTL0_DCORSEL_3;                          // Set DCO to 12MHz
    CS->CTL1 &= ~(CS_CTL1_DIVS_2 | CS_CTL1_DIVS_1);
    CS->CTL1 = (CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK)) | CS_CTL1_SELM__DCOCLK;  
	                                                       // Select MCLK as DCO source
    CS->KEY = 0;

    // Set Flash Bank read buffering
    FLCTL->BANK0_RDCTL = FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_BUFD | FLCTL_BANK0_RDCTL_BUFI);
    FLCTL->BANK1_RDCTL = FLCTL->BANK1_RDCTL & ~(FLCTL_BANK1_RDCTL_BUFD | FLCTL_BANK1_RDCTL_BUFI);

    #elif (__SYSTEM_CLOCK == 24000000)                     // 24 MHz
    // Default VCORE is LDO VCORE0 so no change necessary

    // Switches LDO VCORE0 to DCDC VCORE0 if requested
    #if __REGULATOR
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_4;
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    #endif

    // 1 flash wait state (BANK0 VCORE0 max is 12 MHz)
    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~FLCTL_BANK0_RDCTL_WAIT_MASK) | FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL = (FLCTL->BANK1_RDCTL & ~FLCTL_BANK1_RDCTL_WAIT_MASK) | FLCTL_BANK1_RDCTL_WAIT_1;

    // DCO = 24 MHz; MCLK = source
    CS->KEY = CS_KEY_VAL;                                  // Unlock CS module for register access
    CS->CTL0 = CS_CTL0_DCORSEL_4;                          // Set DCO to 24MHz
    CS->CTL1 &= ~(CS_CTL1_DIVS_2 | CS_CTL1_DIVS_1);
    CS->CTL1 = (CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK)) | CS_CTL1_SELM__DCOCLK | CS_CTL1_DIVS_1;
	                                                       // Select MCLK as DCO source
    CS->KEY = 0;

    // Set Flash Bank read buffering
    FLCTL->BANK0_RDCTL = FLCTL->BANK0_RDCTL | (FLCTL_BANK0_RDCTL_BUFD | FLCTL_BANK0_RDCTL_BUFI);
    FLCTL->BANK1_RDCTL = FLCTL->BANK1_RDCTL & ~(FLCTL_BANK1_RDCTL_BUFD | FLCTL_BANK1_RDCTL_BUFI);

    #elif (__SYSTEM_CLOCK == 48000000)                     // 48 MHz
    // Switches LDO VCORE0 to LDO VCORE1; mandatory for 48 MHz setting
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));

    // Switches LDO VCORE1 to DCDC VCORE1 if requested
    #if __REGULATOR
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_5;
    while((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    #endif

    // 1 flash wait states (BANK0 VCORE1 max is 16 MHz, BANK1 VCORE1 max is 32 MHz)
    FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~FLCTL_BANK0_RDCTL_WAIT_MASK) | FLCTL_BANK0_RDCTL_WAIT_1;
    FLCTL->BANK1_RDCTL = (FLCTL->BANK1_RDCTL & ~FLCTL_BANK1_RDCTL_WAIT_MASK) | FLCTL_BANK1_RDCTL_WAIT_1;

    // DCO = 48 MHz; MCLK = source
    CS->KEY = CS_KEY_VAL;                                  // Unlock CS module for register access
    CS->CTL0 = CS_CTL0_DCORSEL_5;                          // Set DCO to 48MHz
    CS->CTL1 &= ~(CS_CTL1_DIVS_2 | CS_CTL1_DIVS_1);
    CS->CTL1 = (CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK)) | CS_CTL1_SELM__DCOCLK | CS_CTL1_DIVS_2;
	                                                       // Select MCLK as DCO source
    CS->KEY = 0;

    // Set Flash Bank read buffering
    FLCTL->BANK0_RDCTL = FLCTL->BANK0_RDCTL | (FLCTL_BANK0_RDCTL_BUFD | FLCTL_BANK0_RDCTL_BUFI);
    FLCTL->BANK1_RDCTL = FLCTL->BANK1_RDCTL | (FLCTL_BANK1_RDCTL_BUFD | FLCTL_BANK1_RDCTL_BUFI);
    #endif

}


