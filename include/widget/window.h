#ifndef WINDOW_H
#define WINDOW_H

#include "./../global.h"


typedef struct
{
    /* Positions and dimention of window */
    Dimensions dimension;
    // if it resizable or not
    gboolean is_resizable;
    // the start up position of the window  (enum)
    GtkWindowPosition position;
    // if the window fullscreen
    gboolean is_fullscreen;
    // maximized the window or not (use it for gtk_window_maximize and gtk_window_unmaximize functions)
    gboolean is_maximized;
    // if the window is modal or not (we can use other windows in same time )
    gboolean is_modal;
    gboolean is_decorated;
    gboolean is_keep_above;
    gboolean is_keep_below;

    /* window information */
    gchar *title;
    // path to the icon of the window
    gchar *icon_path;

    // behavior of the window
    GdkWindowTypeHint hint_type;

    // the parent window
    GtkWindow *parent;

    gdouble opacity;

    gint move_x;
    gint move_y;

    gchar *new_startup_id;

    gchar bg_color[10];

} Window;

Window *init_window(gchar *title);

GtkWindow *create_window(GtkApplication *app, Window *window_data);

#endif