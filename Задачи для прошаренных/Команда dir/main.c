#if defined _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define PREFIX 1024 

enum DIMENSION
{
    B, KB, MB, GB, TB
} DIMENSION;

struct file_size_t
{
    DWORD fsv_size;
    enum DIMENSION fsv_dimension;
};

static void GetWorkingDirectory(char* exePath)
{
    char* tail = strrchr(exePath, '\\');
    tail[1] = '\0';
}

static void PrintError(void)
{
    char errorMessage[MAX_PATH] = { 0 };
    FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM, 
        NULL, 
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        errorMessage, 
        MAX_PATH,
        NULL
    );

    printf("%s\n", errorMessage);
}

static void PrintFullPath(const char* workingDirName, const char* dirName)
{
    printf("\n\tDirectory of %s%s\n\n", 
        (dirName[1] == ':') ? "" : workingDirName,
        (dirName[0] == '.') ? "" : dirName
    );
}

static void PrintSystemTime(SYSTEMTIME st)
{
    printf("%02hu/%02hu/%hu\t%02d:%02hu %s",  
        st.wMonth, st.wDay, st.wYear,
        (st.wHour % 12 == 0) ? 12 : st.wHour % 12, 
        st.wMinute,
        (st.wHour < 12) ? "AM" : "PM"
    );
}

static void PrintAttribute(DWORD fileAttribute)
{
    printf((FILE_ATTRIBUTE_DIRECTORY            & fileAttribute) ? "D" : "-");
    printf((FILE_ATTRIBUTE_ARCHIVE              & fileAttribute) ? "A" : "-");    
    printf((FILE_ATTRIBUTE_HIDDEN               & fileAttribute) ? "H" : "-");
    printf((FILE_ATTRIBUTE_SYSTEM               & fileAttribute) ? "S" : "-");
    printf((FILE_ATTRIBUTE_READONLY             & fileAttribute) ? "R" : "-");
    printf((FILE_ATTRIBUTE_COMPRESSED           & fileAttribute) ? "C" : "-");
    printf((FILE_ATTRIBUTE_ENCRYPTED            & fileAttribute) ? "E" : "-");
    printf((FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  & fileAttribute) ? "I" : "-");
    printf((FILE_ATTRIBUTE_REPARSE_POINT        & fileAttribute) ? "L" : "-");
    printf((FILE_ATTRIBUTE_OFFLINE              & fileAttribute) ? "O" : "-");
    printf((FILE_ATTRIBUTE_SPARSE_FILE          & fileAttribute) ? "P" : "-");
    printf((FILE_ATTRIBUTE_TEMPORARY            & fileAttribute) ? "T" : "-");
}

static struct file_size_t StandardizeSize(DWORD size)
{
    struct file_size_t newSize = { 
        .fsv_size = 0, 
        .fsv_dimension = B 
    };

    while (size % PREFIX != size)
    {
        size = (DWORD)ceil((double)size / PREFIX);
        ++newSize.fsv_dimension;
    }

    return newSize;
}

static void PrintFileSize(WIN32_FIND_DATA fileData)
{
    DWORD size = (fileData.nFileSizeHigh * (MAXDWORD+1)) + fileData.nFileSizeLow;
    struct file_size_t newSize = StandardizeSize(size);

    printf("%lu %s", newSize.fsv_size,
        (newSize.fsv_dimension == B) ? "B" :
        (newSize.fsv_dimension == KB) ? "KB" :
        (newSize.fsv_dimension == MB) ? "MB" :
        (newSize.fsv_dimension == GB) ? "GB" : "TB"
    );
}

static void PrintInfo(WIN32_FIND_DATA fileData)
{
    SYSTEMTIME stLastWrite;
    if (!FileTimeToSystemTime(&fileData.ftLastWriteTime, &stLastWrite))
    {
        PrintError();
        exit(EXIT_FAILURE);
    }
    PrintSystemTime(stLastWrite);
    printf("\t");

    if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
    {
        PrintFileSize(fileData);
    }
    printf("\t");

    PrintAttribute(fileData.dwFileAttributes);
    printf("\t");

    printf("%s", fileData.cFileName);
    printf("\n");
}

static void PrintDirectory(const char* workingDirName, char* dirName)
{
    PrintFullPath(workingDirName, dirName);

    strcat(dirName, "\\*");
    WIN32_FIND_DATA findFileData;
    HANDLE hFile = FindFirstFile(dirName, &findFileData);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        PrintError();
        exit(EXIT_FAILURE);
    }

    do
    {
        PrintInfo(findFileData);
    } while (FindNextFile(hFile, &findFileData));
    
    if (!FindClose(hFile))
    {
        PrintError();
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    char dirName[MAX_PATH] = { 0 };
    char* workingDirName = argv[0];
    GetWorkingDirectory(workingDirName);

    if (argc == 1)
    {
        snprintf(dirName, MAX_PATH, ".");
        PrintDirectory(workingDirName, dirName);
    }
    else
    {
        while (argc > 1)
        {
            snprintf(dirName, MAX_PATH, "%s", argv[1]);
            PrintDirectory(workingDirName, dirName);
            --argc;
            ++argv;
        }
    }

    return EXIT_SUCCESS;
}

