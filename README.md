## genkeyx

generates XML `.keyx` files for KeePass and KeePassXC. Quoting from [here](https://keepass.info/help/base/keys.html):

> XML (recommended, default). There is an XML format for key files. KeePass 2.x uses this format by default, i.e. when creating a key file in the master key dialog, an XML key file is created. The syntax and the semantics of the XML format allow to detect certain corruptions (especially such caused by faulty hardware or transfer problems), and a hash (in XML key files version 2.0 or higher) allows to verify the integrity of the key. This format is resistant to most encoding and new-line character changes (which is useful for instance when the user is opening and saving the key file or when transferring it from/to a server). Such a key file can be printed (as a backup on paper), and comments can be added in the file (with the usual XML syntax: `<!-- ... -->`). It is the most flexible format; new features can be added easily in the future.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<KeyFile>
    <Meta>
        <Version>2.0</Version>
    </Meta>
    <Key>
        <Data Hash="8488960D">
            D2081287 83DB6F20 F38B6740 71FDE861
            7A0CAF1B CA38138E A7A7F515 02672820
        </Data>
    </Key>
</KeyFile>
```
