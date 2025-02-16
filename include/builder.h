#ifndef BUILDER_H
#define BUILDER_H

#include "./index.h"
#define INDEX_TXT "./src/view/index.xml"
#define DIALOG_TXT "./src/view/dialog.xml"
#define BOX_PROPERTIES_DIALOG_TXT "./src/view/properties/box_dialog.xml"
#define FIXED_PROPERTIES_DIALOG_TXT "./src/view/properties/fixed_dialog.xml"
#define GRID_PROPERTIES_DIALOG_TXT "./src/view/properties/grid_dialog.xml"
#define FLOWBOX_PROPERTIES_DIALOG_TXT "./src/view/properties/flowbox_dialog.xml"
#define PANED_PROPERTIES_DIALOG_TXT "./src/view/properties/paned_dialog.xml"
#define FRAME_PROPERTIES_DIALOG_TXT "./src/view/properties/frame_dialog.xml"
#define OVERLAY_PROPERTIES_DIALOG_TXT "./src/view/properties/overlay_dialog.xml"
#define NOTEBOOK_PROPERTIES_DIALOG_TXT "./src/view/properties/notebook_dialog.xml"
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
    EventBoxTag
} Tags;

// Global structure;

View *create_view(GtkWidget *widget, ViewConfig *view_config);

View *add_view(View *view, View *relative, gboolean is_relative_container);

gchar *read_tag(FILE *index);

int get_view_index(gchar *widget_tag);

View *build_app(GtkApplication *app, View *root_view, const gchar *file_path);

void connect_signales(View *view);

#endif