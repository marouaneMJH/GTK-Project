#ifndef GLOBAL_H
#define GLOBAL_H
#include <gtk/gtk.h>
#include <stdbool.h>


#include "./default_values.h"

/* inline function */

/** 
 * @brief free widget memory space
 * @param widget that will destroy it
 * @return void
 */
static inline void free_widget(GtkWidget* widget);



/**
 * @brief global structure for windget (window, button, label, ...) 
 * Dimension of widget, the height and width of widget. for each widget have default value for this structure (macros value)
 */
typedef struct 
{
  gint width;
  gint height;
}Dimensions;

typedef struct
{
    gint top;               // Top margin
    gint bottom;            // Bottom margin
    gint start;              // Start margin
    gint end;             // End  margin
} Margin;











#endif
