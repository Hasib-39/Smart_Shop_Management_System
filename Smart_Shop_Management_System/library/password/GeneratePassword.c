#pragma once

#include "WjCryptLib_Sha512.c"
#include "WjCryptLib_Sha512.h"
// The credit for the SHA-256 implementation goes to WaterJuice
// Source: https://github.com/WaterJuice/WjCryptLib

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Needs a string pointer to receive the value

char* haSha_512(char* input_string) {
    Sha512Context sha512Context;
    SHA512_HASH sha512Hash;
    uint16_t i;

    Sha512Initialise(&sha512Context);
    Sha512Update(&sha512Context, input_string, (uint32_t)strlen(input_string));
    Sha512Finalise(&sha512Context, &sha512Hash);

    // buffer for hash string
    char* hashed = (char*)malloc(SHA512_HASH_SIZE*2 + 1); 

    for (i = 0; i < sizeof(sha512Hash); i++) {
        // convert each byte to a two-digit hexadecimal string
        sprintf(&hashed[i*2], "%02x", sha512Hash.bytes[i]); 
    }
    
    // terminate the string with a null character
    hashed[sizeof(sha512Hash)*2] = '\0'; 

    return hashed;
}