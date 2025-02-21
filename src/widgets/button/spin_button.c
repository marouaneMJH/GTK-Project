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

gchar *write_spin_button_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    write_widget_tag_style_view_config(output_file, view, "spin_button", tabs_number);

    return "spin_button";
}
