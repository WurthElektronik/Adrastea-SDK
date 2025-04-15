// /*
//  ***************************************************************************************************
//  * Würth Elektronik eiSos GmbH & Co. KG
//  * https://www.we-online.com
//  *
//  * THE SOFTWARE INCLUDING THE SOURCE CODE IS PROVIDED “AS IS”. YOU ACKNOWLEDGE THAT WÜRTH ELEKTRONIK
//  * EISOS MAKES NO REPRESENTATIONS AND WARRANTIES OF ANY KIND RELATED TO, BUT NOT LIMITED
//  * TO THE NON-INFRINGEMENT OF THIRD PARTIES’ INTELLECTUAL PROPERTY RIGHTS OR THE
//  * MERCHANTABILITY OR FITNESS FOR YOUR INTENDED PURPOSE OR USAGE. WÜRTH ELEKTRONIK EISOS DOES NOT
//  * WARRANT OR REPRESENT THAT ANY LICENSE, EITHER EXPRESS OR IMPLIED, IS GRANTED UNDER ANY PATENT
//  * RIGHT, COPYRIGHT, MASK WORK RIGHT, OR OTHER INTELLECTUAL PROPERTY RIGHT RELATING TO ANY
//  * COMBINATION, MACHINE, OR PROCESS IN WHICH THE PRODUCT IS USED. INFORMATION PUBLISHED BY
//  * WÜRTH ELEKTRONIK EISOS REGARDING THIRD-PARTY PRODUCTS OR SERVICES DOES NOT CONSTITUTE A LICENSE
//  * FROM WÜRTH ELEKTRONIK EISOS TO USE SUCH PRODUCTS OR SERVICES OR A WARRANTY OR ENDORSEMENT
//  * THEREOF
//  *
//  * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
//  * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE (license_terms_wsen_sdk.pdf)
//  * LOCATED IN THE ROOT DIRECTORY OF THIS DRIVER PACKAGE.
//  *
//  * COPYRIGHT (c) 2025 Würth Elektronik eiSos GmbH & Co. KG
//  *
//  ***************************************************************************************************
//  */

#include "cString.h"



void Uint_To_String(uint32_t *source, int32_t size, char *dest)
{
    int32_t idx = 0;

    for (int32_t i = 0; i < size; i++)
    {
        // Extract each byte from the 32-bit integer
        for (int shift = 24; shift >= 0; shift -= 8)
        {
            char c = (source[i] >> shift) & 0xFF;
            if (c != '\0' && c != 0xff)
            {
                dest[idx++] = c;
            }
            if (c == 0xFF)
            {
                dest = (char *)realloc(dest, (idx + 1) * sizeof(char));
                dest[idx] = '\0';
                return;
            }
        }
    }

    dest[idx] = '\0';
}

int32_t Search_Text(char *source[], int32_t size, char *dest)
{
    for (int32_t i = 0; i < size; i++)
    {
        if (strcmp(source[i], dest) == 0)
        {
            return i; 
        }
    }
    return -1; 
}

 Replace_DoubleQuotes_With_SingleQuotes(char *source)
 {
      while (*source) {
        if (*source == '"') {
            *source = '\''; 
        }
        source++;
    }

 }

void Replace_DoubleQuotes_With_Escape(char *source, char *dest) {
    while (*source) {
        if (*source == '\"') {
            *dest++ = '\\';  
            *dest++ = '\"';
        } else {
            *dest++ = *source;
        }
        source++;
    }
    *dest = '\0'; 
}