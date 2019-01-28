FROM python:3.7-alpine3.7
LABEL Description="gcm" VERSION='1.0'

RUN apk update && apk add socat gcc g++ make openssl-dev python3-dev python-dev libffi-dev autoconf

RUN pip3 install pycrypto

WORKDIR /opt/GCM
RUN mkdir -p /opt/GCM
COPY secret.py .
COPY server.py .

EXPOSE 5000

RUN adduser -D -H -g '' pwn

CMD su pwn -c "socat TCP-LISTEN:5000,reuseaddr,nodelay,fork EXEC:\"python /opt/GCM/server.py\""