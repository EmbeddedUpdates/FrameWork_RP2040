/*
SPDX-License-Identifier: BSD-3-Clause
Copyright (c) 2021, Alex Taradov <alex@taradov.com>. All rights reserved.
*/

MEMORY
{
  boot  (rx) : ORIGIN = 0x10000000, LENGTH = 256
  flash (rx) : ORIGIN = 0x10000100, LENGTH = 2048K - 256
  ram  (rwx) : ORIGIN = 0x20010000, LENGTH = 264K
}

ENTRY(boot_entry);

SECTIONS
{
  .boot : ALIGN(4)
  {
    KEEP(*(.boot_entry))
    *(.boot*)
    LONG(0xB8BD1F1C) /* CRC */
  } > boot

  .text : ALIGN(4)
  {
    _text = .;
    KEEP(*(.vectors))
    *(.text*)
    *(.rodata)
    *(.rodata.*)
    . = ALIGN(4);
    _etext = .;
  } > ram AT > flash

  .data : ALIGN(4)
  {
    _data = .;
    *(.ramfunc .ramfunc.*);
    *(vtable)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > ram AT > flash

  .bss : ALIGN(4)
  {
    _bss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > ram

  PROVIDE(_end = .);
  PROVIDE(_text_start = ORIGIN(flash));
  PROVIDE(_stack_top = ORIGIN(ram) + LENGTH(ram));
  PROVIDE(boot_entry = ORIGIN(boot)+1);
}