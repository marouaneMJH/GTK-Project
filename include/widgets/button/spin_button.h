#ifndef SPIN_BUTTON_H
#define SPIN_BUTTON_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_BOX_DIMENSIONS \
    {                          \
        .height = 0,           \
        .width = 0}

#define DEFAULT_BOX_MARGINS \
    {                       \
        .bottom = 0,        \
        .top = 0,           \
        .start = 0,         \
        .end = 0}

// the default values of spin button structure
#define DEFAULT_SPIN_BUTTON                   \
    {                                         \
        .margins = DEFAULT_BOX_MARGINS,       \
        .dimensions = DEFAULT_BOX_DIMENSIONS, \
        .min = 0,                             \
        .max = 100,                           \
        .step = 1,                            \
        .initial_value = 50,                  \
        .decimal = 2,                         \
        .hexpand = FALSE,                     \
        .vexpand = FALSE,                     \
        .halign = GTK_ALIGN_FILL,             \
        .valign = GTK_ALIGN_FILL,             \
        .is_numeric = TRUE,                   \
        .bg_color = "\0",                     \
        .text_color = "\0",                   \
        .is_digits = FALSE}

typedef struct
{

    gdouble min;
    gdouble max;
    gdouble step;
    gdouble initial_value;
    gint decimal; // Number of decimal number

    /* Appearance & Behavior */
    gboolean is_numeric;
    gboolean is_digits; // Disable decimal places of an number

    gboolean hexpand;
    gboolean vexpand;

    GtkAlign halign;
    GtkAlign valign;
    // todo to free the function
    // GtkWidget* adjustment;

    Margins margins;

    Dimensions dimensions;

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} SpinButtonConfig;

/**
 * @brief create spin button by spin_button structure
 */
GtkWidget *create_spin_button(SpinButtonConfig spin_button_config);

ViewConfig *configure_window_property(SpinButtonConfig *spin_button_config, ViewConfig *view_config, gchar *property, gchar *value);

ViewConfig *init_spin_button_config(FILE *index, SpinButtonConfig *spin_button_config);

/* Signales */
/**
 * @brief Callback function to retrieve and store the value of a GtkSpinButton.
 * @param[in] spin_button A pointer to the GtkSpinButton widget whose value has changed.
 * @param[in, out] val A pointer to a gdouble variable where the current value of the spin button will be stored.
 */
static void get_button_value_call_back(GtkWidget *spin_button, gpointer val);

/**
 * @brief get the spin button value when value changed
 * @param[in] spin_widget pointer to spin button widget that we want to get her value
 * @return[ou] gdouble changed value
 */
gdouble get_spin_button_value(GtkWidget *spin_widget);

SpinButtonConfig *read_spin_button_config_from_dialog();

gchar *write_spin_button_property(FILE *output_file, View *view, int tabs_number);

#endif