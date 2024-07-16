#ifndef MODULES_H
#define MODULES_H

#include <stdio.h>

#include "database.h"

typedef struct {
    int module_id;
    char module_name[30];
    int memory_level;
    int memory_cell;
    int delete_flag;
} Module;

void select_modules(const char* filename);
void insert_module(const char* filename, Module new_module);
void update_module(const char* filename, int module_id, Module updated_module);
void delete_module(const char* filename, int module_id);

#endif