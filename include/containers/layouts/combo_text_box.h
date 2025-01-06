#ifndef COMBO_TEXT_BOX_H
#define COMBO_TEXT_BOX_H

#include "./../../global.h"

/*
    <combo_text_box
        dimensions=...
        margins=...
        has_entry="tue"
        option1="value of option1"
        option2="value of option2"
        ...

    />
*/

#define DEFAULT_COMBO_TEXT_BOX_DIMENSIONS \
    {                                     \
        .height = 0,                      \
        .width = 0}

#define DEFAULT_COMBO_TEXT_BOX_MARGINS \
    {                                  \
        .bottom = 0,                   \
        .top = 0,                      \
        .start = 0,                    \
        .end = 0}

#define DEFAULT_COMBO_TEXT_BOX_OPTIONS \
    {                                  \
        .key = "\0",                   \
        .value = "\0"}

#define DEFAULT_COMBO_TEXT_BOX_CONFIG                    \
    {                                                    \
        .options = NULL,                                 \
        .dimensions = DEFAULT_COMBO_TEXT_BOX_DIMENSIONS, \
        .margins = DEFAULT_COMBO_TEXT_BOX_MARGINS,       \
        .has_entry = FALSE,                              \
        .deafault_value = "\0"}

/**
 * @brief Structure to hold the key-value pairs for the options in a combo text box
 */

typedef struct
{
    gchar *key;
    gchar *value;
} ComboTextBoxOptions;

/**
 * @brief Structure to configure a combo text box widget
 */
typedef struct
{

    GPtrArray *options;    // The options to display in the combo box
    Dimensions dimensions; // The dimensions of the combo box
    Margins margins;       // The margins of the combo box

    gboolean has_entry;    // Whether the combo box should have an entry field
    gchar *deafault_value; // The default value of the combo box
} ComboTextBoxConfig;

/**
 * @brief Sets the specified property of a combo box to a given value, converting
 *        the value to the appropriate data type.
 *
 * This function retrieves the property indicated by the caller, adjusts the
 * data type if needed, and assigns it to the combo box control.
 *
 * @param property  The name or identifier of the combo box property to modify.
 * @param value  The new value to be assigned to the property. This value
 *                  is automatically converted to the data type required by the combo box.
 *
 * @return True if the property update succeeds, false otherwise.
 */
int configure_combo_text_box_property(ComboTextBoxConfig *combo_text_box_config, ViewConfig *view_config, gchar *property, gchar *value);

/**
 * @brief Initializes the combo text box configuration from the provided file.
 *
 * This function reads properties and values for a combo box balise from the given
 * file stream. It modifies the provided combo box configuration and view configuration
 * structures, and returns a newly allocated string containing the view ID.
 *
 * @param[in] index A pointer to the file stream containing the combo box properties.
 * @param[out] combo_text_box_config A pointer to the ComboTextBoxConfig structure to be modified.
 * @param[out] view_config A pointer to the ViewConfig structure to be modified.
 *
 * @return A dynamically allocated gchar pointer representing the view ID
 */
gchar *init_combo_text_box_config(FILE *index, ComboTextBoxConfig *combo_text_box_config, ViewConfig *view_config);

/**
 * @brief Creates a new GtkWidget for displaying a combo text box.
 *
 * This function takes a ComboTextBoxConfig structure containing the necessary
 * data to configure the combo text box and returns a pointer to a newly created
 * GtkWidget that displays the combo text box.
 *
 * @param combo_text_box_config A pointer to a ComboTextBoxConfig structure containing
 *                              the configuration data for the combo text box.
 * @return GtkWidget* A pointer to the newly created GtkWidget for the combo text box.
 */
GtkWidget *create_combo_text_box(ComboTextBoxConfig combo_text_box_config);

/**
 * @brief Removes all the options from a combo text box.
 *
 * This function removes all the options from the specified combo text box.
 *
 * @param combo_text_box A pointer to the GtkComboBoxText widget to remove the options from.
 */
void combo_text_box_remove_all(GtkComboBoxText *combo_text_box);

/**
 * @brief Removes an option from a combo text box at the specified index.
 *
 * This function removes the option at the specified index from the specified combo text box.
 *
 * @param combo_text_box A pointer to the GtkComboBoxText widget to remove the option from.
 * @param index The index of the option to remove.
 */
void combo_text_box_remove(GtkComboBoxText *combo_text_box, gint index);

/**
 * @brief Inserts a new option into a combo text box at the specified index.
 *
 * This function inserts a new option with the specified ID and text at the specified index
 * in the specified combo text box.
 *
 * @param combo_text_box A pointer to the GtkComboBoxText widget to insert the option into.
 * @param index The index at which to insert the new option.
 * @param id The ID of the new option.
 * @param text The text of the new option.
 */
void combo_text_box_insert(GtkComboBoxText *combo_text_box, gint index, const gchar *id, const gchar *text);

#endif