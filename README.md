# arduino_verkefni

Þetta er skilaverkefnið okkar (hópur: Ásgeir Bjarnason, Eyjólfur Kristjánsson og Vilborg Sveinsdóttir) í Arduino verkefninu í áfanganum T-109-INTO haustið 2012.

Verkefnið okkar ætti að uppfylla öll skilyrðin í verkefnalýsingunni, en þar að auki gerir forritið eftirfarandi:

  * Blikkar morse-kóða á pinna 13, sem er tengt í rauða LED-ljósið á brauðbrettinu okkar.
   Morse kóðinn sem er sendur er „We think we should get 12 for this assignment “
  * Ef ljósneminn skynjar að birtan er orðin lítil „svæfir“ forritið sig:
     * Forritið slekkur á tölu-skjánum.
     * stoppar morse-kóðann (og slekkur á LEDinu ef forritið var í miðju blikki)
     * gerir takkann óvirkann
     * lætur RGB led ljósið „anda“ (sýnir hvítt ljós með sínusbylgju af ljósmagni)
   
   Þegar ljósmagnið eykst aftur fer forritið aftur af stað frá sama punkti og það var svæft.

Með aðalforritunu (arduino_verkefni.ino) fylgja tvö fylgdarskjöl sem voru notuð til þess að búa til aðalforritið:

  * translation_table.txt: Skilgreiningarskjal á morse-kóða stafrófinu
  * translation.py: Python forrit sem býr til C kóða útfrá translation_table.txt.  
    Allur kóðinn í arduino_verkefni.ino milli `// --autogen--` taganna kom úr Python forritinu.

Við erum með 2 youtube myndbönd sem sýna fram á virkni verkefnisins okkar:

  * http://youtu.be/asKE5BN5YV8 sýnir grunnvirknina
  * http://youtu.be/wLxzDiEbjro sýnir aukavirknina


## Uppsetningin á brauðbrettinu

### Töluskjár:

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
 **2 og 7**  |  hliðtengt gegnum 330Ω viðnám, síðan raðtengt í 330Ω og í jörð


### RGB led:

Lengsti pinninn er pinni 1, næstlengsti er pinni 2. Stutti pinninn við hlið þess er númer 3 og stutti pinninn við hlið þess lengsta er pinni 0

Pinni á RGB |       Pinni á Arduino
------------|---------------------------
     0      |  11 (gegnum 330Ω viðnám)
     1      | jörð (gegnum 330Ω viðnám)
     2      |  10 (gegnum 330Ω viðnám)
     3      |   9 (gegnum 330Ω viðnám)


### Takki

Takkinn er symmetrískur. Önnur hliðin þarf að vera tengd við jörð (gegnum 10KΩ viðnám) og við 5V pinnann. Hin hliðin er tengd í digital pinna 12


### Ljósnemi

Annar endirinn er tengdur við 5V strauminn, hinn endinn er tengdur við tvo hluti:
  
  * Beint við hliðræna pinnan A0
  * Í 10KΩ viðnám og þaðan í jörð
