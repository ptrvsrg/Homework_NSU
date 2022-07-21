#include <dirent.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

void PrintDirectory(const char* dirName)
{
    DIR* dir = opendir(dirName);
    if (dir == NULL)
    {
        printf("Error opening directory %s\n", dirName);
        exit(EXIT_FAILURE);
    }

    struct dirent* file = NULL;
    while ((file = readdir(dir)) != NULL)
    {
        printf("%s - ", file->d_name);

        switch(file->d_type)
        {
            case DT_UNKNOWN:
                printf("<UNKNOWN>\n");
                break;
            case DT_REG:
                printf("<REG>\n");
                break;
            case DT_DIR:
                printf("<DIR>\n");
                break;
            case DT_FIFO:
                printf("<FIFO>\n");
                break;
            case DT_CHR:
                printf("<CHR>\n");
                break;
            default:
                printf("<UNKNOWN\n>");
                break;
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    if (argc == 1)
    {
        PrintDirectory(".");
    }
    else
    {
        while (argc > 1)
        {
            PrintDirectory(argv[1]);
            --argc;
            ++argv;
        }
    }

    return EXIT_SUCCESS;
}
