#include "./../../../include/widgets/button/button.h"
#include "./../../../include/widgets/image.h"

ViewConfig *configure_button_property(ButtonConfig *button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!button_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "label") == 0)
        strcpy(button_config->label, value);

    if (g_strcmp0(property, "tooltip") == 0)
        strcpy(button_config->tooltip, value);

    if (g_strcmp0(property, "is_sensitive") == 0)
        button_config->is_sensitive = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_visible") == 0)
        button_config->is_visible = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "icon_path") == 0)
        strcpy(button_config->icon_path, value);

    if (g_strcmp0(property, "halign") == 0)
    {
        if (g_strcmp0(value, "start") == 0)
            button_config->halign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "end") == 0)
            button_config->halign = GTK_ALIGN_END;
        else
            button_config->halign = GTK_ALIGN_CENTER;
    }

    if (g_strcmp0(property, "valign") == 0)
    {
        if (g_strcmp0(value, "start") == 0)
            button_config->valign = GTK_ALIGN_START;
        else if (g_strcmp0(value, "end") == 0)
            button_config->valign = GTK_ALIGN_END;
        else
            button_config->valign = GTK_ALIGN_CENTER;
    }

    if (g_strcmp0(property, "always_show_image") == 0)
        button_config->always_show_image = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "focus_on_click") == 0)
        button_config->focus_on_click = g_strcmp0(value, "true") == 0 ? TRUE : FALSE; // deprecated

    if (g_strcmp0(property, "use_underline") == 0)
        button_config->use_underline = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "use_stock") == 0)
        button_config->use_stock = g_strcmp0(value, "true") == 0 ? TRUE : FALSE; // deprecated

    if (g_strcmp0(property, "icon_position") == 0)
    {
        if (g_strcmp0(value, "top") == 0)
            button_config->icon_position = GTK_POS_TOP;
        else if (g_strcmp0(value, "bottom") == 0)
            button_config->icon_position = GTK_POS_BOTTOM;
        else if (g_strcmp0(value, "left") == 0)
            button_config->icon_position = GTK_POS_LEFT;
        else if (g_strcmp0(value, "right") == 0)
            button_config->icon_position = GTK_POS_RIGHT;
        else
            button_config->icon_position = GTK_POS_LEFT;
    }

    // Icon dimensions
    if (g_strcmp0(property, "icon_width") == 0)
        button_config->icon_dimensions.width = atoi(value);

    if (g_strcmp0(property, "icon_height") == 0)
        button_config->icon_dimensions.height = atoi(value);

    // Margins
    if (g_strcmp0(property, "margin_top") == 0)
        button_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        button_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        button_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
        button_config->margins.end = atoi(value);

    // Dimensions
    else if (g_strcmp0(property, "width") == 0)
        button_config->dimensions.width = atoi(value);

    else if (g_strcmp0(property, "height") == 0)
        button_config->dimensions.height = atoi(value);

    else if (g_strcmp0(property, "bg_color") == 0)
        strcpy(button_config->bg_color, value);

    else if (g_strcmp0(property, "color") == 0)
        strcpy(button_config->color, value);

    else if (g_strcmp0(property, "hexpand") == 0)
        button_config->hexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "vexpand") == 0)
        button_config->vexpand = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    else if (g_strcmp0(property, "bg_image") == 0)
        strcpy(button_config->bg_image, value);

    else if (g_strcmp0(property, "font_size") == 0)
        button_config->font_size = atoi(value);

    // Icon image and icon

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_button_config(FILE *index, ButtonConfig *button_config)
{
    return init_generic_config(index, (void *)button_config, (ConfigurePropertyCallback)configure_button_property);
}

GtkWidget *create_button(ButtonConfig button_config)
{
    GtkWidget *button;

    // Create button with or without mnemonic based on use_underline flag
    button = gtk_button_new_with_mnemonic(button_config.label);

    // Set sensitivity
    gtk_widget_set_sensitive(button, button_config.is_sensitive);

    // Set visibility
    if (!button_config.is_visible)
        gtk_widget_hide(button);

    // Set tooltip
    if (button_config.tooltip) // Ensure tooltip is not empty
        gtk_widget_set_tooltip_text(button, button_config.tooltip);

    // Set dimensions (width and height)
    if (button_config.dimensions.width > 0 || button_config.dimensions.height > 0)
        gtk_widget_set_size_request(button, button_config.dimensions.width, button_config.dimensions.height);

    // Set expand property
    gtk_widget_set_hexpand(button, button_config.hexpand);
    gtk_widget_set_vexpand(button, button_config.vexpand);

    // Set icon if provided
    if (button_config.icon_path[0] != '\0')
    {
        Dimensions dimensions = {32, 32};
        GtkWidget *image = create_image_from_pixbuf(button_config.icon_path, dimensions);
        gtk_button_set_image(GTK_BUTTON(button), image);
        gtk_button_set_image_position(GTK_BUTTON(button), button_config.icon_position);
    }

    // to hide button border
    // gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE );

    // Set bg_image
    if (strcmp(button_config.bg_image, "\0") != 0)
        widget_set_background_image(button, button_config.bg_image, NULL);

    // Set Font Size
    if (button_config.font_size != 10)
        widget_set_font_size(button, button_config.font_size);

    // Set alignment
    gtk_widget_set_halign(button, button_config.halign);
    gtk_widget_set_valign(button, button_config.valign);

    // Control whether to always show the image
    gtk_button_set_always_show_image(GTK_BUTTON(button), button_config.always_show_image);

    // Set background and label colors
    widget_set_colors(button, button_config.bg_color, button_config.color);

    // Set margins
    widget_set_margins(button, button_config.margins);

    return button;
}

