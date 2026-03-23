# KEFP: KiddoZ Encrypted File Package (V2.0)

[![Licence: KiddoZ Freedom](https://img.shields.io/badge/KiddoZ_Freedom-Licence-red.svg)](https://github.com/kiddoz-lab/KEFP/?tab=License-1-ov-file#kiddoz-public-license-v10)

## Introduction

**KEFP** is a high-performance command-line suite designed for secure file transport and archival. It is the flagship encryption tool of the **KiddoZ Lab**.

<ins>***KEFP is a tool to encrypt and decrypt your files***</ins>, and <ins>entire folders into one file</ins>. It is *lightweight*, the **Base85/Z85 we use for encryption is highly effective**, and the **software does not break your files**.

 *Base85/Z85 is a specific, optimized variant of Base85 encoding designed by **ZeroMQ** to represent binary data as printable ASCII text* ( this is What Base85 is all about )
 
---

# How it works

## Encryption
1. **Package:** Folders are flattened into a structured binary stream.
2. **Compress:** Data is shrunk using the KiddoZ high-ratio algorithm and zip compressing.
3. **Z85 Encode:** Binary data is converted to **Base85 ASSCII text** for maximum security and transport efficiency.
4. **JSON Wrap:** Metadata is added to ensure the package is recognizable by the KiddoZ ecosystem.

## Decryption
1. **JSON Unwrap:** Metadata is parsed to reveal the original file architecture.
2. **Z85 Decode:** **Base85** strings are converted back into raw binary.
3. **Decompress:** Data is expanded back to its **original bit-size**.
4. **Unpackage:** The structured stream is reconstructed into the original folder tree or file.

---

# Installation & Usage

### Quick Installation
Download the official V2.0 cloud bootstrapper by clicking here:
**[Download kefp-installer.exe](https://github.com/kiddoz-lab/KEFP/raw/refs/heads/main/kefp-installer.exe)**

# Usage Guide (V2.0)

After running the `kefp-installer.exe`, open your terminal (CMD or PowerShell) and use the following commands.

###  Encrypting a file/folder
To turn a folder or a single file into a secure KEFP package:
* **For Folders:** `kefp --encrypt "C:\MyProject" -o "Backup.kefp"`
* **For Single Files:** `kefp --encrypt "MyPhoto.png" -o "LockedPhoto.kefp"`

###  Decrypting a file/folder
To extract your data back to its original state:
* **Restore Folder:** `kefp --decrypt "Backup.kefp" -o "C:\Recovered"`
* **Restore File:** `kefp --decrypt "LockedPhoto.kefp" -o "MyPhoto.png"`

###  Extra Features
* **Text-to-Speech:** `kefp --tts "Welcome to KiddoZ Lab"` (Generates a voice.mp3) using **Google's TTS service**. I dont kow why you guys will use it but... still.
* **Check Version:** `kefp --version` (Confirms you are on V2.0)
* **Update Engine:** `kefp --update` (Updates to the latest KEFP version)
* **Safety Wipe:** `kefp --uninstall` (Type 'DELETE' to confirm)

***

**If you are still stuck use the `kefp --help` command to get the full manual.**

---

### Licensing
KEFP is released under the **KiddoZ Freedom License 1.0**. You are free to use, modify, and distribute this software as long as the original "KiddoZ Lab" credits remain in the source. *READ* the **[full licence here.](https://github.com/kiddoz-lab/KEFP/?tab=License-1-ov-file)**

__Made with `TIME` and `EFFORT` by the **KiddoZ Lab**__