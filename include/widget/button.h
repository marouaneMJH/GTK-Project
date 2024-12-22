#ifndef BUTTON_H
#define BUTTON_H


#include "./../global.h"


typedef struct
{
    /* Basic properties */
    gchar *label;                  // The text displayed on the button
    gboolean is_sensitive;         // Whether the button is clickable or not
    gboolean is_visible;           // Whether the button is visible or hidden
    gchar *tooltip;                // Tooltip text shown when hovering over the button

    /* Dimensions and placement */
    gint width;                    // Width of the button
    gint height;                   // Height of the button
    gint margin_top;               // Top margin
    gint margin_bottom;            // Bottom margin
    gint margin_left;              // Left margin
    gint margin_right;             // Right margin
    gboolean expand;               // If the button expands in its container

    /* Button appearance */
    gchar *css_class;              // Custom CSS class for styling
    gchar bg_color[10];            // Background color (e.g., "#FFFFFF")

    /* Signals and behaviors */
    gboolean receives_default;     // Whether it can be activated by the Enter key
    gboolean is_focusable;         // Whether it can be focused
    gboolean has_default;          // If it's the default button in a dialog
    gboolean has_focus;            // If it currently has focus

    /* Event handlers */
    void (*on_clicked)(GtkWidget *button, gpointer user_data);  // Click event handler
    void (*on_hover)(GtkWidget *button, gpointer user_data);    // Hover event handler
    void (*on_press)(GtkWidget *button, gpointer user_data);    // Press event handler
    void (*on_release)(GtkWidget *button, gpointer user_data);  // Release event handler

    /* Parent container */
    GtkWidget *parent;             // The container holding this button

}Button;


// GtkWidget* create_button(GtkContainer* container, gchar *title);
GtkWidget* create_button(GtkWidget* container,gchar *title);




// GtkWidget* create_button(GtkContainer* container, gchar *title,GtkWidget* image,GtkReliefStyle relief);


#endif