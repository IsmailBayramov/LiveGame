#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include <stdio.h>

#include "database.h"

typedef struct {
    int event_id;
    int module_id;
    int new_status;
    char date[11];
    char time[9];
} StatusEvent;

void select_status_events(const char* filename);
void insert_status_event(const char* filename, StatusEvent new_event);
void update_status_event(const char* filename, int event_id, StatusEvent updated_event);
void delete_status_event(const char* filename, int event_id);

#endif