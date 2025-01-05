#include "./../../include/builder.h"

View *create_view(gchar *view_id, GtkWidget *widget, ViewConfig *view_config)
{
    View *view = NULL;
    SAFE_ALLOC(view, View, 1);
    if (!view)
        g_critical("Failed: create new view failed!\n");

    view->child = NULL;
    view->parent = NULL;
    view->next = NULL;
    view->view_config = view_config;
    view->widget = widget;

    g_strlcpy(view->view_id, view_id, MAX_VIEW_ID_SIZE);

    return view;
}

gchar *read_tag(FILE *index)
{
    printf("Reading tag\n");
    gchar *tag = NULL;
    SAFE_ALLOC(tag, gchar, MAX_TAG_SIZE);

    int i = 0;
    char c;
    fscanf(index, "%s", tag);
    /*while ((c = fgetc(index)) != '>')
    {
        if (c == ' ' || c == '\n')
            break;

        tag[i++] = c;
    }

    tag[i] = '\0';*/

    return tag;
}

int get_view_index(FILE *index, gchar *widget_tag)
{
    if (!widget_tag)
        return -1;
    if (g_strcmp0(widget_tag, "window") == 0)
        return WindowTag;

    if (g_strcmp0(widget_tag, "scrolled_window") == 0)
        return ScrolledWindowTag;

    if (g_strcmp0(widget_tag, "box") == 0)
        return BoxTag;

    if (g_strcmp0(widget_tag, "fixed") == 0)
        return FixedTag;

    if (g_strcmp0(widget_tag, "stack") == 0)
        return StackTag;

    if (g_strcmp0(widget_tag, "notebook") == 0)
        return NotebookTag;

    if (g_strcmp0(widget_tag, "button") == 0)
        return ButtonTag;

    if (g_strcmp0(widget_tag, "switch") == 0)
        return SwitchTag;

    if (g_strcmp0(widget_tag, "entry") == 0)
        return EntryTag;

    if (g_strcmp0(widget_tag, "label") == 0)
        return LabelTag;

    if (g_strcmp0(widget_tag, "separator") == 0)
        return SeparatorTag;

    if (g_strcmp0(widget_tag, "menu_bar") == 0)
        return MenuBarTag;

    if (g_strcmp0(widget_tag, "menu") == 0)
        return MenuTag;

    if (g_strcmp0(widget_tag, "menu_item") == 0)
        return MenuItemTag;

    if (g_strcmp0(widget_tag, "radio_button") == 0)
        return RadioButtonTag;

    if (g_strcmp0(widget_tag, "image") == 0)
        return ImageTag;

    return -1;
}

int link_with_box_container(GtkWidget *child, GtkWidget *parent, ViewConfig *view_config)
{
    if (!GTK_IS_BOX(parent))
        return 0;

    if (view_config->pack_direction == 0)
        gtk_box_pack_end(GTK_BOX(parent), child, FALSE, FALSE, 5);
    else
        gtk_box_pack_start(GTK_BOX(parent), child, FALSE, FALSE, 5);

    return 1;
}

int link_with_fixed_container(GtkWidget *child, GtkWidget *parent, ViewConfig *view_config)
{
    if (!GTK_IS_FIXED(parent))
        return 0;
    gtk_fixed_put(GTK_FIXED(parent), child, 10, 10);
    return 1;
}

int link_with_container(GtkWidget *child, GtkWidget *parent, ViewConfig *view_config)
{
    if (link_with_box_container(parent, child, view_config))
        return 1;
    if (link_with_fixed_container(parent, child, view_config))
        return 1;

    return 0;
}

