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
    gboolean container_flag = FALSE;
    gchar *widget_tag = NULL;
    int widget_index = -1;
    char c;

    gboolean stop = FALSE;
    while ((c = fgetc(index)) != EOF && !stop)
    {
        if (c == '<')
        {
            if (fgetc(index) == '/')
            {
                // TODO: Close the tag and set container_flag to TRUE
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

            switch (widget_index)
            {
            case WindowTag:
                // TODO: Create window config and init a window widget
                // TODO: Use init function to configure the widget
                // TODO: Add view_id in WindowConfig

                WindowConfig window_config = DEFAULT_WINDOW;

                gchar *view_id = init_window(&window_config, index);

                GtkWidget *window_widget = create_window(app, &window_config);

                // GtkWidget *window_widget = NULL;
                View *window_view = create_view(view_id, window_widget, parent_view);
                root_view = window_view;
                stop = TRUE;
                // return window_view;
                // Add view to view model
                // TODO: Add view to the view model as a child or a brother
                // parent_view = add_to_view_model(window_view, parent_view, container_flag);

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