#include "./../../../include/widgets/View/xml_builder/xml_builder.h"


gboolean is_container(GtkWidget *widget)
{
    if (!widget)
        return FALSE;

    if (GTK_IS_BUTTON(widget))
        return FALSE;

    return (GTK_IS_BOX(widget) ||
            GTK_IS_FLOW_BOX(widget) ||
            GTK_IS_MENU(widget) ||
            GTK_IS_MENU_BAR(widget) ||
            GTK_IS_PANED(widget) ||
            GTK_IS_FIXED(widget) ||
            GTK_IS_FRAME(widget) ||
            GTK_IS_EXPANDER(widget) ||
            GTK_IS_NOTEBOOK(widget) ||
            GTK_IS_OVERLAY(widget) ||
            GTK_IS_EVENT_BOX(widget) ||
            GTK_IS_WINDOW(widget) ||
            GTK_IS_GRID(widget) ||
            GTK_IS_SCROLLED_WINDOW(widget) ||
            GTK_IS_STACK(widget));
}

char *write_widget_property(FILE *output_file, View *view, int tabs_number)
{
    if (!view || !output_file)
        return "\0";

    // // find widget and write it
    // if (GTK_IS_SCROLLED_WINDOW(view->widget))
    // {
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<scrolled_window \n");
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);


    //     return "scrolled_window";
    // }
    // if (GTK_IS_BOX(view->widget))
    // {
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<box\n");
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     return "box";
    // }
    // if (GTK_IS_FIXED(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<fixed \n");
    //     return "fixed";
    // }
    // if (GTK_IS_STACK(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<stack \n");
    //     return "stack";
    // }
    // if (GTK_IS_NOTEBOOK(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<notebook \n");
    //     return "notebook";
    // }
    // if (GTK_IS_SWITCH(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<switch_button \n");
    //     return "switch_button";
    // }
    // if (GTK_IS_ENTRY(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<entry \n");
    //     return "entry";
    // }
    // if (GTK_IS_LABEL(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<label \n");
    //     return "label";
    // }
    // if (GTK_IS_SEPARATOR(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<separator \n");
    //     return "separator";
    // }
    // if (GTK_IS_MENU_BAR(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<menu_bar \n");
    //     return "menu_bar";
    // }
    // if (GTK_IS_MENU(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<menu \n");
    //     return "menu";
    // }
    // if (GTK_IS_MENU_ITEM(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<menu_item \n");
    //     return "menu_item";
    // }
    // if (GTK_IS_SPIN_BUTTON(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<spin_button \n");
    //     return "spin_button";
    // }
    // if (GTK_IS_FLOW_BOX(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<flow_box \n");
    //     return "flow_box";
    // }
    // if (GTK_IS_LIST_BOX(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<list_box \n");
    //     return "list_box";
    // }
    // if (GTK_IS_GRID(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<grid \n");
    //     return "grid";
    // }
    // if (GTK_IS_PANED(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<paned \n");
    //     return "paned";
    // }
    // if (GTK_IS_IMAGE(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<image \n");
    //     return "image";
    // }
    // if (GTK_IS_PROGRESS_BAR(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<progress_bar \n");
    //     return "progress_bar";
    // }
    // if (GTK_IS_CHECK_BUTTON(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<check_button \n");
    //     return "check_button";
    // }
    // if (GTK_IS_LINK_BUTTON(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<link_button \n");
    //     return "link_button";
    // }
    // if (GTK_IS_FRAME(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<frame \n");
    //     return "frame";
    // }
    // if (GTK_IS_TEXT_VIEW(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<text_view \n");
    //     return "text_view";
    // }
    // if (GTK_IS_OVERLAY(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<overlay \n");
    //     return "overlay";
    // }
    // if (GTK_IS_DIALOG(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<dialog \n");
    //     return "dialog";
    // }
    // if (GTK_IS_COMBO_BOX_TEXT(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<combo_text_box\n");
    //     return "combo_text_box";
    // }
    // if (GTK_IS_TOGGLE_BUTTON(view->widget))
    // {
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<toggle_button \n");
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     return "toggle_button";
    // }
    // if (GTK_IS_COLOR_BUTTON(view->widget))
    // {
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<color_button \n");
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     return "color_color";
    // }
    // if (GTK_IS_EXPANDER(view->widget))
    // {
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<expander \n");
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     return "expander";
    // }
    // if (GTK_IS_EVENT_BOX(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<event_box \n");
    //     return "event_box";
    // }
    // if (GTK_IS_WINDOW(view->widget))
    // {
    //     print_tabs(output_file, tabs_number + 1);
    //     fprintf(output_file, "id=\"%s\"\n", view->view_config->view_id);
    //     print_tabs(output_file, tabs_number);
    //     fprintf(output_file, "<window \n");
    //     return "window";
    // }

    
    return "\0";
}

// write child widgets then clos tag
void write_widget_close_tag(FILE *output_file, View *view, gchar *tag, int tabs_number)
{

    if (!output_file || !view || !tag)
    {
        g_critical("write_widget_close_tag: NULL parameter.");
        return;
    }
    // close tag for container
    if (is_container(view->widget))
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, ">\n");

        write_widget(output_file, view->child, tabs_number + 1);

        // verify the dual behavior widget
        // sometime  act like container and other like widget combo_text_box menu_item ...

        print_tabs(output_file, tabs_number);
        fprintf(output_file, "</%s>\n", tag);
    }
    // close tag for  normal widget
    else
    {
        print_tabs(output_file, tabs_number);
        fprintf(output_file, "/>\n");
    }
}

// recursive function to write the the tree
void write_widget(FILE *output_file, View *view, int tabs_number)
{

    // exit the function if void
    if (!view || !output_file)
        return;

    char *str = write_widget_property(output_file, view, tabs_number);

    // printing the tag of the widget
    if (strlen(str))
    {

        // write the widget property
        write_widget_style(output_file, view->widget, tabs_number + 1);

        // close tag
        write_widget_close_tag(output_file, view, str, tabs_number);
    }

    // write the brother widget
    write_widget(output_file, view->next, tabs_number);
}

void build_xml(FILE *output_file)
{
    write_widget(output_file, root_view_global, 0);
}
