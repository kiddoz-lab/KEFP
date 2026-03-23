# KEFP: KiddoZ Encrypted File Package (V2.0)

[![Licence: KiddoZ Freedom](https://img.shields.io/badge/KiddoZ_Freedom-Licence-red.svg)](https://github.com/kiddoz-lab/KEFP/?tab=License-1-ov-file#kiddoz-public-license-v10)

## Introduction

**KEFP** is a high-performance command-line suite designed for secure file transport and archival. It is the flagship encryption tool of the **KiddoZ Lab**.

<ins>***KEFP is a tool to encrypt and decrypt your files***</ins>, and <ins>entire folders into one file</ins>. It is *lightweight*, the **Base85/Z85 we use for encryption is highly effective**, and the **software does not break your files**.

> *Base85/Z85 is a specific, optimized variant of Base85 encoding designed by **ZeroMQ** to represent binary data as printable ASCII text.*

---

# How it works

## Encryption Pipeline

1. **Package:** Folders and files are flattened into a structured binary stream.
2. **Compress:** Data is shrunk using the KiddoZ high-ratio algorithm and ZIP compression.
3. **Z85 Encode:** Binary data is converted to **Base85 ASCII text** for maximum security and transport efficiency.
4. **JSON Wrap:** Metadata is added to ensure the package is recognizable by the KiddoZ ecosystem.

## Decryption Pipeline

1. **JSON Unwrap:** Metadata is parsed and removed to reveal the original file structure.
2. **Z85 Decode:** Z85 ASCII text is converted back into raw binary data.
3. **Decompress:** Data is expanded back to its original bit-size using the inverse KiddoZ algorithm.
4. **Unpackage:** The structured stream is reconstructed into the original folder tree or individual files.

---

### Installation & Usage

1. Download the **kefp-installer.exe** from the releases.
2. Run the installer to set up the environment variables.
3. Use the following commands in your terminal:
   - `kefp --encrypt [path] -o [output]`
   - `kefp --decrypt [file] -o [path]`

---

### Licensing
KEFP is released under the **KiddoZ Freedom License**. You are free to use, modify, and distribute this software as long as the original "KiddoZ Lab" credits remain in the source.

---

Made with **Time** and **Effort** by **KiddoZ Lab**
