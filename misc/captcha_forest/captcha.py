#!/usr/bin/python -u
import sys
import os
import random, time
from PIL import Image

def disable_stdout_buffering():
    import gc
    gc.garbage.append(sys.stdout)
    sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)

disable_stdout_buffering()

def cap_gen():
    img = []
    sol = []
    for i in range(4):
        r = random.randint(65, 90)
        sol.append(chr(r))
        img.append('static/char(' + str(r) + ').png')

    images = map(Image.open, img)
    widths, heights = zip(*(i.size for i in images))
        
    total_width = sum(widths)
    max_height = max(heights)

    new_im = Image.new('RGB', (total_width, max_height))

    x_offset = 0
    for im in images:
        new_im.paste(im, (x_offset,0))
        x_offset += im.size[0]

    return new_im, ''.join(sol)

def p(txt):
    sys.stdout.write(txt + "\r\n")
    sys.stdout.flush()

p("Welcome to Captcha Forest")
p("In order to get the flag, you must cut through 200 captcha trees.")
p("I will send you captcha in png format (hex encoded), you must solve the captcha and give me correct answers to proceed further")
p("Hint: I have used Bill Cipher mappings for captchas, good luck :)")
raw_input("--- press Enter to continue ---\r\n")

for i in range(200):
    im, ans = cap_gen()
    nm = random.randint(10000, 100000)
    name = 'temp/' + str(nm) + '.png'
    im.save(name, 'PNG')
    print(open(name, 'rb').read().encode('hex'))
    os.remove(name)
    got = raw_input("--- Type Answer to provided captcha {} ---\r\n".format(i+1)).strip()
    if got == ans:
        p("Correct!")
        raw_input("--- press Enter to continue ---\r\n")
    else:
        p("Wrong, Bye bye!")
        sys.exit()


p(open('flag.txt', 'r').read())
