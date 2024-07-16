#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levels.h"
#include "modules.h"
#include "status_events.h"

void select_records();
void insert_record();
void update_record();
void delete_record();
void get_all_active_modules(const char *filename);
void delete_modules_by_ids(const char *filename);
void set_protected_mode(const char *filename);

#endif