void write_button_tag(FILE *output_file, GtkWidget *button) {};

void print_tabs(FILE *output_file, int tabs_number)
{
    for (int i = 0; i < tabs_number; fprintf(output_file, "\t", i++))
        ;
}

// find_close_tag(widget)
// print </>

void write_widget_style(FILE *output_file, GtkWidget *widget, int tabs_number)
{
    if (!output_file || !widget)
        return;

    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    GdkRGBA fg_rgba, bg_rgba;
    gboolean bg_found = FALSE;

    // Get the widget's foreground color (for the normal state)
    gtk_style_context_get_color(context, GTK_STATE_FLAG_NORMAL, &fg_rgba);
    guint fg_r = (guint)(fg_rgba.red * 255);
    guint fg_g = (guint)(fg_rgba.green * 255);
    guint fg_b = (guint)(fg_rgba.blue * 255);
    gchar fg_hex[8]; // Format: "#RRGGBB"
    sprintf(fg_hex, "#%02X%02X%02X", fg_r, fg_g, fg_b);

    // Try to retrieve the background color (this may not always be available)
    bg_found = gtk_style_context_lookup_color(context, "background", &bg_rgba);
    gchar bg_hex[8] = "N/A";
    if (bg_found)
    {
        guint bg_r = (guint)(bg_rgba.red * 255);
        guint bg_g = (guint)(bg_rgba.green * 255);
        guint bg_b = (guint)(bg_rgba.blue * 255);
        sprintf(bg_hex, "#%02X%02X%02X", bg_r, bg_g, bg_b);
    }

    // Get widget dimensions from the allocation.
    gint width = gtk_widget_get_allocated_width(widget);
    gint height = gtk_widget_get_allocated_height(widget);

    // Retrieve widget margins.
    gint margin_top = gtk_widget_get_margin_top(widget);
    gint margin_bottom = gtk_widget_get_margin_bottom(widget);
    gint margin_left = gtk_widget_get_margin_start(widget);
    gint margin_right = gtk_widget_get_margin_end(widget);

    // Retrieve font details using Pango.
    PangoContext *pcontext = gtk_widget_get_pango_context(widget);
    PangoFontDescription *font_desc = pango_context_get_font_description(pcontext);
    const char *family = font_desc ? pango_font_description_get_family(font_desc) : "default";
    int font_size = font_desc ? (pango_font_description_get_size(font_desc) / PANGO_SCALE) : 0;

    // Get font style (Normal, Italic, Oblique)
    const char *font_style = "Normal";
    if (font_desc)
    {
        PangoStyle style = pango_font_description_get_style(font_desc);
        if (style == PANGO_STYLE_ITALIC)
            font_style = "Italic";
        else if (style == PANGO_STYLE_OBLIQUE)
            font_style = "Oblique";
    }

    // Get font weight (e.g., Bold, Normal)
    const char *font_weight = "Normal";
    if (font_desc)
    {
        PangoWeight weight = pango_font_description_get_weight(font_desc);
        if (weight >= PANGO_WEIGHT_BOLD)
            font_weight = "Bold";
    }

    // Write all properties to the output file with the requested tabs.

    print_tabs(output_file, tabs_number);
    fprintf(output_file, "color=\"%s\"\n", fg_hex);

    print_tabs(output_file, tabs_number);
    fprintf(output_file, "bg_color=\"%s\"\n", bg_found ? bg_hex : "N/A");

    print_tabs(output_file, tabs_number);
    fprintf(output_file, "width=\"%d\"\n", width);
    print_tabs(output_file, tabs_number);
    fprintf(output_file, "height=\"%d\"\n", height);

    print_tabs(output_file, tabs_number);
    fprintf(output_file, "margin_top=\"%d\"\n", margin_top);
    print_tabs(output_file, tabs_number);
    fprintf(output_file, "margin_bottom=\"%d\"\n", margin_bottom);
    print_tabs(output_file, tabs_number);
    fprintf(output_file, "margin_left=\"%d\"\n", margin_left);
    print_tabs(output_file, tabs_number);
    fprintf(output_file, "margin_right=\"%d\"\n", margin_right);

    print_tabs(output_file, tabs_number);
    fprintf(output_file, "font_size=\"%d\"\n", font_size);
    print_tabs(output_file, tabs_number);
    fprintf(output_file, "font_family=\"%s\"\n", family);
}

