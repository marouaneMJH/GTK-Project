#include "../../include/widgets/progress_bar.h"



GtkWidget *create_progress_bar(ProgressBarConfig progress_bar_config)
{
  

    GtkWidget *progress_bar = gtk_progress_bar_new();

    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.text);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.progress_fraction);
    if (progress_bar_config.progress_pulse_step > 0)
    gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.progress_pulse_step);
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.is_text_visible);
    gtk_progress_bar_set_inverted(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.is_inverted);
    gtk_progress_bar_set_ellipsize(GTK_PROGRESS_BAR(progress_bar), progress_bar_config.ellipsize);
    gtk_widget_set_opacity(progress_bar, progress_bar_config.opacity);
    gtk_widget_set_size_request(progress_bar, progress_bar_config.dimension.width, progress_bar_config.dimension.height);

    widget_set_colors(GTK_WIDGET(progress_bar), progress_bar_config.bg_color, progress_bar_config.text_color);
    widget_set_margins(GTK_WIDGET(progress_bar), progress_bar_config.margins);

    return progress_bar;
}