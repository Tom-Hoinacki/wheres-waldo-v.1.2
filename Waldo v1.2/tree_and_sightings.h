//
//  tree_and_sightings.h
//  Waldo v1.2
//
//  Created by Thomas Hoinacki on 7/16/16.
//  Copyright (c) 2016 Thomas Hoinacki. All rights reserved.
//

#ifndef __Waldo_v1_2__tree_and_sightings__
#define __Waldo_v1_2__tree_and_sightings__

#include <stdio.h>

void create_rand3_file_num(char*, char*, char*, char* const);

void log_waldo_sightings_dir(char * dirPath, FILE * sightingsLogFile, int * sightingsCount);

void log_waldo_sightings_txtfile(char * dirPath, struct dirent * in_Dir, FILE * sightingsLogFile, int * sightingsCount);

#endif