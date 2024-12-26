#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H


/* macros constant */
// set the maximum size of label content
#define MAX_TEXT_LABEL 100
#define MAX_COLOR 10





/* function macros  */

// check if the pointer not null  
#define SAFE_ALLOC(ptr, type)\
    do {\
        ptr = (type *)g_malloc(sizeof(type));\
        if (!ptr) {\
            g_critical("Failed to allocate memory for " #type);\
            return NULL;\
        }\
    } while (0)

#define IS_EXISTE(pointer) \
do { \
    if (!pointer) { \
        g_critical(#pointer " not exist."); \
        return NULL; \
    } \
} while (0)



#endif