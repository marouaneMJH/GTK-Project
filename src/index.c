#include "./../include/index.h"






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
    strcpy(window->bg_color, "#000000");

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

Entry *init_entry(gchar *text, gchar *placeholder_text,Dimensions dimension)
{
    Entry *entry = (Entry*)malloc(sizeof(Entry));
    entry->text = (gchar*) malloc(50*sizeof(gchar));
    entry->placeholder_text = (gchar*) malloc(50*sizeof(gchar));
    strcpy(entry->text, text);
    strcpy(entry->placeholder_text, placeholder_text);
    entry->dimension = dimension;
    entry->is_visible = TRUE;
    entry->is_editable = TRUE;
    entry->purpose = GTK_INPUT_PURPOSE_FREE_FORM;
    entry->max_length = 50;
    entry->alignment = 0;
    strcpy(entry->bg_color, "#FFFFFF");
    strcpy(entry->text_color, "#000000");
    return entry;
}

GtkWidget *create_entry(Entry *entry_data)
{
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), entry_data->text);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), entry_data->placeholder_text);
    gtk_entry_set_visibility(GTK_ENTRY(entry), entry_data->is_visible);
    // ERROR gtk_entry_set_editable(GTK_ENTRY(entry), entry_data->is_editable);
    gtk_entry_set_input_purpose(GTK_ENTRY(entry), entry_data->purpose);
    gtk_entry_set_max_length(GTK_ENTRY(entry), entry_data->max_length);
    gtk_entry_set_alignment(GTK_ENTRY(entry), entry_data->alignment);
    GdkRGBA bg_color;
    gdk_rgba_parse(&bg_color, entry_data->bg_color);
    gtk_widget_override_background_color(GTK_WIDGET(entry), GTK_STATE_FLAG_NORMAL, &bg_color);
    GdkRGBA text_color;
    gdk_rgba_parse(&text_color, entry_data->text_color);
    gtk_widget_override_color(GTK_WIDGET(entry), GTK_STATE_FLAG_NORMAL, &text_color);
    return entry;
}
