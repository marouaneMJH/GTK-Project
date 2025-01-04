#include "./../../include/widgets/scroll.h"
//#include "../../include/widgets/scroll.h"

//#include "C:/Users/Qusai/Desktop/GTK-Project/include/widgets/scroll.h"



//void because the function dosen't need any parameters to perform the task

ScrolledWindowConfig *init_scrolled_window_config(void) {
    ScrolledWindowConfig *scrolled_window_config;
    SAFE_ALLOC(scrolled_window_config, ScrolledWindowConfig, 1);
    
    // Initialiser les valeurs par défaut
    scrolled_window_config->h_adjustment = NULL;
    scrolled_window_config->v_adjustment = NULL;
    scrolled_window_config->h_policy = GTK_POLICY_AUTOMATIC;
    scrolled_window_config->v_policy = GTK_POLICY_AUTOMATIC;
    scrolled_window_config->content = NULL;
    scrolled_window_config->window = NULL;
    
    return scrolled_window_config;
}

// Function to create a scrolled window with specified scrollbar policies
GtkWidget* create_scrolled_window(ScrolledWindowConfig scrolled_window_config)
 {
    GtkWidget *scrolled_window = gtk_scrolled_window_new(scrolled_window_config.h_adjustment, scrolled_window_config.v_adjustment);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), scrolled_window_config.h_policy, scrolled_window_config.v_policy);
    gtk_container_add(GTK_CONTAINER(scrolled_window),scrolled_window_config.content);
    gtk_container_add(GTK_CONTAINER(scrolled_window_config.window),scrolled_window);
    return scrolled_window;

}


// GtkWidget* create_scrolled_window(ScrolledWindowConfig *scrolled_window_config) {
//     // Ensure that content is set before proceeding
//     if (scrolled_window_config->content == NULL) {
//         g_warning("Content widget is NULL!");
//         return NULL;
//     }

//     GtkWidget *scrolled_window = gtk_scrolled_window_new(scrolled_window_config->h_adjustment, scrolled_window_config->v_adjustment);
//     gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), scrolled_window_config->h_policy, scrolled_window_config->v_policy);
    
//     // Add the content widget to the scrolled window
//     gtk_container_add(GTK_CONTAINER(scrolled_window), scrolled_window_config->content);

//     // If a parent window is defined, add the scrolled window to it
//     if (scrolled_window_config->window) {
//         gtk_container_add(GTK_CONTAINER(scrolled_window_config->window), scrolled_window);
//     }

//     return scrolled_window;
// }