#include "./../../../include/containers/layouts/grid.h"

ViewConfig *configure_grid_property(GridConfig *grid_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!grid_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "column_homogeneous") == 0)
        grid_config->column_homogeneous = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "row_homogeneous") == 0)
        grid_config->row_homogeneous = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "vexpand") == 0)
        grid_config->vexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "hexpand") == 0)
        grid_config->hexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "row_homogeneous") == 0)
        grid_config->row_homogeneous = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "column_spacing") == 0)
        grid_config->column_spacing = atoi(value);

    if (g_strcmp0(property, "row_spacing") == 0)
        grid_config->row_spacing = atoi(value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            grid_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            grid_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            grid_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            grid_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            grid_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            grid_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            grid_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            grid_config->halign = GTK_ALIGN_FILL;
    }

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        grid_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        grid_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        grid_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        grid_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        grid_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        grid_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(grid_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(grid_config->text_color, value);

    // Icon image and icon

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_grid_config(FILE *index, GridConfig *grid_config)
{
    return init_generic_config(index, (void *)grid_config, (ConfigurePropertyCallback)configure_grid_property);
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

    // Enable or disable cells expand (the parent should be expandable; not important)
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

void add_grid(GtkWidget *widget, gint column, gint row, gint column_span, gint row_span)
{
    if (column_span == 0 && row_span == 0)
        gtk_grid_attach(GTK_GRID(widget), widget, column, row, 1, 1);
    else
        gtk_grid_attach(GTK_GRID(widget), widget, column, row, column_span, row_span);
}

gchar *write_grid_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    write_widget_tag_style_view_config(output_file, view, "grid", tabs_number);

    return "grid";
}
