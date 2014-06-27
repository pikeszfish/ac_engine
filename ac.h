//
//  ac.h
//  
//
//  Created by Pike on 14-6-27.
//  Copyright (c) 2014年 Pike. All rights reserved.
//

#ifndef ac_a_ac_h
#define ac_a_ac_h

#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LEN 26
#define MAX_LINE 256
#define PATTERN_SIG1 0
#define PATTERN_SIG2 1
#define PATTERN_SIG3 2

typedef struct ac_node{
    struct ac_node *fail;
    struct ac_node *next[MAX_LEN];
    int count;
    int pattern_len;
    int type;
    /* data */
}ac_node;


typedef struct fail_queue{
    /* data */
    struct ac_node *node;
    struct fail_queue *next;
}fail_queue;


static fail_queue *fail_head = NULL;
static fail_queue *fail_tail = NULL;
static ac_node *ac_root = NULL;
