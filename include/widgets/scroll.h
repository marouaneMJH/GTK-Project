#ifndef SCROLL_H
#define SCROLL_H

#include "./../global.h"


#define DEFAULT_SCROLLED_WINDOW_CONFIG                 \
    {                                                  \
        .h_adjustment = NULL,                          \
        .v_adjustment = NULL,                          \
        .h_policy = GTK_POLICY_AUTOMATIC,              \
        .v_policy = GTK_POLICY_AUTOMATIC,              \
        .content = NULL,                               \
        .window = NULL                                 \
    }

typedef struct {
    GtkAdjustment *h_adjustment;
    GtkAdjustment *v_adjustment;
    GtkPolicyType h_policy;
    GtkPolicyType v_policy;
    GtkWidget *content;
    GtkWidget *window;

}ScrolledWindowConfig;

ScrolledWindowConfig *init_scrolled_window_config(void);

/**
 * @brief Creates a scrolled window with specified horizontal and vertical scrollbar policies.
 * 
 * @param h_policy The horizontal scrollbar policy (e.g., GTK_POLICY_ALWAYS, GTK_POLICY_AUTOMATIC).
 * @param v_policy The vertical scrollbar policy (e.g., GTK_POLICY_ALWAYS, GTK_POLICY_AUTOMATIC).
 * @return GtkWidget* A pointer to the newly created GtkScrolledWindow widget.
 */
GtkWidget* create_scrolled_window(GtkPolicyType h_policy, GtkPolicyType v_policy);



#endif // SCROLL_H