#ifndef TEXT_AREA_H
#define TEXT_AREA_H

#include "./../global.h"

/*  default values */
#define DEFAULT_TEXT_AREA_DIMENSIONS \
    {                                \
        .height = 0,                 \
        .width = 0}

#define DEFAULT_TEXT_AREA_MARGINS \
    {                             \
        .bottom = 0,              \
        .top = 0,                 \
        .start = 0,               \
        .end = 0}

#define DEFAULT_TEXT_AREA                           \
    {                                               \
        .font_size = 12,                            \
        .text_color = "\0",                         \
        .bg_color = "\0",                           \
        .is_editable = TRUE,                        \
        .dimensions = DEFAULT_TEXT_AREA_DIMENSIONS, \
        .margins = DEFAULT_TEXT_AREA_MARGINS, \
        .wrap_mode = GTK_WRAP_WORD,                 \
        .hexpand = FALSE,                           \
        .vexpand = FALSE,                           \
        .halign = GTK_ALIGN_FILL,                   \
        .valign = GTK_ALIGN_FILL}

typedef struct
{
    gint font_size; // Font size for text

    gboolean is_editable;  // Editable state
    GtkWrapMode wrap_mode; // Wrap mode for text

    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
    // dimensions
    Dimensions dimensions;
    Margins margins;
    gchar text_color[MAX_COLOR_SIZE]; // Text color
    gchar bg_color[MAX_COLOR_SIZE];   // Background color
} TextAreaConfig;

/**
 * @brief Configure text area properties
 * @param[in] text_area_config pointer to text area configuration
 * @param[in] view_config pointer to view configuration
 * @param[in] property property name to configure
 * @param[in] value property value to set
 * @return ViewConfig pointer
 */
ViewConfig *configure_text_area_property(TextAreaConfig *text_area_config, ViewConfig *view_config, gchar *property, gchar *value);

/**
 * @brief Initialize text area configuration
 * @param[in] index file pointer
 * @param[in] text_area_config text area configuration
 * @return ViewConfig pointer
 */
ViewConfig *init_text_area_config(FILE *index, TextAreaConfig *text_area_config);

/**
 * @brief Create text area widget with configuration
 * @param[in] text_area_config text area configuration structure
 * @return GtkWidget pointer to new text area widget
 */
GtkWidget *create_text_area(TextAreaConfig text_area);

TextAreaConfig *read_text_area_config_from_dialog();

TextAreaConfig *read_text_area_config_from_widget(GtkWidget *widget);

gchar *write_text_area_property(FILE *output_file, View *view, int tabs_number);

#endif
