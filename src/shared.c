// S I U P
#include <stdio.h>
#include <stdlib.h>

#include "database.h"

void select_records() {
    printf("Please choose a table:\n");
    printf("  1. Modules\n");
    printf("  2. Levels\n");
    printf("  3. Status events\n");
    printf("> ");

    int table_choice;
    if (scanf("%d", &table_choice) != 1) {
        printf("Invalid input. Returning to main menu.\n");
        return;
    }

    char filename[256];

    switch (table_choice) {
        case 1:
            snprintf(filename, sizeof(filename), "../materials/master_modules.db");
            select_modules(filename);
            break;
        case 2:
            snprintf(filename, sizeof(filename), "../materials/master_levels.db");
            select_levels(filename);
            break;
        case 3:
            snprintf(filename, sizeof(filename), "../materials/master_status_events.db");
            select_status_events(filename);
            break;
        default:
            printf("Invalid choice, returning to main menu.\n");
    }
}

// Примеры реализаций функций, которые можно детализировать в соответствующих файлах

void insert_record() {
    printf("Please choose a table:\n");
    printf("  1. Modules\n");
    printf("  2. Levels\n");
    printf("  3. Status events\n");
    printf("> ");

    int table_choice;
    if (scanf("%d", &table_choice) != 1) {
        printf("Invalid input. Returning to main menu.\n");
        return;
    }

    char filename[256];

    switch (table_choice) {
        case 1: {
            snprintf(filename, sizeof(filename), "../materials/master_modules.db");
            Module new_module;
            printf("Enter module_id: ");
            if (scanf("%d", &new_module.module_id) != 1) {
                printf("Invalid module_id input. Returning to main menu.\n");
                return;
            }
            printf("Enter module_name: ");
            if (scanf("%s", new_module.module_name) != 1) {
                printf("Invalid module_name input. Returning to main menu.\n");
                return;
            }
            printf("Enter memory_level: ");
            if (scanf("%d", &new_module.memory_level) != 1) {
                printf("Invalid memory_level input. Returning to main menu.\n");
                return;
            }
            printf("Enter cell_number: ");
            if (scanf("%d", &new_module.memory_cell) != 1) {
                printf("Invalid cell_number input. Returning to main menu.\n");
                return;
            }
            printf("Enter delete_flag: ");
            if (scanf("%d", &new_module.delete_flag) != 1) {
                printf("Invalid delete_flag input. Returning to main menu.\n");
                return;
            }
            insert_module(filename, new_module);
            break;
        }
        case 2: {
            snprintf(filename, sizeof(filename), "../materials/master_levels.db");
            Level new_level;
            printf("Enter memory_level: ");
            if (scanf("%d", &new_level.memory_level) != 1) {
                printf("Invalid memory_level input. Returning to main menu.\n");
                return;
            }
            printf("Enter cell_count: ");
            if (scanf("%d", &new_level.cell_count) != 1) {
                printf("Invalid cell_count input. Returning to main menu.\n");
                return;
            }
            printf("Enter protection_flag: ");
            if (scanf("%d", &new_level.protection_flag) != 1) {
                printf("Invalid protection_flag input. Returning to main menu.\n");
                return;
            }
            insert_level(filename, new_level);
            break;
        }
        case 3: {
            snprintf(filename, sizeof(filename), "../materials/master_status_events.db");
            StatusEvent new_event;
            printf("Enter event_id: ");
            if (scanf("%d", &new_event.event_id) != 1) {
                printf("Invalid event_id input. Returning to main menu.\n");
                return;
            }
            printf("Enter module_id: ");
            if (scanf("%d", &new_event.module_id) != 1) {
                printf("Invalid module_id input. Returning to main menu.\n");
                return;
            }
            printf("Enter new_status: ");
            if (scanf("%d", &new_event.new_status) != 1) {
                printf("Invalid new_status input. Returning to main menu.\n");
                return;
            }
            printf("Enter date (dd.mm.yyyy): ");
            if (scanf("%10s", new_event.date) != 1) {
                printf("Invalid date input. Returning to main menu.\n");
                return;
            }
            printf("Enter time (hh:mm:ss): ");
            if (scanf("%8s", new_event.time) != 1) {
                printf("Invalid time input. Returning to main menu.\n");
                return;
            }
            insert_status_event(filename, new_event);
            break;
        }
        default:
            printf("Invalid choice, returning to main menu.\n");
    }
}

