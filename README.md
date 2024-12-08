# morse-cli
A quick project I made that encrypts/decrypts morse code

## Compile
```bash
g++ morse-cli.cpp -o morse-cli
```
This command should compile the `morse-cli.cpp` file, including it's dependency `args.h`

## Using morse-cli
morse-cli help output
```bash
./morse-cli -h
morse-cli {OPTIONS} [input...]

    Morse Code Encryptor/Decryptor made by jeb47

  OPTIONS:

      -h, --help                        Display this help menu
      --encrypt                         Encrypt the input text
      --decrypt                         Decrypt the input Morse code
      input...                          Input text or Morse code
      "--" can be used to terminate flag options and force all following
      arguments to be treated as positional options
```

### Encrypting a message:
```bash
./morse-cli --encrypt hello world
.... . .-.. .-.. --- / .-- --- .-. .-.. -..
```
Usage of quotes `" or '` is required for larger inputs

### Decrypting a message:
```bash
./morse-cli --decrypt ".... . .-.. .-.. --- / .-- --- .-. .-.. -.."
HELLO WORLD
```
Usage of quotes `" or '` is required because dots (`.`) usually refer to directories for most shells
