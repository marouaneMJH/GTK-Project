#include "./../../../include/global.h"
#include "./../../../include/widgets/button/check_button.h"

ViewConfig *configure_check_button_property(CheckButtonConfig *check_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!check_button_config || !property || !value)
        return NULL;

    // Label
    if (g_strcmp0(property, "label") == 0)
        strcpy(check_button_config->label, value);

    // Tooltip
    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(check_button_config->tooltip, value);

    // Active state
    if (g_strcmp0(property, "is_active") == 0)
        check_button_config->is_active = g_strcmp0(value, "true") == 0;

    // Inconsistent state
    if (g_strcmp0(property, "is_inconsistent") == 0)
        check_button_config->is_inconsistent = g_strcmp0(value, "true") == 0;

    // Use underline
    if (g_strcmp0(property, "use_underline") == 0)
        check_button_config->use_underline = g_strcmp0(value, "true") == 0;

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        check_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        check_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        check_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        check_button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        check_button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        check_button_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(check_button_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(check_button_config->text_color, value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            check_button_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            check_button_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            check_button_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            check_button_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            check_button_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            check_button_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            check_button_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            check_button_config->halign = GTK_ALIGN_FILL;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_check_button_config(FILE *index, CheckButtonConfig *check_button_config)
{
    return init_generic_config(index, (void *)check_button_config, (ConfigurePropertyCallback)configure_check_button_property);
}

GtkWidget *create_check_button(CheckButtonConfig check_button_config)
{
    GtkWidget *check_button = NULL;

    // Création du bouton avec ou sans label
    if (check_button_config.label && check_button_config.label[0] != '\0')
    {
        if (check_button_config.use_underline)
        {
            check_button = gtk_check_button_new_with_mnemonic(check_button_config.label);
        }
        else
        {
            check_button = gtk_check_button_new_with_label(check_button_config.label);
        }
    }
    else
    {
        check_button = gtk_check_button_new(); // Bouton vide
    }

    // Configuration des propriétés
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button), check_button_config.is_active);
    gtk_toggle_button_set_inconsistent(GTK_TOGGLE_BUTTON(check_button), check_button_config.is_inconsistent);
    gtk_widget_set_tooltip_text(check_button, check_button_config.tooltip);

    // Dimensions
    if (check_button_config.dimensions.width > 0 && check_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(check_button, check_button_config.dimensions.width, check_button_config.dimensions.height);
    }

    // Couleurs
    widget_set_colors(check_button, check_button_config.bg_color, check_button_config.text_color);

    widget_set_margins(check_button, check_button_config.margins);

    // Enable or disable cells expand (the parent should be expandable; not important)
    gtk_widget_set_hexpand(check_button, check_button_config.hexpand);
    gtk_widget_set_vexpand(check_button, check_button_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(check_button, check_button_config.halign);
    gtk_widget_set_valign(check_button, check_button_config.valign);

    return check_button;
}

CheckButtonConfig *read_check_button_config_from_dialog()
{
    CheckButtonConfig *check_button_config_ptr = NULL;
    SAFE_ALLOC(check_button_config_ptr, CheckButtonConfig, 1);

    CheckButtonConfig check_button_config = DEFAULT_CHECK_BUTTON;

    // Label
    const gchar *label = read_config_value_as_string("label_entry");
    strcpy(check_button_config.label, label);

    // Tooltip
    const gchar *tooltip = read_config_value_as_string("tooltip_entry");
    strcpy(check_button_config.tooltip, tooltip);

    // Active state
    gboolean is_active = read_config_value_as_boolean("active_switch");
    check_button_config.is_active = is_active;

    // Inconsistent state
    gboolean is_inconsistent = read_config_value_as_boolean("inconsistent_switch");
    check_button_config.is_inconsistent = is_inconsistent;

    // Use underline
    gboolean use_underline = read_config_value_as_boolean("underline_switch");
    check_button_config.use_underline = use_underline;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    check_button_config.dimensions.width = dimensions->width;
    check_button_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    check_button_config.margins.top = margins->top;
    check_button_config.margins.bottom = margins->bottom;
    check_button_config.margins.start = margins->start;
    check_button_config.margins.end = margins->end;

    // HAlign
    check_button_config.halign = read_align_config("halign_combo");

    // VAlign
    check_button_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    check_button_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    check_button_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(check_button_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(check_button_config.text_color, text_color);

    memcpy(check_button_config_ptr, &check_button_config, sizeof(CheckButtonConfig));
    return check_button_config_ptr;
}

CheckButtonConfig *read_check_button_config_from_widget(GtkWidget *widget)
{
    CheckButtonConfig *check_button_config_ptr = NULL;
    SAFE_ALLOC(check_button_config_ptr, CheckButtonConfig, 1);

    CheckButtonConfig check_button_config = DEFAULT_CHECK_BUTTON;

    // Label
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    strcpy(check_button_config.label, label ? label : "");

    // Tooltip
    const gchar *tooltip = gtk_widget_get_tooltip_text(widget);
    strcpy(check_button_config.tooltip, tooltip ? tooltip : "");

    // Active state
    check_button_config.is_active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));

    // Inconsistent state
    check_button_config.is_inconsistent = gtk_toggle_button_get_inconsistent(GTK_TOGGLE_BUTTON(widget));

    // Use underline
    check_button_config.use_underline = gtk_button_get_use_underline(GTK_BUTTON(widget));

    // Dimensions
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    check_button_config.dimensions.width = allocation.width;
    check_button_config.dimensions.height = allocation.height;

    // Expand
    check_button_config.hexpand = gtk_widget_get_hexpand(widget);
    check_button_config.vexpand = gtk_widget_get_vexpand(widget);

    // HAlign
    GtkAlign halign = gtk_widget_get_halign(widget);
    check_button_config.halign = halign;

    // VAlign
    GtkAlign valign = gtk_widget_get_valign(widget);
    check_button_config.valign = valign;

    // Margins
    Margins margins;
    widget_get_margins(widget, &margins);
    check_button_config.margins = margins;

    gchar *property_value = NULL;
    // Background color
    property_value = read_bg_color_from_widget(widget);
    if (property_value)
        strcpy(check_button_config.bg_color, property_value);

    // Text color
    property_value = read_text_color_from_widget(widget);
    if (property_value)
        strcpy(check_button_config.text_color, property_value);

    memcpy(check_button_config_ptr, &check_button_config, sizeof(CheckButtonConfig));

    return check_button_config_ptr;
}

