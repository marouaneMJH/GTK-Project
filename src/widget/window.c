#include "./../../include/global.h"
#include "./../../include/widget/window.h"

WindowConfig *init_window(gchar *title)
{
    // TODO: Read from xml file and initialize the window structure

    WindowConfig *window_config = (WindowConfig *)malloc(sizeof(WindowConfig));
    window_config->title = (gchar *)malloc(50 * sizeof(gchar));
    if (title)
        strcpy(window_config->title, title);
    window_config->new_startup_id = NULL;
    window_config->dimension.width = 600;
    window_config->dimension.height = 500;
    window_config->is_resizable = TRUE;
    window_config->position = GTK_WIN_POS_CENTER;
    window_config->is_fullscreen = FALSE;
    window_config->is_maximized = FALSE;
    window_config->is_modal = FALSE;
    window_config->is_decorated = TRUE;
    window_config->is_keep_above = FALSE;
    window_config->is_keep_below = FALSE;
    window_config->icon_path = NULL;
    window_config->hint_type = GDK_WINDOW_TYPE_HINT_NORMAL;
    window_config->parent = NULL;
    window_config->move_x = 0;
    window_config->move_y = 0;
    window_config->opacity = 1;
    strcpy(window_config->bg_color, "#ffffff");

    return window_config;
}

WindowConfig *edit_window(WindowConfig *window_config,
                          gchar *title,
                          gint width,
                          gint height,
                          gboolean is_resizable,
                          gchar *bg_color)
{
    if (!window_config)
    {
        printf("\nthe window_config not exist");
        return window_config;
    }

    if (title)
        strcpy(window_config->title, title);

    if (width > 0)
        window_config->dimension.width = width;

    if (height > 0)
        window_config->dimension.height = height;

    window_config->is_resizable = is_resizable;
    if (bg_color != NULL)
        strcpy(window_config->bg_color, bg_color);

    return window_config;
}

GtkWidget *create_window(GtkApplication *app, WindowConfig *window_config)
{

    if (!window_config)
        exit(EXIT_FAILURE);
    if (!app)
        exit(EXIT_FAILURE);

    GtkWindow *window;
    window = GTK_WINDOW(gtk_application_window_new(app));

    gtk_window_set_title(window, window_config->title);
    gtk_window_set_default_size(window, window_config->dimension.width, window_config->dimension.height);
    gtk_window_set_resizable(window, window_config->is_resizable);
    gtk_window_set_position(window, window_config->position);
    window_config->is_fullscreen ? gtk_window_fullscreen(window) : gtk_window_unfullscreen(window);
    window_config->is_maximized ? gtk_window_maximize(window) : gtk_window_unmaximize(window);
    gtk_window_set_modal(window, window_config->is_modal);
    gtk_window_set_keep_above(window, window_config->is_keep_above);
    gtk_window_set_keep_below(window, window_config->is_keep_below);
    if (window_config->icon_path)
        gtk_window_set_icon_from_file(window, window_config->icon_path, NULL);
    gtk_window_set_decorated(window, window_config->is_decorated);
    gtk_window_set_type_hint(window, window_config->hint_type);
    gtk_widget_set_opacity(GTK_WIDGET(window), window_config->opacity);
    // gtk_window_move(window, window_config->move_x, window_config->move_y);
    gtk_window_set_startup_id(window, window_config->new_startup_id);
    if (window_config->parent)
        gtk_window_set_transient_for(window, window_config->parent);

    // GdkRGBA bg_color;
    // gdk_rgba_parse(&bg_color, window_config->bg_color);
    // gtk_widget_override_background_color(GTK_WIDGET(window), GTK_STATE_FLAG_NORMAL, &bg_color);

    widget_set_colors(GTK_WIDGET(window), window_config->bg_color, NULL);
    return GTK_WIDGET(window);
}
