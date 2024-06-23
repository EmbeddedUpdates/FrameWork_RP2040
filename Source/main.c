#include <stdint.h>
#include "main.h"

/**
 * function: setupInit()
 * entry from startup code: expectation is that rp2040 bootloader has copied the application to RAM
 * main should:
 * 1. initialize all modules
 * 2. start OS (or polling manager)
 * */
static void setupInit(void)
{
	/* kInitZero_HardReset -  Stage Zero - Only triggers for hard reset */
	/* kInitZero           - Stage Zero - always occurs */
	//Timer Init
	//OS_ADDINIT(kInitZero, &timerRp2040_init, 0);
	//Port_init
	//OS_ADDINIT(kInitZero, &portRp2040_init, 0);
	/* kInitOne_HardReset  - Stage One - Only triggers for hard reset */
	/* kInitOne            - Stage  ne - always occurs */
	//i2c_init
	//OS_ADDINIT(kInitOne, &i2cRp2040_init, 0);
	//spi_init
	//OS_ADDINIT(kInitOne, &spiRp2040_init, 0);
	/* kInitTwo            - Stage two - always occurs */
	//stemma - moisture sensor
	//OS_ADDINIT(kInitTwo, &stemma_init, 0);
	//display
	//OS_ADDINIT(kInitTwo, &DISPLAY_init, 0);
	/* kInitThree          - Stage three - always occurs */
	// mainApplication - emotive flower pot
	//OS_ADDINIT(kInitThree, &emotiveFlowerPot_init, 0);
}

/**
 * function: setupInit()
 * entry from startup code: expectation is that rp2040 bootloader has copied the application to RAM
 * main should:
 * 1. initialize all modules
 * 2. start OS (or polling manager)
 * */
static void setupMainFunctions(void)
{
	/* kInitZero_HardReset -  Stage Zero - Only triggers for hard reset */
	/* kInitZero           - Stage Zero - always occurs */
	//Timer Init
	//OS_ADDINIT(kInitZero, &timerRp2040_init, 0);
	//Port_init
	//OS_ADDINIT(kInitZero, &portRp2040_init, 0);
	/* kInitOne_HardReset  - Stage One - Only triggers for hard reset */
	/* kInitOne            - Stage  ne - always occurs */
	//i2c_init
	//OS_ADDINIT(kInitOne, &i2cRp2040_init, 0);
	//spi_init
	//OS_ADDINIT(kInitOne, &spiRp2040_init, 0);
	/* kInitTwo            - Stage two - always occurs */
	//stemma - moisture sensor
	//OS_ADDINIT(kInitTwo, &stemma_init, 0);
	//display
	//OS_ADDINIT(kInitTwo, &DISPLAY_init, 0);
	/* kInitThree          - Stage three - always occurs */
	// mainApplication - emotive flower pot
	//OS_ADDINIT(kInitThree, &emotiveFlowerPot_init, 0);
}

/**
 * function: getResetReason()
 * return the reset reason as int according to enum
 * */
static int getResetReason(void)
{
	/* TODO: implement an actual check - or push this ro brs_rp2040 */
	return kHardReset;
}

/**
 * function: main()
 * entry from startup code: expectation is that rp2040 bootloader has copied the application to RAM
 * main should:
 * 1. initialize all modules
 * 2. start OS (or polling manager)
 * */
int main()
{
	    //release reset on IO_BANK0
    PUT32(RESETS_RESET_CLR,1<<5); //IO_BANK0
    //wait for reset to be done
    while(1)
    {
        if((GET32(RESETS_RESET_DONE_RW)&(1<<5))!=0) break;
    }

    //output disable
    PUT32(SIO_GPIO_OE_CLR,1<<25);
    //turn off pin 25
    PUT32(SIO_GPIO_OUT_CLR,1<<25);

    //set the function select to SIO (software controlled I/O)
    PUT32(IO_BANK0_GPIO25_CTRL_RW,5);

    //output enable
    PUT32(SIO_GPIO_OE_SET,1<<25);
    while(1)
    {
        //turn on the led
        PUT32(SIO_GPIO_OUT_SET,1<<25);
        DELAY(0x100000);
        //turn off the led
        PUT32(SIO_GPIO_OUT_CLR,1<<25);
        DELAY(0x100000);
    }
    return(0);

	return 0; /* should never be reached */
}