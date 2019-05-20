# lightcrafter-firmgen

### Dependencies
* C++ 11
* gcc 9.1

### Building
Ensure gcc is properly configured for your system and, within the source directory, run the following
```
gcc -std=c++11 firmgen.cpp -o firmgen
```

### Usage
Ensure your output executable from the build is located within the same folder as the images you want to add to the
firmware file as well as an empty firmware file title "emptyfrmw.bin" (provided)

and then run
```
./firmgen [options]
```
Viable option flags include
* --uncompress : leave the images uncompressed in the end firmware file. Be advised not all images may be loaded in this case
* --basefile [filename] : specify an empty firmware file other than "emptyfrmw.bin"
* --output [filename] : specify an output file for the built firmware

### Credits
Developed by Jonathan Meade for Elizabeth Strong.   
Property of the University of Colorado, Boulder.  
Adapted from code provided by Texas Instruments Incorporated, which provides the following license.  

```
Copyright (C) {2015} Texas Instruments Incorporated - http://www.ti.com/

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

* Redistributions of source code must retain the above copyright    notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
* Neither the name of Texas Instruments Incorporated nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```
