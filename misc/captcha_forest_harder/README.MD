# name:Captcha Forest Harder
description: This captcha should be used everywhere!

# flag: hackim19{I_guess_I_will_stop_making_captchas_now} 

# solution (non ml)
- 120 out of 200 captcha submission should be right, after 80 wrongs submission we are disconnected
- make three simultaneous connection to the socket
- give 80 wrong answers to first socket and receive 80 correct from the server
- pass 80 correct answers to other two sockets
- give another 40 wrong answers to 2nd socket to get 40 correct
- pass 40 correct answers to 3rd socket to get the flag

