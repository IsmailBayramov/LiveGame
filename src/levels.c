#include "levels.h"

void select_levels(const char *filename) {
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

    Level level;
    int count = 0;
    printf("%-15s %-15s %-15s\n", "Memory Level", "Cell Count", "Protection Flag");
    printf("-----------------------------------------------\n");
    while (fread(&level, sizeof(Level), 1, file)) {
        printf("%-15d %-15d %-15d\n", level.memory_level, level.cell_count, level.protection_flag);
        count++;
        if (limit > 0 && count >= limit) {
            break;
        }
    }

    fclose(file);
}

void insert_level(const char *filename, Level new_level) {
    FILE *file = fopen(filename, "ab");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    fwrite(&new_level, sizeof(Level), 1, file);
    fclose(file);
    printf("Level inserted successfully.\n");
}

void update_level(const char *filename, int memory_level, Level updated_level) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    Level level;
    int found = 0;
    while (fread(&level, sizeof(Level), 1, file)) {
        if (level.memory_level == memory_level) {
            fseek(file, -sizeof(Level), SEEK_CUR);
            updated_level.memory_level = memory_level;
            fwrite(&updated_level, sizeof(Level), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);
    if (found) {
        printf("Level updated successfully.\n");
    } else {
        printf("Level with memory_level %d not found.\n", memory_level);
    }
}

void delete_level(const char *filename, int memory_level) {
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

    Level level;
    int found = 0;
    while (fread(&level, sizeof(Level), 1, file)) {
        if (level.memory_level != memory_level) {
            fwrite(&level, sizeof(Level), 1, temp_file);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(filename);
    rename("temp.db", filename);

    if (found) {
        printf("Level deleted successfully.\n");
    } else {
        printf("Level with memory_level %d not found.\n", memory_level);
    }
}
