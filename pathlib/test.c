#define TINYDIR_IMPLEMENTATION
#include "tinydir.h"

#include <stdio.h>
#include <string.h>

#define IS_DOT(name) \
    (strcmp((name), ".") == 0 || strcmp((name), "..") == 0)

int main(void)
{
    tinydir_dir root;
    if (tinydir_open(&root, "..") == -1) {
        perror("tinydir_open");
        return 1;
    }

    // First layer: directories in root
    while (root.has_next) {
        tinydir_file dir_entry;
        tinydir_readfile(&root, &dir_entry);

        if (dir_entry.is_dir && !IS_DOT(dir_entry.name)) {
            char dir_path[1024];
            snprintf(dir_path, sizeof(dir_path), "../%s", dir_entry.name);

            tinydir_dir subdir;
            if (tinydir_open(&subdir, dir_path) == -1) {
                tinydir_next(&root);
                continue;
            }

            while (subdir.has_next) {
                tinydir_file file;
                tinydir_readfile(&subdir, &file);

                if (!file.is_dir) {
                    printf("%s/%s\n", dir_entry.name, file.name);
                }

                tinydir_next(&subdir);
            }

            tinydir_close(&subdir);
        }

        tinydir_next(&root);
    }

    tinydir_close(&root);
    return 0;
}
