
/**
 * @file main.h
 * @author pflaherty
 * @date 08.04.2023
 * @brief main header file for simple polling os. Declares public functions for other module's use
 *
 * Change History
 * 08.04.2023 - Initial Creation
 */


/************************************************************/
/********************* DEFINES  *****************************/
/************************************************************/
// #define OS_HEADER_FILE "os_polling.h"

#define RESETS_BASE                 0x4000C000

#define RESETS_RESET_RW             (RESETS_BASE+0x0+0x0000)
#define RESETS_RESET_XOR            (RESETS_BASE+0x0+0x1000)
#define RESETS_RESET_SET            (RESETS_BASE+0x0+0x2000)
#define RESETS_RESET_CLR            (RESETS_BASE+0x0+0x3000)

#define RESETS_WDSEL_RW             (RESETS_BASE+0x4+0x0000)
#define RESETS_WDSEL_XOR            (RESETS_BASE+0x4+0x1000)
#define RESETS_WDSEL_SET            (RESETS_BASE+0x4+0x2000)
#define RESETS_WDSEL_CLR            (RESETS_BASE+0x4+0x3000)

#define RESETS_RESET_DONE_RW        (RESETS_BASE+0x8+0x0000)
#define RESETS_RESET_DONE_XOR       (RESETS_BASE+0x8+0x1000)
#define RESETS_RESET_DONE_SET       (RESETS_BASE+0x8+0x2000)
#define RESETS_RESET_DONE_CLR       (RESETS_BASE+0x8+0x3000)

#define SIO_BASE                    0xD0000000

#define SIO_GPIO_OUT_RW             (SIO_BASE+0x10)
#define SIO_GPIO_OUT_SET            (SIO_BASE+0x14)
#define SIO_GPIO_OUT_CLR            (SIO_BASE+0x18)
#define SIO_GPIO_OUT_XOR            (SIO_BASE+0x1C)

#define SIO_GPIO_OE_RW              (SIO_BASE+0x20)
#define SIO_GPIO_OE_SET             (SIO_BASE+0x24)
#define SIO_GPIO_OE_CLR             (SIO_BASE+0x28)
#define SIO_GPIO_OE_XOR             (SIO_BASE+0x2C)

#define IO_BANK0_BASE               0x40014000

#define IO_BANK0_GPIO25_STATUS_RW   (IO_BANK0_BASE+0x0C8+0x0000)
#define IO_BANK0_GPIO25_STATUS_XOR  (IO_BANK0_BASE+0x0C8+0x1000)
#define IO_BANK0_GPIO25_STATUS_SET  (IO_BANK0_BASE+0x0C8+0x2000)
#define IO_BANK0_GPIO25_STATUS_CLR  (IO_BANK0_BASE+0x0C8+0x3000)

#define IO_BANK0_GPIO25_CTRL_RW     (IO_BANK0_BASE+0x0CC+0x0000)
#define IO_BANK0_GPIO25_CTRL_XOR    (IO_BANK0_BASE+0x0CC+0x1000)
#define IO_BANK0_GPIO25_CTRL_SET    (IO_BANK0_BASE+0x0CC+0x2000)
#define IO_BANK0_GPIO25_CTRL_CLR    (IO_BANK0_BASE+0x0CC+0x3000)


/************************************************************/
/********************* INCLUDES  ****************************/
/************************************************************/
// #include OS_HEADER_FILE


/************************************************************/
/******************** ENUMERATIONS **************************/
/************************************************************/

/**
 * @brief enumeration of reset reasons
 *
 *  
 */
typedef enum kResetReason_enum {
  kHardReset,           /** Reset occured from external power drop , aka Power On Reset */
  kSoftwareReset,       /** Reset initiated internally - not watchdog */
  kExternalReset,       /** Reset triggered through reset pin */
  kWatchdogReset,       /** Reset triggered through internal watchdog */
  kInvalidreset = 0xFF, /** Invalid value  */
} kResetReason;

/************************************************************/
/****************** PUBLIC FUNCTIONS  ***********************/
/************************************************************/

/**
 * @brief Adds all module init functions to the OS Init lists
 * 
 * @note Should be the only place to call OS_ADDINIT()
 */
static void setupInit(void);

/**
 * @brief Adds all module main functions to the relevant OS tasks
 * 
 * @note Should be the only place to call OS_ADDMAINFUNCTIONS()
 */
static void setupMainFunctions(void);

/**
 * @brief entry function of application
 * 
 * main should:
 * 1. initialize all modules
 * 2. start OS (or polling manager)
 * @pre: bootloader has executed all necessary initialization to enable XIP for application in RAM
 * @return Should never return.
 * */
int main(void) __attribute__ ((section (".startup_code")));

void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void DELAY ( unsigned int );
