#### Singular
##### Description
Alice and Bob calculated a shared key on the elliptic curve 
y^2 = x^3 + 330762886318172394930696774593722907073441522749*x^2 + 6688528763308432271990130594743714957884433976*x + 759214505060964991648440027744756938681220132782
p = 785482254973602570424508065997142892171538672071
G = (1, 68596750097555148647236998220450053605331891340)
(Alice's public key) P = d1 * G = (453762742842106273626661098428675073042272925939, 680431771406393872682158079307720147623468587944)
(Bob's poblic key) Q = d2 * G = (353016783569351064519522488538358652176885848450, 287096710721721383077746502546881354857243084036)
They have calculated K = d1 * d2 * G. They have taken K's x coordinate in decimal and took sha256 of it and used it for AES ECB to encrypt the flag.

Here is the encrypted flag: 480fd106c9a637d22fddd814965742236eb314c1b8fb68e70a7c7445ff04476082f8b9026c49d27110ba41b95e9f51dc


##### Points

350

##### Flag

hackim19{w0ah_math_i5_quite_fun_a57f8e21}

##### Solution
In this task the curve is weak and it is actualy in the form of y^2 = (x + s)^3 for some integer s which is proven the be isomorphic to the additive group GF(p) hence the discrete log problem is very easy to solve.