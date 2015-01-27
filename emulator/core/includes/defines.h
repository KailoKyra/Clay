#ifndef DEFINES_H
#define DEFINES_H

# define    MHZ             (1000000)
# define    CPU_SPEED       (3.6864*MHZ)

# define    RAM_SIZE        (128*1024)
# define    ROM_SIZE        (32*1024)

# define    HIGH            (1)
# define    LOW             (0)

typedef unsigned char       byte;
typedef unsigned char       bit;        // use this with unions
typedef unsigned short      uint16;
typedef unsigned int        uint32;

#endif // DEFINES_H
