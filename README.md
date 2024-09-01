# NAME

genkeyx - generate XML .keyx files for KeePass(XC)

# SYNOPSIS

genkeyx \[-o *file*\] \[-v\]

# DESCRIPTION

*genkeyx* creates a 32-byte random value and a SHA256 hash of it and
formats these values as an XML document ready for use in KeePass and/or
KeePassXC.

Quoting from <https://keepass.info/help/base/keys.html>:

> XML (recommended, default). There is an XML format for key files.
> KeePass 2.x uses this format by default, i.e. when creating a key file
> in the master key dialog, an XML key file is created. The syntax and
> the semantics of the XML format allow to detect certain corruptions
> (especially such caused by faulty hardware or transfer problems), and
> a hash (in XML key files version 2.0 or higher) allows to verify the
> integrity of the key. This format is resistant to most encoding and
> new-line character changes (which is useful for instance when the user
> is opening and saving the key file or when transferring it from/to a
> server). Such a key file can be printed (as a backup on paper), and
> comments can be added in the file (with the usual XML syntax:
> `<!-- ... -->`). It is the most flexible format; new features can be
> added easily in the future.

*genkeyx* generates 32 bytes of random data, creates a SHA256 hash of
that, adds the first four bytes of the hash to `Data Hash`, and appends
the prettyfied 32 hexlified bytes to the XML.

# OPTIONS

*genkeyx* understands the following global options:

-o  
Write the XML document into the specified file instead of to *stdout*.

-v  
Show version and exit.

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
