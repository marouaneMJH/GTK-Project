#ifndef SIGNAL_H
#define SIGNAL_H

#include "./../../global.h"
/**
 * @brief Most commonly used GTK3 signals
 *
 * This enum defines the most frequently used signals in GTK3 applications.
 * It is used to identify which signals are connected to the current widget.
 * Each signal corresponds to a specific event, such as a button click, text change,
 * or window close request. These signals help in managing user interactions
 * and widget behavior within the application.
 *
 * Usage:
 * - Use this enum to reference signals in a more readable and organized way.
 * - Combine with a signal mapping function to dynamically connect signals.
 * - Used in SignalConfig to know whitch signale the widget use
 *
 * Example:
 * SignalType signal = SIG_ON_CLICK;
 * g_signal_connect(widget, get_signal_name(signal), G_CALLBACK(callback_function), NULL);
 */
typedef enum
{
    SIG_NONE, // No signal

    SIG_ON_CLICK,             // Triggered when a button is clicked.
    SIG_ON_TOGGLE,            // Triggered when a toggleable widget changes state.
    SIG_ON_CHANGE,            // Triggered when content changes.
    SIG_ON_ACTIVATE,          // Triggered when Enter is pressed inside a widget.
    SIG_ON_DELETE_EVENT,      // Triggered when a window is requested to close.
    SIG_ON_DESTROY,           // Triggered when a widget is destroyed.
    SIG_ON_VALUE_CHANGED,     // Triggered when a value changes (e.g., slider moves).
    SIG_ON_ROW_ACTIVATED,     // Triggered when a row is double-clicked or activated.
    SIG_ON_KEY_PRESS,         // Triggered when a key is pressed while widget has focus.
    SIG_ON_KEY_RELEASE,       // Triggered when a key is released.
    SIG_ON_BUTTON_PRESS,      // Triggered when a mouse button is pressed.
    SIG_ON_BUTTON_RELEASE,    // Triggered when a mouse button is released.
    SIG_ON_MOTION_NOTIFY,     // Triggered when the mouse moves over a widget.
    SIG_ON_FOCUS_IN,          // Triggered when a widget gains focus.
    SIG_ON_FOCUS_OUT,         // Triggered when a widget loses focus.
    SIG_ON_SWITCH_PAGE,       // Triggered when switching tabs in a notebook.
    SIG_ON_SELECTION_CHANGED, // Triggered when selection changes in views (e.g., GtkTreeView).
    SIG_ON_POPUP_MENU,        // Triggered when a context menu is requested (right-click).
    SIG_ON_SCROLL,            // Triggered when the scroll wheel is used.
    SIG_ON_ENTER_NOTIFY,      // Triggered when the mouse enters a widget's area.
    SIG_ON_LEAVE_NOTIFY,      // Triggered when the mouse leaves a widget's area.
    SIG_ON_RESPONSE,

    SIG_LAST // Placeholder for the last signal
} SignalType;

/**
 * @brief Signal and its handler configuration
 *
 * This struct defines a mapping between a GTK signal and its corresponding handler function.
 * It is useful for managing multiple signals in a structured way, making it easier to
 * dynamically connect signals to their respective widgets in a GTK application.
 *
 * Fields:
 * - `sig_handler`: A string representing the name of the handler function that will be
 *    called when the signal is emitted.
 * - `event_name`: An enumeration value of type `SignalType` that specifies the signal type.
 *
 * Example usage:
 * @code
 * - XML
 *      on_click="sig_function"
 * - C
 * SignalConfig config = {
 *     .sig_handler = "sig_function",
 *     .event_name = SIG_ON_CLICK
 * };

 * @endcode
 */
typedef struct
{
    gchar sig_handler[MAX_SIGNAL_NAME_SIZE];
    SignalType event_type;
} SignalConfig;


#endif