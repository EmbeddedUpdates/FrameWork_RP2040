
/**
 * @file main.h
 * @author pflaherty
 * @date 08.04.2023
 * @brief main header file for simple polling os. Declares public functions for other module's use
 *
 * Change History
 * 08.04.2023 - Initial Creation
 */


/************************************************************
  DEFINES
************************************************************/
// #define OS_HEADER_FILE "os_polling.h"

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
// static void setupInit(void);

/**
 * @brief Adds all module main functions to the relevant OS tasks
 * 
 * @note Should be the only place to call OS_ADDMAINFUNCTIONS()
 */
// static void setupMainFunctions(void);

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
