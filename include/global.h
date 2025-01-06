#ifndef GLOBAL_H
#define GLOBAL_H
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdlib.h>

#include "./constants.h"

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

#define MAX_TAG_SIZE 50
#define MAX_VIEW_ID_SIZE 50

#define SET_VIEW_CONFIG_PROPERTY(property, value, view_config)                  \
    if (g_strcmp0(property, "position_x") == 0)                                 \
    {                                                                           \
        view_config->position_x = atoi(value);                                  \
    }                                                                           \
    if (g_strcmp0(property, "position_y") == 0)                                 \
    {                                                                           \
        view_config->position_y = atoi(value);                                  \
    }                                                                           \
    if (g_strcmp0(property, "pack_direction") == 0)                             \
    {                                                                           \
        view_config->pack_direction = atoi(value);                              \
    }                                                                           \
    if (g_strcmp0(property, "box_expand") == 0)                                 \
    {                                                                           \
        view_config->box_expand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE; \
    }                                                                           \
    if (g_strcmp0(property, "box_fill") == 0)                                   \
    {                                                                           \
        view_config->box_fill = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;   \
    }                                                                           \
    if (g_strcmp0(property, "box_padding") == 0)                                \
    {                                                                           \
        view_config->box_padding = atoi(value);                                 \
    }                                                                           \
    if (g_strcmp0(property, "flow_box_order") == 0)                             \
    {                                                                           \
        view_config->flow_box_order = atoi(value);                              \
    }                                                                           \
    if (g_strcmp0(property, "paned_position") == 0)                             \
    {                                                                           \
        view_config->paned_position = atoi(value);                              \
    }

#define DFEAULT_VIEW_CONFIG(view_config) \
    do                                   \
    {                                    \
        view_config->position_x = 0;     \
        view_config->position_y = 0;     \
        view_config->pack_direction = 1; \
        view_config->box_expand = FALSE; \
        view_config->box_fill = FALSE;   \
        view_config->box_padding = 0;    \
        view_config->group = NULL;       \
        view_config->view_id[0] = '\0';  \
    } while (0);

typedef struct
{
    gchar view_id[MAX_VIEW_ID_SIZE];

    // Fixed container
    int position_x;
    int position_y;

    // Box container
    int pack_direction;
    gboolean box_expand;
    gboolean box_fill;
    int box_padding;

    // FlowBox container
    gint flow_box_order;

    // Paned container
    // add1: 0 or add2: 1
    gint paned_position;

    // Ex: radio button
    GtkWidget *group;

} ViewConfig;

typedef struct VIEW
{
    GtkWidget *widget;
    struct VIEW *parent;
    struct VIEW *child;
    struct VIEW *next;
    ViewConfig *view_config;
} View;

// We should rename this from global to core wich means system libs and has more signification

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
// void widget_set_font(GtkWidget *widget, const gchar *font_name, gint font_size);

// TODO: Should be not manipulate the end of tag ">" in the file
// TODO: Should manipulate spaces and tabs and new lines
gchar *read_property(FILE *index, int *status);

// Ignore space within the value
gchar *read_value(FILE *index, int *status);

gboolean is_character(gchar c);

#endif
