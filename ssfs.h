#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "disk_emu.h"

//#define __BLOCK_SIZE__ 1024
#define __NUM_BLOCKS__ 1024
#define __INODE_SIZE__ (sizeof(inode_t)) //size of each inode in bytes
#define __NUM_BYTES_INODES__ 12864 //total number of bytes for all inodes including root
#define __NUM_INODES__ 224 //total number of inodes, 200 for files, 1 for the root
#define __NUM_BLOCKS_INODES__ 14 //number of blocks required for 201 inodes
#define __NUM_DIRECTORY_NODES__ 224
#define __FILE_NAME_LENGTH__ 16

typedef struct _block_t {
	unsigned char bytes[1024];
} block_t;

typedef struct _inode_t {
	//char name[16];
	int size; 
	int direct[14]; //points to 14 blocks, each block contains a piece of the whole file
	int indirect; //points to the next inode if more blocks are needed
} inode_t;

typedef struct _f_desc {
	int inode;
	int read_ptr;
	int write_ptr;
	int free_bit;
} f_desc;

typedef struct _superblock_t {
	unsigned char magic[4]; //id for the file system
	int b_size; //block size
	int num_blocks; //total number of DATA blocks
	int num_inodes; //total number of inodes in the system
	inode_t root; //the root node for the system
	//char **files;
	//f_desc *fd_tables;
} superblock_t;

typedef struct _dnode_t {
	int node;
	char name[16];
} dnode_t;





void mkssfs(int fresh);
int ssfs_fopen(char *name);	//create file system
int ssfs_close(int fileID); // close given file
int ssfs_frseek(int fileID, int loc); //seek (READ) to the location from the beginning
int ssfs_fwseek(int fileID, int loc); //seel (WRITE) to the location from the beginning
int ssfs_fwrite(int fileID, char *buf, int length); //write buf characters onto disk
int ssfs_fread(int fileID, char *buf, int length); //read chars from disk into buf
int ssfs_remove(char *file); //remove file from file system
