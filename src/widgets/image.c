#include "../../include/widgets/image.h"

int configure_image_property(ImageConfig *image_config, ViewConfig *view_config, gchar *property, gchar *value)
{
    if (!image_config || !property || !value)
        return -1;

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

    return 1;
}

gchar *init_image_config(FILE *index, ImageConfig *image_config, ViewConfig *view_config)
{
    // Check if the image config and the index file is not null
    if (!image_config || !index)
        return NULL;

    // Store the property and value of the tag
    gchar *property = NULL;
    gchar *value = NULL;

    // The view id of the tag
    gchar *view_id = NULL;

    // Read the tag character by character
    gchar c;
    while ((c = fgetc(index)) != '>')
    {
        printf("INIT : C => %c\n", c);
        /* If the character is a letter then go back one character
            Because when the tag is readed the cursor will start with the first letter in the property and it will be lost */
        if (is_character(c))
            fseek(index, -1, SEEK_CUR);

        int status = -1;

        // Read the property of the tag
        property = read_property(index, &status);

        // If the all properties are readed then break the loop and return the view id and pass the properties to the image config
        if (status == 2)
            return view_id;

        // If the property is readed then read the value of the property
        else if (status == 1 && property)
        {
            // Read the value of the property
            value = read_value(index, &status);
            if (status == 1 && value)
            {
                if (g_strcmp0(property, "id") == 0) // Store the view id
                {
                    view_id = value;
                    free(property);
                }
                else
                {
                    // Apply the property value to the image config
                    configure_image_property(image_config, view_config, property, value);
                    free(value);
                    free(property);
                }
            }
        }
    }
    printf("END INIT C => %c\n", c);

    return view_id;
}

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

GtkWidget *create_image_from_pixbuf(ImageConfig image_config, GdkPixbuf *pixbuf)
{

    GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);

    gtk_widget_set_size_request(image, image_config.dimensions.width, image_config.dimensions.height);
    gtk_widget_set_opacity(image, image_config.opacity);
    widget_set_margins(image, image_config.margins);
    return image;
}