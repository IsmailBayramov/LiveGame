#include <stdio.h>
#include <stdlib.h>

#include "database.h"

int main() {
    const char *filename = "../materials/master_modules.db";

    while (1) {
        printf("Please choose one operation:\n");
        printf("  1. SELECT\n");
        printf("  2. INSERT\n");
        printf("  3. UPDATE\n");
        printf("  4. DELETE\n");
        printf("  5. Get all active additional modules (last module status is 1)\n");
        printf("  6. Delete modules by ids\n");
        printf("  7. Set protected mode for module by id\n");
        printf("  0. Exit\n");
        printf("> ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                select_records();
                break;
            case 2:
                insert_record();
                break;
            case 3:
                update_record();
                break;
            case 4:
                delete_record();
                break;
            case 5:
                get_all_active_modules(filename);
                break;
            case 6:
                delete_modules_by_ids(filename);
                break;
            case 7:
                set_protected_mode(filename);
                break;
            case 0:
                exit(0);
            default:
                printf("n/a\n");
        }
    }
    return 0;
}
