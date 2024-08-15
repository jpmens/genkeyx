---
title: GENKEYX(1) User Manuals
---

# NAME

genkeyx - generate XML .keyx files for KeePass(XC)

# SYNOPSIS

genkeyx \[-o file\]

# DESCRIPTION

*genkeyx* creates a 32-byte random value and a SHA256 hash of it and
formats these values as an XML document ready for use in KeePass and/or
KeePassXC.

If `-o` is specified, *genkeyx* writes the output into the specified
file instead of to *stdout*.

# EXAMPLES

Create an XML keyx document:

    $ genkeyx
    <?xml version="1.0" encoding="UTF-8"?>
    <KeyFile>
        <Meta>
        <Version>2.0</Version>
        </Meta>
        <Key>
        <Data Hash="7CE2614B">
            4C98A7F0 9CA623F7 5E92F566 EE0A70A8 
            21D6ACF4 D645CFDF FFB77A88 73A5E2AB
        </Data>
        </Key>
    </KeyFile>

# BUGS

Maybe not.

# RETURN CODES

*genkeyx* exits with a code 0 on success and non-zero on failure after
indicating what caused the failure.

# AVAILABILITY

<http://github.com/jpmens/genkeyx>

# AUTHOR

Jan-Piet Mens <http://jpmens.net>