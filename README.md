# BBP_on_Arduino
Implementing the Bailey–Borwein–Plouffe Pi digit extraction formula on an Arduino

This uses the 4-term BBP formula to produce Hex Pi digits in a spigot fashon.

Also used are fp64lib.h 64bit floats and int64_t for 64bit ints. This was necessary to get useful precision from the formula.

The program produces about 9000 hex digits in a day on a Atmega32u4, decreasing exponentially as time goes on. 

I haven't yest tested for large offsets. I estimate that it would take a little over an hour to calculate the millionth hex digit on the 32u4.
