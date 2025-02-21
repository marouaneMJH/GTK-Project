#include "./../../../include/widgets/View/xml_builder/xml_writer_globals.h"

void print_tabs(FILE *output_file, int tabs_number)
{
    for (int i = 0; i < tabs_number; fprintf(output_file, "\t", i++))
        ;
}

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
    gchar bg_hex[8] = "\0";
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

    if (strlen(fg_hex))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "color=\"%s\"\n", fg_hex);
    }

    if (strlen(bg_hex) && bg_found)
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "bg_color=\"%s\"\n", bg_hex);
    }

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

void write_widget_tag_style_view_config(FILE *output_file, View *view, gchar *tag, int tabs_number)
{
    // print the tag
    print_tabs(output_file, tabs_number);
    fprintf(output_file, "<%s \n", tag);

    // print the id
    print_tabs(output_file, tabs_number + 1);
    fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);

    // print the style
    write_widget_style(output_file, view->widget, tabs_number + 1);

    // print the view config
    // todo finish the view config
}