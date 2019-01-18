#Pull flask
FROM tiangolo/uwsgi-nginx-flask:python3.7
#Install crypto
RUN apt-get update -y
RUN pip install ebcdic

#Copy all the files
COPY ./app /app

