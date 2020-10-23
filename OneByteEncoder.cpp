#include <iostream>
#include<Windows.h>
#include <stdlib.h>
using namespace std;

struct FileInfo
{
	LPVOID fileData = 0;
	DWORD fileSize = 0;

}ReadedFile;

void usage() {
	printf("\nOne Byte Encription Usage\n\npython3 oneByteEncription[-e / -d] File_Path -k key\n\n- e = > Encode\n- d = > Decode\n- k = > key\n\noutput file name : oneByteEncoder.output\n\nAuthor : Murat ERDEM\nSite : muraterdem.org\n\n");
}

void fileReader(char* filename) {
	HANDLE fileHandle;
	fileHandle = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (fileHandle == INVALID_HANDLE_VALUE) {
		if (GetLastError() == 2) {
			cout << "File not found." << endl;
		}
		else {
			cout << "Open file failed. Error Code: " << GetLastError();
		}
		exit(3);
	}

	DWORD fileSize = GetFileSize(fileHandle, NULL);

	LPVOID fileData = HeapAlloc(GetProcessHeap(), 0, fileSize);

	if (fileData == NULL) {
		cout << "No Memory Reserved for File." << endl;
		exit(3);
	}

	DWORD bytesRead;

	bool r = ReadFile(fileHandle, fileData, fileSize, &bytesRead, NULL);
	ReadedFile.fileSize = fileSize;
	ReadedFile.fileData = fileData;
}

void fileWrite(char * data) {

	HANDLE file = CreateFile(L"oneByteEncoder.output", GENERIC_READ | GENERIC_WRITE, 0, NULL, 2, 0x80, NULL);
	DWORD  written;
	bool donen = WriteFile(file, data, ReadedFile.fileSize, &written, NULL);
	CloseHandle(file);
}


void OneByteEncoder(char* filename, int key) {
	fileReader(filename);
	char* data;
	data = new char [ReadedFile.fileSize];
	data = (char*)ReadedFile.fileData;
	for (int i = 0; i < ReadedFile.fileSize; i++) {
		data[i] = data[i] ^ key;
		key = data[i];
	}
	fileWrite(data);
	
}



void OneByteDecoder(char* filename, int key) {
	fileReader(filename);
	char* data;
	data = new char[ReadedFile.fileSize];
	data = (char*)ReadedFile.fileData;
	int deger;
	for (int i = 0; i < ReadedFile.fileSize; i++) {
		deger = data[i];
		data[i] = data[i] ^ key;
		key = deger;
	}
	fileWrite(data);
}



int main(int argc, char* argv[])
{
	int key, operationType = 0;
	char* p;
	bool singleUse = false;
	char* FileName=0;
	HANDLE fileHandle;
	cout << "\nAuthor: https://github.com/moncasp \n\n";

	if (argc != 5) {
		usage();
		return 0;
	}
	else {
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-k") == 0) {
				if (i != argc - 1) {
					long conv = strtol(argv[4], &p, 10);
					key = conv;
				}
				else usage();
			}
			if (strcmp(argv[i], "-e") == 0) {
				if (operationType == 0) {
					operationType = 1;
					if (i != argc - 1) FileName = argv[i + 1];
					else usage();
				}
				else {
					cout << "The -e and -d parameters cannot be used together\n\n";
					exit(3);
				}
			}
			if (strcmp(argv[i], "-d") == 0) {
				if (operationType == 0) {
					operationType = 2;
					if (i != argc - 1) FileName = argv[i + 1];
					else usage();
				}
				else {
					cout << "The -e and -d parameters cannot be used together\n\n";
					exit(3);
				}
			}
		}
		if (operationType == 1) {
			printf("One Byte Encoder Started....\n");
			OneByteEncoder(FileName, key);
			printf("One Byte Encoder Is Over\n");
		}
		else if (operationType == 2) {
			printf("One Byte Decoder Started....\n");
			OneByteDecoder(FileName, key);
			printf("One Byte Decoder Is Over\n");
		}
		else cout << "Use one of the -e and -d parameters\n";
	}

	return 0;

}








