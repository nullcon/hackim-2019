# name: credz

Alice is a admin of abc company in india. He knows about hackers and makes a system that can login only from his system and only his browser which is chrome lastest. 

# flag: hackim19{JS_GIT_PHP_HeR0_a1m40d}

# solution
- The username and password is admin:admin but login wont work. 
- We need to guess the macID which is generated from JS and predirect the admin macID with the image,Timeoffset,Browser given in html
- even after guessing he need to trackuser first then only he can login
- After that a pack file is given which has code of admin.php. That can be decoded with `cat *.pack | git unpack-objects`
- The admin.php will be bypassed with admin.php/index.php

#Installation
- run ./start.sh
