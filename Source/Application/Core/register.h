#ifndef REGISTER_H
#define REGISTER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "f1c100s.h"

typedef signed char                          S8;
typedef unsigned char                        U8;
typedef short                                S16;
typedef unsigned short                       U16;
typedef int                                  S32;
typedef unsigned int                         U32;
typedef long long                            S64;
typedef unsigned long long                   U64;
typedef unsigned char                        BIT;
typedef unsigned int                         BOOL;

u32 REGISTER_Write(u32 addr, u32 data);
u32 REGISTER_Read(u32 addr);

#endif
