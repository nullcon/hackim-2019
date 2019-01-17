docker ps -a | awk '{ print $1,$2 }' | grep null-ctf-web-nginx | awk '{print $1 }' | xargs -I {} docker rm -f {}
docker build -t null-ctf-web-nginx .
docker run -d --name null2 -p 80:80 null-ctf-web-nginx

