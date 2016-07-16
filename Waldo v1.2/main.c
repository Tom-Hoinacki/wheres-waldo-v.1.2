//
//  main.c
//  Where's Waldo?
//
//  Created by Thomas Hoinacki on 6/20/16.
//  Copyright (c) 2016 Thomas Hoinacki. All rights reserved.
//


// C Library Headers
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>
#include <sys/syslimits.h>
#include <fcntl.h>

// Application Headers
#include "level1.h"

// Functions
void create_rand3_file_num(char*, char*, char*, char* const);
void log_waldo_sightings_dir(char * dirPath, FILE * sightingsLogFile);
void log_waldo_sightings_txtfile(char * dirPath, struct dirent * in_Dir, FILE * sightingsLogFile);

// Global Variables
char * sightingsLogPath;
FILE * sightingsLogFile;
int sightingsCount;



// MAIN
int main(int argc, const char * argv[])
{
    
    // Local Variables
    char cwd[1024];// cwd: current working directory
    char * dirPathLvl1;
    int pathLen;
    char *loremIpsumFilePath;
    
//    char * sightingsLogPath;
//    FILE * sightingsLogFile;
//    int sightingsCount;
  
    
    /* Get directory working directory path where this code is being executed
       from to act as starting point for creating directory tree */
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        /* CREATE LEVEL ONE DIRECTORY AND FILES */
        /****************************************/
        
        // Create Where's Waldo Level 1 top directory wherever code is run from on local machine
        get_dir_lvl1_Path(cwd, &dirPathLvl1, &pathLen);
        
        // Remove top level directory, files, children directories, and children files if exists so we can run this program repeatedly
        check_to_remove_existing_waldo_directory(dirPathLvl1);
        
        // Create top level directory
        mkdir(dirPathLvl1, 0700);
        
        // Create log file of Waldo sightings in top level directory
        create_sightings_log_file(dirPathLvl1, &sightingsLogPath, pathLen);
        
        // Create Lorem Ispum file inside top directory to copy text from for creating other text files
        create_text_filler_file(dirPathLvl1, &loremIpsumFilePath, pathLen);
    
        
        
        /* CREATE RANDOM ASYMMETRICAL CHILD DIRECTORY TREE
         * RANDOM BETWEEN 2-4 LEVELS OF CHILD DEPTH
         * RANDOM BETWEEN 1-3 CHILD DIRECTORIES CREATED WITHIN EACH DIRECTORY
         * RANDOM BETWEEN 1-3 TEXT FILES IN EACH DIRECTORY CREATED
         * RANDOM 1/100 CHANCE STRING "Waldo" IS INSERTED AFTER EACH WORD STREAMED AND PRINTED INTO EACH TEXT FILE
        /*********************************************************************************************************/
        
        // Initialize children directory path variables
        const int WALDO_DIR_NAME_LEN = 11;
        
        char * const WALDO_DIR_NAME_FORMAT = (char *)malloc(strlen(1 + "%s/Level %d-%d"));
        strcpy(WALDO_DIR_NAME_FORMAT, "%s/Level %d-%d");
                                                            
        char * const WALDO_FILE_NAME_FORMAT = (char *)malloc(strlen(1 + "%s/File %d.txt"));
        strcpy(WALDO_FILE_NAME_FORMAT, "%s/File %d.txt");
        
        char * parentDirName = (char *) malloc(strlen(WALDO_DIR_NAME_FORMAT));
        char * newDirPath = (char *) malloc (PATH_MAX);
        char * newFilePath = (char *) malloc(PATH_MAX);
        char * dirPathLvl2 = (char *) malloc(1 + strlen(dirPathLvl1) + WALDO_DIR_NAME_LEN);
        
        
        // Initialize children directory level path identity numbers
        int lvlNum = 2;
        
        // Initialize children directory level path identity numbers
        int dirNumLvl2 = 1;
        int dirNumLvl3 = 1;
        int dirNumLvl4 = 1;
        
        // Seed random number generator
        srand(time(NULL));
        
        // Initialize children directory level counters for how many children directory left to create at that level (random 1-3)
        int mkDirLvl2 = rand() % 3 + 1;
        int mkDirLvl3;
        int mkDirLvl4;
        
        // Initialize number of files left to create in a child directory (random 1-3)
        int filesToCreate;
        int fileNum;
        
        // Initialize parent directory path
        char * parentPath = (char *) malloc(PATH_MAX);
        strcpy(parentPath, dirPathLvl1);
        
                                                             
                                                             
                                                             
        /* RECURSIVE DEPTH-FIRST ALGORITHM, FIRST CREATES AT LEAST ONE LEVEL 2 DIRECTORY, RANDOMIZES CREATION OF CHILD DIRECTORIES AND FILES */
        /*************************************************************************************************************************************/
                                                             
                                                             
        // While there directories left to be made keep creating
        while (mkDirLvl2 > 0 || mkDirLvl3 > 0 || mkDirLvl4 > 0)
        {
            // Switch to create directory at specified level
            switch (lvlNum)
            {
                // Waldo Level 2 Directories
                case 2:
                    
                    // If level 2 directory is to be created
                    if (mkDirLvl2 > 0)
                    {
                        // Create new level 2 directory
                        strcpy(parentPath, dirPathLvl1);
                        sprintf(newDirPath, WALDO_DIR_NAME_FORMAT, parentPath, lvlNum, dirNumLvl2++);
                        mkdir(newDirPath, 0700);
                        
                        // Get random num 1-3 and create that number of empty text files in new directory
                        create_rand3_file_num(newFilePath, newDirPath, loremIpsumFilePath, WALDO_FILE_NAME_FORMAT);

                        // Save new parent path for next level down directory creation
                        strcpy(parentPath, newDirPath);
                        
                        mkDirLvl2--;
                        
                        // Get number of directories to create for next level down
                        mkDirLvl3 = rand() % 4;
                        
                        // Find which level is the next to have a directory be created, specify that level to navigate to for next loop iteration
                        if (mkDirLvl3 > 0)
                        {
                            lvlNum = 3;
                            dirNumLvl3 = 1;
                            
                            // Save parent path for directory level 3
                            strcpy(dirPathLvl2, newDirPath);
                        }
                        else if (mkDirLvl2 > 0)
                        {
                            lvlNum = 2;
                        }
                    }
                    
                    break;
                    
                // Waldo Level 3 Directories
                case 3:
                    
                    if (mkDirLvl3 > 0)
                    {
                        // Create level 3 directory
                        sprintf(newDirPath, WALDO_DIR_NAME_FORMAT, parentPath, lvlNum, dirNumLvl3++);
                        mkdir(newDirPath, 0700);
                        
                        mkDirLvl3--;
                        
                        // Get random num 1-3 and create that number of empty text files in new directory
                        create_rand3_file_num(newFilePath, newDirPath, loremIpsumFilePath, WALDO_FILE_NAME_FORMAT);
                        
                        // Get how many children direct children directories are to be created
                        mkDirLvl4 = rand() % 4;
                        
                        
                        // Check if there are children directories to be made
                        if (mkDirLvl4 > 0)
                        {
                            lvlNum = 4;
                            
                            // Save parent directory path
                            strcpy(parentPath, newDirPath);
                        }
                        // Check if there are any sibling directories to be made
                        else if (mkDirLvl3 > 0)
                        {
                            lvlNum = 3;
                        }
                        // Else traverse back up to parent directory
                        else
                        {
                            lvlNum = 2;
                        }
                    }
                    
                    break;
                    
                // Waldo Level 4 Directories
                case 4:
                    
                    dirNumLvl4 = 1;
                    
                    // Since it is the last directory level, loop and create directories until complete
                    while (mkDirLvl4 > 0)
                    {
                        sprintf(newDirPath, WALDO_DIR_NAME_FORMAT, parentPath, lvlNum, dirNumLvl4++);
                        mkdir(newDirPath, 0700);
                        
                        mkDirLvl4--;
                        
                        // Get random num 1-3 and create that number of empty text files in new directory
                        create_rand3_file_num(newFilePath, newDirPath, loremIpsumFilePath, WALDO_FILE_NAME_FORMAT);
                    }
                    
                    
                    // Check if the parent directory has any siblings that need to be created
                    if (mkDirLvl3 > 0)
                    {
                        lvlNum = 3;
                        strcpy(parentPath, dirPathLvl2);
                    }
                    // Parent has no siblings left to be create recurse back to grandparent
                    else
                    {
                        lvlNum = 2;
                    }
                    
                    break;
            }
        }
        
        // Free memory of all pointers used for random asymmetrical directory tree creation
        free(WALDO_DIR_NAME_FORMAT);
        free(WALDO_FILE_NAME_FORMAT);
        free(parentDirName);
        free(newDirPath);
        free(newFilePath);
        free(dirPathLvl2);
                                                             
        
                                                             
                                                             
        sightingsLogFile = fopen(sightingsLogPath, "w");
    
        DIR * d;
        struct dirent* in_Dir;
        
        if (sightingsLogFile == NULL)
        {
            fprintf(stderr, "Error: Failed to open sightingsLogFile - %s\n", strerror(errno));
            return 1;
        }
        
        sightingsCount = 1;
        
        log_waldo_sightings_dir(dirPathLvl1, sightingsLogFile);
        
        fclose(sightingsLogFile);
    }
    else
    {
        perror("getcwd() error");
    }
    
    return 0;
}


