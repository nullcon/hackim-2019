import pwn as p
from Crypto.Random import get_random_bytes
from base64 import b64encode
from Crypto.Util.number import *
# r = p.process("server.py")
r = p.remote("crypto.ctf.nullcon.net", 5000)


def set_username(username):
    r.recvuntil('Enter username: ')
    r.sendline(username)


def group(a, length=16):
    count = len(a) // length
    if len(a) % length != 0:
        count += 1
    return [a[i * length: (i + 1) * length] for i in range(count)]


def encrypt(msg):
    r.recvuntil("> ")
    r.sendline("1")
    r.recvuntil("Enter message to be encrypted: ")
    r.sendline(msg)
    enc = r.recvline().strip().split(":")
    return map(lambda s: s.decode('hex'), enc)


def decrypt(ct):
    assert len(ct.split(":")) == 3
    r.recvuntil("> ")
    r.sendline("2")
    r.recvuntil("Enter message to be decrypted: ")
    r.sendline(ct)
    return r.recvline().strip()


set_username("test")
t = dict()
H = b""

n = 327989969870981036659934487747327553919
while True:
    msg = b64encode(get_random_bytes(8))
    enc = encrypt(msg)
    if enc[0] in t and t[enc[0]][2] != msg:
        ct1 = bytes_to_long(enc[1])
        ct2 = bytes_to_long(t[enc[0]][0])
        tag1 = bytes_to_long(enc[2])
        tag2 = bytes_to_long(t[enc[0]][1])
        H = ((tag2 - tag1) * inverse(ct2 - ct1, n)) % n
        break
    t[enc[0]] = (enc[1], enc[2], msg)

print("Found H: %s" % hex(H)[2:])
msg = "may i please have the flah"
enc = encrypt(msg)
c = 0
nonce = bytes_to_long(enc[0])
ct = enc[1]
tag = bytes_to_long(enc[2])
blocks = group(ct)
temp_tag = 0

for i, b in enumerate(blocks):
    temp_tag += (bytes_to_long(b) * pow(H, i + 1, n)) % n

c = (tag - temp_tag) % n

desired_msg = "may i please have the flah"
desired_ct = enc[1]
desired_ct = desired_ct[:-1] + chr(ord(desired_ct[-1]) ^ ord('h') ^ ord('g'))
desired_nonce = enc[0]
desired_tag = c

blocks = group(desired_ct)

for i, b in enumerate(blocks):
    desired_tag += (bytes_to_long(b) * pow(H, i + 1, n)) % n

print(decrypt("%s:%s:%s" % (desired_nonce.encode('hex'), desired_ct.encode('hex'), long_to_bytes(desired_tag).encode('hex'))))
r.interactive()
