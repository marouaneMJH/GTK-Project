#include "./../../../include/widgets/button/spin_button.h"

ViewConfig *configure_spin_button_property(SpinButtonConfig *spin_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{

    if (!spin_button_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "min") == 0)
        spin_button_config->min = atof(value);
    else if (g_strcmp0(property, "max") == 0)
        spin_button_config->max = atof(value);

    else if (g_strcmp0(property, "step") == 0)
        spin_button_config->step = atof(value);

    else if (g_strcmp0(property, "initial_value") == 0)
        spin_button_config->initial_value = atof(value);

    else if (g_strcmp0(property, "decimal") == 0)
        spin_button_config->decimal = atoi(value);

    else if (g_strcmp0(property, "is_numeric") == 0)
        spin_button_config->is_numeric = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "is_digits") == 0)
        spin_button_config->is_digits = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        spin_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        spin_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        spin_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        spin_button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        spin_button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        spin_button_config->dimensions.height = atoi(value);

    // Colors
    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(spin_button_config->bg_color, value);

    if (g_strcmp0(property, "color") == 0)
        strcpy(spin_button_config->text_color, value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            spin_button_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            spin_button_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            spin_button_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            spin_button_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            spin_button_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            spin_button_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            spin_button_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            spin_button_config->halign = GTK_ALIGN_FILL;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_spin_button_config(FILE *index, SpinButtonConfig *spin_button_config)
{
    return init_generic_config(index, (void *)spin_button_config, (ConfigurePropertyCallback)configure_spin_button_property);
}

GtkWidget *create_spin_button(SpinButtonConfig spin_button_config)
{
    GtkAdjustment *w_adj = gtk_adjustment_new(
        spin_button_config.initial_value,
        spin_button_config.min,
        spin_button_config.max,
        spin_button_config.step,
        0.1,
        spin_button_config.is_digits ? spin_button_config.decimal : 0);

    GtkWidget *spin_button_widget = gtk_spin_button_new(
        GTK_ADJUSTMENT(w_adj),
        3,
        spin_button_config.is_digits ? spin_button_config.decimal : 0);

    if (spin_button_config.dimensions.width > 0 || spin_button_config.dimensions.height > 0)
        gtk_widget_set_size_request(spin_button_widget, spin_button_config.dimensions.width, spin_button_config.dimensions.height);

    widget_set_margins(spin_button_widget, spin_button_config.margins);

    widget_set_colors(spin_button_widget, spin_button_config.bg_color, spin_button_config.text_color);

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(spin_button_widget, spin_button_config.hexpand);
    gtk_widget_set_vexpand(spin_button_widget, spin_button_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(spin_button_widget, spin_button_config.halign);
    gtk_widget_set_valign(spin_button_widget, spin_button_config.valign);

    return spin_button_widget;
}

/* Signales */

static void get_button_value_call_back(GtkWidget *spin_button, gpointer user_data)
{
    gdouble value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button)); // Get updated value
}

gdouble get_spin_button_value(GtkWidget *spin_widget)
{
    g_signal_connect(spin_widget, "value-changed", G_CALLBACK(get_button_value_call_back), NULL); // Connect callback
    return gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_widget));
}

