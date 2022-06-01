# SHA512 C++ implementation  
Implementation of a cryptographic hash function written in C++. SHA512 belongs to a SHA-2 family. It was designed by NSA and published in 2001.  
Produced hash value is of size 512 bits.  
Implementation is based on SHA-512 pseudocode.  

### SHA512 sum app    
One can compile and use program to calcualte SHA512 sum:  
```
g++ src/SHA512app.cpp src/SHA512.cpp -o sha512app
```
Two supported operations are:  
- file hash with -f/-file option and file name  
- string hash with -s/-string option and string  

### SHA512 in your C++ code  
All you have to do to use this SHA512 implementation is:  
- include header  
```
#include "SHA512.h"
```
- create class object and use preferred method  
```
SHA512 sha512;
sha512.hashString("string");
sha512.hashFile("fileName");
```
- compile your project with SHA512.cpp and link object files  
```
g++ yourProgram.cpp SHA512.cpp -o yourProgram
```

### Project's limitations
Because size() returns 64-bits value of type size_t only the hash of files and strings which sizes are not bigger than 64 bits can be calculated.  
