
#ifndef ENTRY_H
#define ENTRY_H

// TODO: Add entry icon
// TODO: Add entry adjustment
// TODO: Add entry buffer

#include "./../global.h"

/* Max size of entry text */
#define MAX_ENTRY_TEXT_SIZE 100

/* Max size of entry placeholder text */
#define MAX_ENTRY_PLACEHOLDER_TEXT_SIZE 50

/* Default dimensions for entry */
#define DEFAULT_ENTRY_DIMENSIONS \
    {                            \
        .height = 0,             \
        .width = 0}

/* Default margins for entry */
#define DEFAULT_ENTRY_MARGINS \
    {                         \
        .bottom = 0,          \
        .top = 0,             \
        .start = 0,           \
        .end = 0}

/* Default entry configuration */
#define DEFAULT_ENTRY                           \
    {                                           \
        .text = "",                             \
        .placeholder_text = "",                 \
        .is_visible = TRUE,                     \
        .purpose = GTK_INPUT_PURPOSE_FREE_FORM, \
        .dimensions = DEFAULT_ENTRY_DIMENSIONS, \
        .margins = DEFAULT_ENTRY_MARGINS,       \
        .opacity = 1,                           \
        .bg_color = "\0",                       \
        .text_color = "\0",                     \
        .overwrite_mode = FALSE,                \
        .max_length = 100,                      \
        .alignment = 0,                         \
        .completion = NULL,                     \
        .progress_fraction = 0,                 \
        .progress_pulse_step = 0,               \
        .activates_default = FALSE,             \
        .hexpand = FALSE,                       \
        .vexpand = FALSE,                       \
        .halign = GTK_ALIGN_FILL,               \
        .valign = GTK_ALIGN_FILL,               \
        .has_frame = TRUE,                      \
        .has_delete_icon = FALSE}

/**
 * @brief Structure to configure an entry widget
 */
typedef struct
{
    /* Basic properties */
    gchar text[MAX_ENTRY_TEXT_SIZE];                         // The text displayed in the entry
    gchar placeholder_text[MAX_ENTRY_PLACEHOLDER_TEXT_SIZE]; // Placeholder text shown when entry is empty
    gboolean is_visible;                                     // Whether the entry is visible or hidden
    GtkInputPurpose purpose;                                 // Purpose of the entry (e.g., free form, number, etc.)

    
    /* Entry appearance */
    gboolean has_delete_icon;         // Whether the entry has a delete icon
    gboolean has_frame;               // Whether the entry has a frame
    gdouble opacity;                  // Opacity of the entry (0.0 to 1.0)
    
    /* Text handling */
    gboolean overwrite_mode; // Whether the entry is in overwrite mode
    gint max_length;         // Maximum length of the text
    gfloat alignment;        // Alignment of the text (0.0 to 1.0)
    
    /* Progress and completion */
    GtkEntryCompletion *completion; // Completion object for auto-completion
    gdouble progress_fraction;      // Fraction of progress (0.0 to 1.0)
    gdouble progress_pulse_step;    // Step size for progress pulse
    
    /* Activation */
    gboolean activates_default; // Whether the entry activates the default widget when Enter is pressed
    
    /* Dimensions and placement */
    Dimensions dimensions; // Dimensions of the entry
    Margins margins;       // Margins around the entry

    gboolean hexpand;
    gboolean vexpand;
    GtkAlign halign;
    GtkAlign valign;
    gchar bg_color[MAX_COLOR_SIZE];   // Background color (e.g., "\0")
    gchar text_color[MAX_COLOR_SIZE]; // Text color (e.g., "#000000")

} EntryConfig;

ViewConfig *init_entry_config(FILE *index, EntryConfig *entry_config);

/**
 * @brief Create an entry widget with the specified configuration
 * @param[in] entry_data Pointer to the entry configuration structure
 * @return GtkWidget* Pointer to the new entry widget
 */
GtkWidget *create_entry(EntryConfig entry_data);

EntryConfig *read_entry_config_from_dialog();

EntryConfig *read_entry_config_from_widget(GtkWidget *widget);

gchar *write_entry_property(FILE *output_file, View *view, int tabs_number);

#endif