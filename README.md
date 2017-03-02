# A simple radio data logger

Receives data from the radio group 0b01100110 and dumps it
on the serial port. Data is printed using a hex dump checking
for printable characters and with an index.

```
DATA 000000: 4556 454e 5420 5449 4c54 4544 204c 4546  EVENT TILTED LEF
DATA 000010: 54                                       T
```

(c) 2016 Calliope gGmbH

Licensed under the Apache Software License 2.0, see LICENSE.