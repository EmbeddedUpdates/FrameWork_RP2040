# FW_RP2040

Basic Framework for all RP2040 projects going forward.

This is utilizing startup code based on [dwelch67](https://github.com/dwelch67/raspberrypi-pico.git) who deserves 99% credit for the startup code.
In version 1.00.00, I've taken some of his code for my own use.
In version 1.01.00, the relevant code for startup is moved to a different component (BRS_RP2040) and is only called in case the main loop exits.
Futher projects can be started with a new upstream based off a clone of this repo.

## Debt

## [Technical Debt for this component is located here](./debt.md#TechnicalDebt)