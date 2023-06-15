#include <stdio.h>

int main() {
    char filename[100];
    printf("Enter the filename: ");
    scanf("%99s", filename);
    
    char filepath[200];
    snprintf(filepath, sizeof(filepath), "../../customers/%s.dat", filename);
    
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("[ERROR!] : Error occured handling customer file.....\n");
        return 1;
    }
    
    printf("File created successfully: %s\n", filepath);
    
    fclose(file);
    return 0;
}
