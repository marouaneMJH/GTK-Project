#include "./../../include/widgets/label.h"




Label* init_label(const gchar *label_text) 
{
    Label* label;
    SAFE_ALLOC(label, Label, MAX_LABEL_TEXT_SIZE);

    /* Text Content */
    g_strlcpy(label->label_text, label_text ? label_text : "", MAX_LABEL_TEXT_SIZE - 1);
    label->label_text[MAX_LABEL_TEXT_SIZE - 1] = '\0';
    label->is_markup = FALSE;
    label->is_underline = FALSE;

    /* Appearance */
    label->jtype = GTK_JUSTIFY_LEFT;
    label->ellipsize = PANGO_ELLIPSIZE_NONE;
    label->is_wrap = FALSE;
    g_strlcpy(label->text_color, "#000000", MAX_COLOR_SIZE - 1);
    label->text_color[MAX_COLOR_SIZE - 1] = '\0';
    g_strlcpy(label->background_color, "\0", MAX_COLOR_SIZE - 1);
    label->background_color[MAX_COLOR_SIZE - 1] = '\0';

    /* Behavior */
    label->is_selectable = TRUE;

    /* Layout */
    label->padding = 0;

    return label;
}




Label* edit_label(
        gchar *label_text,
        gboolean is_markup,
        gboolean is_underline,
        GtkJustification jtype,
        PangoEllipsizeMode ellipsize,
        gboolean is_wrap,
        gboolean is_selectable,
        gchar *text_color,
        gchar *background_color
    )   
{
    Label* label = init_label(label_text);
    label->is_markup = is_markup;
    label->is_underline = is_underline;
    label->jtype = jtype;
    label->ellipsize = ellipsize;
    label->is_wrap = is_wrap;
    label->is_selectable = is_selectable;

    // Update colors
    g_strlcpy(label->text_color, text_color ? text_color : "#000000", MAX_COLOR_SIZE - 1);
    label->text_color[MAX_COLOR_SIZE - 1] = '\0';
    g_strlcpy(label->background_color, background_color ? background_color : "\0", MAX_COLOR_SIZE - 1);
    label->background_color[MAX_COLOR_SIZE - 1] = '\0';

    return label;
}



// void apply_label_colors(GtkWidget *label_widget, Label *label) 
// {
//     GdkRGBA text_color, background_color;

//     // Convert string colors to GdkRGBA format
//     if (gdk_rgba_parse(&text_color, label->text_color))
//     {
//         gtk_widget_override_color(label_widget, GTK_STATE_FLAG_NORMAL, &text_color);
//     }

//     if (gdk_rgba_parse(&background_color, label->background_color))
//     {
//         gtk_widget_override_background_color(label_widget, GTK_STATE_FLAG_NORMAL, &background_color);
//     }
// }


GtkWidget* create_label(Label* label) 
{
    IS_EXISTE(label);
    GtkWidget *label_widget = gtk_label_new(label->label_text);

    /* Set Properties */
    gtk_label_set_justify(GTK_LABEL(label_widget), label->jtype);
    gtk_label_set_selectable(GTK_LABEL(label_widget), label->is_selectable);
    gtk_label_set_ellipsize(GTK_LABEL(label_widget), label->ellipsize);
    gtk_label_set_line_wrap(GTK_LABEL(label_widget), label->is_wrap);
    gtk_label_set_use_underline(GTK_LABEL(label_widget), label->is_underline);
    
    if (label->is_markup)
    {
        gtk_label_set_markup(GTK_LABEL(label_widget), label->label_text);
    }

    //  apply the font and bg color 
    // apply_label_colors(label_widget, label);

    // Set bg and text colors
    widget_set_colors(label_widget, label->background_color, label->text_color);


    return label_widget;
}


void free_label(Label* label)
{
    // todo: add info to stdout
    if (label)
    {
        g_free(label);
    }
}

void free_widget_label(GtkWidget *label)
{
    if (label)
    {
        g_free(label);
    }
}



/* Signales  */

void on_link_activated(GtkLabel *label, const gchar *uri, gpointer user_data)
{
    g_print("\nLink clicked: %s\n", uri);
}




