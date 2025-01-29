#include "../../include/widgets/image.h"

ViewConfig *configure_image_property(ImageConfig *image_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!image_config || !property || !value)
        return NULL;

    if (g_strcmp0(property, "type") == 0)
    {
        if (g_strcmp0(value, "icon") == 0)
            image_config->type = IMAGE_ICON;
        else if (g_strcmp0(value, "icon_name") == 0)
            image_config->type = IMAGE_ICON_NAME;
        else if (g_strcmp0(value, "file") == 0)
            image_config->type = IMAGE_FILE;
        else if (g_strcmp0(value, "pixbuf") == 0)
            image_config->type = IMAGE_PIXBUF;
        else if (g_strcmp0(value, "animation") == 0)
            image_config->type = IMAGE_ANIMATION;
        else if (g_strcmp0(value, "resource") == 0)
            image_config->type = IMAGE_RESOURCE;
        else
            image_config->type = IMAGE_EMPTY;
    }

    if (g_strcmp0(property, "path") == 0)
        strcpy(image_config->path, value);

    if (g_strcmp0(property, "opacity") == 0)
        image_config->opacity, atof(value);

    // Margins
    if (g_strcmp0(property, "mrgin_top") == 0)
        image_config->margins.top = atoi(value);

    if (g_strcmp0(property, "mrgin_bottom") == 0)
        image_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "mrgin_left") == 0)
        image_config->margins.start = atoi(value);

    if (g_strcmp0(property, "mrgin_right") == 0)
        image_config->margins.end = atoi(value);

    // Dimensions
    if (g_strcmp0(property, "width") == 0)
        image_config->dimensions.width = atoi(value);

    if (g_strcmp0(property, "height") == 0)
        image_config->dimensions.height = atoi(value);

    SET_VIEW_CONFIG_PROPERTY(property, value, view_config);

    return view_config;
}

ViewConfig *init_image_config(FILE *index, ImageConfig *image_config)
{
    return init_generic_config(index,(void*)image_config,(ConfigurePropertyCallback)configure_image_property);
}
GtkWidget *create_image(ImageConfig image_config)
{

    if (image_config.type != IMAGE_EMPTY && image_config.type != IMAGE_FILE && image_config.type != IMAGE_RESOURCE && image_config.type != IMAGE_PIXBUF)
    {
        perror("ERROR => Invalid image type");
        exit(EXIT_FAILURE);
    }

    GtkWidget *image = NULL;

    switch (image_config.type)
    {
    case IMAGE_EMPTY:
        image = gtk_image_new();
        break;
    case IMAGE_FILE:
        image = gtk_image_new_from_file(image_config.path);
        break;
    case IMAGE_RESOURCE:
        image = gtk_image_new_from_resource(image_config.path);
        break;
    case IMAGE_PIXBUF:
        image = create_image_from_pixbuf(image_config);
        break;
    default:
        break;
    }

    gtk_widget_set_size_request(image, image_config.dimensions.width, image_config.dimensions.height);

    gtk_widget_set_opacity(image, image_config.opacity);
    widget_set_margins(image, image_config.margins);

    return image;
}

GtkWidget *create_image_from_Icon(ImageConfig image_config, GIcon *icon, GtkIconSize size)
{

    GtkWidget *image = gtk_image_new_from_gicon(icon, size);

    gtk_widget_set_size_request(image, image_config.dimensions.width, image_config.dimensions.height);
    gtk_widget_set_opacity(image, image_config.opacity);
    widget_set_margins(image, image_config.margins);
    return image;
}

GtkWidget *create_image_from_icon_name(ImageConfig image_config, GtkIconSize size)
{

    GtkWidget *image = gtk_image_new_from_icon_name(image_config.path, GTK_ICON_SIZE_DIALOG); // Should be dynamic

    gtk_widget_set_size_request(image, image_config.dimensions.width, image_config.dimensions.height);
    gtk_widget_set_opacity(image, image_config.opacity);
    widget_set_margins(image, image_config.margins);
    return image;
}

GtkWidget *create_image_from_animation(ImageConfig image_config, GdkPixbufAnimation *animation)
{

    GtkWidget *image = gtk_image_new_from_animation(animation);

    gtk_widget_set_size_request(image, image_config.dimensions.width, image_config.dimensions.height);
    gtk_widget_set_opacity(image, image_config.opacity);
    widget_set_margins(image, image_config.margins);
    return image;
}

GtkWidget *create_image_from_pixbuf(ImageConfig image_config)
{

    // Load the image into a GdkPixbuf
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(image_config.path, NULL);
    if (!pixbuf)
    {
        g_printerr("Error loading image\n");
        return NULL;
    }

    // Resize the image
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, image_config.dimensions.width, image_config.dimensions.height, GDK_INTERP_BILINEAR);

    // Create a GtkImage widget and set the scaled image
    GtkWidget *image = gtk_image_new_from_pixbuf(scaled_pixbuf);

    // Clean up the original pixbuf (not needed anymore)
    g_object_unref(pixbuf);

    return image;

}