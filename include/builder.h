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
    int view_id;
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

// Global structure
View *root_view = NULL;

/*
View *create_view(int widget_id)
{
    View *view = NULL;
    SAFE_ALLOC(view, View, 1);
    if (!view)
        g_critical("Failed: create new view failed!\n");

    view->child = NULL;
    view->parent = NULL;
    view->next = NULL;
    view->widget = NULL;

    view->view_id = widget_id;

    return view;
}

gchar *read_tag(FILE *index)
{
    printf("Reading tag\n");
    gchar *tag = NULL;
    SAFE_ALLOC(tag, gchar, MAX_TAG_SIZE);

    int i = 0;
    char c;
    fscanf(index, "%s", tag);
    /*while ((c = fgetc(index)) != '>')
    {
        if (c == ' ' || c == '\n')
            break;

        tag[i++] = c;
    }

    tag[i] = '\0';

    return tag;
}

int get_view_index(FILE *index, gchar *widget_tag)
{
    if (!widget_tag)
        return -1;
    if (g_strcmp0(widget_tag, "window") == 0)
        return WindowTag;

    if (g_strcmp0(widget_tag, "scrolled_window") == 0)
        return ScrolledWindowTag;

    if (g_strcmp0(widget_tag, "box") == 0)
        return BoxTag;

    if (g_strcmp0(widget_tag, "fixed") == 0)
        return FixedTag;

    if (g_strcmp0(widget_tag, "stack") == 0)
        return StackTag;

    if (g_strcmp0(widget_tag, "notebook") == 0)
        return NotebookTag;

    if (g_strcmp0(widget_tag, "button") == 0)
        return ButtonTag;

    if (g_strcmp0(widget_tag, "switch") == 0)
        return SwitchTag;

    if (g_strcmp0(widget_tag, "entry") == 0)
        return EntryTag;

    if (g_strcmp0(widget_tag, "label") == 0)
        return LabelTag;

    if (g_strcmp0(widget_tag, "separator") == 0)
        return SeparatorTag;

    if (g_strcmp0(widget_tag, "menu_bar") == 0)
        return MenuBarTag;

    if (g_strcmp0(widget_tag, "menu") == 0)
        return MenuTag;

    if (g_strcmp0(widget_tag, "menu_item") == 0)
        return MenuItemTag;

    return -1;
}

void ignore_space();

void ignore_new_line();

View *add_container_view(View *view, View *parent_view)
{
    if (!view)
        return parent_view;

    if (!parent_view)
        return view;

    parent_view->child = view;
    view->parent = parent_view;
    return view;
}

View *add_child_view();*/

View *build_app();

#endif