gboolean is_container(GtkWidget *widget)
{
    if (!widget)
        return FALSE;

    if (GTK_IS_BUTTON(widget))
        return FALSE;

    return (GTK_IS_BOX(widget) ||
            GTK_IS_FLOW_BOX(widget) ||
            GTK_IS_MENU(widget) ||
            GTK_IS_PANED(widget) ||
            GTK_IS_FIXED(widget) ||
            GTK_IS_FRAME(widget) ||
            GTK_IS_EXPANDER(widget) ||
            GTK_IS_NOTEBOOK(widget) ||
            GTK_IS_OVERLAY(widget) ||
            GTK_IS_EVENT_BOX(widget) ||
            GTK_IS_WINDOW(widget) ||
            GTK_IS_GRID(widget) ||
            GTK_IS_SCROLLED_WINDOW(widget) ||
            GTK_IS_STACK(widget));
}

void write_widget(FILE *output_file, View *view, int tabs_number)
{

    // exit the function if void
    if (!view || !output_file)
        return;

    // find widget and write it
    else if (GTK_IS_SCROLLED_WINDOW(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<scrolled_window \n");
    }
    else if (GTK_IS_BOX(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<box \n");
    }
    else if (GTK_IS_FIXED(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<fixed \n");
    }
    else if (GTK_IS_STACK(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<stack \n");
    }
    else if (GTK_IS_NOTEBOOK(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<notebook \n");
    }
    else if (GTK_IS_SWITCH(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<switch \n");
    }
    else if (GTK_IS_ENTRY(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<entry \n");
    }
    else if (GTK_IS_LABEL(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<label \n");
    }
    else if (GTK_IS_SEPARATOR(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<separator \n");
    }
    else if (GTK_IS_MENU_BAR(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<menu_bar \n");
    }
    else if (GTK_IS_MENU(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<menu \n");
    }
    else if (GTK_IS_MENU_ITEM(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<menu_item \n");
    }
    else if (GTK_IS_SPIN_BUTTON(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<spin_button \n");
    }
    else if (GTK_IS_FLOW_BOX(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<flow_box \n");
    }
    else if (GTK_IS_LIST_BOX(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<list_box \n");
    }
    else if (GTK_IS_GRID(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<grid \n");
    }
    else if (GTK_IS_PANED(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<paned \n");
    }
    else if (GTK_IS_IMAGE(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<image \n");
    }
    else if (GTK_IS_PROGRESS_BAR(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<progress_bar \n");
    }
    else if (GTK_IS_CHECK_BUTTON(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<check_button \n");
    }
    else if (GTK_IS_LINK_BUTTON(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<link_button \n");
    }
    else if (GTK_IS_FRAME(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<frame \n");
    }
    else if (GTK_IS_TEXT_VIEW(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<text_view \n");
    }
    else if (GTK_IS_OVERLAY(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<overlay \n");
    }
    else if (GTK_IS_DIALOG(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<dialog \n");
    }
    else if (GTK_IS_COMBO_BOX_TEXT(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<combo_box_text \n");
    }
    else if (GTK_IS_TOGGLE_BUTTON(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<toggle_button \n");
    }
    else if (GTK_IS_COLOR_BUTTON(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<color_button \n");
    }
    else if (GTK_IS_EXPANDER(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<expander \n");
    }
    else if (GTK_IS_EVENT_BOX(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<event_box \n");
    }
    else
    {
        // Handle unknown widget types or log an error
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "<unknown_widget \n");
    }

    print_tabs(output_file, tabs_number + 1);
    fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    write_widget_style(output_file, view->widget, tabs_number + 1);

    // closetag  if container
    if (is_container(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, ">\n");

        write_widget(output_file, view->child, tabs_number + 1);

        print_tabs(output_file, tabs_number);
        fprintf(output_file, "</widget>\n");
    }
    else
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "/>\n");
    }

    write_widget(output_file, view->next, tabs_number);
}

void build_xml(FILE *output_file)
{
    write_widget(output_file, root_view_global, 0);
}