gchar *write_check_button_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "check_button", tabs_number);

    // Get the GtkCheckButton from the view
    GtkCheckButton *check_button = GTK_CHECK_BUTTON(view->widget);

    // Get the label text
    const gchar *label = gtk_button_get_label(GTK_BUTTON(check_button));
    if (g_strcmp0(label, "\0") != 0) // Check if the label text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "label=\"%s\"\n", label);
    }

    // Get the tooltip text
    const gchar *tooltip = gtk_widget_get_tooltip_text(GTK_WIDGET(check_button));
    if (tooltip && g_strcmp0(tooltip, "\0") != 0) // Check if the tooltip text is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "tooltip=\"%s\"\n", tooltip);
    }

    // Check if the check button is active
    gboolean is_active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button));
    if (is_active != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_active=\"%s\"\n", is_active ? "true" : "false");
    }

    // Check if the check button is in an inconsistent state
    gboolean is_inconsistent = gtk_toggle_button_get_inconsistent(GTK_TOGGLE_BUTTON(check_button));
    if (is_inconsistent != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "is_inconsistent=\"%s\"\n", is_inconsistent ? "true" : "false");
    }

    // Check if the check button uses underline in the label
    gboolean use_underline = gtk_button_get_use_underline(GTK_BUTTON(check_button));
    if (use_underline != FALSE) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "use_underline=\"%s\"\n", use_underline ? "true" : "false");
    }

    return "check_button";
}