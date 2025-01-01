#include "./include/index.h"

// Function to create the completion system
GtkEntryCompletion* create_completion_system() {
    // Create a completion object
    GtkEntryCompletion *completion = gtk_entry_completion_new();

    // Create a model with some sample completion data (a simple list of strings)
    GtkListStore *store = gtk_list_store_new(1, G_TYPE_STRING);
    gtk_list_store_insert_with_values(store, NULL, -1, 0, "Apple", -1);
    gtk_list_store_insert_with_values(store, NULL, -1, 0, "Banana", -1);
    gtk_list_store_insert_with_values(store, NULL, -1, 0, "Cherry", -1);
    gtk_list_store_insert_with_values(store, NULL, -1, 0, "Grape", -1);
    gtk_list_store_insert_with_values(store, NULL, -1, 0, "Orange", -1);

    // Set the model for the completion system
    gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(store));

    // Set the column that will be used for completion (in this case, the first column)
    gtk_entry_completion_set_text_column(completion, 0);

    return completion;
}

static void activate(GtkApplication *app, gpointer user_data)
{
  // Window *window_data = 


  // Window *window_data =

  WindowConfig win1 = DEFAULT_WINDOW;
  g_strlcpy(win1.title, "Window 1", MAX_WINDOW_TITLE_SIZE);
  WindowConfig wn2 = DEFAULT_WINDOW;

  GtkWidget *window = create_window(app, &win1);
  EntryConfig entry = DEFAULT_ENTRY;
  g_strlcpy(entry.placeholder_text, "Enter your name", entry.max_length);
  //g_strlcpy(entry.bg_color, "red", 50);
  entry.margins.top = 100;
  entry.opacity = 0.1;
  g_strlcpy(entry.bg_color, "red", MAX_COLOR_SIZE);
  GtkWidget* Myentry = create_entry(&entry);
  //----------------------------------------------


  GtkWidget *progress_bar = gtk_progress_bar_new();
  gtk_widget_set_size_request(progress_bar, 50, 50);
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 0.9);
  gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), TRUE);
  gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), "99999999999999999999999999999999999999999999999999999999999999999999999999çç%");
  gtk_progress_bar_set_inverted(GTK_PROGRESS_BAR(progress_bar), FALSE);
  gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar), 0.1);
  gtk_progress_bar_set_ellipsize(GTK_PROGRESS_BAR(progress_bar), PANGO_ELLIPSIZE_END);
  gtk_widget_set_opacity(progress_bar, 0.5);
    

  //GtkWindow *window2 = create_window(app, init_window("window 2"));

  // GtkWidget *entry = gtk_entry_new();
  
  // GtkWidget *entry2 = gtk_entry_new();
  // //gtk_entry_set_text(GTK_ENTRY(entry),"hiiiiii");
  // gtk_entry_set_input_purpose(GTK_ENTRY(entry), GTK_INPUT_PURPOSE_PASSWORD);
  // gtk_widget_set_size_request(entry, 50, 200);
  // //gtk_entry_set_visibility(GTK_ENTRY(entry),FALSE);
  //  GdkRGBA color,bg_color;
  // gdk_rgba_parse(&color, "red");
  // gdk_rgba_parse(&bg_color,"green");
  // gtk_widget_override_color(entry,GTK_STATE_FLAG_FOCUSED,&color);
  // gtk_widget_override_background_color(entry,GTK_STATE_FLAG_FOCUSED,&bg_color);
  // gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter your name");
  // gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(Myentry), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(progress_bar), FALSE, FALSE, 0);
  //gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(entry2), FALSE, FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(box));


 
  gtk_widget_show_all(GTK_WIDGET(window));
}








int main(int argc, char *argv[]) {

    GtkApplication *app;
    int status;

    app = gtk_application_new("gtk.app.root", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);


    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}



// static void activate(GtkApplication *app, gpointer data)
// {
//   WindowConfig window_config = DEFAULT_WINDOW;
//   g_strlcpy(window_config.title, "Containers testing", MAX_WINDOW_TITLE_SIZE);
//   g_strlcpy(window_config.icon_name, "go-home", MAX_ICON_NAME_SIZE);
//   g_strlcpy(window_config.bg_color, "#999999", MAX_COLOR_SIZE);
//   window_config.dimensions.width = 700;
//   window_config.dimensions.height = 500;
//   GtkWidget *window = create_window(app, &window_config);

//   ButtonConfig btn_config = DEFAULT_BUTTON;
//   g_strlcpy(btn_config.label, "Button 1", MAX_BUTTON_LABEL_SIZE);
//   GtkWidget *btn1 = create_button(btn_config);

//   g_strlcpy(btn_config.label, "Button 2", MAX_BUTTON_LABEL_SIZE);
//   GtkWidget *btn2 = create_button(btn_config);