View *add_view(View *view, View *relative, gboolean is_relative_container)
{
    if (!view)
        return NULL;

    if (!relative)
        return view;

    // Group radio buttons
    if (GTK_IS_RADIO_BUTTON(view->widget))
    {
        printf("This view is a RADIO BUTTON => %s\n", view->view_id);

        if (GTK_IS_RADIO_BUTTON(relative->widget) && !relative->view_config->group)
        {
            view->view_config->group = relative->widget;
            radio_button_set_group(view->widget, relative->widget);
        }
        else
        {
            view->view_config->group = relative->view_config->group;
            radio_button_set_group(view->widget, relative->view_config->group);
        }
    }

    if (is_relative_container)
    {
        view->parent = relative;
        relative->child = view;

        // Window case
        if (GTK_IS_WINDOW(relative->widget))
        {
            printf("The relative: %s ==> is a window\n", relative->view_id);
            gtk_container_add(GTK_CONTAINER(relative->widget), view->widget);
        }

        link_with_container(relative->widget, view->widget, view->view_config);
    }
    else
    {
        view->parent = relative->parent;
        relative->next = view;

        link_with_container(relative->parent->widget, view->widget, view->view_config);
    }

    return view;
}

// This function is not nesseccary we can use GTK_IS_CONTAINER instead
gboolean is_container_view(FILE *index)
{
    fseek(index, -2, SEEK_CUR);
    gchar c1 = fgetc(index);
    gchar c2 = fgetc(index);
    if (c1 == '/' && c2 == '>')
        return FALSE;
    else if (c2 == '>')
        return TRUE;

    return FALSE;
}

View *read_window_tag(FILE *index, GtkApplication *app, View *parent_view, gboolean is_relative_container)
{
    WindowConfig window_config = DEFAULT_WINDOW;
    ViewConfig view_config;

    gchar *view_id = init_window_config(index, &window_config, &view_config);

    GtkWidget *window_widget = create_window(app, window_config);

    // GtkWidget *window_widget = NULL;
    View *window_view = create_view(view_id, window_widget, &view_config);

    // Should be returned as the top of the graph
    // root_view = window_view;

    // Add view to view model
    add_view(window_view, parent_view, is_relative_container);

    // Update parent view
    return window_view;
}

// TODO: There is a bug in this function
View *read_box_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    BoxConfig box_config = DEFAULT_BOX;
    ViewConfig view_config;

    gchar *view_id = init_box_config(index, &box_config, &view_config);

    GtkWidget *box_widget = create_box(box_config);

    View *box_view = create_view(view_id, box_widget, &view_config);

    // Add view to view model
    add_view(box_view, parent_view, is_relative_container);

    free(view_id);
    // Update parent view
    return box_view;
}

