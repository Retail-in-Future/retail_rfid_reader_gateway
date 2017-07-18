retail_rfid_reader_gateway
==================

The gateway between device of rfid and AWS IoT cloud.

## How to build

### Dependencies

* gcc > 4.8.1 with C++11 standard support fully
* autoconf
* automake
* libtool
* boost > 1.6.0
* aws iot device sdk for c++
* pthread
* openssl > 1.0.2k
* cpputest

### Build method

After you cloned source code, you can build it with autoconf toolset.

```bash
$ autoreconf -i
$ mkdir build
$ cd build
$ ../configure --enable-tests
$ make 
$ VERBOSE=1 make check
```
