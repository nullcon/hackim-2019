from flask import Flask
from flask import request
import ebcdic
app = Flask(__name__)


@app.route("/")
def hello():
    hello="Hello /fetch~%[]^@)(  me"
    st = hello.encode("cp1047")
    return str(st)

@app.route("/fetch~%[]^@)(")
def fetch():
    flag= "Flag{PHP_Streams_are_t00_MainStream0}"
    st = flag.encode("cp1047")
    return str(st)


if __name__ == "__main__":
    # Only for debugging while developing
    app.run(host='0.0.0.0', port=180)