void update_record() {
    printf("Please choose a table:\n");
    printf("  1. Modules\n");
    printf("  2. Levels\n");
    printf("  3. Status events\n");
    printf("> ");

    int table_choice;
    if (scanf("%d", &table_choice) != 1) {
        printf("Invalid input. Returning to main menu.\n");
        return;
    }
    getchar();  // Consume the newline character left by scanf

    char filename[256];

    switch (table_choice) {
        case 1: {
            snprintf(filename, sizeof(filename), "../materials/master_modules.db");
            int module_id;
            Module updated_module;

            printf("Enter module_id to update: ");
            if (scanf("%d", &module_id) != 1) {
                printf("Invalid module_id input. Returning to main menu.\n");
                return;
            }

            printf("Enter new module_name: ");
            if (scanf("%s", updated_module.module_name) != 1) {
                printf("Invalid module_name input. Returning to main menu.\n");
                return;
            }

            printf("Enter new memory_level: ");
            if (scanf("%d", &updated_module.memory_level) != 1) {
                printf("Invalid memory_level input. Returning to main menu.\n");
                return;
            }

            printf("Enter new cell_number: ");
            if (scanf("%d", &updated_module.memory_cell) != 1) {
                printf("Invalid cell_number input. Returning to main menu.\n");
                return;
            }

            printf("Enter new delete_flag: ");
            if (scanf("%d", &updated_module.delete_flag) != 1) {
                printf("Invalid delete_flag input. Returning to main menu.\n");
                return;
            }

            update_module(filename, module_id, updated_module);
            break;
        }
        case 2: {
            snprintf(filename, sizeof(filename), "../materials/master_levels.db");
            int memory_level;
            Level updated_level;
            printf("Enter memory_level to update: ");
            if (scanf("%d", &memory_level) != 1) {
                printf("Invalid memory_level input. Returning to main menu.\n");
                return;
            }

            printf("Enter new cell_count: ");
            if (scanf("%d", &updated_level.cell_count) != 1) {
                printf("Invalid cell_count input. Returning to main menu.\n");
                return;
            }

            printf("Enter new protection_flag: ");
            if (scanf("%d", &updated_level.protection_flag) != 1) {
                printf("Invalid protection_flag input. Returning to main menu.\n");
                return;
            }

            update_level(filename, memory_level, updated_level);
            break;
        }
        case 3: {
            snprintf(filename, sizeof(filename), "../materials/master_status_events.db");
            int event_id;
            StatusEvent updated_event;
            printf("Enter event_id to update: ");
            if (scanf("%d", &event_id) != 1) {
                printf("Invalid event_id input. Returning to main menu.\n");
                return;
            }
            printf("Enter new module_id: ");
            if (scanf("%d", &updated_event.module_id) != 1) {
                printf("Invalid module_id input. Returning to main menu.\n");
                return;
            }
            printf("Enter new new_status: ");
            if (scanf("%d", &updated_event.new_status) != 1) {
                printf("Invalid new_status input. Returning to main menu.\n");
                return;
            }
            printf("Enter new date (dd.mm.yyyy): ");
            if (scanf("%10s", updated_event.date) != 1) {
                printf("Invalid date input. Returning to main menu.\n");
                return;
            }
            printf("Enter new time (hh:mm:ss): ");
            if (scanf("%8s", updated_event.time) != 1) {
                printf("Invalid time input. Returning to main menu.\n");
                return;
            }
            update_status_event(filename, event_id, updated_event);
            break;
        }
        default:
            printf("Invalid choice, returning to main menu.\n");
    }
}

