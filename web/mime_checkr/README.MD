# name:Mim3_Ch3ckr 
description: Upload and check your Mim3 type

# flag: hackim19{PHP_Streams_are_t00_MainStream0}

# solution
- download the backup file getmime.bak
- Upload a phar with image header
- check the mime type with phar://image
- Perform deserialization on MainClass to perform SSRF with curl
- Docker range - 172.17.0.0/24
- On 172.17.0.3:180 you would get crypto which is ebcdic with cp1047 encoding (DD & online converters wont work, you need to use py script)
- Navigate to /fetch~%[]^@)( and You would get the flag

#Installation
- Navigate to apache and run start.sh
- Navigate to crypto and run start.sh
