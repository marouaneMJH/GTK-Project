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

    // Dimensions
    if (grid_config.dimensions.height || grid_config.dimensions.width)
        gtk_widget_set_size_request(grid, grid_config.dimensions.width, grid_config.dimensions.height);

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

GridConfig *read_grid_config_from_dialog()
{
    GridConfig *grid_config_ptr = NULL;
    SAFE_ALLOC(grid_config_ptr, GridConfig, 1);

    GridConfig grid_config = DEFAULT_GRID;

    // Column homogeneous
    gboolean column_homogeneous = read_config_value_as_boolean("column_homogeneous_switch");
    grid_config.column_homogeneous = column_homogeneous;

    // Row homogeneous
    gboolean row_homogeneous = read_config_value_as_boolean("row_homogeneous_switch");
    grid_config.row_homogeneous = row_homogeneous;

    // Column spacing
    grid_config.column_spacing = read_config_value_as_int("column_spacing_spin");

    // Row spacing
    grid_config.row_spacing = read_config_value_as_int("row_spacing_spin");

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    grid_config.dimensions.width = dimensions->width;
    grid_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    grid_config.margins.top = margins->top;
    grid_config.margins.bottom = margins->bottom;
    grid_config.margins.start = margins->start;
    grid_config.margins.end = margins->end;

    // HAlign
    grid_config.halign = read_align_config("halign_combo");

    // VAlign
    grid_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    grid_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    grid_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(grid_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(grid_config.text_color, text_color);

    memcpy(grid_config_ptr, &grid_config, sizeof(GridConfig));
    return grid_config_ptr;
}

GridConfig *read_grid_config_from_widget(GtkWidget *widget)
{
    GridConfig *grid_config_ptr = NULL;
    SAFE_ALLOC(grid_config_ptr, GridConfig, 1);

    GridConfig grid_config = DEFAULT_GRID;

    // Column homogeneous
    grid_config.column_homogeneous = gtk_grid_get_column_homogeneous(GTK_GRID(widget));

    // Row homogeneous
    grid_config.row_homogeneous = gtk_grid_get_row_homogeneous(GTK_GRID(widget));

    // Column spacing
    grid_config.column_spacing = gtk_grid_get_column_spacing(GTK_GRID(widget));

    // Row spacing
    grid_config.row_spacing = gtk_grid_get_row_spacing(GTK_GRID(widget));

    // Dimensions
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    grid_config.dimensions.width = allocation.width;
    grid_config.dimensions.height = allocation.height;

    // Expand
    grid_config.hexpand = gtk_widget_get_hexpand(widget);
    grid_config.vexpand = gtk_widget_get_vexpand(widget);

    // HAlign
    GtkAlign halign = gtk_widget_get_halign(widget);
    grid_config.halign = halign;

    // VAlign
    GtkAlign valign = gtk_widget_get_valign(widget);
    grid_config.valign = valign;

    // Margins
    Margins margins;
    widget_get_margins(widget, &margins);
    grid_config.margins = margins;

    gchar *property_value = NULL;

    // Background color
    property_value = read_bg_color_from_widget(widget);
    if (property_value)
        strcpy(grid_config.bg_color, property_value);

    // Text color
    property_value = read_text_color_from_widget(widget);
    if (property_value)
        strcpy(grid_config.text_color, property_value);

    memcpy(grid_config_ptr, &grid_config, sizeof(GridConfig));

    return grid_config_ptr;
}

gchar *write_grid_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "grid", tabs_number);

    // Get the GtkGrid from the view
    GtkGrid *grid = GTK_GRID(view->widget);

    // Get the row spacing
    gint row_spacing = gtk_grid_get_row_spacing(grid);
    if (row_spacing != 0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "row_spacing=\"%d\"\n", row_spacing);
    }

    // Get the column spacing
    gint column_spacing = gtk_grid_get_column_spacing(grid);
    if (column_spacing != 0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "column_spacing=\"%d\"\n", column_spacing);
    }

    // Check if the grid columns are homogeneous
    gboolean column_homogeneous = gtk_grid_get_column_homogeneous(grid);
    if (column_homogeneous != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "column_homogeneous=\"%s\"\n", column_homogeneous ? "true" : "false");
    }

    // Check if the grid rows are homogeneous
    gboolean row_homogeneous = gtk_grid_get_row_homogeneous(grid);
    if (row_homogeneous != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "row_homogeneous=\"%s\"\n", row_homogeneous ? "true" : "false");
    }

    // Get the horizontal expand property
    gboolean hexpand = gtk_widget_get_hexpand(GTK_WIDGET(grid));
    if (hexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hexpand=\"%s\"\n", hexpand ? "true" : "false");
    }

    // Get the vertical expand property
    gboolean vexpand = gtk_widget_get_vexpand(GTK_WIDGET(grid));
    if (vexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "vexpand=\"%s\"\n", vexpand ? "true" : "false");
    }

    return "grid";
}
