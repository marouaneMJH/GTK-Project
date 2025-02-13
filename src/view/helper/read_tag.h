#ifndef READ_TAG_H
#define READ_TAG_H

#include "./../../../include/builder.h"

View *read_window_tag(FILE *index, GtkApplication *app, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    WindowConfig window_config = DEFAULT_WINDOW;

    view_config = init_window_config(index, &window_config);

    GtkWidget *window_widget = create_window(app, window_config);

    // GtkWidget *window_widget = NULL;
    View *window_view = create_view(view_config->view_id, window_widget, view_config);

    // Add view to view model
    parent_view = add_view(window_view, parent_view, is_relative_container);

    // Update parent view
    return window_view;
}

View *read_dialog_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    DialogConfig dialog_config = DEFAULT_DIALOG;

    view_config = init_dialog_config(index, &dialog_config);

    GtkWidget *dialog_widget = create_dialog(dialog_config);

    View *dialog_view = create_view(view_config->view_id, dialog_widget, view_config);
    
    // Add view to view model
    parent_view = add_view(dialog_view, parent_view, is_relative_container);
    
    return dialog_view;
}

View *read_box_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    BoxConfig box_config = DEFAULT_BOX;

    view_config = init_box_config(index, &box_config);

    GtkWidget *box_widget = create_box(box_config);

    View *box_view = create_view(view_config->view_id, box_widget, view_config);

    // Add view to view model
    parent_view = add_view(box_view, parent_view, is_relative_container);

    return box_view;
}

View *read_stack_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    StackConfig stack_config = DEFAULT_STACK;

    view_config = init_stack_config(index, &stack_config);

    GtkWidget *stack_widget = create_stack(stack_config);

    View *stack_view = create_view(view_config->view_id, stack_widget, view_config);

    // Add view to view model
    parent_view = add_view(stack_view, parent_view, is_relative_container);

    return stack_view;
}

View *read_frame_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    FrameConfig frame_config = DEFAULT_FRAME;

    view_config = init_frame_config(index, &frame_config);

    GtkWidget *frame_widget = create_frame(frame_config);

    View *frame_view = create_view(view_config->view_id, frame_widget, view_config);

    // Add view to view model
    parent_view = add_view(frame_view, parent_view, is_relative_container);

    return frame_view;
}

View *read_overlay_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    OverlayConfig overlay_config = DEFAULT_OVERLAY;

    view_config = init_overlay_config(index, &overlay_config);

    GtkWidget *overlay_widget = create_overlay(overlay_config);

    View *overlay_view = create_view(view_config->view_id, overlay_widget, view_config);

    // Add view to view model
    parent_view = add_view(overlay_view, parent_view, is_relative_container);

    return overlay_view;
}

View *read_fixed_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    FixedConfig fixed_config = DEFAULT_FIXED;

    view_config = init_fixed_config(index, &fixed_config);

    GtkWidget *fixed_widget = create_fixed(fixed_config);

    View *fixed_view = create_view(view_config->view_id, fixed_widget, view_config);

    // Add view to view model
    parent_view = add_view(fixed_view, parent_view, is_relative_container);

    return fixed_view;
}

View *read_button_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    ButtonConfig button_config = DEFAULT_BUTTON;

    view_config = init_button_config(index, &button_config);

    GtkWidget *button_widget = create_button(button_config);

    View *button_view = create_view(view_config->view_id, button_widget, view_config);

    // Add view to view model
    parent_view = add_view(button_view, parent_view, is_relative_container);

    return button_view;
}

View *read_entry_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    EntryConfig entry_config = DEFAULT_ENTRY;

    view_config = init_entry_config(index, &entry_config);

    GtkWidget *entry_widget = create_entry(entry_config);

    View *entry_view = create_view(view_config->view_id, entry_widget, view_config);

    // Add view to view model
    parent_view = add_view(entry_view, parent_view, is_relative_container);


    return entry_view;
}

View *read_radio_button_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    RadioButtonConfig radio_button_config = DEFAULT_RADIO_BUTTON;

    view_config = init_radio_button_config(index, &radio_button_config);

    GtkWidget *radio_button_widget = create_radio_button(radio_button_config);

    View *radio_button_view = create_view(view_config->view_id, radio_button_widget, view_config);

    // Add view to view model
    parent_view = add_view(radio_button_view, parent_view, is_relative_container);

    return radio_button_view;
}

