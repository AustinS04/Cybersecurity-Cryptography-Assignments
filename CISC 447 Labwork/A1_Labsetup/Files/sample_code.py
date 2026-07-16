import sys
IV_B  = bytes.fromhex("eebe6b34da9a3e7bfcbb9aa5ebdbc05d")   # <-- replace with "The IV used" (Bob)
IV_NEXT = bytes.fromhex("c18c898ada9a3e7bfcbb9aa5ebdbc05d") # <-- replace with "Next IV" shown now
def make_block(msg):
    b = msg.encode('ascii')
    pad = 16 - len(b)
    return b + bytes([pad])*pad
for msg in ("Yes","No"):
    Pb = make_block(msg)
    Pprime = bytes(x^y^z for x,y,z in zip(Pb, IV_B, IV_NEXT))
    print(msg, Pprime.hex())
