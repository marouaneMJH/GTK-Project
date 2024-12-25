#ifndef GLOBAL_H
#define GLOBAL_H
#include <gtk/gtk.h>
#include <stdbool.h>


/* macros constant */
// set the maximum size of label content
#define MAX_TEXT_LABEL 100
#define MAX_COLOR 10

/* macros functions  */
// check if the pointer not null  

#define SAFE_ALLOC(ptr, type)\
    do {\
        ptr = (type *)g_malloc(sizeof(type));\
        if (!ptr) {\
            g_critical("Failed to allocate memory for " #type);\
            return NULL;\
        }\
    } while (0)

#define IS_EXISTE(pointer)\
do{\
if(!pointer)\    
{\
    g_critical(#pointer "not exist.");\
    return  NULL;\
}}while (0)
/* inline function */


// global structure for winget (window, button, label, ...) 
// the demention of Widget
typedef struct 
{
  gint width;
  gint height;
}Dimensions;




#endif
