#include "./../../../include/containers/layouts/notebook.h"

ViewConfig *configure_notebook_property(NotebookConfig *notebook_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!notebook_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "group_name") == 0)
        strcpy(notebook_config->group_name, value);

    if (g_strcmp0(property, "is_scrollable") == 0)
        notebook_config->is_scrollable = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "show_border") == 0)
        notebook_config->show_border = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "show_tabs") == 0)
        notebook_config->show_tabs = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "current_page") == 0)
        notebook_config->current_page = atoi(value);

    if (g_strcmp0(property, "tab_position") == 0)
    {
        if (g_strcmp0(value, "top") == 0)
            notebook_config->tab_position = GTK_POS_TOP;
        else if (g_strcmp0(value, "bottom") == 0)
            notebook_config->tab_position = GTK_POS_BOTTOM;
        else if (g_strcmp0(value, "left") == 0)
            notebook_config->tab_position = GTK_POS_LEFT;
        else if (g_strcmp0(value, "right") == 0)
            notebook_config->tab_position = GTK_POS_RIGHT;
    }

    // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        notebook_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        notebook_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        notebook_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        notebook_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        notebook_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        notebook_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(notebook_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(notebook_config->text_color, value);

    // Icon image and icon

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_notebook_config(FILE *index, NotebookConfig *notebook_config)
{
    return init_generic_config(index, (void *)notebook_config, (ConfigurePropertyCallback)configure_notebook_property);
}

GtkWidget *create_notebook(NotebookConfig notebook_config)
{
    GtkWidget *notebook = NULL;

    // Creation
    notebook = gtk_notebook_new();

    // Set current page
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), notebook_config.current_page);

    // Enable or disable scrollability
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook), notebook_config.is_scrollable);

    // Set tab position
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), notebook_config.tab_position);

    // Set group name (Not sure)
    if (notebook_config.group_name)
        gtk_notebook_set_group_name(GTK_NOTEBOOK(notebook), notebook_config.group_name);

    // Show or hide borders
    gtk_notebook_set_show_border(GTK_NOTEBOOK(notebook), notebook_config.show_border);

    // Show or hide tabs
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), notebook_config.show_tabs);

    // Set colors
    widget_set_colors(notebook, notebook_config.bg_color, notebook_config.text_color);

    // Set margins
    widget_set_margins(notebook, notebook_config.margins);

    // gtk_notebook_set_tab_detachable(GTK_NOTEBOOK(notebook), child, TRUE);
    // gtk_notebook_set_menu_label(GTK_NOTEBOOK(notebook), child, label);
    // gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook), child, TRUE);
    return notebook;
}