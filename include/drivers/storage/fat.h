#pragma once

#include <stddef.h>
#include <stdint.h>

#include <drivers/storage/harddrive.h>

// Sector 0 : Master Boot Record
//  -- 0x000 [0x003] : Jump instruction
//  -- 0x003 [0x008] : OEM name
//  --------------------------------
//  Without partition table:
//  -- 0x00B [0x1F2] : Boot code
//  -- 0x1FD [0x001] : Physical drive number
//  With partition table:
//  -- 0x00B [0x1B3] : Unknown
//  -- 0x1BE [0x010] : Partition 0
//  -- 0x1CE [0x010] : Partition 1
//  -- 0x1DE [0x010] : Partition 2
//  -- 0x1EE [0x010] : Partition 3
//  --------------------------------
//  -- 0x1FE [0x002] : Boot sector signature (0x55, 0xAA)
//
// Partition:
//  -- 0x0 [0x1] : Boot flag
//  -- 0x1 [0x3] : CHS begin
//  -- 0x4 [0x1] : Type code (0x0B / 0x0C for FAT32)
//  -- 0x5 [0x3] : CHS end
//  -- 0x8 [0x4] : LBA begin
//  -- 0xC [0x4] : Number of sectors
//
// Volume ID
// TODO :)

struct PARTITION
{
    uint8_t bootflag;
    uint8_t chsbegin[3];
    uint8_t typecode;
    uint8_t chsend[3];
    uint32_t lbabegin;
    uint32_t sectors;
} __attribute__((packed));

struct MBR
{
    uint8_t jumpinstr[0x3];
    uint8_t oemname[0x8];
    uint8_t unknown[0x1B3];
    struct PARTITION part[4];
    uint16_t signature;
} __attribute__((packed));

struct VOLUMEID
{
    uint8_t unknown0[0xB];
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t reservedSectors;
    uint8_t fatCount;
    uint8_t unknown1[0x13];
    uint32_t fatSectors;
    uint8_t unknown2[0x4];
    uint32_t rootDirCluster;
    uint8_t unknown3[0x1CE];
    uint16_t signature;
} __attribute__((packed));

bool fat_init(const struct HARDDRIVE hdd);