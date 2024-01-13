#ifndef _H_USBBLUETOOTH_API_
#define _H_USBBLUETOOTH_API_

#if defined(_WIN32) || defined(__CYGWIN__)
#include <windows.h>
#endif

/* The following macro defines the calling convention for functions.
 * This macro should be placed after the return type and before the function name.
 * This macro should be used in both definition and declaration of a function.
 */
#if defined(_WIN32) || defined(__CYGWIN__)
#define USBBLUETOOTH_CALL WINAPI
#else
#define USBBLUETOOTH_CALL
#endif

#endif