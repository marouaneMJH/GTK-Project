#include "../../include/widgets/image.h"

GtkWidget *create_image(ImageConfig *image_data)
{
    if (!image_data){
        perror("Invalid image data");
        exit(EXIT_FAILURE);
    }
    
    if (image_data->type != IMAGE_EMPTY && image_data->type != IMAGE_FILE && image_data->type != IMAGE_RESOURCE ){
        perror("Invalid image type");
        exit(EXIT_FAILURE);
    }

    GtkWidget *image = NULL;

    switch (image_data->type)
    {
    case IMAGE_EMPTY :
        image = gtk_image_new();
        break;
    case IMAGE_FILE:
        image = gtk_image_new_from_file(image_data->path);
        break;
    case IMAGE_RESOURCE:
        image = gtk_image_new_from_resource(image_data->path);
        break;
    default:
        break;
    }

    gtk_widget_set_size_request(image, image_data->dimensions.width, image_data->dimensions.height);
    gtk_widget_set_opacity(image, image_data->opacity);
    widget_set_margins(image, image_data->margins);

    return image;
}

GtkWidget* create_image_from_Icon(ImageConfig *image_data, GIcon *icon, GtkIconSize size)
{
    if (!image_data){
        perror("Invalid image data");
        exit(EXIT_FAILURE);
    }

    GtkWidget *image = gtk_image_new_from_gicon(icon,size);

    return image;
}

GtkWidget* create_image_from_icon_name(ImageConfig* image_data,GtkIconSize size)
{
    if (!image_data){
        perror("Invalid image data");
        exit(EXIT_FAILURE);
    }

    GtkWidget *image = gtk_image_new_from_icon_name(image_data->path,size);

    return image;
}

GtkWidget* create_image_from_animation(ImageConfig* image_data,GdkPixbufAnimation* animation)
{
    if (!image_data){
        perror("Invalid image data");
        exit(EXIT_FAILURE);
    }

    GtkWidget *image = gtk_image_new_from_animation(animation);

    return image;
}

GtkWidget* create_image_from_pixbuf(ImageConfig* image_data,GdkPixbuf* pixbuf)
{
    if (!image_data){
        perror("Invalid image data");
        exit(EXIT_FAILURE);
    }

    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);

    return image;
}