#!/usr/bin/env python3

# mk-keyx.py, (C) by Jan-Piet Mens <jp@mens.de>, August 2024

import hashlib
import secrets
import binascii
from string import Template


# reverse engineered from FileKey.cpp, function createXMLv2 in [1]
# [1] https://github.com/keepassxreboot/keepassxc/tree/develop/src/keys/FileKey.cpp 

# create a random array of 32 bytes. Create a SHA256 hash from those, and take
# the left 4 bytes to add to Hash. The remaining bytes are spread out in 8
# groups of 4 hex bytes each

#  <?xml version="1.0" encoding="UTF-8"?>
#  <KeyFile>
#      <Meta>
#          <Version>2.0</Version>
#      </Meta>
#      <Key>
#          <Data Hash="68FD83CF">
#              3671CF5B 10FDE15D 063E4195 6CA8E85D
#              10438C5F 56B00EE8 719B004E F74BB01C
#          </Data>
#      </Key>
#  </KeyFile>

# see also: https://keepass.info/help/base/keys.html

# Using a template here instead of constructing XML because
# we're just adding hex so nothing can happen (famous last--)

xml = """<?xml version="1.0" encoding="UTF-8"?>
<KeyFile>
    <Meta>
        <Version>2.0</Version>
    </Meta>
    <Key>
        <Data Hash="$hash4">
            $bytes1
            $bytes2
        </Data>
    </Key>
</KeyFile>"""

# Generate 32 bytes of randomness
randbytes = secrets.token_bytes(32)
r = binascii.hexlify(randbytes).upper().decode("utf-8")

# Hash the random bytes to create a 4-byte (8 character) string
hexdigest = hashlib.sha256(randbytes).hexdigest().upper()
hash4 = str(hexdigest[0:8])
# print(hash4)

b1=b2=""
for n in range(8):
    if n < 4:
        b1 = b1 + r[n*8:(n+1)*8] + " "
    else:
        b2 = b2 + r[n*8:(n+1)*8] + " "

s = Template(xml).safe_substitute(hash4=hash4, bytes1=b1, bytes2=b1)
print(s)
