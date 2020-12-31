#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* readline();
char** split_string(char*);

typedef struct linkedlist_node linkedlist_node;
typedef struct linkedlist linkedlist;


struct linkedlist_node
    {
       linkedlist_node *next;
       char *name;
    };
struct linkedlist
    {
       struct linkedlist_node *head;
       struct linkedlist_node *tail;
    };

linkedlist_node* create_linkedlist_node (char *name){
    linkedlist_node *node = malloc(sizeof(linkedlist_node));
    node->name= name;
    node->next = NULL;
    return node;
}

/* "head_p" - pointer to the list's head */
void insert_node(linkedlist **linked, char *name) { 
linkedlist_node* node = create_linkedlist_node(name);
if (!(*linked)->head) { 
    (*linked)->head = node;    
    }
else{
     (*linked)->tail->next = node;    
    }    
    (*linked)->tail = node;
return;
}

void free_all_linked_list(linkedlist_node *node)
    {while (node) {        
        linkedlist_node* temp = node;
        node = node->next;        
        free(temp);
    }
}

void delete_node(linkedlist *list, char *key);


bool list_contains_and_delete(struct linkedlist *list, struct linkedlist_node *head, char *name) {
    for (linkedlist_node *cursor=head; cursor; cursor=cursor->next ) {
        if ( !strcmp((cursor->name),name) ) {
            delete_node(list, cursor->name);
            return true;
        }
        
        
    }
    return false;
}
    

void delete_node(linkedlist *list, char *key) {
    linkedlist_node* tmp = list->head , *prev; 
    if (tmp != NULL && tmp->name==key){
        list->head=tmp->next;
        free(tmp);
        return;
    }
    
    while (tmp != NULL && tmp->name!=key){ 
        prev=tmp;
        tmp=tmp->next;

    }
    if (tmp==NULL) 
    {
        return;
    }
    prev->next=tmp->next;
    free(tmp);
}    
// Complete the checkMagazine function below.
void checkMagazine(int magazine_count, char** magazine, int note_count, 
                    char** note) {

    //creat magazine linked list
    struct linkedlist *magazine_linkedlist = malloc(sizeof(struct linkedlist));
    struct linkedlist *note_linkedlist = malloc(sizeof(struct linkedlist));

    for(int i=0 ; i < magazine_count ; i++){  
    insert_node(&magazine_linkedlist, magazine[i]); //insert
    }
    for(int i=0 ; i < note_count ; i++){  
    insert_node(&note_linkedlist, note[i]); //insert
    }
   
    struct linkedlist_node *magazine_head = magazine_linkedlist->head;
    for(struct linkedlist_node *cursor=note_linkedlist->head; cursor; cursor=cursor->next){
        bool contains_current_name = list_contains_and_delete(
                                                    magazine_linkedlist,
                                                    magazine_head,
                                                    cursor->name);
        magazine_head = magazine_linkedlist->head; 
        if(!contains_current_name){
            printf("No");
            free_all_linked_list(magazine_linkedlist->head);
            free_all_linked_list(note_linkedlist->head);
            return;
        }
   }
    free_all_linked_list(magazine_linkedlist->head);
    free_all_linked_list(note_linkedlist->head);
    printf("Yes");
    return;



}





int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
