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
//  * COPYRIGHT (c) 2024 Würth Elektronik eiSos GmbH & Co. KG
//  *
//  ***************************************************************************************************
//  */
#ifndef CSTRING_H_
#define CSTRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Converts an unsigned integer to a string.
 *
 * Converts an unsigned 32-bit integer to its string representation and stores
 * the result in the destination buffer.
 *
 * @param source Pointer to the unsigned integer to be converted.
 * @param size Size of the destination buffer.
 * @param dest Pointer to the destination character buffer.
 */
void Uint_To_String(uint32_t *source, int32_t size, char *dest);

/**
 * @brief Searches for a target string in an array of strings.
 *
 * Searches for the target string (`dest`) in the given array of strings (`source`)
 * and returns the index of the first match.
 *
 * @param source Array of strings to search.
 * @param size Number of strings in the array.
 * @param dest Target string to find.
 * @return Index of the target string if found, -1 otherwise.
 */
int32_t Search_Text(char *source[], int32_t size, char *dest);

/**
 * @brief Replaces double quotes with single quotes in a string.
 *
 * Scans the input string and replaces all double quotes (`"`) with single quotes (`'`).
 *
 * @param source Pointer to the input string.
 */
void Replace_DoubleQuotes_With_SingleQuotes(char *source);

/**
 * @brief Replaces double quotes with escape sequences in a string.
 *
 * Replaces all double quotes (`"`) in the source string with escaped double quotes (`\"`)
 * and writes the result into the destination buffer.
 *
 * @param source Pointer to the input string.
 * @param dest Pointer to the destination buffer to store the escaped string.
 */
void Replace_DoubleQuotes_With_Escape(char *source, char *dest);

#ifdef __cplusplus
}
#endif

#endif /* CSTRING_H_ */