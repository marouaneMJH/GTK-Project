#include "./../../../include/global.h"
#include "./../../../include/widget/button/spin_button.h"


SpinButton edit_spin_button(
        gdouble min,
        gdouble max,
        gdouble step,
        gint decimal,
        gdouble initial_value,
        gboolean is_numeric,
        gboolean is_digits
)
{
    SpinButton sb;
    sb.decimal=decimal;
    sb.initial_value=initial_value;
    sb.is_digits=is_digits;
    sb.is_numeric=is_numeric;
    sb.max=max;
    sb.min=min;
    sb.step=step;

    return ((SpinButton)sb);
}



GtkWidget* create_spin_button(SpinButton spin_button)
{
    GtkAdjustment* w_adj=gtk_adjustment_new(
        spin_button.initial_value,
        spin_button.min,
        spin_button.max,
        spin_button.step,
        0.1,
        spin_button.is_digits ? 2 : 0 
    );

    
    GtkWidget *w_spin_button=gtk_spin_button_new(
        GTK_ADJUSTMENT(w_adj),
        3,
        spin_button.is_digits ? 2 : 0
    );

    
}




/* Signales */

static void get_button_value_call_back(GtkWidget *spin_button, gpointer user_data)
{
    gdouble value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button)); // Get updated value
}




gdouble get_spin_button_value(GtkWidget *spin_widget)
{
    g_signal_connect(spin_widget, "value-changed", G_CALLBACK(get_button_value_call_back), NULL); // Connect callback
    return gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_widget)); 
}



