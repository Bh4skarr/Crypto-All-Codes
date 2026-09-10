# Crypto Lab Codes

This repository contains separate C programs for common classical ciphers.

## Files

- monoalphabetic.c - monoalphabetic substitution cipher
- caesar.c - Caesar cipher
- vigenere.c - Vigenere cipher
- hill.c - Hill cipher using a 2x2 key matrix
- playfair.c - Playfair cipher
- rail_fence.c - Rail fence cipher
- double_transposition.c - double columnar transposition cipher

## Compile

Use any C compiler. Example with GCC:

```bash
gcc monoalphabetic.c -o monoalphabetic
gcc caesar.c -o caesar
gcc vigenere.c -o vigenere
gcc hill.c -o hill
gcc playfair.c -o playfair
gcc rail_fence.c -o rail_fence
gcc double_transposition.c -o double_transposition
```

## Notes

- The programs are kept as separate files so each cipher can be compiled and run independently.
- To publish on GitHub, create a repository and push this folder with git after adding a remote.