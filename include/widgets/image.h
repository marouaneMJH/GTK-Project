#ifndef IMAGE_H
#define IMAGE_H

#include "./../global.h"

/* Max size of image path */
#define MAX_IMAGE_PATH_SIZE 200

/* Default dimensions for image */
#define DEFAULT_IMAGE_DIMENSIONS \
    {                            \
        .height = 100,           \
        .width = 100}

/* Default margins for image */
#define DEFAULT_IMAGE_MARGINS \
    {                         \
        .bottom = 0,          \
        .top = 0,             \
        .start = 0,           \
        .end = 0}

/* Default image configuration */
#define DEFAULT_IMAGE \
    {                 \
        .type = IMAGE_FILE, \
        .path = "\0", \
        .dimensions = DEFAULT_IMAGE_DIMENSIONS, \
        .margins = DEFAULT_IMAGE_MARGINS, \
        .opacity = 1,}

/**
 * @brief Structure to configure an image widget
 */
typedef struct
{
    ImageConfigType type;            // The type of the image (e.g., file, icon, etc.)
    gchar path[MAX_IMAGE_PATH_SIZE]; // The path of the image file
    Dimensions dimensions;           // The dimensions of the image
    Margins margins;                 // The margins around the image
    gboolean expand;                 // Whether the image should expand to fill its allocated space
    gdouble opacity;                 // The opacity of the image (0.0 to 1.0)

} ImageConfig;

/**
 * @brief Creates a new GtkWidget for displaying an image.
 *
 * This function takes an ImageConfig structure containing the necessary
 * data to configure the image and returns a pointer to a newly created
 * GtkWidget that displays the image.
 *
 * @param image_data A pointer to an ImageConfig structure containing
 *                   the configuration data for the image.
 * @return GtkWidget* A pointer to the newly created GtkWidget for the image.
 */
GtkWidget *create_image(ImageConfig *image_data);

/**
 * @brief Creates a new GtkWidget for displaying an image from a GIcon.
 *
 * This function takes an ImageConfig structure containing the necessary
 * data to configure the image and a GIcon structure containing the icon
 * data, and returns a pointer to a newly created GtkWidget that displays
 * the image.
 *
 * @param image_data A pointer to an ImageConfig structure containing
 *                   the configuration data for the image.
 * @param icon A pointer to a GIcon structure containing the icon data.
 * @param size The size of the icon to display.
 * @return GtkWidget* A pointer to the newly created GtkWidget for the image.
 */
GtkWidget* create_image_from_Icon(ImageConfig *image_data, GIcon *icon, GtkIconSize size);

/**
 * @brief Creates a new GtkWidget for displaying an image from an icon name.
 *
 * This function takes an ImageConfig structure containing the necessary
 * data to configure the image and an icon name, and returns a pointer to
 * a newly created GtkWidget that displays the image.
 *
 * @param image_data A pointer to an ImageConfig structure containing
 *                   the configuration data for the image.
 * @param size The size of the icon to display.
 * @return GtkWidget* A pointer to the newly created GtkWidget for the image.
 */
GtkWidget* create_image_from_icon_name(ImageConfig* image_data,GtkIconSize size);

/**
 * @brief Creates a new GtkWidget for displaying an image from a GdkPixbufAnimation.
 * 
 *  This function takes an ImageConfig structure containing the necessary
 *  data to configure the image and a GdkPixbufAnimation structure containing
 *  the image data, and returns a pointer to a newly created GtkWidget that
 *  displays the image.
 *
 *
 * @param image_data A pointer to an ImageConfig structure containing
 *                   the configuration data for the image.
 * @param animation A pointer to a GdkPixbufAnimation structure containing the image data.
 * @return GtkWidget* A pointer to the newly created GtkWidget for the image.
 */
GtkWidget* create_image_from_animation(ImageConfig* image_data,GdkPixbufAnimation* animation);

/**
 * @brief Creates a new GtkWidget for displaying an image from a GdkPixbuf.
 *
 * This function takes an ImageConfig structure containing the necessary
 * data to configure the image and a GdkPixbuf structure containing the
 * image data, and returns a pointer to a newly created GtkWidget that
 * displays the image.
 *
 * @param image_data A pointer to an ImageConfig structure containing
 *                   the configuration data for the image.
 * @param pixbuf A pointer to a GdkPixbuf structure containing the image data.
 * @return GtkWidget* A pointer to the newly created GtkWidget for the image.
 */
GtkWidget* create_image_from_pixbuf(ImageConfig* image_data,GdkPixbuf* pixbuf);

#endif