SpinButtonConfig *read_spin_button_config_from_dialog()
{
    SpinButtonConfig *spin_button_config_ptr = NULL;
    SAFE_ALLOC(spin_button_config_ptr, SpinButtonConfig, 1);

    SpinButtonConfig spin_button_config = DEFAULT_SPIN_BUTTON;

    // Minimum value
    spin_button_config.min = read_config_value_as_double("min_spin");

    // Maximum value
    spin_button_config.max = read_config_value_as_double("max_spin");

    // Step value
    spin_button_config.step = read_config_value_as_double("step_spin");

    // Initial value
    spin_button_config.initial_value = read_config_value_as_double("initial_value_spin");

    // Decimal places
    spin_button_config.decimal = read_config_value_as_int("decimal_spin");

    // Is numeric
    gboolean is_numeric = read_config_value_as_boolean("numeric_switch");
    spin_button_config.is_numeric = is_numeric;

    // Is digits
    gboolean is_digits = read_config_value_as_boolean("digits_switch");
    spin_button_config.is_digits = is_digits;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    spin_button_config.dimensions.width = dimensions->width;
    spin_button_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    spin_button_config.margins.top = margins->top;
    spin_button_config.margins.bottom = margins->bottom;
    spin_button_config.margins.start = margins->start;
    spin_button_config.margins.end = margins->end;

    // HAlign
    spin_button_config.halign = read_align_config("halign_combo");

    // VAlign
    spin_button_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    spin_button_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    spin_button_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(spin_button_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(spin_button_config.text_color, text_color);

    memcpy(spin_button_config_ptr, &spin_button_config, sizeof(SpinButtonConfig));
    return spin_button_config_ptr;
}

SpinButtonConfig *read_spin_button_config_from_widget(GtkWidget *widget)
{
    SpinButtonConfig *spin_button_config_ptr = NULL;
    SAFE_ALLOC(spin_button_config_ptr, SpinButtonConfig, 1);

    SpinButtonConfig spin_button_config = DEFAULT_SPIN_BUTTON;

    // Minimum value
    spin_button_config.min = gtk_adjustment_get_lower(gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(widget)));

    // Maximum value
    spin_button_config.max = gtk_adjustment_get_upper(gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(widget)));

    // Step value
    spin_button_config.step = gtk_adjustment_get_step_increment(gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(widget)));

    // Initial value
    spin_button_config.initial_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget));

    // Decimal places
    spin_button_config.decimal = gtk_spin_button_get_digits(GTK_SPIN_BUTTON(widget));

    // Is numeric
    spin_button_config.is_numeric = gtk_spin_button_get_numeric(GTK_SPIN_BUTTON(widget));

    // Is digits
    spin_button_config.is_digits = gtk_spin_button_get_snap_to_ticks(GTK_SPIN_BUTTON(widget));
   
    // Dimensions
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    spin_button_config.dimensions.width = allocation.width;
    spin_button_config.dimensions.height = allocation.height;

    // Expand
    spin_button_config.hexpand = gtk_widget_get_hexpand(widget);
    spin_button_config.vexpand = gtk_widget_get_vexpand(widget);

    // HAlign
    GtkAlign halign = gtk_widget_get_halign(widget);
    spin_button_config.halign = halign;

    // VAlign
    GtkAlign valign = gtk_widget_get_valign(widget);
    spin_button_config.valign = valign;

    // Margins
    Margins margins;
    widget_get_margins(widget, &margins);
    spin_button_config.margins = margins;

    gchar *property_value = NULL;
    // Background color
    property_value = read_bg_color_from_widget(widget);
    if (property_value)
        strcpy(spin_button_config.bg_color, property_value);

    // Text color
    property_value = read_text_color_from_widget(widget);
    if (property_value)
        strcpy(spin_button_config.text_color, property_value);

    memcpy(spin_button_config_ptr, &spin_button_config, sizeof(SpinButtonConfig));

    return spin_button_config_ptr;
}

gchar *write_spin_button_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "spin_button", tabs_number);

    // Get the GtkSpinButton from the view
    GtkSpinButton *spin_button = GTK_SPIN_BUTTON(view->widget);

    // Get the minimum value
    gdouble min;
    gtk_spin_button_get_range(spin_button, &min, NULL);
    if (min != 0.0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "min=\"%f\"\n", min);
    }

    // Get the maximum value
    gdouble max;
    gtk_spin_button_get_range(spin_button, NULL, &max);
    if (max != 100.0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "max=\"%f\"\n", max);
    }

    // Get the step value
    gdouble step;
    gtk_spin_button_get_increments(spin_button, &step, NULL);
    if (step != 1.0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "step=\"%f\"\n", step);
    }

    // Get the initial value
    gdouble initial_value = gtk_spin_button_get_value(spin_button);
    if (initial_value != 50.0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "initial_value=\"%f\"\n", initial_value);
    }

    // Get the number of decimal places
    gint decimal = gtk_spin_button_get_digits(spin_button);
    if (decimal != 2) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "decimal=\"%d\"\n", decimal);
    }

    // Check if the spin button is numeric
    gboolean is_numeric = gtk_spin_button_get_numeric(spin_button);
    if (is_numeric != TRUE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_numeric=\"%s\"\n", is_numeric ? "true" : "false");
    }

    // Check if the spin button disables decimal places
    gboolean is_digits = gtk_spin_button_get_snap_to_ticks(spin_button);
    if (is_digits != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_digits=\"%s\"\n", is_digits ? "true" : "false");
    }

    // Get the horizontal expand property
    gboolean hexpand = gtk_widget_get_hexpand(GTK_WIDGET(spin_button));
    if (hexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "hexpand=\"%s\"\n", hexpand ? "true" : "false");
    }

    // Get the vertical expand property
    gboolean vexpand = gtk_widget_get_vexpand(GTK_WIDGET(spin_button));
    if (vexpand != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "vexpand=\"%s\"\n", vexpand ? "true" : "false");
    }

    return "spin_button";
}