#ifndef BUILDER_H
#define BUILDER_H

#include "./index.h"
#define INDEX_TXT "./src/view/index.xml"
#define DIALOG_TXT "./src/view/dialog.xml"
#define MODE "r"

typedef enum
{
    WindowTag,
    ScrolledWindowTag,
    BoxTag,
    FixedTag,
    StackTag,
    NotebookTag,
    ButtonTag,
    SwitchButtonTag,
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
    PanedTag,
    ImageTag,
    ProgressBarTag,
    CheckButtonTag,
    LinkButtonTag,
    FrameTag,
    TextAreaTag,
    OverlayTag,
    DialogTag,
    ComboTextBoxTag,
    ToggleButtonTag,
    ColorButtonTag,
    ExpanderTag,
} Tags;

// Global structure;

View *create_view(gchar *view_id, GtkWidget *widget, ViewConfig *view_config);

View *add_view(View *view, View *relative, gboolean is_relative_container);

gchar *read_tag(FILE *index);

int get_view_index(gchar *widget_tag);

View *build_app(GtkApplication *app, View *root_view, const gchar *file_path);

void connect_signales(View* view);

#endif