View *read_image_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    ImageConfig image_config = DEFAULT_IMAGE;

    view_config = init_image_config(index, &image_config);

    GtkWidget *image_widget = create_image(image_config);

    View *image_view = create_view(view_config->view_id, image_widget, view_config);

    // Add view to view model
    add_view(image_view, parent_view, is_relative_container);

    // Update parent view
    return image_view;
}

View *read_menu_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    MenuConfig menu_config = DEFAULT_MENU;

    view_config = init_menu_config(index, &menu_config);

    GtkWidget *menu_widget = create_menu(menu_config);

    View *menu_view = create_view(view_config->view_id, menu_widget, view_config);

    // Add view to view model
    add_view(menu_view, parent_view, is_relative_container);

    return menu_view;
}

View *read_menu_item_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    MenuItemConfig menu_item_config = DEFAULT_MENU_ITEM;

    view_config = init_menu_item_config(index, &menu_item_config);

    GtkWidget *menu_item_widget = create_menu_item(menu_item_config);

    View *menu_item_view = create_view(view_config->view_id, menu_item_widget, view_config);

    // Add view to view model
    add_view(menu_item_view, parent_view, is_relative_container);

    return menu_item_view;
}

View *read_menu_bar_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    MenuBarConfig menu_bar_config = DEFAULT_MENU_BAR;

    view_config = init_menu_bar_config(index, &menu_bar_config);

    GtkWidget *menu_bar_widget = create_menu_bar(menu_bar_config);

    View *menu_bar_view = create_view(view_config->view_id, menu_bar_widget, view_config);

    // Add view to view model
    add_view(menu_bar_view, parent_view, is_relative_container);

    // Update parent view
    return menu_bar_view;
}

View *read_spin_button_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    SpinButtonConfig spin_button_config = DEFAULT_SPIN_BUTTON;

    view_config = init_spin_button_config(index, &spin_button_config);

    GtkWidget *spin_button_widget = create_spin_button(spin_button_config);

    View *spin_button_view = create_view(view_config->view_id, spin_button_widget, view_config);

    // Add view to view model
    add_view(spin_button_view, parent_view, is_relative_container);

    return spin_button_view;
}

View *read_flow_box_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    // initialize flow box config
    FlowBoxConfig flow_box_config = DEFAULT_FLOW_BOX;

    // Update flow box config and view config from index file
    view_config = init_flow_box_config(index, &flow_box_config);

    // Create flow box widget
    GtkWidget *flow_box_widget = create_flow_box(flow_box_config);

    View *flow_box_view = create_view(view_config->view_id, flow_box_widget, view_config);

    // Add view to view model
    add_view(flow_box_view, parent_view, is_relative_container);

    return flow_box_view;
}

View *read_paned_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    PanedConfig paned_config = DEFAULT_PANED;

    view_config = init_paned_config(index, &paned_config);

    GtkWidget *paned_widget = create_paned(paned_config);

    View *paned_view = create_view(view_config->view_id, paned_widget, view_config);

    // Add view to view model
    add_view(paned_view, parent_view, is_relative_container);

    return paned_view;
}

View *read_label_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    LabelConfig label_config = DEFAULT_LABEL;

    view_config = init_label_config(index, &label_config);

    GtkWidget *label_widget = create_label(label_config);

    View *label_view = create_view(view_config->view_id, label_widget, view_config);

    // Add view to view model
    add_view(label_view, parent_view, is_relative_container);
    return label_view;
}

View *read_separator_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    SeparatorConfig separator_config = DEFAULT_SEPARATOR;

    view_config = init_separator_config(index, &separator_config);

    GtkWidget *separator_widget = create_separator(separator_config);

    View *separator_view = create_view(view_config->view_id, separator_widget, view_config);

    // Add view to view model
    add_view(separator_view, parent_view, is_relative_container);
    return separator_view;
}

View *read_check_button_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    CheckButtonConfig check_button_config = DEFAULT_CHECK_BUTTON;

    view_config = init_check_button_config(index, &check_button_config);

    GtkWidget *check_button_widget = create_check_button(check_button_config);

    View *check_button_view = create_view(view_config->view_id, check_button_widget, view_config);

    // Add view to view model
    add_view(check_button_view, parent_view, is_relative_container);

    return check_button_view;
}

