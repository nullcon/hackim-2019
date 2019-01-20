from Crypto.Cipher import AES
from Crypto.Util import Counter
from Crypto import Random
from secret import flag, key
from hashlib import sha256
from Crypto.Util.number import *
from binascii import hexlify

H = AES.new(key, AES.MODE_ECB).encrypt(bytes(16))
sessionid = b''
n = 2**129 - 1


def group(a, length=16):
    count = len(a) // length
    if len(a) % length != 0:
        count += 1
    return [a[i * length: (i + 1) * length] for i in range(count)]


def GHASH(ciphertext, nonce):
    assert len(nonce) == 12
    c = AES.new(key, AES.MODE_ECB).encrypt(nonce + bytes(3) + b'\x01')
    blocks = group(ciphertext)
    tag = bytes_to_long(c)
    for i, b in enumerate(blocks):
        tag += (bytes_to_long(b) * pow(bytes_to_long(H), i, n)) % n
    return long_to_bytes(tag)


def encrypt(msg):
    nonce = sessionid + Random.get_random_bytes(2)
    assert len(nonce) == 12
    ctr = Counter.new(32, prefix=nonce)
    cipher = AES.new(key, AES.MODE_CTR, counter=ctr)
    ciphertext = cipher.encrypt(msg)
    tag = GHASH(ciphertext, nonce)
    return (nonce, ciphertext, tag)


def decrypt(nonce, ciphertext, tag):
    assert len(nonce) == 12
    assert GHASH(ciphertext, nonce) == tag
    ctr = Counter.new(32, prefix=nonce)
    cipher = AES.new(key, AES.MODE_CTR, counter=ctr)
    plaintext = cipher.decrypt(ciphertext)
    return plaintext


def main():
    global sessionid
    username = input('Enter username: ')
    sessionid = sha256(username.encode()).digest()[:10]

    while True:
        print("Menu")
        print("[1] Encrypt")
        print("[2] Decrypt")
        print("[3] Exit")

        choice = input("> ")

        if choice == '1':
            msg = input('Enter message to be encrypted: ')
            if 'flag' in msg:
                print("You cant encrypt flag :(")
                continue
            c = encrypt(msg.encode())
            nonce = hexlify(c[0]).decode()
            ciphertext = hexlify(c[1]).decode()
            tag = hexlify(c[2]).decode()
            print(nonce + ':' + ciphertext + ':' + tag)
            continue

        if choice == '2':
            nonce, ciphertext, tag = input(
                'Enter message to be decrypted: ').split(':')
            nonce = long_to_bytes(int(nonce, 16))
            ciphertext = long_to_bytes(int(ciphertext, 16))
            tag = long_to_bytes(int(tag, 16))
            pt = decrypt(nonce, ciphertext, tag).decode()
            if pt == 'may i please have the flag':
                print("Congrats %s" % username)
                print("Here is your flag: %s" % flag)
            print(pt)
            continue

        if choice == '3':
            break


if __name__ == '__main__':
    main()
