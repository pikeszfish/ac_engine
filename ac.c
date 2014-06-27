//
//  ac.c
//  
//
//  Created by Pike on 14-6-27.
//  Copyright (c) 2014年 Pike. All rights reserved.
//
#include "ac.h"
void insert(char *str, int num){
    int i = 0;
    int index = 0;
    ac_node *p = ac_root;
    while(str[i]){
        index = str[i] -'a';
        if(index >= 0 && index < 26){
            if(p->next[index] == NULL){
                if((p->next[index] = (ac_node *)malloc(sizeof(ac_node))) == NULL){
                    printf("malloc ac_node failed");
                    exit(0);
                }
                p->count = 0;
                p->type = 0;
                p = p->next[index];
                p->fail = NULL;
            }
            else{
                p->type = 0;
                p->count = 0;
                p = p->next[index];
                p->fail = NULL;
            }
        }
        i++;
    }
    p->type = num;
    p->count = 1;
    p->pattern_len = i;
}

void build_ac_fail(ac_node *root){
    int i = 0;
    root->fail = NULL;
    ac_node *temp_ac;
    fail_queue *temp;
    fail_queue *temp_queue;
    if((fail_head = (fail_queue *)malloc(sizeof(fail_queue))) == NULL){
        printf("queue head fails");
        exit(0);
    }
    if((fail_tail = (fail_queue *)malloc(sizeof(fail_queue))) == NULL){
        printf("queue head fails");
        exit(0);
    }
    //t = root;
    fail_head->node = root;
    fail_tail = NULL;
    temp = fail_head;          // 当前循环指针
    temp_queue = fail_head;    // 当前队列尾指针
    while(temp != fail_tail){
        for(i = 0; i < 26; i++){
            if(temp->node->next[i] != NULL){
                temp_queue->next =(fail_queue *)malloc(sizeof(fail_queue));
                temp_queue = temp_queue->next;
                temp_queue->node = temp->node->next[i];
                fail_tail = temp_queue;
                
                temp_ac = temp->node->fail;
                while(temp_ac != NULL){
                    if(temp_ac->next[i] != NULL){
                        temp->node->next[i]->fail = temp_ac->next[i];
                        break;
                    }
                    temp_ac = temp_ac->fail;
                }
                if(temp_ac == NULL){
                    temp->node->next[i]->fail = root;
                }
            }
        }
        temp = temp->next;
    }
}

int main(int argc, const char * argv[]){
    char pattern[10][20] = {"licenses","foundation","freedom","make","restrictions","programs"};
    int pattern_num = 6;
    char *ch = NULL;
    int len = 0;
    int i =0;
    int index = 0;
    FILE *fp;
    ac_node *p;
    if(argc > 1){
        fprintf(stdout, "读取指定文件：%s", argv[1]);
        if((fp = fopen(argv[1], "r")) == NULL){
            printf("open fail!");
            return 0;
        }
        fseek(fp,0,SEEK_END);
        len = (int)ftell(fp);
        rewind(fp);
        ch = (char *)malloc(sizeof(char)*len + 1);
        if(!ch){
            printf("error");
            return 0;
        }
        len = (int)fread(ch, sizeof(char), len, fp);
        ch[len] = '\0';
        fclose(fp);
    }
    else{
        if((fp = fopen("LICENSE", "r")) == NULL){
            printf("open fail!");
            return 0;
        }
        fseek(fp,0,SEEK_END);
        len = (int)ftell(fp);
        rewind(fp);
        ch = (char *)malloc(sizeof(char)*len + 1);
        if(!ch){
            printf("error");
            return 0;
        }
        len = (int)fread(ch, sizeof(char), len, fp);
        ch[len] = '\0';
        fclose(fp);
    }
    
    if((ac_root = (ac_node *)malloc(sizeof(ac_node))) == NULL){
        printf("shit failer\n");
    }
    for(i = 0; i < pattern_num; i++){
        insert(pattern[i], i);
    }
    build_ac_fail(ac_root);
    p = ac_root;
    while(ch[i]){
        index = ch[i] - 'a';
        if(index >= 0 && index < 26){
            while(p->next[index] == NULL && p != ac_root){
                p = p->fail;
            }
            if(p->next[index] == NULL){
                p = ac_root;
            }
            else{
                p = p->next[index];
                if(p->count == 1){
                    fprintf(stdout, "在文件的第%d个字节处找到关键词：%s\n",i-p->pattern_len+1,pattern[p->type]);
                    p = ac_root;
                }
            }
        }
        i++;
    }
    return 0;
}



