docker ps -a | awk '{ print $1,$2 }' | grep null-ctf-web-proto | awk '{print $1 }' | xargs -I {} docker rm -f {}
docker build -t null-ctf-web-proto .
docker run -d --name proto -p 8888:8080 null-ctf-web-proto

