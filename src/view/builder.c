#include "./../../include/builder.h"

#define INDEX_TXT "./src/view/index.txt"
// #define CHARAF_TXT "./src/view/charaf.txt"
#define MODE "r" 

View *create_view(gchar *view_id, GtkWidget *widget, ViewConfig *view_config)
{
    View *view = NULL;
    SAFE_ALLOC(view, View, 1);
    if (!view)
        g_printerr("Failed: create new view failed!\n");

    view->child = NULL;
    view->parent = NULL;
    view->next = NULL;
    view->view_config = view_config;
    view->widget = widget;

    return view;
}

gchar *read_tag(FILE *index)
{
    gchar *tag = NULL;
    SAFE_ALLOC(tag, gchar, MAX_TAG_SIZE);

    int i = 0;
    char c;
    // fscanf(index, "%s", tag);
    while ((c = fgetc(index)) != '>')
    {
        if (c == ' ' || c == '\n')
            break;

        tag[i++] = c;
    }

    tag[i] = '\0';
    return tag;
}

int get_view_index(gchar *widget_tag) //Why FILE *index
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

    if (g_strcmp0(widget_tag, "radio_button") == 0)
        return RadioButtonTag;

    if (g_strcmp0(widget_tag, "image") == 0)
        return ImageTag;

    if (g_strcmp0(widget_tag, "spin_button") == 0)
        return SpinButtonTag;

    if (g_strcmp0(widget_tag, "flow_box") == 0)
        return FlowBoxTag;

    if (g_strcmp0(widget_tag, "list_box") == 0)
        return ListBoxTag;

    if (g_strcmp0(widget_tag, "grid") == 0)
        return GridTag;

    if (g_strcmp0(widget_tag, "paned") == 0)
        return PanedTag;

    if (g_strcmp0(widget_tag, "link_button") == 0)
        return LinkButtonTag;

    if (g_strcmp0(widget_tag, "switch_button") == 0)
        return SwitchButtonTag;

    if (g_strcmp0(widget_tag, "check_button") == 0)
        return CheckButtonTag;

    if (g_strcmp0(widget_tag, "progress_bar") == 0)
        return ProgressBarTag;

    if (g_strcmp0(widget_tag, "frame") == 0)
        return FrameTag;

    if (g_strcmp0(widget_tag, "text_area") == 0)
        return TextAreaTag;
    
    if (g_strcmp0(widget_tag, "overlay") == 0)
        return OverlayTag;
    
    if (g_strcmp0(widget_tag, "combo_text_box") == 0)
        return ComboTextBoxTag;
    
    return -1;
}

int link_with_box_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_BOX(parent))
        return 0;

    if (view_config->pack_direction == 0)
        gtk_box_pack_end(GTK_BOX(parent), child, view_config->box_expand, view_config->box_fill, view_config->box_padding);
    else
        gtk_box_pack_start(GTK_BOX(parent), child, view_config->box_expand, view_config->box_fill, view_config->box_padding);

    return 1;
}

int link_with_fixed_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_FIXED(parent))
        return 0;
    gtk_fixed_put(GTK_FIXED(parent), child, view_config->position_x, view_config->position_y);
    return 1;
}

int link_with_flow_box_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_FLOW_BOX(parent))
        return 0;

    // debug the view config not working
    gtk_flow_box_insert(GTK_FLOW_BOX(parent), child, view_config->flow_box_order);
    return 1;
}

int link_with_paned_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_PANED(parent))
        return 0;

    gtk_paned_add1(GTK_PANED(parent), child);
    if (view_config->paned_order == 1)
        gtk_paned_add1(GTK_PANED(parent), child);
    else
        gtk_paned_add2(GTK_PANED(parent), child);

    return 1;
}

int link_with_grid_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_GRID(parent))
        return 0;

    gtk_grid_attach(GTK_GRID(parent), child, view_config->column, view_config->row, view_config->column_span, view_config->row_span);

    return 1;
}

int link_with_stack_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_STACK(parent))
        return 0;
    gtk_stack_add_named(GTK_STACK(parent), child, view_config->view_id);
    return 1;
}

