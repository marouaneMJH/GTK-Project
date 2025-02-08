#ifndef COMBO_TEXT_BOX_H
#define COMBO_TEXT_BOX_H

#include "./../../global.h"

// Default style configuration
#define DEFAULT_COMBO_TEXT_BOX_STYLE ((ComboTextBoxStyle){ \
    .bg_color = "\0",                                      \
    .color = "\0",                                         \
    .font_family = "\0",                                   \
    .font_size = 0,                                        \
    .is_bold = FALSE,                                      \
    .is_italic = FALSE})

// Default dimensions
#define DEFAULT_COMBO_TEXT_BOX_DIMENSION { \
    .width = -1,                           \
    .height = -1}

// Default Margins
#define DEFAULT_COMBO_TEXT_BOX_MARGINS { \
    .top = 0,                           \
    .bottom = 0,                        \
    .start = 0,                         \
    .end = 0}

// Default configuration including all new properties
// Default configuration
#define DEFAULT_COMBO_TEXT_BOX_CONFIG ((ComboTextBoxConfig){ \
    .options = NULL,                                         \
    .dimensions = DEFAULT_COMBO_TEXT_BOX_DIMENSION,          \
    .margins = DEFAULT_COMBO_TEXT_BOX_MARGINS,                \
    .has_entry = FALSE,                                      \
    .placeholder_text = NULL,                                \
    .wrap_width = 0,                                         \
    .popup_fixed_width = FALSE,                               \
    .popup_shown_rows = 10,                                  \
    .style = DEFAULT_COMBO_TEXT_BOX_STYLE})
/**
 * @brief Structure to hold the key-value pairs for combo box options
 */
typedef struct
{
    gchar *key;
    gchar *value;
} ComboTextBoxOption;

/**
 * @brief Visual style configuration for the combo box
 */
typedef struct
{
    gchar bg_color[MAX_COLOR_SIZE];          // Background color in CSS format
    gchar color[MAX_COLOR_SIZE];             // Text color in CSS format
    gchar font_family[MAX_FONT_FAMILY_SIZE]; // Font family name
    gint font_size;                          // Font size in points
    gboolean is_bold;                        // Whether text should be bold
    gboolean is_italic;                      // Whether text should be italic
} ComboTextBoxStyle;

/**
 * @brief Configuration structure for the combo box widget
 *
 * Usage in XML:
 * <combo_text_box
 *     dimensions="width,height"
 *     margins="top,bottom,start,end"
 *     has_entry="true"
 *     default_value="optional default"
 *     popup_fixed_width="true"
 *     placeholder_text="Select an option..."
 *     ...
 * />
 */

typedef struct
{
    // Basic properties
    GPtrArray *options;      // Array of ComboTextBoxOption (list of options)
    Dimensions dimensions;   // Widget dimensions (width & height)
    Margins margins;         // Widget margins
    gboolean has_entry;      // Whether to allow text input
    gchar *placeholder_text; // Placeholder text inside the entry
    gint wrap_width;
    // Behavior properties
    gboolean popup_fixed_width; // Whether popup should match combo width
    gint popup_shown_rows;      // Maximum number of visible rows in dropdown

    // Style properties
    ComboTextBoxStyle style; // Background, text color, font, etc.

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
ViewConfig *configure_combo_text_box_property(
    ComboTextBoxConfig *combo_text_box_config,
    ViewConfig *view_config,
    gchar *property,
    gchar *value);

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
ViewConfig *init_combo_text_box_config(FILE *index,
                                       ComboTextBoxConfig *combo_text_box_config);

/**
 * @brief Creates a new GtkWidget for displaying a combo text box.
 *
 * This function takes a ComboTextBoxConfig structure containing the necessary
 * data to configure the combo text box and returns a pointer to a newly created
 * GtkWidget that displays the combo text box.
 *
 * @param combo_text_box_config A pointer to a ComboTextBoxConfig structure containing
 *                              the configuration data for the combo text box.
 * @return GtkW idget* A pointer to the newly created GtkWidget for the combo text box.
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