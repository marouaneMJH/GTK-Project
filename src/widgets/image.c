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
    if (g_strcmp0(property, "margin_top") == 0)
        image_config->margins.top = atoi(value);

    if (g_strcmp0(property, "margin_bottom") == 0)
        image_config->margins.bottom = atoi(value);

    if (g_strcmp0(property, "margin_left") == 0)
        image_config->margins.start = atoi(value);

    if (g_strcmp0(property, "margin_right") == 0)
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
    return init_generic_config(index, (void *)image_config, (ConfigurePropertyCallback)configure_image_property);
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
    case IMAGE_ICON:
        image = gtk_image_new_from_icon_name(image_config.path, GTK_ICON_SIZE_DIALOG);
        break;
    case IMAGE_ANIMATION:
        image = gtk_image_new_from_animation(gdk_pixbuf_animation_new_from_file(image_config.path, NULL));
        break;
    case IMAGE_PIXBUF:
        image = create_image_from_pixbuf(image_config.path, image_config.dimensions);
        break;
    case IMAGE_ICON_NAME:
        image = gtk_image_new_from_icon_name(image_config.path, GTK_ICON_SIZE_DIALOG); // size should be configurable
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
    return image;
}

GtkWidget *create_image_from_animation(ImageConfig image_config, GdkPixbufAnimation *animation)
{
    GtkWidget *image = gtk_image_new_from_animation(animation);
    return image;
}

GtkWidget *create_image_from_pixbuf(char *path, Dimensions dimensions)
{

    // Load the image into a GdkPixbuf
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);
    if (!pixbuf)
    {
        g_printerr("Error loading image\n");
        return NULL;
    }

    // Resize the image
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, dimensions.width, dimensions.height, GDK_INTERP_BILINEAR);

    // Create a GtkImage widget and set the scaled image
    GtkWidget *image = gtk_image_new_from_pixbuf(scaled_pixbuf);

    // Clean up the original pixbuf (not needed anymore)
    g_object_unref(pixbuf);
    g_object_unref(scaled_pixbuf);

    return image;
}

gchar *write_image_property(FILE *output_file, View *view, int tabs_number)
{
    if (!output_file || !view)
        return "\0";

    // Write the widget tag and style configuration (without styling elements)
    write_widget_tag_style_view_config(output_file, view, "image", tabs_number);

    // Get the GtkImage from the view
    GtkImage *image = GTK_IMAGE(view->widget);

    // Get the image type (file, icon, etc.)
    GtkImageType image_type = gtk_image_get_storage_type(image);
    if (image_type != GTK_IMAGE_EMPTY) // Check if the image type is not empty
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "type=\"%s\"\n", image_type == GTK_IMAGE_PIXBUF ? "file" : image_type == GTK_IMAGE_ICON_NAME ? "icon"
                                                                                    : image_type == GTK_IMAGE_GICON       ? "gicon"
                                                                                    : image_type == GTK_IMAGE_ANIMATION   ? "animation"
                                                                                    : image_type == GTK_IMAGE_ICON_SET    ? "icon_set"
                                                                                                                          : "unknown");
    }

    // Get the image path or icon name (if applicable)
    const gchar *path = NULL;
    if (image_type == GTK_IMAGE_PIXBUF)
    {
        // todo solve the problem of this type
    }
    else if (image_type == GTK_IMAGE_ICON_NAME)
    {
        const gchar *icon_name = NULL;
        gtk_image_get_icon_name(image, &icon_name, NULL);
        path = icon_name;
    }
    else if (image_type == GTK_IMAGE_GICON)
    {
        GIcon *gicon = NULL;
        gtk_image_get_gicon(image, &gicon, NULL);
        if (G_IS_FILE_ICON(gicon))
        {
            GFile *file = g_file_icon_get_file(G_FILE_ICON(gicon));
            path = g_file_get_path(file);
        }
    }

    if (path && g_strcmp0(path, "\0") != 0) // Check if the path is not the default
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "path=\"%s\"\n", path);
    }

    // Get the opacity
    gdouble opacity = gtk_widget_get_opacity(GTK_WIDGET(image));
    if (opacity != 1.0) // Check if it's not the default value
    {
        print_tabs(output_file, tabs_number + 1);
        fprintf(output_file, "opacity=\"%f\"\n", opacity);
    }

    return "image";
}
