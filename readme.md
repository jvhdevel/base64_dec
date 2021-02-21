# base64_enc

Base64 encoding is primarily used to store binary data as an ASCII string for
use with ASCII-based applications, e.g. embedding images withing HTML pages.

Base64 encoding is also used for various puzzles and ARGs to encode plain text.

## How it works

The input string is converted into an array of indices. These indices are then
grouped into 24-bit chunks (four 6-bit numbers) and then processed into ASCII
characters (three 8-bit characters).

```
Input   - S       G       V       s
Indices - 18      6       21      44
        - 010010  000110  010101  101100
ASCII   - 01001000   01100101   01101100
Input   - H          e          l
```

The input must be padded (with `=`) to ensure each 24-bit chunk is full.
