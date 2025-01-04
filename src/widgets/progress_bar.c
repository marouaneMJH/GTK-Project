#include "../../include/widgets/progress_bar.h"



GtkWidget *create_progress_bar(ProgressBarConfig *progress_bar_data)
{
    if (!progress_bar_data)
        exit(EXIT_FAILURE);

    GtkWidget *progress_bar = gtk_progress_bar_new();

    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), progress_bar_data->text);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), progress_bar_data->progress_fraction);
    if (progress_bar_data->progress_pulse_step > 0)
    gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar), progress_bar_data->progress_pulse_step);
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), progress_bar_data->is_text_visible);
    gtk_progress_bar_set_inverted(GTK_PROGRESS_BAR(progress_bar), progress_bar_data->is_inverted);
    gtk_progress_bar_set_ellipsize(GTK_PROGRESS_BAR(progress_bar), progress_bar_data->ellipsize);
    gtk_widget_set_opacity(progress_bar, progress_bar_data->opacity);
    gtk_widget_set_size_request(progress_bar, progress_bar_data->dimension.width, progress_bar_data->dimension.height);

    widget_set_colors(GTK_WIDGET(progress_bar), progress_bar_data->bg_color, progress_bar_data->text_color);
    widget_set_margins(GTK_WIDGET(progress_bar), progress_bar_data->margins);

    return progress_bar;
}