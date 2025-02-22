#include "./../../../include/containers/windows/window.h"

ViewConfig *configure_window_property(WindowConfig *window_config, ViewConfig *view_config, gchar *property, gchar *value, int *status)
{
    if (!window_config || !property || !value)
    {
        *status = 0;
        return NULL;
    }

    if (g_strcmp0(property, "title") == 0)
        strcpy(window_config->title, value);

    if (g_strcmp0(property, "icon_path") == 0)
        strcpy(window_config->icon_path, value);

    if (g_strcmp0(property, "icon_name") == 0)
        strcpy(window_config->icon_name, value);

    if (g_strcmp0(property, "bg_image") == 0)
        strcpy(window_config->bg_image, value);

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        window_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        window_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        window_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        window_config->margins.end = atoi(value);

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
        window_config->is_fullscreen = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_maximized") == 0)
        window_config->is_maximized = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_modal") == 0)
        window_config->is_modal = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_decorated") == 0)
        window_config->is_decorated = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_keep_above") == 0)
        window_config->is_keep_above = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_keep_below") == 0)
        window_config->is_keep_below = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "new_startup_id") == 0)
        strcpy(window_config->new_startup_id, value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(window_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(window_config->text_color, value);

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
    if (g_strcmp0(property, "has_header") == 0)
        window_config->has_header = strcmp(value, "true") == 0;

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    *status = 1;
    return view_config;
}

ViewConfig *init_window_config(FILE *index, WindowConfig *window_config)
{
    // Check if the window config and the index file is not null
    if (!window_config || !index)
        return NULL;

    // Create view config
    ViewConfig *view_config = NULL;
    SAFE_ALLOC(view_config, ViewConfig, 1);
    DFEAULT_VIEW_CONFIG(view_config);

    // Store the property and value of the tag
    gchar *property = NULL;
    gchar *value = NULL;

    // Read the tag character by character
    gchar c;
    while ((c = fgetc(index)) != '>')
    {
        /* If the character is a letter then go back one character
            Because when the tag is readed the cursor will start with the first letter in the property and it will be lost */
        if (is_character(c))
            fseek(index, -1, SEEK_CUR);

        int status = -1;

        // Read the property of the tag
        property = read_property(index, &status);

        // If the all properties are readed then break the loop and return the view id and pass the properties to the window config
        if (status == 2)
            return view_config;

        // If the property is readed then read the value of the property
        else if (status == 1 && property)
        {
            // Read the value of the property
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                if (g_strcmp0(property, "id") == 0) // Store the view id
                {
                    strcpy(view_config->view_id, value);
                    free(property);
                }
                else
                {
                    // Apply the property value to the window config
                    int config_status;
                    view_config = configure_window_property(window_config, view_config, property, value, &config_status);
                    if (config_status == 0)
                    {
                        printf("Error configuring the property %s\n", property);
                    }
                    free(value);
                    free(property);
                }
            }
        }
    }

    return view_config;
}

GtkWidget *create_window(GtkApplication *app, WindowConfig window_config)
{
    if (!app)
        exit(EXIT_FAILURE);

    GtkWindow *window;
    window = GTK_WINDOW(gtk_application_window_new(app));

    gtk_window_set_title(window, window_config.title);
    gtk_window_set_default_size(window, window_config.dimensions.width, window_config.dimensions.height);
    gtk_window_set_resizable(window, window_config.is_resizable);
    gtk_window_set_position(window, window_config.position);
    window_config.is_fullscreen ? gtk_window_fullscreen(window) : gtk_window_unfullscreen(window);
    window_config.is_maximized ? gtk_window_maximize(window) : gtk_window_unmaximize(window);
    gtk_window_set_modal(window, FALSE);
    gtk_window_set_keep_above(window, window_config.is_keep_above);
    gtk_window_set_keep_below(window, window_config.is_keep_below);
    if (window_config.icon_path && window_config.icon_path[0] != '\0')
        gtk_window_set_icon_from_file(window, window_config.icon_path, NULL);
    else
        gtk_window_set_icon_name(GTK_WINDOW(window), window_config.icon_name);
    gtk_window_set_decorated(window, window_config.is_decorated);
    gtk_window_set_type_hint(window, window_config.hint_type);
    gtk_widget_set_opacity(GTK_WIDGET(window), window_config.opacity);
    // gtk_window_move(window, window_config.move_x, window_config.move_y);
    gtk_window_set_startup_id(window, window_config.new_startup_id);

    // Attach to parent
    if (window_config.parent)
        gtk_window_set_transient_for(window, window_config.parent);

    // GdkRGBA bg_color;
    // gdk_rgba_parse(&bg_color, window_config.bg_color);
    // gtk_widget_override_background_color(GTK_WIDGET(window), GTK_STATE_FLAG_NORMAL, &bg_color);

    gtk_container_set_border_width(GTK_CONTAINER(window), window_config.border_width);

    if (window_config.bg_color && window_config.bg_image[0] != '\0')
        widget_set_background_image(GTK_WIDGET(window), window_config.bg_image, window_config.text_color);

    // Set colors
    if (window_config.bg_color && window_config.bg_color[0] != '\0')
        widget_set_colors(GTK_WIDGET(window), window_config.bg_color, window_config.text_color);

    // Set margins
    widget_set_margins(GTK_WIDGET(window), window_config.margins);
    if (window_config.has_header)
        set_header_bar(GTK_WIDGET(window), window_config.title, window_config.icon_path);

    return GTK_WIDGET(window);
}

