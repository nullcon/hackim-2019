FROM mongo

COPY ./files /home/dump/
COPY run.sh /home/mongo.sh

RUN chmod 77 /home/mongo.sh

CMD /home/mongo.sh