View *build_app(GtkApplication *app, View *root_view)
{
    printf("Building app\n");

    // This file is read from the main.c path because this function is called/executed from main.c
    FILE *index = fopen("./src/view/index.txt", "r");
    if (!index)
    {
        printf("Failed to open index file\n");
        return NULL;
    }

    printf("Index file opened\n");

    View *parent_view = root_view;
    gboolean is_relative_container = TRUE;
    gchar *widget_tag = NULL;
    gchar *view_id = NULL;
    int widget_index = -1;
    char c;

    gboolean stop = FALSE;
    while ((c = fgetc(index)) != EOF && !stop)
    {
        if (c == '<')
        {
            if (fgetc(index) == '/')
            {
                is_relative_container = FALSE;
                continue;
            }
            else
            {
                fseek(index, -1, SEEK_CUR);

                // Read tag and check if exists
                widget_tag = read_tag(index);
                printf("Tag: %s\n", widget_tag);

                // TODO: if the tag = NULL then ignore the tag and Display an error message

                // Get the widget index
                widget_index = get_view_index(index, widget_tag);
            }

            ViewConfig view_config;
            switch (widget_index)
            {

            case WindowTag:
                // Read window tag
                // parent_view = read_window_tag(index, app, parent_view, is_relative_container);
                // Set window as root view
                // root_view = parent_view;
                // Update container flag
                // is_relative_container = is_container_view(index);
                // return window_view;

                WindowConfig window_config = DEFAULT_WINDOW;

                view_id = init_window_config(index, &window_config, &view_config);

                GtkWidget *window_widget = create_window(app, window_config);

                // GtkWidget *window_widget = NULL;
                View *window_view = create_view(view_id, window_widget, &view_config);

                // Should be returned as the top of the graph
                root_view = window_view;

                // Add view to view model
                add_view(window_view, parent_view, is_relative_container);

                is_relative_container = is_container_view(index);

                parent_view = window_view;

                break;

            case BoxTag:

                // TODO: Fix this function to be work
                // parent_view = read_box_tag(index, parent_view, is_relative_container);
                // is_relative_container = is_container_view(index);

                BoxConfig box_config = DEFAULT_BOX;

                view_id = init_box_config(index, &box_config, &view_config);

                GtkWidget *box_widget = create_box(box_config);

                View *box_view = create_view(view_id, box_widget, &view_config);

                // Add view to view model
                add_view(box_view, parent_view, is_relative_container);

                // Update container flag
                is_relative_container = is_container_view(index);

                // Update parent view
                parent_view = box_view;

                break;
            case EntryTag:

                EntryConfig entry_config = DEFAULT_ENTRY;

                view_id = init_entry_config(index, &entry_config, &view_config);

                GtkWidget *entry_widget = create_entry(entry_config);

                View *entry_view = create_view(view_id, entry_widget, &view_config);

                // Add view to view model
                add_view(entry_view, parent_view, is_relative_container);
                // Update container flag
                is_relative_container = is_container_view(index);

                // Update parent view
                parent_view = entry_view;
                break;

            case RadioButtonTag:
                RadioButtonConfig radio_button_config = DEFAULT_RADIO_BUTTON;

                view_id = init_radio_button_config(index, &radio_button_config, &view_config);

                GtkWidget *radio_button_widget = create_radio_button(radio_button_config);

                View *radio_button_view = create_view(view_id, radio_button_widget, &view_config);

                // Add view to view model
                add_view(radio_button_view, parent_view, is_relative_container);
                // Update container flag
                is_relative_container = is_container_view(index);

                // Update parent view
                parent_view = radio_button_view;
                break;

            case ButtonTag:
                ButtonConfig button_config = DEFAULT_BUTTON;

                view_id = init_button_config(index, &button_config, &view_config);

                GtkWidget *button_widget = create_button(button_config);

                View *button_view = create_view(view_id, button_widget, &view_config);

                // Add view to view model
                add_view(button_view, parent_view, is_relative_container);
                // Update container flag
                is_relative_container = is_container_view(index);

                // Update parent view
                parent_view = button_view;
                break;
            case FixedTag:
                FixedConfig fixed_config = DEFAULT_FIXED;

                view_id = init_fixed_config(index, &fixed_config, &view_config);

                GtkWidget *fixed_widget = create_fixed(fixed_config);

                View *fixed_view = create_view(view_id, fixed_widget, &view_config);

                // Add view to view model
                add_view(fixed_view, parent_view, is_relative_container);

                // Update container flag
                is_relative_container = is_container_view(index);

                // Update parent view
                parent_view = fixed_view;
                break;
            case LabelTag:
                //  TODO Complete label
                continue;
                break;
            case ImageTag:
                ImageConfig image_config = DEFAULT_IMAGE;

                view_id = init_image_config(index, &image_config, &view_config);

                GtkWidget *image_widget = create_image(image_config);

                View *image_view = create_view(view_id, image_widget, &view_config);

                // Add view to view model
                add_view(image_view, parent_view, is_relative_container);

                // Update container flag
                is_relative_container = is_container_view(index);

                // Update parent view
                parent_view = image_view;
                break;

            // TODO : Complete other widgets
            default:
                stop = TRUE;
                fclose(index);
                g_print("ERROR: => Widget not found\n");
                //  exit(EXIT_FAILURE);
                break;
            }
            free(widget_tag);
        }
    }

    fclose(index);

    return root_view;
}