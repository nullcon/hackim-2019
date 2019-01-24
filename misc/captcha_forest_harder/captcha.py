#!/usr/bin/python -u
import sys
import os
import random, time
from PIL import Image

random.seed(int(time.time())+1000)
def cap_gen():
	img = []
	sol = []
	for i in range(4):
		r = random.randint(65, 90)
		sol.append(chr(r))
		img.append('static/char(' + str(r) + ').png')

	images = map(Image.open, img)
	widths, heights = zip(*(i.size for i in images))
        
        rot_images = []
        for i in images:
            ratio = random.randint(7,10)*0.1
            rot_images.append(i.rotate((random.randint(0,60)-30)%360).resize([int(ratio*s) for s in i.size]))
        final_images = []
        for i in rot_images:
            img_w, img_h = i.size
            background = Image.new('RGB', (max(widths), max(heights)), (255, 255, 255))
            bg_w, bg_h = background.size
            offset = ((bg_w - img_w) // 2, (bg_h - img_h) // 2)
            background.paste(i, offset, i)
            final_images.append(background)

	total_width = sum(widths)
	max_height = max(heights)

	new_im = Image.new('RGB', (total_width, max_height), (255, 255, 255))

	x_offset = 0
	for im in final_images:
		new_im.paste(im, (x_offset,0))
		x_offset += im.size[0]

	return new_im, ''.join(sol)

def p(txt):
	sys.stdout.write(txt + "\r\n")

p("Welcome to Captcha Forest (Harder)")
p("In order to get the flag, you must answer at least 120 out of 200 captcha correctly.")
p("I made captchas a little difficult now, some rotation and some resizing of symbols to keep bots away.")
raw_input("--- press Enter to continue ---\r\n")

solves = 0
wrongs = 0
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
                solves += 1
                if solves >= 120:
                    p(open('flag.txt', 'r').read())
                    sys.exit()

		raw_input("--- press Enter to continue ---\r\n")
	else:
		p("Wrong!")
                wrongs += 1
                if wrongs > 80:
                    p("you already have more than 80 wrong solves")
                    sys.exit()
                p("Correct Answer: {}".format(ans))


