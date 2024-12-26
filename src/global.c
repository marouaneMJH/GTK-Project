#include "./../include/global.h"



static inline void free_widget(GtkWidget* widget)
{
    if (widget != NULL) {
        gtk_widget_destroy(widget);
        widget = NULL; // Avoid dangling pointers
    }
}