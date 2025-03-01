#ifndef CREATE_NEW_WIDGET_FROM_DIALOG_H
#define CREATE_NEW_WIDGET_FROM_DIALOG_H

#include "./../../../include/builder.h"

View *create_new_box_from_dialog(View *parent_view, gboolean is_relative_container)
{
    BoxConfig *box_config = read_box_config_from_dialog();
    g_print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><\n");
    g_print("%s\n", box_config->bg_color);
    GtkWidget *new_box = create_box(*box_config);
    View *new_box_view = create_view(new_box, read_view_config_from_dialog());
    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    add_view(new_box_view, parent_view, is_relative_container);
    return new_box_view;
}

View *create_new_fixed_from_dialog(View *parent_view, gboolean is_relative_container)
{
    FixedConfig *fixed_config = read_fixed_config_from_dialog();
    GtkWidget *new_fixed = create_fixed(*fixed_config);
    View *new_fixed_view = create_view(new_fixed, read_view_config_from_dialog());
    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    add_view(new_fixed_view, parent_view, is_relative_container);
    return new_fixed_view;
}

View *create_new_flow_box_from_dialog(View *parent_view, gboolean is_relative_container)
{
    FlowBoxConfig *flowbox_config = read_flow_box_config_from_dialog();
    GtkWidget *new_flowbox = create_flow_box(*flowbox_config);
    View *new_flowbox_view = create_view(new_flowbox, read_view_config_from_dialog());
    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    add_view(new_flowbox_view, parent_view, is_relative_container);
    return new_flowbox_view;
}

View *create_new_frame_from_dialog(View *parent_view, gboolean is_relative_container)
{
    FrameConfig *frame_config = read_frame_config_from_dialog();
    GtkWidget *new_frame = create_frame(*frame_config);
    View *new_frame_view = create_view(new_frame, read_view_config_from_dialog());
    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    add_view(new_frame_view, parent_view, is_relative_container);
    return new_frame_view;
}

View *create_new_grid_from_dialog(View *parent_view, gboolean is_relative_container)
{
    GridConfig *grid_config = read_grid_config_from_dialog();
    GtkWidget *new_grid = create_grid(*grid_config);
    View *new_grid_view = create_view(new_grid, read_view_config_from_dialog());
    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    add_view(new_grid_view, parent_view, is_relative_container);
    return new_grid_view;
}

View *create_new_notebook_from_dialog(View *parent_view, gboolean is_relative_container)
{
    NotebookConfig *notebook_config = read_notebook_config_from_dialog();
    GtkWidget *new_notebook = create_notebook(*notebook_config);
    View *new_notebook_view = create_view(new_notebook, read_view_config_from_dialog());
    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    add_view(new_notebook_view, parent_view, is_relative_container);
    return new_notebook_view;
}

// View *create_new_overlay_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     OverlayConfig *overlay_config = read_overlay_config_from_dialog();
//     GtkWidget *new_overlay = create_overlay(*overlay_config);
//     View *new_overlay_view = create_view(new_overlay, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_overlay_view, parent_view, is_relative_container);
//     return new_overlay_view;
// }

// View *create_new_paned_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     PanedConfig *paned_config = read_paned_config_from_dialog();
//     GtkWidget *new_paned = create_paned(*paned_config);
//     View *new_paned_view = create_view(new_paned, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_paned_view, parent_view, is_relative_container);
//     return new_paned_view;
// }

// View *create_new_stack_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     StackConfig *stack_config = read_stack_config_from_dialog();
//     GtkWidget *new_stack = create_stack(*stack_config);
//     View *new_stack_view = create_view(new_stack, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_stack_view, parent_view, is_relative_container);
//     return new_stack_view;
// }

View *create_new_button_from_dialog(View *parent_view, gboolean is_relative_container)
{
    ButtonConfig *button_config = read_button_config_from_dialog();
    GtkWidget *new_button = create_button(*button_config);
    View *new_button_view = create_view(new_button, read_view_config_from_dialog());
    g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
    add_view(new_button_view, parent_view, is_relative_container);
    return new_button_view;
}

// View *create_new_check_button_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     CheckButtonConfig *check_button_config = read_check_button_config_from_dialog();
//     GtkWidget *new_check_button = create_check_button(*check_button_config);
//     View *new_check_button_view = create_view(new_check_button, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_check_button_view, parent_view, is_relative_container);
//     return new_check_button_view;
// }

// View *create_new_color_button_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     ColorButtonConfig *color_button_config = read_color_button_config_from_dialog();
//     GtkWidget *new_color_button = create_color_button(*color_button_config);
//     View *new_color_button_view = create_view(new_color_button, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_color_button_view, parent_view, is_relative_container);
//     return new_color_button_view;
// }

// View *create_new_link_button_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     LinkButtonConfig *link_button_config = read_link_button_config_from_dialog();
//     GtkWidget *new_link_button = create_link_button(*link_button_config);
//     View *new_link_button_view = create_view(new_link_button, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_link_button_view, parent_view, is_relative_container);
//     return new_link_button_view;
// }

// View *create_new_radio_button_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     RadioButtonConfig *radio_button_config = read_radio_button_config_from_dialog();
//     GtkWidget *new_radio_button = create_radio_button(*radio_button_config);
//     View *new_radio_button_view = create_view(new_radio_button, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_radio_button_view, parent_view, is_relative_container);
//     return new_radio_button_view;
// }

