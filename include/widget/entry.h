#ifndef ENTRY_H
#define ENTRY_H

#include "../global.h"

typedef struct {

    GtkWidget *entry;
    Dimensions dimension;
    gchar *text;
    gchar *placeholder_text;
    gboolean is_visible;
    gboolean is_editable;
    GtkInputPurpose purpose;

    gint max_length;
    gfloat alignment;
    gchar bg_color[10];
    gchar text_color[10];

}Entry;

Entry *init_entry(gchar *text, gchar *placeholder_text,Dimensions dimension);
GtkWidget *create_entry(Entry *entry_data);


#endif