void log_waldo_sightings_dir(char * dirPath, FILE * sightingsLogFile)
{
    struct dirent * in_Dir;
    DIR * d;
    struct stat st;
    char * childDirPath = malloc(PATH_MAX);
    strcpy(childDirPath, dirPath);

    
    
    
    d = opendir(dirPath);
    stat(dirPath, &st);
    
    // Child directories
    while ((in_Dir = readdir(d)) != NULL)
    {
        if (strcmp(in_Dir->d_name, ".") == 0 || strcmp(in_Dir->d_name, "..") == 0)
            continue;
        
        if (fstatat(dirfd(d), in_Dir->d_name, &st, 0) < 0)
        {
            perror(in_Dir->d_name);
            continue;
        }
        
        if (S_ISREG(st.st_mode))
        {
            log_waldo_sightings_txtfile(dirPath, in_Dir, sightingsLogFile);
        }
        else if (S_ISDIR(st.st_mode))
        {
            strcat(childDirPath, "/");
            strcat(childDirPath, in_Dir->d_name);
            log_waldo_sightings_dir(childDirPath, sightingsLogFile);
            strcpy(childDirPath, dirPath);
        }
    }
}


void log_waldo_sightings_txtfile(char* dirPath, struct dirent* in_File, FILE * sightingsLogFile)
{
    char* filePath = malloc(PATH_MAX);
    FILE* entry_File;
    const int BUF_RLINE_SIZE = 150;
    char lineBuf[BUF_RLINE_SIZE];
    
    strcpy(filePath, dirPath);
    strcat(filePath, "/");
    strcat(filePath, in_File->d_name);
    
    struct stat statbuf;

    entry_File = fopen(filePath, "r");
    
    if (entry_File == NULL)
    {
        fprintf(stderr, "Error: Failed to open entry file - %s\n", strerror(errno));
        fclose(entry_File);
    }
    
    while (fgets(lineBuf, BUF_RLINE_SIZE, entry_File) != NULL)
    {
        const char * tmp = lineBuf;
        
        while((tmp = strstr(tmp, "Waldo")))
        {

            fprintf(sightingsLogFile, "%d:\t%s (Line %c)\n", sightingsCount, filePath, lineBuf[0]);
            sightingsCount++;
            
            if (tmp == "Waldo\n")
                break;;

            tmp += strlen("Waldo ");
        }
    }
    fclose(entry_File);
}