//   g_strlcpy(btn_config.label, "Button 3", MAX_BUTTON_LABEL_SIZE);
//   GtkWidget *btn3 = create_button(btn_config);

  // Box container //////////////////
  // BoxConfig box_config = DEFAULT_BOX;
  // GtkWidget *box = create_box(box_config);

  // gtk_box_pack_start(GTK_BOX(box), btn1, FALSE, FALSE, 3);
  // gtk_box_pack_start(GTK_BOX(box), btn2, FALSE, FALSE, 3);

  // Fixed container ////////////////
  // FixedConfig fixed_config = DEFAULT_FIXED;
  // GtkWidget* fixed = create_fixed(fixed_config);

  // gtk_fixed_put(GTK_FIXED(fixed), btn1, 100, 100);
  // gtk_fixed_put(GTK_FIXED(fixed), btn2, 150, 300);

  // FlowBox container //////////////
  // FlowBoxConfig flow_box_config = DEFAULT_FLOW_BOX;
  // flow_box_config.max_childern_per_line = 1;
  // GtkWidget *flow_box = create_flow_box(flow_box_config);

  // gtk_flow_box_insert(GTK_FLOW_BOX(flow_box), btn1, 0);
  // gtk_flow_box_insert(GTK_FLOW_BOX(flow_box), btn2, 1);
  // gtk_flow_box_insert(GTK_FLOW_BOX(flow_box), btn3, 3);
  // for (int i = 4; i < 6; i++)
  // {
  //   g_strlcpy(btn_config.label, g_strdup_printf("Button %d", i), MAX_BUTTON_LABEL_SIZE);
  //   GtkWidget *btn = create_button(btn_config);
  //   gtk_flow_box_insert(GTK_FLOW_BOX(flow_box), btn, i);
  // }

  // Grid container //////////////////
  // GridConfig grid_config = DEFAULT_GRID;
  // GtkWidget *grid = create_grid(grid_config);

  // gtk_grid_insert_row(GTK_GRID(grid), 0);
  // gtk_grid_insert_row(GTK_GRID(grid), 1);
  // gtk_grid_insert_row(GTK_GRID(grid), 2);
  // gtk_grid_insert_column(GTK_GRID(grid), 0);
  // gtk_grid_insert_column(GTK_GRID(grid), 1);

  // Width and height works both of them but they mean colspan and rowspan not the dimensions
  // gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
  // gtk_grid_attach(GTK_GRID(grid), btn2, 2, 1, 1, 1);
  // gtk_grid_attach(GTK_GRID(grid), btn3, 1,  2, 1, 1);

  // Only width wich is works like box exactly
  // gtk_grid_attach_next_to(GTK_GRID(grid), btn1, NULL, GTK_POS_RIGHT, 100, 30);
  // gtk_grid_attach_next_to(GTK_GRID(grid), btn2, btn1, GTK_POS_BOTTOM, 400, 40);
  // gtk_grid_attach_next_to(GTK_GRID(grid), btn3, btn1, GTK_POS_LEFT, 300, 50);

  // ListBox container /////////////////
  // ListBoxConfig list_box_config = DEFAULT_LIST_LIST_BOX;
  // GtkWidget *list_box = create_list_box(list_box_config);

  // for (int i = 0; i < 5; i++)
  // {
  //   GtkWidget *lbr = gtk_list_box_row_new();
  //   g_strlcpy(btn_config.label, g_strdup_printf("Button %d", i), MAX_BUTTON_LABEL_SIZE);
  //   btn_config.dimensions.width = 300;
  //   btn_config.dimensions.height = 70;
  //   gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(lbr), FALSE);
  //   GtkWidget *btn = create_button(btn_config);
  //   gtk_container_add(GTK_CONTAINER(lbr), btn);
  //   gtk_list_box_insert(GTK_LIST_BOX(list_box), lbr, -1);
  // }

  // Notebook container /////////////////
  // NotebookConfig notebook_config = DEFAULT_NOTEBOOK;
  // g_strlcpy(notebook_config.group_name, "GroupTabs", MAX_GROUP_NAME_SIZE); // Not working
  // notebook_config.show_border = TRUE;
  // notebook_config.show_tabs = TRUE;
  // notebook_config.tab_position = GTK_POS_TOP;

  // GtkWidget *notebook1 = create_notebook(notebook_config);
  // notebook_config.tab_position = GTK_POS_TOP;
  // GtkWidget *notebook2 = create_notebook(notebook_config);

  // GtkWidget *tab1_label = gtk_label_new("Tab1");
  // GtkWidget *tab2_label = gtk_label_new("Tab2");
  // GtkWidget *tab3_label = gtk_label_new("Tab3");
  // GtkWidget *note_label = gtk_label_new("NoteTab");
  // GtkWidget *menu_label = gtk_label_new("MenuLabel");

  // gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), btn1, tab1_label);
  // gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), btn2, tab2_label);
  // gtk_notebook_append_page(GTK_NOTEBOOK(notebook2), btn3, tab3_label);
  // gtk_notebook_append_page(GTK_NOTEBOOK(notebook1), notebook2, note_label);

  // gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook1), btn1, TRUE);
  // gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook1), btn2, TRUE);
  // gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook2), btn3, TRUE);
  // gtk_notebook_set_tab_reorderable(GTK_NOTEBOOK(notebook1), notebook2, TRUE);

  // gtk_notebook_set_menu_label(GTK_NOTEBOOK(notebook1), btn1, menu_label); // Not working

  // gtk_notebook_set_tab_detachable(GTK_NOTEBOOK(notebook1), btn1, TRUE); // Not sure

  // gtk_notebook_set_action_widget(GTK_NOTEBOOK(notebook1), btn2, GTK_PACK_END); // Not working


  // Paned container ///////////////////////
  // Paned container split the content into two resizable slide
  // PanedConfig paned_config = DEFAULT_PANED;
  // paned_config.is_wide = TRUE;
  // paned_config.orientation = GTK_ORIENTATION_HORIZONTAL;
  // paned_config.position = -1;
  // GtkWidget *paned = create_paned(paned_config);

  // // add1 and add2 doen not resized when the paned is expaned
  // gtk_paned_add1(GTK_PANED(paned), btn1);
  // gtk_paned_add2(GTK_PANED(paned), btn2);

  // // add1 and add2 are resized when the paned is expaned
  // gtk_paned_pack1(GTK_PANED(paned), btn1, TRUE, TRUE); 
  // gtk_paned_pack2(GTK_PANED(paned), btn3, TRUE, TRUE);


  // Stack container ////////////////////////
  // StackConfig stack_config = DEFAULT_STACK;
  // stack_config.interpolate_size = FALSE;
  // GtkWidget *stack = create_stack(stack_config);

  // gtk_stack_add_titled(GTK_STACK(stack), btn1, "btn1", "b1");
  // gtk_stack_add_titled(GTK_STACK(stack), btn2, "btn2", "b2");

  // gtk_stack_set_visible_child_name(GTK_STACK(stack), "btn2");

  // TODO: There something wrong with this container I will check it later

  // GtkWid

  // Add container to window
  // gtk_container_add(GTK_CONTAINER(window), box);
  // gtk_container_add(GTK_CONTAINER(window), fixed);
  // gtk_container_add(GTK_CONTAINER(window), flow_box);
  // gtk_container_add(GTK_CONTAINER(window), grid);
  // gtk_container_add(GTK_CONTAINER(window), list_box);
  // gtk_container_add(GTK_CONTAINER(window), notebook1);
  // gtk_container_add(GTK_CONTAINER(window), paned);
  // gtk_container_add(GTK_CONTAINER(window), stack);

