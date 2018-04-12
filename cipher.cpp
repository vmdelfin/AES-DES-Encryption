#include <string>
#include <iostream>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */

	 string aes = "AES";
 	 string des = "DES";
	 string enc = "ENC";
	 string dec = "DEC";
	 string current_cipher = argv[1];
	 string current_key = argv[2];
	 string current_op = argv[3];
	 string in = argv[4];
	 string out = argv[5];
	 ofstream outfile;
	 string plaintext, ciphertext;
	 unsigned char* key = new unsigned char;
	 fstream infile(argv[4], fstream::in);

	 // read the plaintext
	 getline(infile, plaintext);

	 cout << "plaintext: " << plaintext << endl;
	 cout << "**************\n" << endl;

	 // covert plaintext string to unsigned char*
	 int n = plaintext.length() - 1;
	 cout << "plaintext length: " << n+1 << endl;

	 // close the input file
	 infile.close();

	 // open output file
	 outfile.open(out);

	 // check arguments
	 cout << "**************\n";
	 cout << "cipher: " << argv[1] << endl;
	 cout << "key: " << argv[2] << endl;
	 cout << "ENC/DEC: " << argv[3] << endl;
	 cout << "input file: " << argv[4] << endl;
	 cout << "output file: " << argv[5] << endl;

	/* Create an instance of the DES cipher */
	CipherInterface* cipher = NULL;

	if(argc < 6)
	{
		cout << "incorrect execution: \n";
		cout << "correct: ./cipher <CIPHER NAME> <KEY> <ENC/DEC> ";
		cout << "<INPUT FILE> <OUTPUT FILE>\n";
		cout << "valid ciphers: DES, AES\n";
	}
	else if(current_cipher.compare(aes) == 0)
	{
		/* Create an instance of the AES cipher */
		cipher = new AES();

	}
	else if(current_cipher.compare(des) == 0)
	{
		/* Create an instance of the DES cipher */
		cipher = new DES();
	}
	else
	{
		// if cipher cannot be found
		cout << "Non-valid choice of cipher\n" << endl;
	}


	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	else
	{
		/* Set the encryption key
		 * A valid key comprises 16 hexidecimal
		 * characters. Below is one example.
		 * Your program should take input from
		 * command line.
		 */

		 cout << "key length: " << current_key.length() << endl;

		 if(current_cipher.compare(des) == 0)
		 {
			 // check the key, then check
			 if(current_key.length() != 16)
			 {
				 cout << "Invalid DES key! Must be 64bit (16 characters) hexidecimal characters\n";
				 exit(1);
			 }
			 else
			 {
				 cout << "current key: ";
				 for(int i = 0; i < 16; i++)
				 {
					 	if(isxdigit(current_key[i]))
						{
							key[i] = current_key[i];
							cout << key[i];
						}
				 }
				 cout << endl;
				 cipher->setKey(key);
			 }

			 // perform encryption
			 if(current_op.compare(enc) == 0)
	 		 {
	 				/* Perform encryption */
	 				unsigned char* cipherText = new unsigned char;

	 				for(int i = 0; i < n; i+=8)
	 				{
	 					// encrypt from i to i + 8
	 					cout << "i: " << i << endl;
	 					unsigned char* current_block = new unsigned char;
	 					cout << "***current block: ";
	 					for(int j = 0; j < 8; j++)
	 					{
	 						current_block[j] = plaintext[i + j];
	 						cout << current_block[j];
	 					}
	 					cout << endl;

	 					cipherText = cipher->encrypt(current_block);

	 					cout << "***ciphertext from this block: ";
	 					for(int i = 0; i < 8; i++)
	 					{
	 						outfile << cipherText[i];
	 						cout << cipherText[i];
	 					}
	 					cout << endl;

	 				}

	 				cout << "encryption finished successfully\n";

	 				outfile.close();
	 			}
				else if(current_op.compare(dec) == 0)
	 			{
	 				/* Perform decryption */
	 				unsigned char* cipherText = new unsigned char;

	 				for(int i = 0; i < n; i+=8)
	 				{
	 					// encrypt from i to i + 8
	 					cout << "i: " << i << endl;
	 					unsigned char* current_block = new unsigned char;
	 					cout << "***current block: ";
	 					for(int j = 0; j < 8; j++)
	 					{
	 						current_block[j] = plaintext[i + j];
	 						cout << current_block[j];
	 					}
	 					cout << endl;

	 					cipherText = cipher->decrypt(current_block);

	 					cout << "***ciphertext from this block: ";
	 					for(int i = 0; i < 8; i++)
	 					{
	 						outfile << cipherText[i];
	 						cout << cipherText[i];
	 					}
	 					cout << endl;

	 				}

	 				cout << "decryption finished successfully\n";

	 				outfile.close();
	 			}

		 }
		 else if(current_cipher.compare(aes) == 0)
		 {
			 // check then set the AES key
			 if(current_key.length() != 32)
			 {
				 cout << "Invalid AES key! Must be 128bit (32 characters) hexidecimal characters\n";
				 exit(1);
			 }
			 else
			 {
				 if(current_op.compare(enc) == 0)
				 {
					 // set first char of key to 0 for encrypt
					 key[0] = 0;
				 }
				 else
				 {
					 // set first char of key to 1 for decrypt
					 key[0] = 1;
				 }


				 cout << "current key: ";
				 for(int i = 1; i < 33; i++)
				 {
					 	if(isxdigit(current_key[i-1]))
						{
							key[i] = current_key[i-1];
							cout << key[i];
						}
				 }
				 cout << endl;
				 cipher->setKey(key);
				 cout << "key set successfully" << endl;

				 // AES encryption
				 // perform encryption
				 if(current_op.compare(enc) == 0)
		 		 {
		 				/* Perform encryption */
		 				unsigned char* cipherText = new unsigned char[16];

		 				for(int i = 0; i < n; i+=16)
		 				{
		 					// encrypt from i to i + 8
		 					cout << "i: " << i << endl;
		 					unsigned char* current_block = new unsigned char;
		 					cout << "***current block: ";
		 					for(int j = 0; j < 16; j++)
		 					{
		 						current_block[j] = plaintext[i + j];
		 						cout << current_block[j];
		 					}
		 					cout << endl;

		 					cipherText = cipher->encrypt(current_block);
							cout << "encryption successful.\n";

		 					cout << "***ciphertext from this block: ";
		 					for(int i = 0; i < 16; i++)
		 					{
		 						outfile << cipherText[i];
		 						cout << cipherText[i];
		 					}
		 					cout << endl;

		 				}

		 				cout << "encryption finished successfully\n";

		 				outfile.close();

						//exit(1);
		 			}
					else if(current_op.compare(dec) == 0)
		 			{
		 				/* Perform decryption */

		 			}



				 // quit for now to avoid error dump
				 exit(1);
			 }


		 }
		 else
			{
				cout << "Invalid operation: must be ENC/DEC for encrypt/decrypt\n";
			}
	}

	//system("pause");
	return 0;
}