// View *create_new_spin_button_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     SpinButtonConfig *spin_button_config = read_spin_button_config_from_dialog();
//     GtkWidget *new_spin_button = create_spin_button(*spin_button_config);
//     View *new_spin_button_view = create_view(new_spin_button, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_spin_button_view, parent_view, is_relative_container);
//     return new_spin_button_view;
// }

// View *create_new_switch_button_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     SwitchButtonConfig *switch_button_config = read_switch_button_config_from_dialog();
//     GtkWidget *new_switch_button = create_switch_button(*switch_button_config);
//     View *new_switch_button_view = create_view(new_switch_button, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_switch_button_view, parent_view, is_relative_container);
//     return new_switch_button_view;
// }

// View *create_new_toggle_button_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     ToggleButtonConfig *toggle_button_config = read_toggle_button_config_from_dialog();
//     GtkWidget *new_toggle_button = create_toggle_button(*toggle_button_config);
//     View *new_toggle_button_view = create_view(new_toggle_button, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_toggle_button_view, parent_view, is_relative_container);
//     return new_toggle_button_view;
// }

// View *create_new_menu_bar_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     MenuBarConfig *menu_bar_config = read_menu_bar_config_from_dialog();
//     GtkWidget *new_menu_bar = create_menu_bar(*menu_bar_config);
//     View *new_menu_bar_view = create_view(new_menu_bar, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_menu_bar_view, parent_view, is_relative_container);
//     return new_menu_bar_view;
// }

// View *create_new_menu_item_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     MenuItemConfig *menu_item_config = read_menu_item_config_from_dialog();
//     GtkWidget *new_menu_item = create_menu_item(*menu_item_config);
//     View *new_menu_item_view = create_view(new_menu_item, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_menu_item_view, parent_view, is_relative_container);
//     return new_menu_item_view;
// }

// View *create_new_menu_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     MenuConfig *menu_config = read_menu_config_from_dialog();
//     GtkWidget *new_menu = create_menu(*menu_config);
//     View *new_menu_view = create_view(new_menu, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_menu_view, parent_view, is_relative_container);
//     return new_menu_view;
// }

// View *create_new_entry_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     EntryConfig *entry_config = read_entry_config_from_dialog();
//     GtkWidget *new_entry = create_entry(*entry_config);
//     View *new_entry_view = create_view(new_entry, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_entry_view, parent_view, is_relative_container);
//     return new_entry_view;
// }

// View *create_new_image_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     ImageConfig *image_config = read_image_config_from_dialog();
//     GtkWidget *new_image = create_image(*image_config);
//     View *new_image_view = create_view(new_image, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_image_view, parent_view, is_relative_container);
//     return new_image_view;
// }

// View *create_new_label_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     LabelConfig *label_config = read_label_config_from_dialog();
//     GtkWidget *new_label = create_label(*label_config);
//     View *new_label_view = create_view(new_label, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_label_view, parent_view, is_relative_container);
//     return new_label_view;
// }

// View *create_new_progress_bar_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     ProgressBarConfig *progress_bar_config = read_progress_bar_config_from_dialog();
//     GtkWidget *new_progress_bar = create_progress_bar(*progress_bar_config);
//     View *new_progress_bar_view = create_view(new_progress_bar, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_progress_bar_view, parent_view, is_relative_container);
//     return new_progress_bar_view;
// }

// View *create_new_separator_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     SeparatorConfig *separator_config = read_separator_config_from_dialog();
//     GtkWidget *new_separator = create_separator(*separator_config);
//     View *new_separator_view = create_view(new_separator, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_separator_view, parent_view, is_relative_container);
//     return new_separator_view;
// }

// View *create_new_text_area_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     TextAreaConfig *text_area_config = read_text_area_config_from_dialog();
//     GtkWidget *new_text_area = create_text_area(*text_area_config);
//     View *new_text_area_view = create_view(new_text_area, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_text_area_view, parent_view, is_relative_container);
//     return new_text_area_view;
// }

// View *create_new_combo_text_box_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     ComboTextBoxConfig *combo_text_box_config = read_combo_text_box_config_from_dialog();
//     GtkWidget *new_combo_text_box = create_combo_text_box(*combo_text_box_config);
//     View *new_combo_text_box_view = create_view(new_combo_text_box, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_combo_text_box_view, parent_view, is_relative_container);
//     return new_combo_text_box_view;
// }

// View *create_new_event_box_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     EventBoxConfig *event_box_config = read_event_box_config_from_dialog();
//     GtkWidget *new_event_box = create_event_box(*event_box_config);
//     View *new_event_box_view = create_view(new_event_box, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_event_box_view, parent_view, is_relative_container);
//     return new_event_box_view;
// }

// View *create_new_expander_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     ExpanderConfig *expander_config = read_expander_config_from_dialog();
//     GtkWidget *new_expander = create_expander(*expander_config);
//     View *new_expander_view = create_view(new_expander, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_expander_view, parent_view, is_relative_container);
//     return new_expander_view;
// }

// View *create_new_list_box_from_dialog(View *parent_view, gboolean is_relative_container)
// {
//     ListBoxConfig *list_box_config = read_list_box_config_from_dialog();
//     GtkWidget *new_list_box = create_list_box(*list_box_config);
//     View *new_list_box_view = create_view(new_list_box, read_view_config_from_dialog());
//     g_print("PARENT VIEW ===============> %s\n", parent_view->view_config->view_id);
//     add_view(new_list_box_view, parent_view, is_relative_container);
//     return new_list_box_view;
// }

#endif