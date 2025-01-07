#ifndef LABEL_H
#define LABEL_H

#include "./../global.h"

#define MAX_LABEL_TEXT_SIZE 100

typedef struct
{
    /* Text Content */
    gchar label_text[MAX_LABEL_TEXT_SIZE]; // Pointer for dynamic text allocation
    gboolean is_markup;                    // Parse and render Pango markup
    gboolean is_underline;                 // Mnemonic support for underline

    /* Appearance */
    GtkJustification jtype;                 // Text alignment (left, right, center)
    PangoEllipsizeMode ellipsize;           // Ellipsization mode
    gboolean is_wrap;                       // Enable word wrap
    gchar text_color[MAX_COLOR_SIZE];       // Text color
    gchar background_color[MAX_COLOR_SIZE]; // Background color

    /* Behavior */
    gboolean is_selectable; // Text can be copied by user

    /* Layout */
    gint padding; // Padding around the label
} LabelConfig;

/**
 * @brief to initialize the label structure
 * @param[in] label_text the label content of the label
 * @return[ou] pointer to new label
 */
ViewConfig *init_label_config(FILE *index, LabelConfig *label_config);

GtkWidget *create_label(LabelConfig *label);

void free_label(LabelConfig *label);

void free_widget_label(GtkWidget *label);

#endif