void delete_record() {
    printf("Please choose a table:\n");
    printf("  1. Modules\n");
    printf("  2. Levels\n");
    printf("  3. Status events\n");
    printf("> ");

    int table_choice;
    if (scanf("%d", &table_choice) != 1) {
        printf("Invalid input. Returning to main menu.\n");
        return;
    }

    char filename[256];

    switch (table_choice) {
        case 1: {
            snprintf(filename, sizeof(filename), "../materials/master_modules.db");
            int module_id;
            printf("Enter module_id to delete: ");
            if (scanf("%d", &module_id) != 1) {
                printf("Invalid module_id input. Returning to main menu.\n");
                return;
            }
            delete_module(filename, module_id);
            break;
        }
        case 2: {
            snprintf(filename, sizeof(filename), "../materials/master_levels.db");
            int memory_level;
            printf("Enter memory_level to delete: ");
            if (scanf("%d", &memory_level) != 1) {
                printf("Invalid memory_level input. Returning to main menu.\n");
                return;
            }
            delete_level(filename, memory_level);
            break;
        }
        case 3: {
            snprintf(filename, sizeof(filename), "../materials/master_status_events.db");
            int event_id;
            printf("Enter event_id to delete: ");
            if (scanf("%d", &event_id) != 1) {
                printf("Invalid event_id input. Returning to main menu.\n");
                return;
            }
            delete_status_event(filename, event_id);
            break;
        }
        default:
            printf("Invalid choice, returning to main menu.\n");
    }
}

void get_all_active_modules(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    Module module;
    printf("%-10s %-30s %-15s %-10s %-10s\n", "Module ID", "Module Name", "Memory Level", "Cell Number",
           "Delete Flag");
    printf("-------------------------------------------------------------------------------\n");
    while (fread(&module, sizeof(Module), 1, file)) {
        if (module.delete_flag == 0) {  // Assuming active module means delete_flag is 0
            printf("%-10d %-30s %-15d %-10d %-10d\n", module.module_id, module.module_name,
                   module.memory_level, module.memory_cell, module.delete_flag);
        }
    }

    fclose(file);
}

void delete_modules_by_ids(const char *filename) {
    printf("Please input the ids of the deleting modules (space-separated): ");
    char ids[256];
    getchar();
    fgets(ids, sizeof(ids), stdin);

    // Convert ids to an array of integers
    int id_array[100];
    int id_count = 0;
    char *token = strtok(ids, " ");
    while (token != NULL && id_count < 100) {
        id_array[id_count++] = atoi(token);
        token = strtok(NULL, " ");
    }

    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    Module module;
    while (fread(&module, sizeof(Module), 1, file)) {
        for (int i = 0; i < id_count; ++i) {
            if (module.module_id == id_array[i]) {
                module.delete_flag = 1;
                fseek(file, -sizeof(Module), SEEK_CUR);
                fwrite(&module, sizeof(Module), 1, file);
                fseek(file, 0, SEEK_CUR);  // Move file pointer to next record
                break;
            }
        }
    }

    fclose(file);
    printf("Modules marked as deleted\n");
}

void set_protected_mode(const char *filename) {
    printf("Enter module_id to set protected mode: ");
    int module_id;
    scanf("%d", &module_id);

    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    Module module;
    while (fread(&module, sizeof(Module), 1, file)) {
        if (module.module_id == module_id) {
            module.delete_flag = 0;
            fseek(file, -sizeof(Module), SEEK_CUR);
            fwrite(&module, sizeof(Module), 1, file);
            fseek(file, 0, SEEK_CUR);  // Move file pointer to next record
            printf("Module ID %d set to protected mode.\n", module_id);
            fclose(file);
            return;
        }
    }

    printf("Module ID %d not found.\n", module_id);
    fclose(file);
}
