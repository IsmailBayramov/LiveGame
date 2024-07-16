#include "modules.h"

void select_modules(const char *filename) {
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

    Module module;
    int count = 0;
    printf("%-10s %-20s %-10s %-10s %-10s\n", "Module ID", "Module Name", "Mem Level", "Mem Cell",
           "Del Flag");
    printf("--------------------------------------------------------------------------\n");
    while (fread(&module, sizeof(Module), 1, file)) {
        if (module.delete_flag == 0) {  // Skip deleted modules
            printf("%-10d %-20s %-10d %-10d %-10d\n", module.module_id, module.module_name,
                   module.memory_level, module.memory_cell, module.delete_flag);
            count++;
            if (limit > 0 && count >= limit) {
                break;
            }
        }
    }

    fclose(file);
}

void insert_module(const char *filename, Module new_module) {
    FILE *file = fopen(filename, "ab");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    fwrite(&new_module, sizeof(Module), 1, file);
    fclose(file);
    printf("Module inserted successfully.\n");
}

void update_module(const char *filename, int module_id, Module updated_module) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    Module module;
    int found = 0;
    while (fread(&module, sizeof(Module), 1, file)) {
        if (module.module_id == module_id) {
            fseek(file, -sizeof(Module), SEEK_CUR);
            updated_module.module_id = module_id;
            fwrite(&updated_module, sizeof(Module), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);
    if (found) {
        printf("Module updated successfully.\n");
    } else {
        printf("Module with module_id %d not found.\n", module_id);
    }
}

void delete_module(const char *filename, int module_id) {
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

    Module module;
    int found = 0;
    while (fread(&module, sizeof(Module), 1, file)) {
        if (module.module_id != module_id) {
            fwrite(&module, sizeof(Module), 1, temp_file);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(filename);
    rename("temp.db", filename);

    if (found) {
        printf("Module deleted successfully.\n");
    } else {
        printf("Module with module_id %d not found.\n", module_id);
    }
}
