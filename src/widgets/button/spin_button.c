#include "./../../../include/widgets/button/spin_button.h"

ViewConfig *configure_spin_button_property(SpinButtonConfig *spin_button_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!spin_button_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "min") == 0)
        spin_button_config->min = atof(value);

    if (g_strcmp0(property, "max") == 0)
        spin_button_config->max = atof(value);

    if (g_strcmp0(property, "step") == 0)
        spin_button_config->step = atof(value);

    if (g_strcmp0(property, "initial_value") == 0)
        spin_button_config->initial_value = atof(value);

    if (g_strcmp0(property, "decimal") == 0)
        spin_button_config->decimal = atoi(value);

    if (g_strcmp0(property, "is_numeric") == 0)
        spin_button_config->is_numeric = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    if (g_strcmp0(property, "is_digits") == 0)
        spin_button_config->is_digits = g_strcmp0(value, "true") == 0 ? TRUE : FALSE;

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_spin_button_config(FILE *index, SpinButtonConfig *spin_button_config)
{
    // Check if the window config and the index file is not null
    if (!spin_button_config || !index)
        return NULL;

    // Create view config
    ViewConfig *view_config = NULL;
    SAFE_ALLOC(view_config, ViewConfig, 1);
    DFEAULT_VIEW_CONFIG(view_config);

    // Store the property and value of the tag
    gchar *property = NULL;
    gchar *value = NULL;

    // Read the tag character by character
    gchar c;
    while ((c = fgetc(index)) != '>')
    {
        /* If the character is a letter then go back one character
            Because when the tag is readed the cursor will start with the first letter in the property and it will be lost */
        if (is_character(c))
            fseek(index, -1, SEEK_CUR);

        int status = -1;

        // Read the property of the tag
        property = read_property(index, &status);

        // If the all properties are readed then break the loop and return the view id and pass the properties to the window config
        if (status == 2)
            return view_config;

        // If the property is readed then read the value of the property
        else if (status == 1 && property)
        {
            // Read the value of the property
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                if (g_strcmp0(property, "id") == 0) // Store the view id
                {
                    strcpy(view_config->view_id, value);
                    free(property);
                }
                else
                {
                    // Apply the property value to the spin button config
                    view_config = configure_spin_button_property(spin_button_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }
    return view_config;
}

GtkWidget *create_spin_button(SpinButtonConfig spin_button)
{
    GtkAdjustment *w_adj = gtk_adjustment_new(
        spin_button.initial_value,
        spin_button.min,
        spin_button.max,
        spin_button.step,
        0.1,
        spin_button.is_digits ? 2 : 0);

    GtkWidget *w_spin_button = gtk_spin_button_new(
        GTK_ADJUSTMENT(w_adj),
        3,
        spin_button.is_digits ? 2 : 0);
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
