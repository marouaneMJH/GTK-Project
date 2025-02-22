#ifndef GLOBAL_H
#define GLOBAL_H
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./constants.h"
#include "widgets/view/view.h"
#include "./widgets/View/xml_builder/xml_writer_globals.h"

/* Global macros  */

// check if the pointer is not null
#define SAFE_ALLOC(ptr, type, length)                           \
    do                                                          \
    {                                                           \
        ptr = (type *)g_malloc(length * sizeof(type));          \
        if (!ptr)                                               \
        {                                                       \
            g_critical("Failed to allocate memory for " #type); \
        }                                                       \
    } while (0)

#define IS_EXISTE(pointer)                      \
    do                                          \
    {                                           \
        if (!pointer)                           \
        {                                       \
            g_critical(#pointer " not exist."); \
            return NULL;                        \
        }                                       \
    } while (0)

extern View *root_view_global;
extern View *root_dialog_view_global;
extern GtkApplication *root_app;

extern View *new_root_view_global;

// We should rename this from global to core wich means system libs and has more signification

/**
 * @brief global structure for windget (window, button, label, ...)
 * Dimension of widget, the height and width of widget. for each widget have default value for this structure (macros value)
 */
/**
 * @brief Structure to hold the dimensions of a widget
 */
typedef struct
{
    gint width;  /**< Width of the widget */
    gint height; /**< Height of the widget */
} Dimensions;

/**
 * @brief Structure to hold the margins of a widget
 */
typedef struct
{
    gint top;    /**< Top margin */
    gint bottom; /**< Bottom margin */
    gint start;  /**< Start margin */
    gint end;    /**< End margin */
} Margins;

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
 * @param color the color of label text that will be applyed on the widget
 * @param bg_image the background image name of the widget
 * @return GtkStyleContext pointer
 */
GtkStyleContext *get_style_provider_context(GtkWidget *widget, const gchar *bg_color, const gchar *color, const gchar *bg_image);

/**
 * @brief This function gives a background and text color to a widget
 * @param widget Widget cible
 * @param bg_color The background color
 * @param color The text color
 * @return void
 */
void widget_set_colors(GtkWidget *widget, const gchar *bg_color, const gchar *color);

/**
 * @brief This function gives a background image to a widget
 * @param widget Widget cible
 * @param bg_image The background image name
 * @param color The text color
 * @return void
 */
void widget_set_background_image(GtkWidget *widget, const gchar *bg_image, const gchar *color);

/**
 * @brief This function gives a background image to a widget without using css
 * @param widget Widget cible
 * @param bg_image The background image name
 * @return void
 */
void widget_set_background_image_without_css(GtkWidget *widget, const gchar *bg_image);

/**
 * @brief This function add margins to a widget
 * @param widget Widget cible
 * @param top The top margin
 * @param bottom The bottom margin
 * @param start The left margin
 * @param end The right margin
 * @return void
 */
void widget_set_margins(GtkWidget *widget, Margins margins);

/**
 * @brief This function set the text color of a widget
 * @param widget Widget cible
 * @param color The text color
 * @param state The state of the widget (ex: GTK_STATE_FLAG_NORMAL, GTK_STATE_FLAG_ACTIVE, ...)
 * @return void
 */
// void widget_set_background_color(GtkWidget *widget, const gchar *color, GtkStateFlags state);

/**
 * @brief This function set the text color of a widget
 * @param widget Widget cible
 * @param color The text color
 * @param state The state of the widget (ex: GTK_STATE_FLAG_NORMAL, GTK_STATE_FLAG_ACTIVE, ...)
 * @return void
 */
// void widget_set_text_color(GtkWidget *widget, const gchar *color, GtkStateFlags state);

/**
 * @brief This function set the font of a widget
 * @param widget Widget cible
 * @param font_name The font name or family (ex: "Arial, SansSerif")
 * @param font_size The font size
 * @return void
 */
void widget_set_font_size(GtkWidget *widget, int size);

// TODO: Should be not manipulate the end of tag ">" in the file
// TODO: Should manipulate spaces and tabs and new lines
gchar *read_property(FILE *index, int *status);

// Ignore space within the value
gchar *read_value(FILE *index, int *status);

gboolean is_character(gchar c);

/**
 * @typedef ConfigurePropertyCallback
 * @brief A callback function type for configuring properties.
 *
 * This callback function is used to configure specific properties
 * for a given configuration type.
 *
 * @param config A pointer to the specific configuration structure.
 * @param view_config A pointer to the ViewConfig structure.
 * @param property The property name as a string.
 * @param value The property value as a string.
 * @return A pointer to the updated ViewConfig structure.
 */
typedef ViewConfig *(*ConfigurePropertyCallback)(void *config, ViewConfig *view_config, gchar *property, gchar *value);

/**
 * @brief Initialize a generic configuration using a callback function.
 *
 * This function reads properties and their values from the provided file index
 * and uses the callback function to configure the specific properties for
 * the given configuration.
 *
 * @param index The file pointer to the configuration index file.
 * @param config A pointer to the specific configuration structure.
 * @param configure_property_callback The callback function to configure properties.
 * @return A pointer to the initialized ViewConfig structure, or NULL on failure.
 */
ViewConfig *init_generic_config(FILE *index, void *config, ConfigurePropertyCallback configure_property_callback);
/**
 * @brief Set the fixed size of a widget.
 * @param widget The GtkWidget to resize.
 * @param dimensions The dimensions structure containing width and height.
 */
void set_widget_size(GtkWidget *widget, Dimensions dimensions);

/**
 * @brief function to constrole font family
 * @param widget The widget to change font
 * @param font_family a string indicate the font family
 *
 * here a list of font family example:
 * 1.   "Arial"
 * 2.   "Courier New"
 * 3.   "Times New Roman"
 * 4.   "Comic Sans MS"
 * 5.   "Verdana"
 */
void widget_set_font_family(GtkWidget *widget, const char *font_family);

/**
 * @brief Finds a view by its ID in a graph of views.
 *
 * This function searches for a view with the specified ID in a graph of views.
 * Each node in the graph contains pointers to its child and next (sibling) views.
 *
 * @param view_id The ID of the view to find.
 * @param root_view The root view of the graph to start the search from.
 * @return A pointer to the view with the specified ID, or NULL if not found.
 */
View *find_view_by_id(char *view_id, View *root_view);

/**
 * @brief Set the header bar of a window.
 *
 * This function sets the title and icon of the header bar of a window.
 *
 * @param window The window to set the header bar for.
 * @param title The title of the header bar.
 * @param icon_path The path to the icon image file.
 */
void set_header_bar(GtkWidget *window, const gchar *title, const gchar *icon_path);

#endif
