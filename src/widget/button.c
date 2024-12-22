#include "./../../include/global.h"
#include "./../../include/widget/button.h"


GtkWidget* create_button(GtkWidget* container, gchar *title)
{
    // create the button
    GtkWidget* button=gtk_button_new();

    // add label if it exist  to function
    if(title) gtk_button_set_label(GTK_BUTTON(button),title);

    // add the button to the container
    gtk_container_add(GTK_CONTAINER(container),button);

    
    return button;
}









