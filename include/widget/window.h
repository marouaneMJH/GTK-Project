#include "./../global.h"

// the start up position of the window
typedef enum
{
    GTK_WINDOW_CENTER,
    GTK_WINDOW_POS_CENTER_ALWAYS,
    GTK_WINDOW_POS_CENTER_ON_PARENT,
    GTK_WINDOW_POS_MOUSE,
    GTK_WINDOW_POS_NONE
} GtkPosition;

typedef struct
{
    /* Positions and dimention of window */
    Dimension dimension;
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




Window* init_window(gchar *title)
{
    // TODO: Read from xml file and initialize the window structure

    Window *window = (Window*)malloc(sizeof(Window));
    window->title = (gchar*) malloc(50*sizeof(gchar));
    strcpy(window->title, title);
    window->new_startup_id = NULL;
    window->dimension.width = 400;
    window->dimension.height = 400;
    window->is_resizable = TRUE;
    window->position = GTK_WIN_POS_CENTER;
    window->is_fullscreen = FALSE;
    window->is_maximized = FALSE;
    window->is_modal = FALSE;
    window->is_decorated = TRUE;
    window->is_keep_above = FALSE;
    window->is_keep_below = FALSE;
    window->icon_path = NULL;
    window->hint_type = GDK_WINDOW_TYPE_HINT_NORMAL;
    window->parent = NULL;
    window->move_x = 0;
    window->move_y = 0;
    window->opacity = 1;

    return window;
}


GtkWindow* create_window(GtkApplication *app , Window *window_data)
{

    if (!window_data) exit(EXIT_FAILURE);
    if (!app) exit(EXIT_FAILURE);

    GtkWindow *window;
    window = GTK_WINDOW(gtk_application_window_new(app));

    gtk_window_set_title(window, window_data->title);
    gtk_window_set_default_size(window, window_data->dimension.width, window_data->dimension.height);
    gtk_window_set_resizable(window, window_data->is_resizable);
    gtk_window_set_position(window, window_data->position);
    window_data->is_fullscreen ? gtk_window_fullscreen(window) : gtk_window_unfullscreen(window);
    window_data->is_maximized ? gtk_window_maximize(window) : gtk_window_unmaximize(window);
    gtk_window_set_modal(window, window_data->is_modal);
    gtk_window_set_keep_above(window, window_data->is_keep_above);
    gtk_window_set_keep_below(window, window_data->is_keep_below);
    if (window_data->icon_path) gtk_window_set_icon_from_file(window, window_data->icon_path, NULL);
    gtk_window_set_decorated(window, window_data->is_decorated);
    gtk_window_set_type_hint(window, window_data->hint_type);
    gtk_widget_set_opacity(GTK_WIDGET(window), window_data->opacity);
    //gtk_window_move(window, window_data->move_x, window_data->move_y);
    gtk_window_set_startup_id(window, window_data->new_startup_id);
    if(window_data->parent) gtk_window_set_transient_for(window, window_data->parent);

    GdkRGBA bg_color;
    gdk_rgba_parse(&bg_color, window_data->bg_color);
    gtk_widget_override_background_color(GTK_WIDGET(window), GTK_STATE_FLAG_NORMAL, &bg_color);

    return window;
}