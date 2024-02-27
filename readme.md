## Debugging

```
mspdebug rf2500 gdb

msp430-gdb -x firmware.gdb
```

Attention: the gdb in the TI toolchain package is broken, use the one from Debian



## Signals Working Cycler

These signals are related to code under tag `cycler_works_include_output_stage`.

First octets:

![](./docs/cycler_working_first_octets.png)

Last octets:

![](./docs/cycler_working_last_octets.png)
