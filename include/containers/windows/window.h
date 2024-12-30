#ifndef WINDOW_H
#define WINDOW_H

#include "../../global.h"

/* Max size of element */
#define MAX_WINDOW_TITLE_SIZE 50
#define MAX_ICON_PATH_SIZE 50
#define MAX_STARTUP_ID_SIZE 50

/*  default values */
#define DEFAULT_WINDOW_DIMENSIONS \
    {                             \
        .height = 600,            \
        .width = 500}

#define DEFAULT_WINDOW_MARGINS \
    {                          \
        .bottom = 0,           \
        .top = 0,              \
        .start = 0,            \
        .end = 0}

#define DEFAULT_WINDOW                            \
    {                                             \
        .title = "Window",                        \
        .icon_path = "\0",                        \
        .icon_name = "go-home",                   \
        .dimensions = DEFAULT_WINDOW_DIMENSIONS,  \
        .is_resizable = TRUE,                     \
        .position = GTK_WIN_POS_CENTER,           \
        .is_fullscreen = FALSE,                   \
        .is_maximized = FALSE,                    \
        .is_modal = FALSE,                        \
        .is_modal = FALSE,                        \
        .is_decorated = TRUE,                     \
        .is_keep_above = FALSE,                   \
        .is_keep_below = FALSE,                   \
        .hint_type = GDK_WINDOW_TYPE_HINT_NORMAL, \
        .margins = DEFAULT_WINDOW_MARGINS,        \
        .parent = NULL,                           \
        .opacity = 1,                             \
        .move_x = 0,                              \
        .move_y = 0,                              \
        .border_width = 0,                        \
        .new_startup_id = "\0",                   \
        .bg_color = "\0",                         \
        .text_color = "\0"}

typedef struct
{
    /* window information */
    gchar title[MAX_WINDOW_TITLE_SIZE];

    // path to the icon of the window
    gchar icon_path[MAX_ICON_PATH_SIZE];

    gchar icon_name[MAX_ICON_NAME_SIZE];

    /* Positions and dimention of window */
    Dimensions dimensions;

    // the start up position of the window  (enum)
    GtkWindowPosition position;

    // if it resizable or not
    gboolean is_resizable;
    // if the window fullscreen
    gboolean is_fullscreen;
    // maximized the window or not (use it for gtk_window_maximize and gtk_window_unmaximize functions)
    gboolean is_maximized;
    // if the window is modal or not (we can use other windows in same time )
    gboolean is_modal;
    gboolean is_decorated;
    gboolean is_keep_above;
    gboolean is_keep_below;

    // behavior of the window
    GdkWindowTypeHint hint_type;

    // the parent window
    GtkWindow *parent;

    Margins margins;

    gdouble opacity;

    gint move_x;
    gint move_y;

    gint border_width;

    gchar new_startup_id[MAX_STARTUP_ID_SIZE];

    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} WindowConfig;

/**
 * @brief initial the window by default value
 * @return the default window structure
 */
WindowConfig *init_window(gchar *title);

/**
 * @brief function to edit predefined window with juste
 * @return the edited window
 */
WindowConfig *edit_window(WindowConfig *window_config,
                          gchar *title,
                          gint width,
                          gint height,
                          gboolean is_resizable,
                          gchar *bg_color);

GtkWidget *create_window(GtkApplication *app, WindowConfig *window_config);

#endif