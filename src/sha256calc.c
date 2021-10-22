#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <openssl/sha.h>
#include <stddef.h>
#include <string.h>


void sha256_hash_string (char hash[SHA256_DIGEST_LENGTH], char outputBuffer[65])
{
    int i = 0;

    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", (unsigned char)hash[i]);
    }

    outputBuffer[64] = 0;
}


void sha256(char *string, char outputBuffer[65])
{
    unsigned char  hash[SHA256_DIGEST_LENGTH];
    int len;
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

	len=strlen(string);
    SHA256_Update(&sha256, string,len);
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", (unsigned char)hash[i]);
    }
    outputBuffer[64] = 0;
}

int sha256_file(char *path, char outputBuffer[65])
{
    FILE *file = fopen(path, "rb");
    if(!file) return -534;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    const int bufSize = 32768;
    unsigned char *buffer = malloc(bufSize);
    int bytesRead = 0;
    if(!buffer) return ENOMEM;
    while((bytesRead = fread(buffer, 1, bufSize, file)))
    {
        SHA256_Update(&sha256, buffer, bytesRead);
    }
    SHA256_Final(hash, &sha256);

    sha256_hash_string(hash, outputBuffer);
    fclose(file);
    free(buffer);
    return 0;
}
