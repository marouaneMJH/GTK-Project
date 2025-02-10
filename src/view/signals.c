#include "./../../include/builder.h"
// todo the tab to structure;

// typedef struct 
// {
//     gchar param[PARAM_COUNT][MAX_SIGNAL_NAME_SIZE]; 
// } node;

static void change_self_bg_color(GtkWidget *widget, gpointer data)
{

    widget_set_colors(widget, (gchar *)data, "black");
}

// static void change_friend_bg_color(GtkWidget *widget, gpointer data)
// {
//     View* friend = find_view_by_id((node*)data->param[0],root_view_gloabl);
//     widget_set_colors(widget, data[1], "black");
// }


static void click1(GtkWidget *widget, gpointer data)
{
    View *view = find_view_by_id("btn1", root_view_gloabl);
    widget_set_colors(view->widget, "yellow", "green");
}

void connect_signales(View *view)
{
    void *callback_fuction = NULL;
    void *data = NULL;
    if (view->view_config->onclick[0] != '\0')
    {
        // apply name of function
        if (strcmp(view->view_config->onclick, "change_self_bg_color") == 0)
        {
            callback_fuction = change_self_bg_color;
            data = g_strdup(view->view_config->param[0]);
        }
        else if (strcmp(view->view_config->onclick, "click1") == 0)
        {
            callback_fuction = click1;
        }
        if (callback_fuction)
            g_signal_connect(G_OBJECT(view->widget), "clicked", G_CALLBACK(callback_fuction), data);
        return; // exit the function
    }
}

// Link signals
// if (view_config->onclick[0] != '\0')
// {
//     if (g_strcmp0(view_config->onclick, "click1") == 0)
//         g_signal_connect(G_OBJECT(button_widget), "clicked", G_CALLBACK(click1), NULL);
//     else if (g_strcmp0(view_config->onclick, "click2") == 0)
//         g_signal_connect(G_OBJECT(button_widget), "clicked", G_CALLBACK(click2), NULL);
// }

// if (view_config->onclick[0] != '\0')
// {
//     if (g_strcmp0(view_config->onclick, "menu_onclick") == 0)
//         g_signal_connect(G_OBJECT(menu_item_widget), "activate", G_CALLBACK(menu_item_onclick), NULL);
//     else if (g_strcmp0(view_config->onclick, "menu_onclick1") == 0)
//         g_signal_connect(G_OBJECT(menu_item_widget), "activate", G_CALLBACK(menu_item_onclick), NULL);
//     }