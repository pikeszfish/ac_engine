#include "ac.h"



void insert(char *str){
    int i = 0;
    int index = 0;
    ac_node *p = ac_root;
    while(*str){
        index = *str -'a';
        if(p->next[index] == NULL){
            p->next[index] = (ac_node *)malloc(sizeof(ac_node));
        }
        p = p->next[index];
        str++;
        i++;
    }
    p->pattern_len = i;
            // index = str[i] - 'a';
        // if(p->next[index] == NULL){
        //     p->next[index] = (ac_node *)malloc(sizeof(ac_node));
        // }
        // p = p->next[index];
        // i++;
}

void build_ac_fail(ac_node *root){
    int i = 0;

}

int main(){
    char pattern[10][100];
    int pattern_num = 0;
    char *ch = NULL;
    int len = 0;
    int i =0;
    FILE *fp;
    ac_pattern *p;
    ac_node *q;
    for(i=0; i<10; i++){
        memcpy(pattern[i], 0 ,99);
    }
    if((fp = fopen("LICENSE", "r")) == NULL){
        printf("open fail!");
        return 0;
    }
    fseek(fp,0,SEEK_END);
    len = ftell(fp);
    rewind(fp);
    ch = (char *)malloc(sizeof(char)*len + 1);
    if(!ch){
        printf("error");
        return 0;
    }
    len = fread(ch, sizeof(char), len, fp);
    ch[len] = '\0';
    fclose(fp);
    if((fp = fopen("ac_pattern", "r")) == NULL){
        printf("open ac_pattern error");
        return 0;
    }
    while(fgets(pattern[pattern_num], MAX_LINE, fp) != NULL){
        pattern_num++;
    }
    while(pattern_num){
        printf("%s\n", pattern[pattern_num--]);
    }
    ac_root = (ac_node *)malloc(sizeof(ac_node));
    for(i=0; i<pattern_num; i++){
        insert(pattern[i]);
    }




    // while(pattern_num){
    //     pattern_num--;
    //     insert()
    // }
    //insert(pattern, pattern_num,ac_root);
    //printf("%c", pattern[0][3]);






}



