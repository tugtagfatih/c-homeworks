#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "customdict.h"
#define MAX_LINE_LENGTH 44 /* max column numbers in out data.csv file is 43*/

struct CustomDict* create_dict() {
    struct CustomDict* dict = (struct CustomDict*)malloc(sizeof(struct CustomDict));
    dict->capacity = 0;
    dict->size = 0;
    dict->items = (struct Item*)malloc(dict->capacity * sizeof(struct Item));
    return dict;
};

void add_item(struct CustomDict* dict, char* key, union Value* value) {
    if (dict->size == dict->capacity) {
        if (dict->capacity == 0) {
            dict->capacity = 1;
        } else {
            dict->capacity *= 2;
        }
        dict->items = (struct Item*)realloc(dict->items, dict->capacity * sizeof(struct Item));
    }
    dict->items[dict->size].key = (char*)malloc(strlen(key) + 1);
    strcpy(dict->items[dict->size].key, key);
    dict->items[dict->size].value = NULL;
    dict->items[dict->size].value = value;
    dict->size++;
}

void delete_item(struct CustomDict* dict, char* key) {
    int i, j;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            /*free(dict->items[i].key);
            free(dict->items[i].value);*/
            for (j = i; j < dict->size - 1; j++) {
                dict->items[j] = dict->items[j + 1];
            }
            dict->size--;
            break;
        }
    }
}

void set_value(struct CustomDict* dict, char* key, union Value* value) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            dict->items[i].value = value;
            break;
        }
    }
}

union Value* search_item(struct CustomDict* dict, char* key) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (strcmp(dict->items[i].key, key) == 0) {
            return dict->items[i].value;
        }
    }
    return NULL;
}

void sort_dict(struct CustomDict* dict) {
    int i, j;
    for (i = 0; i < dict->size - 1; i++) {
        for (j = 0; j < dict->size - i - 1; j++) {
            if (strcmp(dict->items[j].key, dict->items[j + 1].key) > 0) {
                struct Item temp = dict->items[j];
                dict->items[j] = dict->items[j + 1];
                dict->items[j + 1] = temp;
            }
        }
    }
}


void print_dict(struct CustomDict* dict) {
    int i;
    for (i = 0; i < dict->size; i++) {
        printf("%s: ", dict->items[i].key);
        if (dict->items[i].value->integer) {
            printf("%d\n", dict->items[i].value->integer);
        } else if (dict->items[i].value->f) {
            printf("%f\n", dict->items[i].value->f);
        } else if (dict->items[i].value->d) {
            printf("%lf\n", dict->items[i].value->d);
        } else {
            printf("%c\n", dict->items[i].value->c);
        }
    }
}

void free_dict(struct CustomDict* dict) {
    int i;
    for (i = 0; i < dict->size; i++) {
        if (dict->items[i].key != NULL) {
            free(dict->items[i].key);
            dict->items[i].key = NULL;
        }
        if (dict->items[i].value != NULL) {
            free(dict->items[i].value);
            dict->items[i].value = NULL;
        }
    }
    free(dict->items);
    free(dict);
}

int read_csv(struct CustomDict* dict, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char* key = strtok(line, ",");
        char* value = strtok(NULL, ",");
        if (key != NULL && value != NULL) {
            while (isspace(*key)) {
                key++;
            }
            char* end = key + strlen(key) - 1;
            while (end > key && isspace(*end)) {
                end--;
            }
            *(end + 1) = '\0';

            while (isspace(*value)) {
                value++;
            }
            end = value + strlen(value) - 1;
            while (end > value && isspace(*end)) {
                end--;
            }
            *(end + 1) = '\0';

            union Value* val = (union Value*)malloc(sizeof(union Value));
            if (sscanf(value, "%d", &val->integer) == 1) {
                add_item(dict, key, val);
            } else if (sscanf(value, "%f", &val->f) == 1) {
                add_item(dict, key, val);
            } else if (sscanf(value, "%lf", &val->d) == 1) {
                add_item(dict, key, val);
            } else {
                val->c = value[0];
                add_item(dict, key, val);
            }
        }
    }
}

int main() {
    struct CustomDict* dict = create_dict();
    read_csv(dict, "data.csv");
    add_item(dict, "key1", &(union Value){.c = 'a'});
    add_item(dict, "key2", &(union Value){.integer = 2});
    add_item(dict, "key3", &(union Value){.f = 3.0});
    add_item(dict, "key4", &(union Value){.d = 4.0});


    print_dict(dict);
    printf("First print is over. \n\n\n\n");
    sort_dict(dict);
    set_value(dict, "key1", search_item(dict, "key2"));    
    delete_item(dict, "key2");
    set_value(dict, "key3", &(union Value){.integer = 336});
    print_dict(dict);



    /*free_dict(dict);*/
    return 0;
}