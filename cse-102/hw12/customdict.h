#ifndef CUSTOMDICT_H
#define CUSTOMDICT_H

union Value {
    int integer;
    float f;
    double d;
    char c;
};

struct Item {
    char* key;
    union Value* value;
};

struct CustomDict {
    struct Item* items;
    int capacity;
    int size;
};

struct CustomDict* create_dict();
void add_item(struct CustomDict* dict, char* key, union Value* value);
void delete_item(struct CustomDict* dict, char* key);
void set_value(struct CustomDict* dict, char* key, union Value* value);
union Value* search_item(struct CustomDict* dict, char* key);
void sort_dict(struct CustomDict* dict);
void print_dict(struct CustomDict* dict);
void free_dict(struct CustomDict* dict);
int read_csv(struct CustomDict* dict, const char* filename);

#endif /* CUSTOMDICT_H */