#include <iostream>
#include <string>
#include <unordered_map>

#include "args.h"

// Morse table for decoding
static std::unordered_map<std::string, std::string> morse_table = {
    {".-", "A"}, {"-...", "B"}, {"-.-.", "C"}, {"-..", "D"}, {".", "E"},
    {"..-.", "F"}, {"--.", "G"}, {"....", "H"}, {"..", "I"}, {".---", "J"},
    {"-.-", "K"}, {".-..", "L"}, {"--", "M"}, {"-.", "N"}, {"---", "O"},
    {".--.", "P"}, {"--.-", "Q"}, {".-.", "R"}, {"...", "S"}, {"-", "T"},
    {"..-", "U"}, {"...-", "V"}, {".--", "W"}, {"-..-", "X"}, {"-.--", "Y"},
    {"--..", "Z"}, {".----", "1"}, {"..---", "2"}, {"...--", "3"},
    {"....-", "4"}, {".....", "5"}, {"-....", "6"}, {"--...", "7"},
    {"---..", "8"}, {"----.", "9"}, {"-----", "0"}
};

// Reverse table for encoding
static std::unordered_map<char, std::string> reverse_morse_table = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
    {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
    {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
    {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
    {'Z', "--.."}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
    {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
    {'8', "---.."}, {'9', "----."}, {'0', "-----"}
};

// Encrypt function
std::string encrypt(const std::string &text) {
    std::string cipher;
    for (size_t i = 0; i < text.length(); ++i) {
        if (const char c = text[i]; c != ' ') {
            cipher += reverse_morse_table[static_cast<char>(toupper(c))] + " ";
        } else {
            cipher.pop_back();  // Remove trailing space before adding a slash
            cipher += " / ";      // Add a slash for word separation
        }
    }
    if (!cipher.empty() && cipher.back() == ' ') {
        cipher.pop_back(); // Remove trailing space at the end
    }
    return cipher;
}

// Decrypt function
std::string decrypt(const std::string& text) {
    std::string decipher;
    std::string citext;
    for (size_t i = 0; i < text.length(); ++i) {
        if (const char c = text[i]; c == '/') {
            if (!citext.empty()) {
                decipher += morse_table[citext];
                citext.clear();
            }
            decipher += " "; // Add a space for word separation
        } else if (c == ' ') {
            if (!citext.empty()) {
                decipher += morse_table[citext];
                citext.clear();
            }
        } else {
            citext += c;
        }
    }
    if (!citext.empty()) {
        decipher += morse_table[citext];
    }
    return decipher;
}

int main(int argc, char **argv) {
    args::ArgumentParser parser("Morse Code Encryptor/Decryptor made by jeb47");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::Flag encryptFlag(parser, "encrypt", "Encrypt the input text", {"encrypt"});
    args::Flag decryptFlag(parser, "decrypt", "Decrypt the input Morse code", {"decrypt"});
    args::PositionalList<std::string> inputText(parser, "input", "Input text or Morse code");

    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Help&) {
        std::cout << parser;
        return 0;
    } catch (args::ParseError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if (!encryptFlag && !decryptFlag) {
        std::cerr << "Error: You must specify either --encrypt or --decrypt." << std::endl;
        return 1;
    }

    std::string input = args::get(inputText).empty() ? "" : args::get(inputText)[0];
    for (size_t i = 1; i < inputText.Get().size(); ++i) {
        input += " " + inputText.Get()[i];
    }

    if (encryptFlag) {
        std::cout << encrypt(input) << std::endl;
    } else if (decryptFlag) {
        std::cout << decrypt(input) << std::endl;
    }

    return 0;
}

