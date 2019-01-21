from flask import Flask
from flask import request
import ebcdic
app = Flask(__name__)


@app.route("/")
def hello():
    hello="\xc8\x85\x93\x93\x96@a\x86\x85\xa3\x83\x88\xa1l\xad\xbd_|]M@@\x94\x85"
    return hello

@app.route("/fetch~%[]^@)(")
def fetch():
    id="\xc6\x93\x81\x87\xc0\xd7\xc8\xd7m\xe2\xa3\x99\x85\x81\x94\xa2m\x81\x99\x85m\xa3\xf0\xf0m\xd4\x81\x89\x95\xe2\xa3\x99\x85\x81\x94\xf0\xd0"
    return id


if __name__ == "__main__":
    # Only for debugging while developing
    app.run(host='0.0.0.0', debug=True, port=180)