#elif defined __linux__
#include <dirent.h>
#include <errno.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_PATH 256
#define PREFIX 1024 

enum DIMENSION
{
    B, KB, MB, GB, TB
};

struct file_size_t
{
    off_t fsv_size;
    enum DIMENSION fsv_dimension;
};

static void GetWorkingDirectory(char* exePath)
{
    char* tail = strrchr(exePath, '/');
    tail[1] = '\0';
}

static void PrintError(void)
{
    perror(strerror(errno));
}

static void PrintFullPath(const char* workingDirName, const char* dirName)
{
    printf("\n\tDirectory of %s%s\n\n", 
        (dirName[0] == '/') ? "" : workingDirName,
        (dirName[0] == '.') ? "" : dirName
    );
}

static void PrintAttribute(mode_t attribute)
{
    switch (attribute & S_IFMT)
    {
        case S_IFDIR:
            printf("d");
            break;
        case S_IFCHR:
            printf("c");
            break;
        case S_IFBLK:
            printf("b");
            break;
        case S_IFREG:
            printf("r");
            break;
        case S_IFIFO:
            printf("i");
            break;
        case S_IFLNK:
            printf("l");
            break;
        case S_IFSOCK:
            printf("s");
            break;
        default:
            printf("u");
    }

    printf("%c", (attribute & S_IRUSR) ? 'r' : '-');
    printf("%c", (attribute & S_IWUSR) ? 'w' : '-');
    printf("%c", (attribute & S_IXUSR) ? 'x' : '-');

    printf("%c", (attribute & S_IRGRP) ? 'r' : '-');
    printf("%c", (attribute & S_IWGRP) ? 'w' : '-');
    printf("%c", (attribute & S_IXGRP) ? 'x' : '-');

    printf("%c", (attribute & S_IROTH) ? 'r' : '-');
    printf("%c", (attribute & S_IWOTH) ? 'w' : '-');
    printf("%c", (attribute & S_IXOTH) ? 'x' : '-');
}

static struct file_size_t StandardizeSize(off_t size)
{
    struct file_size_t newSize = { 
        .fsv_size = 0, 
        .fsv_dimension = B 
    };

    while (size % PREFIX != size)
    {
        size = (off_t)ceil((double)size / PREFIX);
        ++newSize.fsv_dimension;
    }

    return newSize;
}

static void PrintFileSize(off_t fileSize)
{
    struct file_size_t size = StandardizeSize(fileSize);
    printf("%lu %s", size.fsv_size,
        (size.fsv_dimension == B) ? "B" :
        (size.fsv_dimension == KB) ? "KB" :
        (size.fsv_dimension == MB) ? "MB" :
        (size.fsv_dimension == GB) ? "GB" : "TB"
    );
}

static void PrintSystemTime(struct timespec st)
{
    const struct tm * const clock = localtime(&st.tv_sec);
    
    printf("%02d/%02d/%d\t%02d:%02d %s",  
        clock->tm_mon, clock->tm_mday, clock->tm_year,
        (clock->tm_hour % 12 == 0) ? 12 : clock->tm_hour  % 12, 
        clock->tm_min,
        (clock->tm_hour < 12) ? "AM" : "PM"
    );
}

static void PrintInfo(const char* dirName, const char* fileName)
{
    char fullFileName[MAX_PATH] = { 0 };
    snprintf(fullFileName, MAX_PATH, "%s%s%s",
        dirName,
        (dirName[strlen(dirName) - 1] != '/') ? "/" : "",
        fileName
    );

    struct stat fileStat;
    if (stat(fullFileName, &fileStat) == -1)
    {
        PrintError();
        exit(EXIT_FAILURE);
    }

    PrintAttribute(fileStat.st_mode);
    printf("\t");

    if ((fileStat.st_mode & S_IFDIR) == 0)
    {
        PrintFileSize(fileStat.st_size);
    }
    printf("\t");

    PrintSystemTime(fileStat.st_ctim);
    printf("\t");

    printf("%s", fileName);
    printf("\n");
}

static void PrintDirectory(const char* workingDirName, const char* dirName)
{
    DIR * const  dirStream = opendir(dirName);
    if (dirStream == NULL)
    {
        PrintError();
        exit(EXIT_FAILURE);
    }

    PrintFullPath(workingDirName, dirName);

    struct dirent* file = NULL;
    while ((file = readdir(dirStream)) != NULL)
    {
        PrintInfo(dirName, file->d_name);
    }
    
    if (closedir(dirStream) == -1)
    {
        PrintError();
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");
    char dirName[MAX_PATH] = { 0 };
    char* workingDirName = argv[0];
    GetWorkingDirectory(workingDirName);

    if (argc == 1)
    {
        snprintf(dirName, MAX_PATH, ".");
        PrintDirectory(workingDirName, dirName);
    }
    else
    {
        while (argc > 1)
        {
            PrintDirectory(workingDirName, argv[1]);
            --argc;
            ++argv;
        }
    }

    return EXIT_SUCCESS;
}

#endif
