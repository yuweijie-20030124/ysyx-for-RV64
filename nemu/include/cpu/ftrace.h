#ifndef __FTRACE_H__
#define __FTRACE_H__
#include <cpu/decode.h>
#include "elf.h"
#include "utils.h"

#ifdef CONFIG_FTRACE

typedef struct symbol_node{
    char *name;
    word_t first_addr;
    word_t end_addr;
    struct symbol_node *prev;
    struct symbol_node *next;
}symbol_node;

typedef struct symbol_list{
    int node_num;
    symbol_node *head;
    symbol_node *end;
}symbol_list;

char *symbol_find_name(word_t pc,word_t *first_addr);

void ftrce_text_jump(word_t pc);

void ftrce_text_retu(word_t pc);

void symbol_list_push(symbol_list *list,char *name,word_t first_addr,word_t func_size);

void init_ftrace(const char *ELF_FILE);

#endif

#endif