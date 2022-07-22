#if defined _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <windows.h>

#define PREFIX 1024 

typedef enum DIMENSION
{
    B, KB, MB, GB, TB
} DIMENSION;

static void PrintError(void)
{
    TCHAR errorMessage[MAX_PATH] = { 0 };
    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM, 
        NULL, 
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        errorMessage, 
        MAX_PATH,
        NULL
    );

    _tprintf(_TEXT("%s\n"), errorMessage);
}

static void PrintFullPath(PTCHAR exePath, PTCHAR dirName)
{
    TCHAR fullPath[MAX_PATH] = { 0 };

    if (dirName[1] != _TEXT(':'))
    {
        PTCHAR endPath = _tcsrchr(exePath, _TEXT('\\'));
        endPath[1] = _TEXT('\0');
        _stprintf(fullPath, _TEXT("%s"), exePath);
    }

    _tprintf(_TEXT("\n\tDirectory of %s%s\n\n"), 
        fullPath, 
        (_tcscmp(dirName, _TEXT(".\\")) == 0) ? _TEXT("") : dirName
    );
}

static void PrintSystemTime(SYSTEMTIME st)
{
    _tprintf(_TEXT("%02hu/%02hu/%hu\t%02d:%02hu %s"),  
        st.wMonth, st.wDay, st.wYear,
        (st.wHour % 12 == 0) ? 12 : st.wHour % 12, 
        st.wMinute,
        (st.wHour < 12) ? "AM" : "PM"
    );
}

static void PrintAttribute(DWORD fileAttribute)
{
    while (fileAttribute)
    {
        if (FILE_ATTRIBUTE_READONLY & fileAttribute)
        {
            _tprintf(_TEXT("<R>"));
            fileAttribute &= ~FILE_ATTRIBUTE_READONLY;
        }
        if (FILE_ATTRIBUTE_HIDDEN & fileAttribute)
        {
            _tprintf(_TEXT("<H>"));
            fileAttribute &= ~FILE_ATTRIBUTE_HIDDEN;
        }
        if (FILE_ATTRIBUTE_SYSTEM & fileAttribute)
        {
            _tprintf(_TEXT("<S>"));
            fileAttribute &= ~FILE_ATTRIBUTE_SYSTEM;
        }
        if (FILE_ATTRIBUTE_DIRECTORY & fileAttribute)
        {
            _tprintf(_TEXT("<DIR>"));
            fileAttribute &= ~FILE_ATTRIBUTE_DIRECTORY;
        }
        if (FILE_ATTRIBUTE_ARCHIVE & fileAttribute)
        {
            _tprintf(_TEXT("<A>"));
            fileAttribute &= ~FILE_ATTRIBUTE_ARCHIVE;
        }
        if (FILE_ATTRIBUTE_DEVICE & fileAttribute)
        {
            _tprintf(_TEXT("<DEV>"));
            fileAttribute &= ~FILE_ATTRIBUTE_DEVICE;
        }
        if (FILE_ATTRIBUTE_NORMAL & fileAttribute)
        {
            _tprintf(_TEXT("<N>"));
            fileAttribute &= ~FILE_ATTRIBUTE_NORMAL;
        }
        if (FILE_ATTRIBUTE_TEMPORARY & fileAttribute)
        {
            _tprintf(_TEXT("<T>"));
            fileAttribute &= ~FILE_ATTRIBUTE_TEMPORARY;
        }
        if (FILE_ATTRIBUTE_SPARSE_FILE & fileAttribute)
        {
            _tprintf(_TEXT("<S>"));
            fileAttribute &= ~FILE_ATTRIBUTE_SPARSE_FILE;
        }
        if (FILE_ATTRIBUTE_REPARSE_POINT & fileAttribute)
        {
            _tprintf(_TEXT("<R>"));
            fileAttribute &= ~FILE_ATTRIBUTE_REPARSE_POINT;
        }
        if (FILE_ATTRIBUTE_COMPRESSED & fileAttribute)
        {
            _tprintf(_TEXT("<C>"));
            fileAttribute &= ~FILE_ATTRIBUTE_COMPRESSED;
        }
        if (FILE_ATTRIBUTE_OFFLINE & fileAttribute)
        {
            _tprintf(_TEXT("<O>"));
            fileAttribute &= ~FILE_ATTRIBUTE_OFFLINE;
        }
        if (FILE_ATTRIBUTE_NOT_CONTENT_INDEXED & fileAttribute)
        {
            _tprintf(_TEXT("<N>"));
            fileAttribute &= ~FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
        }
        if (FILE_ATTRIBUTE_ENCRYPTED & fileAttribute)
        {
            _tprintf(_TEXT("<E>"));
            fileAttribute &= ~FILE_ATTRIBUTE_ENCRYPTED;
        }
        if (FILE_ATTRIBUTE_VIRTUAL & fileAttribute)
        {
            _tprintf(_TEXT("<V>"));
            fileAttribute &= ~FILE_ATTRIBUTE_VIRTUAL;
        }
    }
}

static void StandardizeSize(LPDWORD size, DIMENSION* unit)
{
    *unit = B;
    while ((*size) % PREFIX != (*size))
    {
        (*size) = (DWORD)ceil((double)(*size) / PREFIX);
        ++(*unit);
    }
}

static void PrintFileSize(WIN32_FIND_DATA fileData)
{
    DWORD size = (fileData.nFileSizeHigh * (MAXDWORD+1)) + fileData.nFileSizeLow;

    DIMENSION unit;
    StandardizeSize(&size, &unit);
    _tprintf(_TEXT("%lu %s"), size,
        (unit == B) ? _TEXT("B") :
        (unit == KB) ? _TEXT("KB") :
        (unit == MB) ? _TEXT("MB") :
        (unit == GB) ? _TEXT("GB") : _TEXT("TB")
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
    _tprintf(_TEXT("\t"));

    if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
    {
        PrintFileSize(fileData);
    }
    _tprintf(_TEXT("\t"));

    PrintAttribute(fileData.dwFileAttributes);
    _tprintf(_TEXT("\t"));

    _tprintf(_TEXT("%s"), fileData.cFileName);
    _tprintf(_TEXT("\n"));
}

static void PrintDirectory(PTCHAR exePath, PTCHAR dirName)
{
    _tcscat(dirName, _TEXT("\\"));
    PrintFullPath(exePath, dirName);

    _tcscat(dirName, _TEXT("*"));

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

int _tmain(int argc, TCHAR *argv[])
{
    setlocale(LC_ALL, "Russian");
    TCHAR dirName[MAX_PATH] = { 0 };
    PTCHAR exePath = argv[0];

    if (argc == 1)
    {
        _stprintf(dirName, _TEXT("."));
        PrintDirectory(exePath, dirName);
    }
    else
    {
        while (argc > 1)
        {
            _stprintf(dirName, _TEXT("%s"), argv[1]);
            PrintDirectory(exePath, dirName);
            --argc;
            ++argv;
        }
    }

    return EXIT_SUCCESS;
}

#endif
