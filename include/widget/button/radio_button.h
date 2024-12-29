#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "./../../global.h"

/*  default values */
#define DEFAULT_RADIO_BUTTON_DIMENSIONS \
    {                                   \
        .height = 0,                    \
        .width = 0}

#define DEFAULT_RADIO_BUTTON_MARGIN \
    {                               \
        .bottom = 0,                \
        .top = 0,                   \
        .start = 0,                 \
        .end = 0}

#define DEFAULT_RADIO_BUTTON                           \
    {                                                  \
        .label = "Option",                              \
        .is_group = FALSE,                             \
        .is_selected = FALSE,                          \
        .group = NULL,                                 \
        .dimensions = DEFAULT_RADIO_BUTTON_DIMENSIONS, \
        .bg_color = "#FFFFFF",                         \
        .text_color = "#333333"}
// .margin = DEFAULT_RADIO_BUTTON_MARGIN,

typedef struct
{
    gchar label[MAX_BUTTON_LABEL_SIZE];
    gchar icon_name[MAX_ICON_NAME_SIZE];
    gboolean is_group;
    GtkRadioButton *group;
    gboolean is_selected;
    gboolean is_button_mode;
    gboolean is_inconsistent;
    gboolean use_underline;
    GtkPositionType icon_position;
    Dimensions dimensions;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];

} RadioButtonConfig;

RadioButtonConfig *init_radio_button_config(const gchar *label, gboolean is_group)
{
    RadioButtonConfig *radio_button_config;
    SAFE_ALLOC(radio_button_config, RadioButtonConfig, 1);

    g_strlcpy(radio_button_config->label, label, MAX_BUTTON_LABEL_SIZE);
    radio_button_config->is_group = is_group;
    return radio_button_config;
}

GtkWidget *create_radio_button(RadioButtonConfig radio_button_config)
{
    GtkWidget *radio_button = NULL;

    // Creation
    if (radio_button_config.is_group)
    {
        radio_button = gtk_radio_button_new_with_label(NULL, radio_button_config.label);
    }
    else if (radio_button_config.group)
    {
        if (radio_button_config.label)
        {
            radio_button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_button_config.group), radio_button_config.label);
        }
        else
        {
            radio_button = gtk_radio_button_new(gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_button_config.group)));
        }
    }

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_button), radio_button_config.is_selected);
    gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(radio_button), radio_button_config.is_button_mode);
    gtk_toggle_button_set_inconsistent(GTK_TOGGLE_BUTTON(radio_button), radio_button_config.is_inconsistent);

    if (radio_button_config.icon_name)
    {
        GtkWidget *radio_button_icon = gtk_image_new_from_icon_name(radio_button_config.icon_name, GTK_ICON_SIZE_BUTTON);
        gtk_button_set_image(GTK_BUTTON(radio_button), radio_button_icon);
        gtk_button_set_image_position(GTK_BUTTON(radio_button), GTK_POS_RIGHT);
    }

    gtk_button_set_use_underline(GTK_BUTTON(radio_button), radio_button_config.use_underline);

    if (radio_button_config.dimensions.width > 0 && radio_button_config.dimensions.height > 0)
    {
        gtk_widget_set_size_request(radio_button, radio_button_config.dimensions.width, radio_button_config.dimensions.height);
    }

    widget_set_colors(radio_button, radio_button_config.bg_color, radio_button_config.text_color);

    // GdkRGBA bg_color;
    // gdk_rgba_parse(&bg_color, "#ff00ff");
    // gtk_widget_override_background_color(GTK_WIDGET(rb2), GTK_STATE_FLAG_NORMAL, &bg_color);

    return radio_button;
}

void radio_button_set_group(GtkWidget *widget, GtkWidget *group)
{
    gtk_radio_button_set_group(GTK_RADIO_BUTTON(widget), gtk_radio_button_get_group(GTK_RADIO_BUTTON(group)));
}

#endif