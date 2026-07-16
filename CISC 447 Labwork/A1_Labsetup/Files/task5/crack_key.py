#!/usr/bin/python3
from sys import argv
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import re
import datetime

_= argv
first = "This is a top secret."
second = "2a94d3a3df0a72b3535c1bbcd873f09f5f9dd18d68d240e662190bb3627720498faa86b2cc0ff0d6cf8334a279d482b8"
third = "aabbccddeeff00998877665544332211"

data = bytearray(first, encoding='utf-8')
ciphertext = bytearray.fromhex(second)
iv = bytearray.fromhex(third)

with open('/usr/share/dict/words') as f:
    keys = f.readlines()

keys_dict = []

for i in range(16):
    keys_dict.append([])

for k in keys:
    k = k.rstrip('\n')
    if k.isalpha() and len(k) <= 15:
        keys_dict[len(k)].append(re.sub(r'[^a-zA-Z0-9\s]', '', k))

start = datetime.datetime.now()
for i in range(1,15):
    slot1_words = keys_dict[i]
    for j in range(i, 15-i):
       slot2_words = keys_dict[j]
       for word1 in slot1_words:
            for word2 in slot2_words:
                key = word1+word2 + '#'*(16-(len(word1)+ len(word2)))
                print(key)
                cipher = AES.new(key=bytearray(key,encoding='utf-8'), mode=AES.MODE_CBC, iv=iv)
                guess = cipher.encrypt(pad(data, 16))
                if guess == ciphertext:
                    print("key is:", key)
                    end = datetime.datetime.now()
                    print("Took "+ (start-end).total_seconds() +" seconds")
                    exit(0)
 

print("cannot find the key!")
