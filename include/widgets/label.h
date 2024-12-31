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
} Label;

/**
 * @brief to initialize the label structure
 * @param[in] label_text the label content of the label
 * @return[ou] pointer to new label
 */
Label *init_label(const gchar *label_text);

Label *edit_label(
    gchar *label_text,
    gboolean is_markup,
    gboolean is_underline,
    GtkJustification jtype,
    PangoEllipsizeMode ellipsize,
    gboolean is_wrap,
    gboolean is_selectable,
    gchar *text_color,
    gchar *background_color);

void apply_label_colors(GtkWidget *label_widget, Label *label);

GtkWidget *create_label(Label *label);

void free_label(Label *label);

void free_widget_label(GtkWidget *label);

#endif