View *read_switch_button_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    SwitchButtonConfig switch_button_config = DEFAULT_SWITCH_BUTTON;

    view_config = init_switch_button_config(index, &switch_button_config);

    GtkWidget *switch_button_widget = create_switch_button(switch_button_config);

    View *switch_button_view = create_view(view_config->view_id, switch_button_widget, view_config);

    // Add view to view model
    add_view(switch_button_view, parent_view, is_relative_container);

    return switch_button_view;
}

View *read_link_button_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    LinkButtonConfig link_button_config = DEFAULT_LINK_BUTTON;

    view_config = init_link_button_config(index, &link_button_config);

    GtkWidget *link_button_widget = create_link_button(link_button_config);

    View *link_button_view = create_view(view_config->view_id, link_button_widget, view_config);

    // Add view to view model
    add_view(link_button_view, parent_view, is_relative_container);

    return link_button_view;
}

View *read_scrolled_window_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    ScrolledWindowConfig scrolled_window_config = DEFAULT_SCROLLED_WINDOW;

    view_config = init_scrolled_window_config(index, &scrolled_window_config);

    GtkWidget *scrolled_window_widget = create_scrolled_window(scrolled_window_config);

    View *scrolled_window_view = create_view(view_config->view_id, scrolled_window_widget, view_config);

    // Add view to view model
    add_view(scrolled_window_view, parent_view, is_relative_container);

    return scrolled_window_view;
}

View *read_progress_bar_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    ProgressBarConfig progress_bar_config = DEFAULT_PROGRESS_BAR;

    view_config = init_progress_bar_config(index, &progress_bar_config);

    GtkWidget *progress_bar_widget = create_progress_bar(progress_bar_config);

    View *progress_bar_view = create_view(view_config->view_id, progress_bar_widget, view_config);

    // Add view to view model
    add_view(progress_bar_view, parent_view, is_relative_container);

    return progress_bar_view;
}

View *read_notebook_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    NotebookConfig notebook_config = DEFAULT_NOTEBOOK;

    view_config = init_notebook_config(index, &notebook_config);

    GtkWidget *notebook_widget = create_notebook(notebook_config);

    View *notebook_view = create_view(view_config->view_id, notebook_widget, view_config);

    // Add view to view model
    add_view(notebook_view, parent_view, is_relative_container);

    return notebook_view;
}

View *read_grid_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    GridConfig grid_config = DEFAULT_GRID;

    view_config = init_grid_config(index, &grid_config);

    GtkWidget *grid_widget = create_grid(grid_config);

    View *grid_view = create_view(view_config->view_id, grid_widget, view_config);

    // Add view to view model
    add_view(grid_view, parent_view, is_relative_container);

    return grid_view;
}

View *read_text_area_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    TextAreaConfig text_area_config = DEFAULT_TEXT_AREA;

    view_config = init_text_area_config(index, &text_area_config);

    GtkWidget *text_area_widget = create_text_area(text_area_config);

    View *text_area_view = create_view(view_config->view_id, text_area_widget, view_config);

    // Add view to view model
    add_view(text_area_view, parent_view, is_relative_container);

    return text_area_view;
}

View *read_combo_text_box_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    ComboTextBoxConfig combo_text_box_config = DEFAULT_COMBO_TEXT_BOX_CONFIG;

    view_config = init_combo_text_box_config(index, &combo_text_box_config);

    GtkWidget *combo_text_box_widget = create_combo_text_box(combo_text_box_config);

    View *combo_text_box_view = create_view(view_config->view_id, combo_text_box_widget, view_config);

    // Add view to view model
    add_view(combo_text_box_view, parent_view, is_relative_container);

    return combo_text_box_view;
}

View *read_toggle_button_tag(FILE *index, View *parent_view, gboolean is_relative_container)
{
    ViewConfig *view_config;
    ToggleButtonConfig toggle_button_config = DEFAULT_TOGGLE_BUTTON;

    view_config = init_toggle_button_config(index, &toggle_button_config);

    GtkWidget *toggle_button_widget = create_toggle_button(toggle_button_config);

    View *toggle_button_view = create_view(view_config->view_id, toggle_button_widget, view_config);

    // Ajouter le toggle_button à la hiérarchie des vues

    add_view(toggle_button_view, parent_view, is_relative_container);

    return toggle_button_view;
}



#endif