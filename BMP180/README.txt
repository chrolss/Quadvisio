BMP085 C++ Library
==================
Version 0.1.1

Copyright 2013 M. Eriksen
Creative Commons Attribution 4.0 International License.
http://creativecommons.org/licenses/by/4.0/

To try the demo program, "make", then run ./demo.  You will need the kernel
i2c-dev module loaded.  Note that some older pi's use a different device node;
that is hardcoded in the demo (see line ~53 in demo.cpp).  If you are not using
a BMP085 with the breakout board from Adafruit, you will probably also have to
set the correct I2C address for the device (see constructor args in BMP085.hpp).

API documentation is in the header (BMP085.hpp).

Bosch Sensortec's datasheet for the BMP085 is not redistributable by me, nor can
it be found on their site, but it is available from retailers such as Sparkfun
and Adafruit:

http://www.adafruit.com/datasheets/BMP085_DataSheet_Rev.1.0_01July2008.pdf
https://www.sparkfun.com/datasheets/Components/General/BST-BMP085-DS000-05.pdf

Note the Sparkfun one looks to be a later revision.

Contact: devk@cognitivedissonance.ca
