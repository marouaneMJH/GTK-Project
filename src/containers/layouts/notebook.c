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
    if (g_strcmp0(property, "margin_top") == 0)
        notebook_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        notebook_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        notebook_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
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

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            notebook_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            notebook_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            notebook_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            notebook_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            notebook_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            notebook_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            notebook_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            notebook_config->halign = GTK_ALIGN_FILL;
    }

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

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(notebook, notebook_config.hexpand);
    gtk_widget_set_vexpand(notebook, notebook_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(notebook, notebook_config.halign);
    gtk_widget_set_valign(notebook, notebook_config.valign);

    // gtk_notebook_set_tab_detachable(GTK_NOTEBOOK(notebook), child, TRUE);
    // gtk_notebook_set_menu_label(GTK_NOTEBOOK(notebook), child, label);
    // gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook), child, TRUE);
    return notebook;
}

gchar *write_notebook_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "notebook", tabs_number);

    // Get the GtkNotebook from the view
    GtkNotebook *notebook = GTK_NOTEBOOK(view->widget);

    // Get the group name
    const gchar *group_name = gtk_notebook_get_group_name(notebook);
    if (g_strcmp0(group_name, "\0") != 0) // Check if the group name is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "group_name=\"%s\"\n", group_name);
    }

    // Get the current page
    gint current_page = gtk_notebook_get_current_page(notebook);
    if (current_page != 0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "current_page=\"%d\"\n", current_page);
    }

    // Check if the notebook is scrollable
    gboolean is_scrollable = gtk_notebook_get_scrollable(notebook);
    if (is_scrollable != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_scrollable=\"%s\"\n", is_scrollable ? "true" : "false");
    }

    // Check if the notebook shows a border
    gboolean show_border = gtk_notebook_get_show_border(notebook);
    if (show_border != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "show_border=\"%s\"\n", show_border ? "true" : "false");
    }

    // Check if the notebook shows tabs
    gboolean show_tabs = gtk_notebook_get_show_tabs(notebook);
    if (show_tabs != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "show_tabs=\"%s\"\n", show_tabs ? "true" : "false");
    }

    // Get the tab position
    GtkPositionType tab_position = gtk_notebook_get_tab_pos(notebook);
    if (tab_position != GTK_POS_TOP) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "tab_position=\"%s\"\n", tab_position == GTK_POS_LEFT ? "left" : tab_position == GTK_POS_RIGHT ? "right"
                                                                                          : tab_position == GTK_POS_TOP     ? "top"
                                                                                          : tab_position == GTK_POS_BOTTOM  ? "bottom"
                                                                                                                            : "unknown");
    }

    return "notebook";
}