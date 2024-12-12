#include <stdio.h>

#define MAX_PARTITIONS 4
#define MAX_FILES 100

// Structure to represent a file in a partition
typedef struct {
    char name[32];
    size_t size; // Size of the file in bytes
} File;

// Structure to represent a partition
typedef struct {
    char filesystem[16];
    size_t size; // Size of the partition in bytes
    size_t used; // Used space in bytes
    File files[MAX_FILES]; // Array of files in the partition
    size_t file_count; // Number of files in the partition
} Partition;

// Structure to represent an SD card
typedef struct {
    char label[32];
    size_t total_size; // Total size of the SD card in bytes
    Partition partitions[MAX_PARTITIONS]; // Array of partitions
    size_t partition_count; // Number of partitions
} SDCard;

void print_sd_card_info(const SDCard *sd) {
    printf("SD Card Label: %s\n", sd->label);
    printf("Total Size: %zu bytes\n", sd->total_size);
    printf("Partitions:\n");
    for (size_t i = 0; i < sd->partition_count; i++) {
        printf("  Partition %zu:\n", i + 1);
        printf("    File System: %s\n", sd->partitions[i].filesystem);
        printf("    Size: %zu bytes, Used: %zu bytes\n",
               sd->partitions[i].size, sd->partitions[i].used);
        printf("    Files:\n");
        for (size_t j = 0; j < sd->partitions[i].file_count; j++) {
            printf("      - %s (%zu bytes)\n",
                   sd->partitions[i].files[j].name,
                   sd->partitions[i].files[j].size);
        }
    }
}

int main() {
    SDCard sd = {
        .label = "MySDCard",
        .total_size = 32 * 1024 * 1024, // 32 MB
        .partition_count = 2,
        .partitions = {
            {
                .filesystem = "FAT32",
                .size = 16 * 1024 * 1024, // 16 MB
                .used = 8 * 1024 * 1024, // 8 MB used
                .file_count = 1,
                .files = {
                    {"file1.txt", 1024} // 1 KB file
                }
            },
            {
                .filesystem = "ext4",
                .size = 16 * 1024 * 1024, // 16 MB
                .used = 4 * 1024 * 1024, // 4 MB used
                .file_count = 2,
                .files = {
                    {"file2.txt", 2048}, // 2 KB file
                    {"file3.txt", 4096}  // 4 KB file
                }
            }
        }
    };

    print_sd_card_info(&sd);
    return 0;
}