void show_window(GtkWidget *window)
{
    gtk_widget_show_all(GTK_WIDGET(window));
}

gchar *write_window_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "window", tabs_number);

    // Get the GtkWindow from the view
    GtkWindow *window = GTK_WINDOW(view->widget);

    // Get the title
    const gchar *title = gtk_window_get_title(window);
    if (g_strcmp0(title, "Window") != 0) // Check if the title is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "title=\"%s\"\n", title);
    }

    // Get the icon name
    const gchar *icon_name = gtk_window_get_icon_name(window);
    if (g_strcmp0(icon_name, "go-home") != 0) // Check if the icon name is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "icon_name=\"%s\"\n", icon_name);
    }

    // Check if the window is resizable
    gboolean is_resizable = gtk_window_get_resizable(window);
    if (is_resizable != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_resizable=\"%s\"\n", is_resizable ? "true" : "false");
    }

    // Get the window position
    gint root_x, root_y;
    gtk_window_get_position(window, &root_x, &root_y);
    if (root_x != 0 || root_y != 0) // Check if it's not the default position
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "position=\"%d,%d\"\n", root_x, root_y);
    }

    // Check if the window is modal
    gboolean is_modal = gtk_window_get_modal(window);
    if (is_modal != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_modal=\"%s\"\n", is_modal ? "true" : "false");
    }

    // Check if the window is decorated
    gboolean is_decorated = gtk_window_get_decorated(window);
    if (is_decorated != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_decorated=\"%s\"\n", is_decorated ? "true" : "false");
    }

    // Check if the window has a header
    gboolean has_header = gtk_window_get_titlebar(window) != NULL;
    if (has_header != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "has_header=\"%s\"\n", has_header ? "true" : "false");
    }

    // Get the window type hint
    GdkWindowTypeHint hint_type = gtk_window_get_type_hint(window);
    if (hint_type != GDK_WINDOW_TYPE_HINT_NORMAL) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hint_type=\"%s\"\n", hint_type == GDK_WINDOW_TYPE_HINT_NORMAL ? "normal" : hint_type == GDK_WINDOW_TYPE_HINT_DIALOG      ? "dialog"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_MENU          ? "menu"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_TOOLBAR       ? "toolbar"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_SPLASHSCREEN  ? "splashscreen"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_UTILITY       ? "utility"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_DOCK          ? "dock"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_DESKTOP       ? "desktop"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_DROPDOWN_MENU ? "dropdown_menu"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_POPUP_MENU    ? "popup_menu"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_TOOLTIP       ? "tooltip"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_NOTIFICATION  ? "notification"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_COMBO         ? "combo"
                                                                                                     : hint_type == GDK_WINDOW_TYPE_HINT_DND           ? "dnd"
                                                                                                                                                       : "unknown");
    }

    // Get the opacity
    gdouble opacity = gtk_widget_get_opacity(GTK_WIDGET(window));
    if (opacity != 1.0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "opacity=\"%f\"\n", opacity);
    }

    return "window";
}
