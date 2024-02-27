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

Schematics and legend for signals:

![](./docs/schematics.jpeg)


## Timing

Complete cycle: 2.48us

![](./docs/pulse_complete.png)

Short pulse: 550ns

![](./docs/pulse_short.png)

Long pulse: 1.18us

![](./docs/pulse_long.png)

During of loading data into five LEDs: 297us

![](./docs/five_leds.png)

| # of LEDs | Load Time |
| --------- | --------- |
| 5         | 297us     |
| 10        | 594us     |
| 100       | 5.9ms     |
| 200       | 11.8ms    |

