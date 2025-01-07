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
 * @brief Configures the combo text box property with the given value.
 *
 * This function configures the combo text box property with the given value. It modifies
 * the provided combo text box configuration and view configuration structures and returns
 * the modified view configuration.
 *
 * @param[in] combo_text_box_config A pointer to the ComboTextBoxConfig structure to be modified.
 * @param[in] view_config A pointer to the ViewConfig structure to be modified.
 * @param[in] property The property to configure.
 * @param[in] value The value to set the property to.
 *
 * @return A pointer to the modified ViewConfig structure.
 */
ViewConfig* configure_combo_text_box_property(ComboTextBoxConfig *combo_text_box_config, ViewConfig *view_config, gchar *property, gchar *value);


/**
 * @brief Initializes a combo text box configuration structure with default values.
 *
 * This function initializes a ComboTextBoxConfig structure with default values.
 *
 * @param[in] index A pointer to the file to read the combo text box configuration from index.txt file.
 * @param[out] combo_text_box_config A pointer to the ComboTextBoxConfig structure to initialize.
 *
 * @return A pointer to the initialized ComboTextBoxConfig structure.
 */
ViewConfig *init_combo_text_box_config(FILE *index, ComboTextBoxConfig *combo_text_box_config);

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