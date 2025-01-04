#ifndef BUILDER_H
#define BUILDER_H

#include "./index.h"

#define MAX_TAG_SIZE 50

typedef struct VIEW
{
    GtkWidget *widget;
    struct VIEW *parent;
    struct VIEW *child;
    struct VIEW *next;
    gchar *view_id;
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

View *create_view(gchar *view_id, GtkWidget *widget, View *parent);

gchar *read_tag(FILE *index);

int get_view_index(FILE *index, gchar *widget_tag);

View *build_app(GtkApplication *app, View *root_view);

#endif