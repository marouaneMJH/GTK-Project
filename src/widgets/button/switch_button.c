
#include "./../../../include/widgets/button/switch_button.h"

ViewConfig *configure_switch_button_property(SwitchButtonConfig *switch_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!switch_button_config || !property || !value)
        return NULL;

    // Tooltip
    if (g_strcmp0(property, "tooltip") == 0)
    {
        strcpy(switch_button_config->tooltip, value);
        return view_config;
    }

    // Visibility
    if (g_strcmp0(property, "is_visible") == 0)
    {
        switch_button_config->is_visible = g_strcmp0(value, "true") == 0;
        return view_config;
    }

    // Active state
    if (g_strcmp0(property, "is_active") == 0)
    {
        switch_button_config->is_active = g_strcmp0(value, "true") == 0;
        return view_config;
    }

    // State
    if (g_strcmp0(property, "state") == 0)
    {
        switch_button_config->state = g_strcmp0(value, "true") == 0;
        return view_config;
    }

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        switch_button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        switch_button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        switch_button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        switch_button_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        switch_button_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        switch_button_config->dimensions.height = atoi(value);

    if (g_strcmp0(property, "bg_color") == 0)
        strcpy(switch_button_config->bg_color, value);

    if (g_strcmp0(property, "text_color") == 0)
        strcpy(switch_button_config->text_color, value);

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            switch_button_config->valign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            switch_button_config->valign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            switch_button_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            switch_button_config->valign = GTK_ALIGN_FILL;
    }

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "center") == 0)
            switch_button_config->halign = GTK_ALIGN_CENTER;
        else if (g_strcmp0(value, "end") == 0)
            switch_button_config->halign = GTK_ALIGN_END;
        else if (g_strcmp0(value, "start") == 0)
            switch_button_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "fill") == 0)
            switch_button_config->halign = GTK_ALIGN_FILL;
    }

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_switch_button_config(FILE *index, SwitchButtonConfig *switch_button_config)
{
    return init_generic_config(index, (void *)switch_button_config, (ConfigurePropertyCallback)configure_switch_button_property);
}

GtkWidget *create_switch_button(SwitchButtonConfig switch_button_config)
{
    GtkWidget *switch_button = NULL;

    // Creation
    switch_button = gtk_switch_new();

    // Set dimensions
    if (switch_button_config.dimensions.width > 0 && switch_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(switch_button, switch_button_config.dimensions.width, switch_button_config.dimensions.height);
    }

    // Set colors (background and/or text colors)
    widget_set_colors(switch_button, switch_button_config.bg_color, switch_button_config.text_color);

    // Enable or disable the switch
    gtk_switch_set_active(GTK_SWITCH(switch_button), switch_button_config.is_active);

    // Set visibility
    if (switch_button_config.is_visible)
        gtk_widget_show(switch_button);

    // Set a tooltip
    gtk_widget_set_tooltip_text(switch_button, switch_button_config.tooltip);

    // Set the state to ON or OFF like active but this one controll the switch during transition not only the final state
    gtk_switch_set_state(GTK_SWITCH(switch_button), switch_button_config.state);

    // Set margins
    widget_set_margins(switch_button, switch_button_config.margins);

    gtk_widget_set_hexpand(switch_button, switch_button_config.hexpand);
    gtk_widget_set_vexpand(switch_button, switch_button_config.vexpand);

    // Set alignments
    gtk_widget_set_halign(switch_button, switch_button_config.halign);
    gtk_widget_set_valign(switch_button, switch_button_config.valign);

    return switch_button;
}

SwitchButtonConfig *read_switch_button_config_from_dialog()
{
    SwitchButtonConfig *switch_button_config_ptr = NULL;
    SAFE_ALLOC(switch_button_config_ptr, SwitchButtonConfig, 1);

    SwitchButtonConfig switch_button_config = DEFAULT_SWITCH_BUTTON;

    // Label
    const gchar *label = read_config_value_as_string("label_entry");
    strcpy(switch_button_config.label, label);

    // Tooltip
    const gchar *tooltip = read_config_value_as_string("tooltip_entry");
    strcpy(switch_button_config.tooltip, tooltip);

    // Visibility
    gboolean is_visible = read_config_value_as_boolean("visible_switch");
    switch_button_config.is_visible = is_visible;

    // Active state
    gboolean is_active = read_config_value_as_boolean("active_switch");
    switch_button_config.is_active = is_active;

    // State
    gboolean state = read_config_value_as_boolean("state_switch");
    switch_button_config.state = state;

    // Dimensions
    Dimensions *dimensions = read_dimensions_config();
    switch_button_config.dimensions.width = dimensions->width;
    switch_button_config.dimensions.height = dimensions->height;

    // Margins
    Margins *margins = read_margins_config();
    switch_button_config.margins.top = margins->top;
    switch_button_config.margins.bottom = margins->bottom;
    switch_button_config.margins.start = margins->start;
    switch_button_config.margins.end = margins->end;

    // HAlign
    switch_button_config.halign = read_align_config("halign_combo");

    // VAlign
    switch_button_config.valign = read_align_config("valign_combo");

    // HExpand
    gboolean hexpand = read_config_value_as_boolean("hexpand_switch");
    switch_button_config.hexpand = hexpand;

    // VExpand
    gboolean vexpand = read_config_value_as_boolean("vexpand_switch");
    switch_button_config.vexpand = vexpand;

    // Background color
    const gchar *bg_color = read_config_value_as_string("bg_color_entry");
    strcpy(switch_button_config.bg_color, bg_color);

    // Text color
    const gchar *text_color = read_config_value_as_string("color_entry");
    strcpy(switch_button_config.text_color, text_color);

    memcpy(switch_button_config_ptr, &switch_button_config, sizeof(SwitchButtonConfig));
    return switch_button_config_ptr;
}


gchar *write_switch_button_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    write_widget_tag_style_view_config(output_file, view, "switch_button", tabs_number);

    return "switch_button";
}
