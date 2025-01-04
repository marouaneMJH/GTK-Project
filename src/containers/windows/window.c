#include "./../../../include/global.h"
#include "./../../../include/containers/windows/window.h"

gchar *read_property(FILE *index, int *status)
{
    gchar *property = NULL;
    SAFE_ALLOC(property, gchar, MAX_PROPERTY_SIZE);

    int i = 0;
    gchar c;
    while ((c = fgetc(index)) != '>')
    {
        if (c == '=')
        {
            *status = 1;
            property[i] = '\0';
            return property;
        }
        if (c != ' ' && c != '\n' && c != '\t')
            property[i++] = c;
    }
    if (c == '>') 
        *status = 2;
    return NULL;
}

gchar *read_value(FILE *index, int *status)
{
    gchar *value = NULL;
    SAFE_ALLOC(value, gchar, MAX_PROPERTY_SIZE);

    int i = 0;
    gboolean reading_flag = FALSE;
    gchar c;

    while ((c = fgetc(index)) != '"' || !reading_flag)
    {
        if (c != '"' && !reading_flag)
        {
            *status = -1;
            return value;
        }

        if (c == '"' && !reading_flag)
            reading_flag = !reading_flag;

        else if (c != ' ' && c != '\n' && c != '\t')
            value[i++] = c;
    }
    value[i] = '\0';
    *status = 1;
    return value;
}

int apply_property_value(WindowConfig *window_config, gchar *property, gchar *value)
{
    if (!window_config || !property || !value)
        return -1;

    if (g_strcmp0(property, "title") == 0)
        strcpy(window_config->title, value);

    if (g_strcmp0(property, "icon_path") == 0)
        strcpy(window_config->icon_path, value);

    if (g_strcmp0(property, "icon_name") == 0)
    {
        printf("Icon name: %s\n", value);
        strcpy(window_config->icon_name, value);
    }

    // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        window_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        window_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        window_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        window_config->dimensions.width = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        window_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        window_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "border_width") == 0)
        window_config->border_width = atoi(value);

    if (g_strcmp0(property, "opacity") == 0)
        window_config->opacity = atof(value);

    // Boolean options
    if (g_strcmp0(property, "resizable") == 0)
        window_config->is_resizable = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_fullscreen") == 0)
        window_config->is_resizable = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_maximized") == 0)
        window_config->is_resizable = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_modal") == 0)
        window_config->is_resizable = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_decorated") == 0)
        window_config->is_resizable = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_keep_above") == 0)
        window_config->is_resizable = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_keep_below") == 0)
        window_config->is_resizable = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "new_startup_id") == 0)
        strcpy(window_config->new_startup_id, value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(window_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(window_config->bg_color, value);

    if (g_strcmp0(property, "position") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            window_config->position = GTK_WIN_POS_CENTER;
        else if (g_strcmp0(value, "mouse") == 0)
            window_config->position = GTK_WIN_POS_MOUSE;
        else if (g_strcmp0(value, "center_always") == 0)
            window_config->position = GTK_WIN_POS_CENTER_ALWAYS;
        else if (g_strcmp0(value, "none") == 0)
            window_config->position = GTK_WIN_POS_NONE;
    }

    if (g_strcmp0(property, "hint_type") == 0)
    {
        if (g_strcmp0(value, "normal") == 0)
            window_config->hint_type = GDK_WINDOW_TYPE_HINT_NORMAL;
        else if (g_strcmp0(value, "dialog") == 0)
            window_config->hint_type = GDK_WINDOW_TYPE_HINT_DIALOG;
        else if (g_strcmp0(value, "menu") == 0)
            window_config->hint_type = GDK_WINDOW_TYPE_HINT_MENU;
        else if (g_strcmp0(value, "toolbar") == 0)
            window_config->hint_type = GDK_WINDOW_TYPE_HINT_TOOLBAR;
        else if (g_strcmp0(value, "splashscreen") == 0)
            window_config->hint_type = GDK_WINDOW_TYPE_HINT_SPLASHSCREEN;
        else if (g_strcmp0(value, "utility") == 0)
            window_config->hint_type = GDK_WINDOW_TYPE_HINT_UTILITY;
        else if (g_strcmp0(value, "dock") == 0)
            window_config->hint_type = GDK_WINDOW_TYPE_HINT_DOCK;
        else if (g_strcmp0(value, "desktop") == 0)
            window_config->hint_type = GDK_WINDOW_TYPE_HINT_DESKTOP;
    }

    return 1;
}

gchar *init_window(WindowConfig *window_config, FILE *index)
{
    if (!window_config || !index)
        return NULL;

    gchar c;
    gchar *property = NULL;
    gchar *value = NULL;
    gchar *view_id = NULL;
    while ((c = fgetc(index)) != '>')
    {
        if ((c > 'A' && c < 'Z') || (c > 'a' && c < 'z'))
            fseek(index, -1, SEEK_CUR);

        int status = -1;
        property = read_property(index, &status);
        if (status == 2)
        {
            return view_id;
        }
        else if (status == 1 && property)
        {
            printf("Property: %s\n", property);
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                printf("Value: %s\n", value);
                if (g_strcmp0(property, "id") == 0)
                    view_id = value;
                else
                    apply_property_value(window_config, property, value);
            }
        }
    }

    return view_id;
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
        window_config->dimensions.width = width;

    if (height > 0)
        window_config->dimensions.height = height;

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
    gtk_window_set_default_size(window, window_config->dimensions.width, window_config->dimensions.height);
    gtk_window_set_resizable(window, window_config->is_resizable);
    gtk_window_set_position(window, window_config->position);
    window_config->is_fullscreen ? gtk_window_fullscreen(window) : gtk_window_unfullscreen(window);
    window_config->is_maximized ? gtk_window_maximize(window) : gtk_window_unmaximize(window);
    gtk_window_set_modal(window, window_config->is_modal);
    gtk_window_set_keep_above(window, window_config->is_keep_above);
    gtk_window_set_keep_below(window, window_config->is_keep_below);
    if (window_config->icon_path && window_config->icon_path[0] != '\0')
        gtk_window_set_icon_from_file(window, window_config->icon_path, NULL);
    else
        gtk_window_set_icon_name(GTK_WINDOW(window), window_config->icon_name);
    gtk_window_set_decorated(window, window_config->is_decorated);
    gtk_window_set_type_hint(window, window_config->hint_type);
    gtk_widget_set_opacity(GTK_WIDGET(window), window_config->opacity);
    // gtk_window_move(window, window_config->move_x, window_config->move_y);
    gtk_window_set_startup_id(window, window_config->new_startup_id);

    // Attach to parent
    if (window_config->parent)
        gtk_window_set_transient_for(window, window_config->parent);

    // GdkRGBA bg_color;
    // gdk_rgba_parse(&bg_color, window_config->bg_color);
    // gtk_widget_override_background_color(GTK_WIDGET(window), GTK_STATE_FLAG_NORMAL, &bg_color);

    gtk_container_set_border_width(GTK_CONTAINER(window), window_config->border_width);

    // Set colors
    widget_set_colors(GTK_WIDGET(window), window_config->bg_color, window_config->text_color);

    // Set margins
    widget_set_margins(GTK_WIDGET(window), window_config->margins);
    return GTK_WIDGET(window);
}


void show_window(GtkWidget* window)
{
    gtk_widget_show_all(GTK_WIDGET(window)); 
}