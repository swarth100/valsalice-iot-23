MEMORY
{
  rom (rx) : ORIGIN = 0x4400, LENGTH = 0xFC00 /* Adjust ROM size for simulation */
  ram (rwx) : ORIGIN = 0x1100, LENGTH = 0x2000 /* Adjust RAM size for simulation */
}

SECTIONS
{
  .text :
  {
    *(.text*)           /* Code */
    *(.rodata*)         /* Read-only data (constants) */
  } > rom

  .data : AT(ADDR(.text) + SIZEOF(.text))
  {
    _data = .;
    *(.data*)           /* Data */
    _edata = .;
  } > ram

  .bss :
  {
    _bss = .;
    *(.bss*)            /* Zero-initialized data */
    _ebss = .;
  } > ram
}
