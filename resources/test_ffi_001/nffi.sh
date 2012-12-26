#A script to build a shared library to test FFI support on Clever.
gcc -fPIC -O3 -shared -c nffi.c
gcc -shared -Wl,-soname,nffi.so -o nffi.so nffi.o -lc -ldl


set LD_LIBRARY_PATH=.

./clever  nffi.clv
