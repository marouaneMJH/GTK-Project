#include "./../../../include/containers/layouts/grid.h"

GridConfig *init_grid()
{
    GridConfig *grid_config = NULL;
    SAFE_ALLOC(grid_config, GridConfig, 1);

    // TODO: Read from xml file and update the config

    return grid_config;
}

GtkWidget *create_grid(GridConfig grid_config)
{
    GtkWidget *grid = NULL;

    // Creation
    grid = gtk_grid_new();

    // Enable or disable homogeneous (Give all children the same size)
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), grid_config.column_homogeneous);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), grid_config.row_homogeneous);

    // Set spacings
    gtk_grid_set_column_spacing(GTK_GRID(grid), grid_config.column_spacing);
    gtk_grid_set_row_spacing(GTK_GRID(grid), grid_config.row_spacing);

    // Enable or disable cells expand
    gtk_widget_set_hexpand(grid, grid_config.hexpand);
    gtk_widget_set_vexpand(grid, grid_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(grid, grid_config.halign);
    gtk_widget_set_valign(grid, grid_config.valign);

    // Set colors
    widget_set_colors(grid, grid_config.bg_color, grid_config.text_color);

    // Set margins
    widget_set_margins(grid, grid_config.margins);

    // gtk_grid_set_column_baseline_position(GTK_GRID(grid), grid_config.column_index, grid_config.column_baseline_position);
    // gtk_grid_set_row_baseline_position(GTK_GRID(grid), grid_config.row_index, grid_config.row_baseline_position);

    return grid;
}