int link_with_overlay_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_OVERLAY(parent))
        return 0;
    gtk_overlay_add_overlay(GTK_OVERLAY(parent), child);
    return 1;
}

int link_with_frame_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (!GTK_IS_FRAME(parent))
        return 0;
    frame_add_child(parent, child);
    return 1;
}

int link_with_container(GtkWidget *parent, GtkWidget *child, ViewConfig *view_config)
{
    if (GTK_IS_MENU_ITEM(child) || GTK_IS_MENU(child) || GTK_IS_NOTEBOOK(parent))
        return 0;
    return ((link_with_box_container(parent, child, view_config) ||
             link_with_fixed_container(parent, child, view_config) ||
             link_with_flow_box_container(parent, child, view_config) ||
             link_with_paned_container(parent, child, view_config) ||
             link_with_grid_container(parent, child, view_config) ||
                    link_with_stack_container(parent, child, view_config) ||
                    link_with_frame_container(parent, child, view_config) ||
                    link_with_overlay_container(parent, child, view_config))
                ? 1
                : 0);
    ;
}

View *add_view(View *view, View *relative, gboolean is_relative_container)
{
    if (!view)
        return NULL;

    if (!relative)
        return view;

    // Group radio buttons
    if (GTK_IS_RADIO_BUTTON(view->widget))
    {

        if (GTK_IS_RADIO_BUTTON(relative->widget) && !relative->view_config->group)
        {
            view->view_config->group = relative->widget;
            radio_button_set_group(view->widget, relative->widget);
        }
        else
        {
            view->view_config->group = relative->view_config->group;
            radio_button_set_group(view->widget, relative->view_config->group);
        }
    }

    // Menu bar and menu items
    if (GTK_IS_MENU_ITEM(view->widget))
    {
        if (GTK_IS_MENU_BAR(relative->widget) || GTK_IS_MENU(relative->widget))
        {
            view->view_config->group = relative->widget;
            gtk_menu_shell_append(GTK_MENU_SHELL(relative->widget), view->widget);
        }
        else if (relative->view_config->group)
        {
            view->view_config->group = relative->view_config->group;
            gtk_menu_shell_append(GTK_MENU_SHELL(relative->view_config->group), view->widget);
        }
    }

    if (GTK_IS_MENU(view->widget))
    {
        if (GTK_IS_MENU_ITEM(relative->widget))
        {
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(relative->widget), view->widget);
        }
    }

    // Notebook
    if (view->view_config->tab_label[0] != '\0')
    {
        if (GTK_IS_NOTEBOOK(relative->widget))
        {
            gtk_notebook_append_page(GTK_NOTEBOOK(relative->widget), view->widget, gtk_label_new(view->view_config->tab_label));
            gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(relative->widget), view->widget, view->view_config->is_reorderable);
        }
        else if (relative->parent)
        {
            if (GTK_IS_NOTEBOOK(relative->parent->widget))
            {
                gtk_notebook_append_page(GTK_NOTEBOOK(relative->parent->widget), view->widget, gtk_label_new(view->view_config->tab_label));
                gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(relative->parent->widget), view->widget, view->view_config->is_reorderable);
            }
        }
    }

    if (is_relative_container)
    {
        view->parent = relative;
        relative->child = view;

        printf("RELATIVE PARENT %s IS A CONTAINER FOR: %s\n", relative->view_config->view_id, view->view_config->view_id);
        // Window case
        if (GTK_IS_WINDOW(relative->widget) || GTK_IS_SCROLLED_WINDOW(relative->widget))
        {
            gtk_container_add(GTK_CONTAINER(relative->widget), view->widget);
            return view;
        }

        link_with_container(relative->widget, view->widget, view->view_config);
    }
    else
    {
        printf("RELATIVE PARENT %s IS NOT A CONTAINER FOR: %s\n", relative->view_config->view_id, view->view_config->view_id);
        view->parent = relative->parent;
        relative->next = view;

        link_with_container(relative->parent->widget, view->widget, view->view_config);
    }

    printf("This widget %s is linked to container\n", view->view_config->view_id);
    return view;
}

