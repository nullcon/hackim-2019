#### cat
##### Description

Decrypt to file to unlock the door


##### Points

100

##### Flag

hackim19{018576llAwEs0mE_C@T}

##### Solution

- As the INS was readable, I wrote a encoder for the encrpytion. Now decrpyting the file gives the INS
- Need to use this interpreter https://github.com/gemdude46/unicat/blob/master/cat.py
- To make this challenge tricky, I have added ('inputst',1),('diepgrm',) to stop script kiddies. These both stop the execution of the scipt and removed ('diepgrm',) at the end so the loop never ends. 
