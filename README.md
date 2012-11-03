# arduino_verkefni

Uppsetning á brauðbrettinu:


## Töluskjár:

Pinni á skjá | Pinni á Arduino
-------------|-----------------------------------------------------------------
     0       |       0
     1       |       1
     2       | *(sjá neðstu línu)*
     3       |       2
     4       |     ekkert
     5       |       4
     6       |       5
     7       | *(sjá neðstu línu)*
     8       |       6
     9       |       7
 **2 og 7**  |  hliðtengt gegnum 330Ω viðnám, síðan raðtengt í 330Ω og í jörð


## RGB led:

Lengsti pinninn er pinni 1, næstlegsti er pinni 2. Stutti pinninn við hlið þess er númer 3 og stutti pinninn við hlið þess lengsta er pinni 0

Pinni á RGB |     Pinni á Arduino
------------|-------------------------
     0      |  11 (gegnum 330Ω viðnám)
     1      |        jörð
     2      |  10 (gegnum 330Ω viðnám)
     3      |   9 (gegnum 330Ω viðnám)


## Takki

Takkinn er symmetrískur. Önnur hliðin þarf að vera tengd við jörð (gegnum 10KΩ viðnám) og við 5V pinnann. Hin hliðin er tengd í digital pinna 12