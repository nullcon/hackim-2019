FROM mongo

COPY files/ /tmp/dump/

CMD mongod --fork --logpath /var/log/mongodb.log; \
    mongorestore -d challenge /tmp/dump/; \
    mongod --shutdown; \
    docker-entrypoint.sh mongod

