from flask import Flask
from flask import request
import ebcdic
app = Flask(__name__)


@app.route("/")
def hello():
    hello="Hello /fetch~%[]^@)(  me"
    return hello.encode('cp1047')

@app.route("/fetch~%[]^@)(")
def fetch():
    id="flag[~]!@~`#$%^*&()"
    enc=id.encode('cp1047')
    return str(enc)

@app.route("/flag[]!@~`#$%^*&()")
def wat():
    return "Flag{PHP_Streams_are_t00_MainStream0}"

if __name__ == "__main__":
    # Only for debugging while developing
    app.run(host='0.0.0.0', debug=True, port=80)

