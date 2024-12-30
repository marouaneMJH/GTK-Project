#include "./../../../include/global.h"
#include "./../../../include/widget/button/button.h"




Button edit_button(
    gchar* label,
    gboolean is_sensitive,
    gboolean is_visible,
    gchar* tooltip,
    Dimensions dimensions,
    Margin margin,
    gboolean expand,
    gchar* bg_color,
    gchar* text_color
    
)
{
    Button b;


    // Pointers  values
    if(label)
        g_strlcpy(b.label, label,MAX_BUTTON_LABEL);
    if(tooltip)
        g_strlcpy(b.tooltip,tooltip, MAX_BUTTON_TOOLTIP);
    if(bg_color)
        g_strlcpy(b.bg_color,bg_color,MAX_COLOR);
    if(text_color)
        g_strlcpy(b.text_color,text_color, MAX_COLOR);


    b.is_sensitive=is_sensitive;
    b.is_visible=is_visible;
    b.dimensions=dimensions;
    b.margin=margin;
    b.expand=expand;

    return ((Button)b);
}



GtkWidget* create_button(Button button)
{
    // Create a new button with the given label
    GtkWidget* b = gtk_button_new_with_label(button.label);

    // Set sensitivity
    gtk_widget_set_sensitive(b, button.is_sensitive);

    // Set visibility
    if (!button.is_visible) 
            gtk_widget_hide(b);

    // Set tooltip
    if (button.tooltip) // Ensure tooltip is not empty
        gtk_widget_set_tooltip_text(b, button.tooltip);
    

    // todo dimensions validate function
    // Set dimensions (width and height)
    if (button.dimensions.width > 0 && button.dimensions.height > 0)
        gtk_widget_set_size_request(b, button.dimensions.width, button.dimensions.height);

    // Set expand property
    if (button.expand) {
        gtk_widget_set_hexpand(b, TRUE);
        gtk_widget_set_vexpand(b, TRUE);
    }

    // Set text and background color
    if (button.text_color || button.bg_color ) {
        GdkRGBA text_color,
                bg_color;


        // Set the label color
        if (gdk_rgba_parse(&text_color, button.text_color)) {
            gtk_widget_override_color(b, GTK_STATE_FLAG_NORMAL, &text_color);
        }

        // Set the background color
        if (gdk_rgba_parse(&bg_color, button.bg_color)) {
            gtk_widget_override_background_color(b, GTK_STATE_FLAG_NORMAL, &bg_color);
        }
    }

    // Set margin
    gtk_widget_set_margin_start(b, button.margin.start);
    gtk_widget_set_margin_end(b, button.margin.end);
    gtk_widget_set_margin_top(b, button.margin.top);
    gtk_widget_set_margin_bottom(b, button.margin.bottom);
    
    return ((GtkWidget*)b);
}

GtkWidget* create_button_icon(gchar* icon_name,GtkIconSize icon_size)
{
    GtkWidget* b;
    if(icon_name)
        b=gtk_button_new_from_icon_name(icon_name,icon_size);
    else
        b=gtk_button_new_from_icon_name("computer",GTK_ICON_SIZE_BUTTON);

    return ((GtkWidget*)b);
}







