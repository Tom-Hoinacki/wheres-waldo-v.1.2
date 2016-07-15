//
//  level1.h
//  Waldo v1.2
//
//  Created by Thomas Hoinacki on 7/14/16.
//  Copyright (c) 2016 Thomas Hoinacki. All rights reserved.
//

#ifndef __Waldo_v1_2__level1__
#define __Waldo_v1_2__level1__

#include <stdio.h>

void get_dir_lvl1_Path(char * currentWorkingDirectory, char ** dirPathLvl1, int * pathLen);

void check_to_remove_preexisting_waldo_dir(char * dirPathLvl1);

void create_sightings_log_file(char * dirPathLvl1, char * sightingsLogPath);

void create_text_filler_file(char * dirPathLvl1, char * textFillerPath);

#endif

