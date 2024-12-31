#include "./../../../include/containers/layouts/notebook.h"

NotebookConfig *init_notebook()
{
    NotebookConfig *notebook_config = NULL;
    SAFE_ALLOC(notebook_config, NotebookConfig, 1);

    return notebook_config;
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