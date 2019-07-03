## Signature

It was required to implement a console application for file signature generation. To generate a signature one must divide the file into blocks of fixed size, generate some hash (MD5, CRC32) for each block and write these hashes to the output file.

## Requirements:
* the app has command line arguments for the input file, the output file and the block size; 
* one should optimize the app speed to work in multi-processor environment;
* handle errors with exceptions, use smart ptrs;
* it's not allowed to use external libraries except of boost;
* there could be really big files as input (bigger than RAM).
