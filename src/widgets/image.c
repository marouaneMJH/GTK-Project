#include "../../include/widgets/image.h"

GtkWidget *create_image(ImageConfig image_config)
{


    if (image_config.type != IMAGE_EMPTY && image_config.type != IMAGE_FILE && image_config.type != IMAGE_RESOURCE)
    {
        perror("Invalid image type");
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


    GtkWidget *image = gtk_image_new_from_icon_name(image_config.path, size);

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

GtkWidget *create_image_from_pixbuf(ImageConfig image_config, GdkPixbuf *pixbuf)
{


    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);

    gtk_widget_set_size_request(image, image_config.dimensions.width, image_config.dimensions.height);
    gtk_widget_set_opacity(image, image_config.opacity);
    widget_set_margins(image, image_config.margins);
    return image;
}