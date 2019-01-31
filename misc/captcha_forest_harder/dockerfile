FROM python:2.7-alpine3.7
LABEL Description="captcha_forest_harder" VERSION='1.0'

RUN apk update && apk --no-cache add gcc python-dev musl-dev socat jpeg-dev zlib-dev

RUN pip install Pillow

WORKDIR /opt/captcha
RUN mkdir -p /opt/captcha
RUN mkdir -p /opt/captcha/temp
RUN chmod -R 777 temp
COPY captcha.py .
COPY flag.txt .
COPY static static

EXPOSE 6002

RUN adduser -D -H -g '' pwn

CMD su pwn -c "socat TCP-LISTEN:6002,reuseaddr,fork EXEC:\"python /opt/captcha/captcha.py\""
