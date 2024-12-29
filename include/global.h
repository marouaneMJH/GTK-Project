#ifndef GLOBAL_H
#define GLOBAL_H
#include <gtk/gtk.h>
#include <stdbool.h>

#include "./constants.h"


/**
 * @brief global structure for windget (window, button, label, ...)
 * Dimension of widget, the height and width of widget. for each widget have default value for this structure (macros value)
 */
typedef struct
{
  gint width;
  gint height;
} Dimensions;

typedef struct
{
  gint top;    // Top margin
  gint bottom; // Bottom margin
  gint start;  // Start margin
  gint end;    // End  margin
} Margin;

/* inline function */

/**
 * @brief free widget memory space
 * @param widget that will destroy it
 * @return void
 */
// inline void free_widget(GtkWidget *widget);

/* Global functions */
/**
 * @brief This function init the style provider context that hold the css code and apply it in the screen
 * @param widget the widget that we want apply the style on it
 * @param bg_color the background color will be applyed on the widget
 * @param color the color of label that will be applyed on the widget
 * @return GtkStyleContext pointer
 */
GtkStyleContext *get_style_provider_context(GtkWidget *widget, const gchar *bg_color, const gchar *color);


/**
 * @brief This function gives a background and text color to a widget
 * @param widget Widget cible
 * @param bg_color The background color
 * @param color The text color
 * @return void
 */
void widget_set_colors(GtkWidget *widget, const gchar *bg_color, const gchar *color);


/* Global macros  */

// check if the pointer is not null  
#define SAFE_ALLOC(ptr, type, length)\
    do {\
        ptr = (type *)g_malloc(length*sizeof(type));\
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
