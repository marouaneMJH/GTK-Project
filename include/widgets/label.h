#ifndef LABEL_H
#define LABEL_H

#include "./../global.h"

#define MAX_LABEL_TEXT_SIZE 100
/* Default values for label configuration */

#define DEFAULT_LABEL_CONTENT \
    {                         \
        .label_text = "\0",   \
        .is_markup = FALSE,   \
        .is_underline = FALSE}

#define DEFAULT_LABEL_APPEARANCE           \
    {                                      \
        .jtype = GTK_JUSTIFICATION_LEFT,   \
        .ellipsize = PANGO_ELLIPSIZE_NONE, \
        .is_wrap = FALSE,                  \
        .text_color = "\0",                \
        .background_color = "\0"}

#define DEFAULT_LABEL_BEHAVIOR \
    {                          \
        .is_selectable = FALSE}

#define DEFAULT_LABEL_LAYOUT \
    {                        \
        .padding = 0}

#define DEFAULT_LABEL                      \
    {                                      \
        .font_size = 12,                   \
        .label_text = "\0",                \
        .is_markup = FALSE,                \
        .is_underline = FALSE,             \
        .jtype = GTK_JUSTIFY_CENTER,       \
        .ellipsize = PANGO_ELLIPSIZE_NONE, \
        .is_wrap = FALSE,                  \
        .text_color = "\0",                \
        .bg_color = "\0",                  \
        .is_selectable = FALSE,            \
        .padding = 0}

typedef struct
{
    gint font_size;
    /* Text Content */
    gchar label_text[MAX_LABEL_TEXT_SIZE]; // Pointer for dynamic text allocation
    gboolean is_markup;                    // Parse and render Pango markup
    gboolean is_underline;                 // Mnemonic support for underline

    /* Appearance */
    GtkJustification jtype;           // Text alignment (left, right, center)
    PangoEllipsizeMode ellipsize;     // Ellipsization mode
    gboolean is_wrap;                 // Enable word wrap
    gchar text_color[MAX_COLOR_SIZE]; // Text color
    gchar bg_color[MAX_COLOR_SIZE];   // Background color

    /* Behavior */
    gboolean is_selectable; // Text can be copied by user

    /* Layout */
    gint padding; // Padding around the label
} LabelConfig;
ViewConfig *configure_label_property(LabelConfig *label_config, ViewConfig *view_config, gchar *property, gchar *value);

/**
 * @brief to initialize the label structure
 * @param[in] label_text the label content of the label
 * @return[ou] pointer to new label
 */
ViewConfig *init_label_config(FILE *index, LabelConfig *label_config);

GtkWidget *create_label(LabelConfig label);

// void free_label(LabelConfig *label);

// void free_widget_label(GtkWidget *label);

#endif