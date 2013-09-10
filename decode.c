#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void capKey(char[]);
int addKey(char[]);
void makeCipher();
int charIsInCipher(char,  int);
int findChar(char);

char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char cipher[26];
int length;

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stdout, "Usage:\ndecode key\n");
		return 0;
	}
	capKey(argv[1]);
	length = addKey(argv[1]);
	makeCipher();
	char c;
	while((c=fgetc(stdin)) != EOF){
		if(isalpha(c)){
			// If c is an alphabetic character, find it's position in the cipher ('pos')
			// and write the letter in the alphabet at 'pos' to stdout
			int pos = findChar(c);
			c = alphabet[pos];
		}
		fputc(c, stdout);
	}
	return 0;
}

// Convert the key to capital letters
void capKey (char argv[]){
	int i = 0;
	int keylen = strlen(argv);
	while(i < keylen){
		argv[i] = toupper(argv[i]);
		i++;
	}
}

// Add the key to the cipher array, removing any duplicate characters
int addKey(char argv[]){
	int keyLength = strlen(argv);
	int cipherIndex = 0;
	int keyIndex = 0;
	while(cipherIndex < keyLength){
		int inCipher = charIsInCipher(argv[keyIndex], cipherIndex);
		if(!isalpha(argv[keyIndex])){
					// Don't add non-alphabet characters to the cipher
					keyIndex++;
				}
		else if(inCipher == 1){
			// Character was found already in the cipher, do not add it again.
			// Move to the next key character and decrement key length
			keyLength--;
			keyIndex++;
		} else if (inCipher == 0){
			// Character was not found already in cipher, add it to cipher
			cipher[cipherIndex++] = argv[keyIndex++];
		}
	}
	// cipherIndex will be the length of the key with duplicate chars removed
	return cipherIndex;
}

void makeCipher(){
	int alphabetIndex = 0;
	int cipherIndex = length;

	while(cipherIndex < 26){
		int inCipher = charIsInCipher(alphabet[alphabetIndex], length);
		if(inCipher == 1){
			// If the character was found already in the cipher, move to the next one
			alphabetIndex++;
		} else if(inCipher == 0){
			// Character was not found in cipher, add it and increment
			cipher[cipherIndex++] = alphabet[alphabetIndex++];
		}
	}
}

int charIsInCipher(char c, int len){
	int keyIndex = 0;
	// Check all chars in cipher up to 'len'-th index
	// If 'c' is encountered in cipher, return 1 to indicate it was found
	while(keyIndex < len){
		if(cipher[keyIndex++] == c){
			return 1;
		}
	}
	return 0;
}

// Return the character's position in the cipher array (or -1 if it wasn't found but that shouldn't happen)
int findChar(char c){
	int i = 0;
	while(i < 26){
		if(cipher[i] == c){
			return i;
		}
		i++;
	}
	return -1;
}
