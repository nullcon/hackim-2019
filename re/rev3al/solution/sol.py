from subprocess import Popen, PIPE, STDOUT
import string
import sys

PIN = '/home/vagrant/tools/pin-3.7-97619-g0d0c92f4f-gcc-linux/pin'
TOOL = '/home/vagrant/tools/pin-3.7-97619-g0d0c92f4f-gcc-linux/source/tools/rev3al/obj-intel64/reveal.so'
CHAL = './vm'
CMD = [PIN, '-t', TOOL, '--', CHAL]
alphabet = string.letters + string.digits


def generate_input(done, i, char):
    default = 'a'
    n = 14
    data = [default] * n
    for idx in done:
        data[idx] = done[idx]
    data[i] = char
    data = ''.join(data)
    sys.stdout.write(data + '\r')
    sys.stdout.flush()
    return data

p = Popen(CMD, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
stdout = p.communicate(input='aaaa')[0].split('\n')[1]
max_ins = int(stdout)

order = [0, 4, 13, 1, 7, 3, 10, 5, 11, 6, 12, 2, 8]
done = {}

for idx in order:
    for c in alphabet:
        data = generate_input(done, idx, c)
        p = Popen(CMD, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
        stdout = p.communicate(input=data)[0].split('\n')[1]
        if p.returncode == 0:
            print '\nFound flag:'
            print 'hackim19{%s}' % data
            sys.exit(0)
        ins = int(stdout)
        if ins > max_ins:
            max_ins = ins
            done[idx] = c
            break
sys.exit(1)
