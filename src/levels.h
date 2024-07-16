#ifndef LEVELS_H
#define LEVELS_H

#include <stdio.h>

#include "database.h"

typedef struct {
    int memory_level;
    int cell_count;
    int protection_flag;
} Level;

void select_levels(const char* filename);
void insert_level(const char* filename, Level new_level);
void update_level(const char* filename, int memory_level, Level updated_level);
void delete_level(const char* filename, int memory_level);

#endif