gboolean is_container_view(FILE *index)
{
    fseek(index, -2, SEEK_CUR);
    gchar c1 = fgetc(index);
    gchar c2 = fgetc(index);
    if (c1 == '/' && c2 == '>')
        return FALSE;
    else if (c2 == '>')
        return TRUE;

    return FALSE;
}

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

View* read_combo_text_box_tag(FILE *index, View *parent_view, gboolean is_relative_container)
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

View *build_app(GtkApplication *app, View *root_view)
{
    printf("Building app\n");

    // This file is read from the main.c path because this function is called/executed from main.c
    FILE *index = fopen(INDEX_TXT, MODE);

    if (!index)
    {
        g_printerr("Failed to open index file\n");
        return NULL;
    }

    g_print("Index file opened\n");

    View *parent_view = root_view;
    View *root_menu_bar_view = NULL;
    gboolean is_relative_container = TRUE;
    gchar *widget_tag = NULL;

    // gchar *view_id = NULL;
    int widget_index = -1;
    char c;

    gboolean stop = FALSE;
    while ((c = fgetc(index)) != EOF && !stop)
    {
        if (c == '<')
        {
            if (fgetc(index) == '/')
            {
                is_relative_container = FALSE;
                parent_view = parent_view->parent;
                continue;
            }
            else
            {
                fseek(index, -1, SEEK_CUR);

                // Read tag and check if exists
                widget_tag = read_tag(index);

                // TODO: if the tag = NULL then ignore the tag and Display an error message

                // Get the widget index
                widget_index = get_view_index(widget_tag);
            }

            switch (widget_index)
            {
            case WindowTag:
                // Read window tag
                parent_view = read_window_tag(index, app, parent_view, is_relative_container);

                // Set window as root view
                root_view = parent_view;

                // Update container flag
                is_relative_container = is_container_view(index);

                break;
            case BoxTag:

                parent_view = read_box_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case FixedTag:

                parent_view = read_fixed_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case FlowBoxTag:

                parent_view = read_flow_box_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case PanedTag:
                parent_view = read_paned_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case NotebookTag:
                parent_view = read_notebook_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case GridTag:
                parent_view = read_grid_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case EntryTag:

                parent_view = read_entry_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case RadioButtonTag:

                parent_view = read_radio_button_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;

            case ButtonTag:

                parent_view = read_button_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;

            case ImageTag:
                parent_view = read_image_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;

            case MenuBarTag:
                parent_view = read_menu_bar_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                root_menu_bar_view = parent_view;

                break;
            case MenuTag:
                parent_view = read_menu_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case MenuItemTag:

                parent_view = read_menu_item_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                // TODO: Check why it works
                // parent_view = menu_item_view;

                // gtk_menu_shell_append(GTK_MENU_SHELL(root_menu_bar_view->widget), menu_item_view->widget);

                break;
            case SpinButtonTag:
                parent_view = read_spin_button_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case LabelTag:
                parent_view = read_label_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
            case SeparatorTag:
                parent_view = read_separator_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
            case CheckButtonTag:
                parent_view = read_check_button_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
            case LinkButtonTag:
                parent_view = read_link_button_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
            case ScrolledWindowTag:
                parent_view = read_scrolled_window_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
            case ProgressBarTag:

                parent_view = read_progress_bar_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);

                break;
            case SwitchButtonTag:
                parent_view = read_switch_button_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
            case StackTag:
                parent_view = read_stack_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
            case FrameTag:

                parent_view = read_frame_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;

            case TextAreaTag:

                parent_view = read_text_area_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
            case OverlayTag:

                parent_view = read_overlay_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
                
            case ComboTextBoxTag:
                
                parent_view = read_combo_text_box_tag(index, parent_view, is_relative_container);
                is_relative_container = is_container_view(index);
                break;
                



            // TODO : Complete other widgets
            default:
                stop = TRUE;
                fclose(index);
                g_print("ERROR: %d => Widget << %s >> not found\n", widget_index, widget_tag);
                //  exit(EXIT_FAILURE);
                break;
            } // end of switch

            free(widget_tag);
        }
    }

    fclose(index);

    return root_view;
}