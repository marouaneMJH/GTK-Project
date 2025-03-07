#ifndef UPDATE_WIDGET_FROM_DIALOG_H
#define UPDATE_WIDGET_FROM_DIALOG_H

#include "./../../../include/builder.h"
#include "./../../../include/widgets/View/signals.h"


void set_current_button_config_to_dialog(ButtonConfig *button_config)
{
    // Label
    write_config_value_as_string("label_entry", button_config->label);

    // Width
    write_config_value_as_int("width_spin", button_config->dimensions.width);

    // Height
    write_config_value_as_int("height_spin", button_config->dimensions.height);

    // Margin top
    write_config_value_as_int("margin_top_spin", button_config->margins.top);

    // Margin bottom
    write_config_value_as_int("margin_bottom_spin", button_config->margins.bottom);

    // Margin left
    write_config_value_as_int("margin_left_spin", button_config->margins.start);

    // Margin right
    write_config_value_as_int("margin_right_spin", button_config->margins.end);

    // HAlign
    gchar *halign = NULL;
    switch (button_config->halign)
    {
    case GTK_ALIGN_START:
        halign = "start";
        break;
    case GTK_ALIGN_END:
        halign = "end";
        break;
    case GTK_ALIGN_BASELINE:
        halign = "baseline";
        break;
    case GTK_ALIGN_CENTER:
        halign = "center";
        break;
    default:
        halign = "center";
        break;
    }
    write_config_value_as_string("halign_combo", halign);

    // VAlign
    gchar *valign = NULL;
    switch (button_config->valign)
    {
    case GTK_ALIGN_START:
        valign = "start";
        break;
    case GTK_ALIGN_END:
        valign = "end";
        break;
    case GTK_ALIGN_BASELINE:
        valign = "baseline";
        break;
    case GTK_ALIGN_CENTER:
        valign = "center";
        break;
    default:
        valign = "center";
        break;
    }
    write_config_value_as_string("valign_combo", valign);

    // HExpand
    write_config_value_as_boolean("hexpand_switch", button_config->hexpand);

    // VExpand
    write_config_value_as_boolean("vexpand_switch", button_config->vexpand);

    // Background color
    write_config_value_as_string("bg_color_entry", button_config->bg_color);

    // Text color
    write_config_value_as_string("color_entry", button_config->color);
}

void set_current_view_config_to_dialog(ViewConfig *view_config)
{
    if (!view_config)
        return;
    write_view_config_to_dialog(view_config);
}

// void update_button_config(View *target_view)
// {
//     ButtonConfig *button_config = read_button_config_from_widget(target_view->widget);
//     build_app(root_app, NULL, BUTTON_PROPERTIES_DIALOG_TXT);
//     dialog = root_dialog_view_global->widget;
//     set_current_button_config_to_dialog(button_config);
//     set_current_view_config_to_dialog(target_view->view_config);
//     set_available_scopes(target_view->view_config->view_id);
// }


#endif