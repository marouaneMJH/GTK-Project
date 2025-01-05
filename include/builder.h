#ifndef BUILDER_H
#define BUILDER_H

#include "./index.h"

#define MAX_TAG_SIZE 50
#define MAX_VIEW_ID_SIZE 50

typedef struct VIEW
{
    GtkWidget *widget;
    struct VIEW *parent;
    struct VIEW *child;
    struct VIEW *next;
    gchar view_id[MAX_VIEW_ID_SIZE];
} View;

typedef enum
{
    WindowTag,
    ScrolledWindowTag,
    BoxTag,
    FixedTag,
    StackTag,
    NotebookTag,
    ButtonTag,
    SwitchTag,
    EntryTag,
    LabelTag,
    SeparatorTag,
    MenuBarTag,
    MenuTag,
    MenuItemTag,
    RadioButtonTag,
    SpinButtonTag,
    FlowBoxTag,
    ListBoxTag,
    GridTag,
    PanedTag
} Tags;

// Global structure;

View *create_view(gchar *view_id, GtkWidget *widget);

View *add_view(View *view, View *relative, gboolean is_relative_container);

gchar *read_tag(FILE *index);

int get_view_index(FILE *index, gchar *widget_tag);

View *build_app(GtkApplication *app, View *root_view);

#endif