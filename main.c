#include "./include/index.h"


static void activate(GtkApplication *app, gpointer data)
{
  WindowConfig *window_config = init_window("RadioButton Example");
  GtkWidget *window = create_window(app, window_config);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  RadioButtonConfig rb_config;
  rb_config.is_group = TRUE;
  rb_config.is_inconsistent = FALSE;
  rb_config.dimensions.width = 200;
  rb_config.dimensions.height = 40; 
  g_strlcpy(rb_config.label, "JAVA", MAX_BUTTON_LABEL_SIZE);
  g_strlcpy(rb_config.bg_color, "#FF0000", MAX_COLOR_SIZE);
  g_strlcpy(rb_config.text_color, "#999999", MAX_COLOR_SIZE);
  GtkWidget *rb = create_radio_button(rb_config);

  Button btn_conf = DEFAULT_BUTTON;

  g_strlcpy(btn_conf.label, "CLICK", MAX_BUTTON_LABEL_SIZE);

  GtkWidget *btn = create_button(btn_conf);

  /*rb_config.is_group = FALSE;
  GtkWidget *rb1 = create_radio_button(rb_config);
  radio_button_set_group(rb1, rb);*/

  gtk_box_pack_start(GTK_BOX(box), rb, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_widget_show_all(window);
}

// The main function
int main(int argc, char *argv[])
{

  GtkApplication *app;
  int status;

  app = gtk_application_new("gtk.app.root", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);

  g_object_unref(app);

  return status;
}
