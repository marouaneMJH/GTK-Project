#include "./../../include/builder.h"

View *create_view(gchar *view_id, GtkWidget *widget, View *parent)
{
    View *view = NULL;
    SAFE_ALLOC(view, View, 1);
    if (!view)
        g_critical("Failed: create new view failed!\n");

    view->child = NULL;
    view->parent = parent;
    view->next = NULL;
    view->widget = widget;

    view->view_id = view_id;

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

    return -1;
}

View *add_view(View *view, View *relative, gboolean is_relative_container)
{
    if (!view)
        return NULL;

    if (!relative)
        return view;

    if (is_relative_container)
    {
        view->parent = relative;
        relative->child = view;
    }
    else
    {
        view->parent = relative->parent;
        relative->next = view;
    }
    return view;
}

gboolean is_container_view(FILE *index)
{
    fseek(index, -2, SEEK_CUR);
    gchar c1 = fgetc(index);
    gchar c2 = fgetc(index);
    if (c1 == '/' && c2 == '>')
        return TRUE;
    else if (c2 == '>')
        return FALSE;
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
                if (fgetc(index) == '>')
                {
                    is_relative_container = FALSE;
                    continue;
                }
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

            switch (widget_index)
            {
            case WindowTag:

                WindowConfig window_config = DEFAULT_WINDOW;

                view_id = init_window(&window_config, index);

                GtkWidget *window_widget = create_window(app, window_config);

                // GtkWidget *window_widget = NULL;
                View *window_view = create_view(view_id, window_widget, parent_view);

                // Should be returned as the top of the graph
                root_view = window_view;

                // Add view to view model
                add_view(window_view, parent_view, is_relative_container);
                // Update container flag
                is_relative_container = is_container_view(index);
                // Update parent view
                parent_view = window_view;
                // return window_view;
                break;

            case BoxTag:
            
                BoxConfig box_config = DEFAULT_BOX;

                view_id = init_box(&box_config, index);

                GtkWidget *box_widget = create_box(box_config);

                View *box_view = create_view(view_id, box_widget, parent_view);

                // Add view to view model
                add_view(box_view, parent_view, is_relative_container);
                // Update container flag
                is_relative_container = is_container_view(index);
                // Update parent view
                parent_view = box_view;
                
                stop = TRUE;
                // return box_view;
                break;

            default:
                fclose(index);
                g_print("ERROR: => Widget not found\n");
                exit(EXIT_FAILURE);
                break;
            }
        }
    }

    fclose(index);

    printf("VIEW ID: %s\n", root_view->view_id);
    return root_view;
}