//   gtk_widget_show_all(window);
// }

// int main(int argc, char *argv[])
// {

//   GtkApplication *app;
//   int status;

//   app = gtk_application_new("gtk.app.root", G_APPLICATION_DEFAULT_FLAGS);

//   g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

//   status = g_application_run(G_APPLICATION(app), argc, argv);

//   g_object_unref(app);

//   return status;
// }

// Callback function for button click
// static void run_run(GtkWidget *button, GtkWidget *toggle_button) {
//     gdouble value = gtk_toggle_button_get_value(GTK_SPIN_BUTTON(toggle_button)); // Get current spin button value
//     g_print("\nSpin button value: %f\n", value);
// }

// Main activate function
// static void activate(GtkApplication *app, gpointer user_data) {
//     // Create spin button adjustment
//     GtkAdjustment *adjustment = gtk_adjustment_new(50, 0, 100, 1, 1, 0);

//     // Create window
//     GtkWindow *window = create_window(app, init_window(NULL));
//     GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);


//     // creat widget
    
//     GtkWidget *toggle_button=gtk_toggle_button_new_with_label("Name of God") ;
//     // gtk_toggle_button_toggled(GTK_TOGGLE_BUTTON(toggle_button));
//     if(gtk_toggle_button_get_mode(GTK_TOGGLE_BUTTON(toggle_button)));
//         g_print("\n button toggoled");

//     // Pack widgets into box and add to window
//     gtk_box_pack_start(GTK_BOX(box), toggle_button, FALSE, FALSE, 0);
//     // gtk_box_pack_start(GTK_BOX(box), button_check, FALSE, FALSE, 0);
//     gtk_container_add(GTK_CONTAINER(window), box);

//     // Show all widgets
//     gtk_widget_show_all(GTK_WIDGET(window));
// }