#### Unicat
##### Description

Decrypt to unlock the door

[('inputst',1),('diepgrm',),('asgnlit', 1, 1),('asgnlit', 4, 1),('asgnlit', 10, 7),('echoval', 2),('pointer',4,4),('echoval',4),('applop+', 10, 1),('echoval',10),('asgnlit', 2, 72),('applop*', 2, 10),('echoval',2),('asgnlit', 0, 108), ('echovar', 0),('asgnlit', 0, 108), ('echovar', 0),('asgnlit', 0, 65), ('echovar', 0),('asgnlit', 0, 119), ('echovar', 0),('asgnlit', 0, 69), ('echovar', 0),('asgnlit', 0, 115), ('echovar', 0),('asgnlit', 0, 48), ('echovar', 0),('asgnlit', 0, 109), ('echovar', 0),('asgnlit', 0, 69), ('echovar', 0),('asgnlit', 0, 95), ('echovar', 0),('asgnlit', 0, 67), ('echovar', 0),('asgnlit', 0, 64), ('echovar', 0),('asgnlit', 0, 84), ('echovar', 0)]


##### Points

150

##### Flag

hackim19{018576llAwEs0mE_C@T}

##### Solution

- Need to use this interpreter https://github.com/gemdude46/unicat/blob/master/cat.py
- To make this challenge tricky, I have added ('inputst',1),('diepgrm',) to stop script kiddies. These both stop the execution of the scipt and removed ('diepgrm',) at the end so the loop never ends. 
