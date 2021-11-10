```
Build

    cmake CMakeList.txt
    make
```
```
Usage

    ./mtctl [options] "Command"

Options

    -v --verbose	print log
    -u, --usec	    use usec (default is sec)
*   -d, --delay	    command delay time (waiting after send)
*   -c, --count	    command repeat count
*   -l, --len       (Byte)length of command
*   -b, --boudrate	serial port speed
*   -p, --port	    serial port path

    (You must use the options marked with *)

Command

    See the pelco-D(7 byte) or pelco-P(8 byte) protocol.
    It contains the function to verify the checksum.

Example

    (tilt-up)
    ./mtctl -v -l 7 -u -d 150000 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 08 20 20 49'
    ./mtctl -v -l 7 -u -d 1 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 00 00 00 01'

    (tilt-down)
    ./mtctl -v -l 7 -u -d 150000 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 10 20 20 51'
    ./mtctl -v -l 7 -u -d 1 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 00 00 00 01'

    (pan-left)
    ./mtctl -v -l 7 -u -d 150000 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 04 20 20 45'
    ./mtctl -v -l 7 -u -d 1 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 00 00 00 01'

    (pan-right)
    ./mtctl -v -l 7 -u -d 150000 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 02 20 20 43'
    ./mtctl -v -l 7 -u -d 1 -c 1 -b 2400 -p /dev/ttyUSB0 'FF 01 00 00 00 00 01'
```

```
Script

    vi mt_test.sh
    ------------------
    #!/bin/bash
    command1..
    command2..
    command3..
    ------------------

    chmod +x mt_test.sh
    ./mt_test.sh
```
