docker ps -a | awk '{ print $1,$2 }' | grep null-ctf-web-crypto | awk '{print $1 }' | xargs -I {} docker rm -f {}
docker build -t null-ctf-web-crypto .
docker run -d --name null -p 180:80 null-ctf-web-crypto

