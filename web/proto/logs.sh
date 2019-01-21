docker ps -a | awk '{ print $1,$2 }' | grep null-ctf-web-proto | awk '{print $1 }' | xargs -I {} docker logs {}

