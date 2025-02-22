#include "./../../../include/containers/layouts/event_box.h"

ViewConfig *configure_event_box_property(EventBoxConfig *event_box_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!event_box_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "is_sensitive") == 0)
        event_box_config->is_above = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_visible") == 0)
        event_box_config->is_visible = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_event_box_config(FILE *index, EventBoxConfig *event_box_config)
{
    return init_generic_config(index, (void *)event_box_config, (ConfigurePropertyCallback)configure_event_box_property);
}

GtkWidget *create_event_box(EventBoxConfig event_box_config)
{
    GtkWidget *event_box = gtk_event_box_new();

    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), event_box_config.is_above);

    gtk_event_box_set_visible_window(GTK_EVENT_BOX(event_box), event_box_config.is_visible);
    return event_box;
}

gchar *write_event_box_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    write_widget_tag_style_view_config(output_file, view, "event_box", tabs_number);

    return "event_box";
}
