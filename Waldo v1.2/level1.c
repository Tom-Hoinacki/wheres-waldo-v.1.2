//
//  level1.c
//  Waldo v1.2
//
//  Created by Thomas Hoinacki on 7/14/16.
//  Copyright (c) 2016 Thomas Hoinacki. All rights reserved.
//

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

#include "level1.h"

/* Creates Waldo Level 1 folder */
void get_dir_lvl1_Path(char * cwd, char ** dirPathLvl1, int * pathLen)
{
    // Initialize and assign name
    char * dirNameLvl1;
    dirNameLvl1 = "/Where's Waldo Level 1";
    
    // Assign pathLen pointer for reuse in main to point to len's address
    int len = 1 + strlen(cwd) + strlen(dirNameLvl1);
    *pathLen = len;
    
    // Allocate memory for level 1 folder path, assign, and append to build its string name
    *dirPathLvl1 = (char *) malloc(*pathLen);
    strcpy(*dirPathLvl1, cwd);
    strcat(*dirPathLvl1, dirNameLvl1);
}