#ifndef EVENT_BOX
#define EVENT_BOX

#include "../../global.h"

#define DEFAULT_EVENT_BOX_CONFIG { \
    .is_above = TRUE,              \
    .is_visible = TRUE,            \
}

typedef struct
{
    gboolean is_above;
    gboolean is_visible;

} EventBoxConfig;

ViewConfig *configure_event_box_property(EventBoxConfig *event_box_config, ViewConfig *view_config, gchar *property, gchar *value);

ViewConfig *init_event_box_config(FILE *index, EventBoxConfig *event_box_config);

GtkWidget *create_event_box(EventBoxConfig event_box_config);

gchar *write_event_box_property(FILE *output_file, View *view, int tabs_number);

#endif