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
     /* data */
}ac_node;

typedef struct ac_pattern{
	char pattern[MAX_LEN];
	char name[MAX_LEN];
	int type;
	int enabled;
}ac_pattern;

static ac_node *ac_root = NULL;
