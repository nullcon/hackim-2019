# name: proto

# flag: flag{Prototype_for_the_win}

#Points: 100

# solution
- To make this Object prototype injection more fun, I add a cookie which Cyrillic "а" (U+0430) rather than the ASCII "a" (U+0061)
- A post request should be made to /signup with  {"name":"World","__proto__":{"admin":1}} 
- Then navigate to /getFlag to get the flag.

#Installation
- run ./start.sh
