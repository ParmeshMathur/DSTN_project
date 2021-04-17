#ifndef MAIN_MEMORY_H
#define MAIN_MEMORY_H

#define VALID 1
#define INVALID 0

#include "pagetable.h"

typedef struct
{
    unsigned int frame_number:16; //TODO: will be removed, frame table indexed by frame number.
    unsigned int pid:16;
    unsigned int page_number:23;
    unsigned int valid_bit:1;
    unsigned int modified_bit:1;
} frame_table_entry;

typedef struct 
{
    frame_table_entry* entry_table[65536];
} frame_table;


typedef struct 
{
    unsigned int entry[128];
} main_memory_block;

typedef struct
{
    frame_table f_table;
    page_table* p_tables[1024]; //CHANGED from 65536 to 1024//
    main_memory_block* blocks[63488]; //65536 - 2048. 1024 each for page table and frame table//
    unsigned int total_access_count;
    unsigned int access_hit_count;
} main_memory;

typedef struct 
{
    unsigned int block_number:16;
    main_memory_block* data;
    second_chance_node* prev;
    second_chance_node* next;
    unsigned int second_chance_bit:1;
} second_chance_node;

typedef struct 
{
    second_chance_node* head;
    second_chance_node* tail;
} second_chance_fifo_queue;


#endif