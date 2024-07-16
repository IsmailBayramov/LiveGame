#include "status_events.h"

void select_status_events(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    char input[10];
    printf("Insert the number of records or leave empty to output all of them: ");
    getchar();
    fgets(input, sizeof(input), stdin);

    // Remove newline character
    input[strcspn(input, "\n")] = 0;

    int limit = 0;  // 0 means no limit
    if (strlen(input) > 0) {
        limit = atoi(input);
    }

    StatusEvent event;
    int count = 0;
    printf("%-10s %-10s %-10s %-12s %-10s\n", "Event ID", "Module ID", "New Status", "Date", "Time");
    printf("-------------------------------------------------------------\n");
    while (fread(&event, sizeof(StatusEvent), 1, file)) {
        printf("%-10d %-10d %-10d %-12s %-10s\n", event.event_id, event.module_id, event.new_status,
               event.date, event.time);
        count++;
        if (limit > 0 && count >= limit) {
            break;
        }
    }

    fclose(file);
}

void insert_status_event(const char *filename, StatusEvent new_event) {
    FILE *file = fopen(filename, "ab");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    fwrite(&new_event, sizeof(StatusEvent), 1, file);
    fclose(file);
    printf("Status event inserted successfully.\n");
}

void update_status_event(const char *filename, int event_id, StatusEvent updated_event) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    StatusEvent event;
    int found = 0;
    while (fread(&event, sizeof(StatusEvent), 1, file)) {
        if (event.event_id == event_id) {
            fseek(file, -sizeof(StatusEvent), SEEK_CUR);
            updated_event.event_id = event_id;
            fwrite(&updated_event, sizeof(StatusEvent), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);
    if (found) {
        printf("Status event updated successfully.\n");
    } else {
        printf("Status event with event_id %d not found.\n", event_id);
    }
}

void delete_status_event(const char *filename, int event_id) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    FILE *temp_file = fopen("temp.db", "wb");
    if (temp_file == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(file);
        return;
    }

    StatusEvent event;
    int found = 0;
    while (fread(&event, sizeof(StatusEvent), 1, file)) {
        if (event.event_id != event_id) {
            fwrite(&event, sizeof(StatusEvent), 1, temp_file);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(filename);
    rename("temp.db", filename);

    if (found) {
        printf("Status event deleted successfully.\n");
    } else {
        printf("Status event with event_id %d not found.\n", event_id);
    }
}
