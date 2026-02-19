#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bitmask Definitions
#define READ    0x01  // 00000001 (1) 
#define WRITE   0x02  // 00000010 (2)
#define EXECUTE 0x04  // 00000100 (4)
#define DELETE  0x08  // 00001000 (8)
#define ADMIN   0x80  // 10000000 (128)

