#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aes.h"

int main(int argc, char* argv[])
{
    /*
    const uint8_t key[] =    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
    const uint8_t buffer[] = { 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0B };
    const uint8_t bufferSize = 17;
    */

    const uint8_t key[] =    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    const uint8_t buffer[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 };
    const uint8_t bufferSize = 18;

    uint8_t* encBuffer = malloc(32);
    uint8_t* decBuffer = malloc(32);

    aes_context AesContext;

    memset( AesContext.ksch, '\0', 240 );
    aes_set_key( key, 16, &AesContext );

    printf("--- encode --> decode ---\n");
    printf("buffer:\t\t");
    for (int r = 0; r < bufferSize; r++) {
        printf("0x%X ", buffer[r]);
    }
    printf("\n");
    /*
     * encryption
     */
    aes_encrypt( buffer, encBuffer, &AesContext );
    // Check if optional CFList is included
    if( bufferSize > 16 )
    {
        aes_encrypt( buffer + 16, encBuffer + 16, &AesContext );
    }

    printf("encBuffer:\t");
    for (int r = 0; r < bufferSize; r++) {
        printf("0x%X ", encBuffer[r]);
    }
    printf("\n");

    /*
     * decryption
     */
    aes_decrypt( encBuffer, decBuffer, &AesContext );
    // Check if optional CFList is included
    if( bufferSize > 16 )
    {
        aes_decrypt( encBuffer + 16, decBuffer + 16, &AesContext );
    }

    printf("decBuffer:\t");
    for (int r = 0; r < bufferSize; r++) {
        printf("0x%X ", decBuffer[r]);
    }
    printf("\n");
    printf("--- encode --> decode ---\n");

    

    printf("--- decode --> encode ---\n");
    printf("buffer:\t\t");
    for (int r = 0; r < bufferSize; r++) {
        printf("0x%X ", buffer[r]);
    }
    printf("\n");

    /*
     * decryption
     */
    aes_decrypt( buffer, decBuffer, &AesContext );
    // Check if optional CFList is included
    if( bufferSize > 16 )
    {
        aes_decrypt( buffer + 16, decBuffer + 16, &AesContext );
    }

    printf("decBuffer:\t");
    for (int r = 0; r < bufferSize; r++) {
        printf("0x%X ", decBuffer[r]);
    }
    printf("\n");

    /*
     * encryption
     */
    aes_encrypt( decBuffer, encBuffer, &AesContext );
    // Check if optional CFList is included
    if( bufferSize > 16 )
    {
        aes_encrypt( decBuffer + 16, encBuffer + 16, &AesContext );
    }

    printf("encBuffer:\t");
    for (int r = 0; r < bufferSize; r++) {
        printf("0x%X ", encBuffer[r]);
    }
    printf("\n");
    printf("--- decode --> encode ---\n");

    free(encBuffer);
    free(decBuffer);

}