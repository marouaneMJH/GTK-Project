#include "./../include/builder.h"

View *build_app()
{
    printf("Building app\n");
    /*system("pwd");
    FILE *index = fopen("index.txt", "r");
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
    while ((c = fgetc(index)) != EOF)
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
                // widget_tag = read_tag(index);
                // printf("Tag: %s\n", widget_tag);

                // TODO: if the tag = NULL then ignore the tag and Display an error message

                // Get the widget index
                // widget_index = get_view_index(index, widget_tag);
            }

            switch (widget_index)
            {
            case WindowTag:
                // TODO: Create window config and init a window widget
                // TODO: Use init function to configure the widget
                // TODO: Add view_id in WindowConfig

                WindowConfig window_config = DEFAULT_WINDOW;
                // init_window(&window_config);

                // WindowConfig window_config = DEFAULT_WINDOW;
                // init_window(&window_config);
                // GtkWidget *window_widget = create_window(app, window_config);

                // GtkWidget *window_widget = NULL;
                // View *window_view = create_view(window_config.view_id);

                // Add view to view model
                // TODO: Add view to the view model as a child or a brother
                // parent_view = add_to_view_model(window_view, parent_view, container_flag);

                break;

            default:
                fclose(index);
                g_print("Widget not found\n");
                exit(EXIT_FAILURE);
                break;
            }
        }
    }

    fclose(index);*/
}