void create_rand3_file_num(char * newFilePath, char * newDirPath, char * loremPath, char * const format)
{
    int filesToCreate = rand() % 3 + 1;
    int fileNum = 1;
    
    while (filesToCreate > 0)
    {
        sprintf(newFilePath, format, newDirPath, fileNum++);
        
        size_t n = 0;
        int c;
        
        
        FILE* fd = fopen(newFilePath, "ab+");
        
        // Write random Lorem Ipsum to file with random Waldos
        FILE* fdLorem= fopen(loremPath, "r");
        
        char * loremChar = malloc(2000);
        
        
        int lineNum = 1;
        int chCount = 0;
        const int  MAX_CHAR_LAST_WORD = 75;
        
        
        // Process Lorem Ipsum text file one char at a time to print to current Waldo Level text file
        while ((c = fgetc(fdLorem)) != EOF)
        {
            if ((char) c == ' ')
            {
                // 1 in 100 chance Waldo will be printed after each word
                int printWaldo = rand() % 100 + 1;
                if (printWaldo == 100)
                {
                    fprintf(fd, " Waldo");
                    chCount += 6;
                }
            }
            
            // If start of line print line number and tab
            if (chCount == 0)
            {
                fprintf(fd, "%d", lineNum);
                lineNum++;
                fputs("\t", fd);
                
                // Print character, increase count
                fputc((char) c , fd);
                chCount++;
            }
            // Else if the character counter has reached the maximum for the last word check for whitespace
            // to start a new line and reset the character counter
            else if (chCount >= MAX_CHAR_LAST_WORD)
            {
                if ((char) c == ' ')
                {
                    fputs("\n", fd);
                    chCount = 0;
                }
            }
            else
            {
                // Print character, increase count
                fputc((char) c , fd);
                chCount++;
            }
        }
        
        filesToCreate--;
        
        if (fd != NULL)
        {
            fclose(fd);
        }
    }
}
