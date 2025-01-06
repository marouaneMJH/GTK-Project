#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H


/* macros constant */
// set the maximum size of label content
#define MAX_COLOR_SIZE 10 // Maximum size for color labels
#define MAX_TOOLTIP_SIZE 100 // Maximum size for tooltip content
#define MAX_ICON_NAME_SIZE 50 // Maximum size for icon names
#define MAX_URI_SIZE 256 // Maximum size for URIs
#define MAX_PROPERTY_SIZE 50 // Maximum size for properties
#define MAX_VALUE_SIZE 100 // Maximum size for values

// Enumeration for different image configuration types
typedef enum 
{
    IMAGE_EMPTY, // No image
    IMAGE_FILE, // Image from a file
    IMAGE_ICON, // Image as an icon
    IMAGE_ICON_NAME, // Image as an icon name
    IMAGE_PIXBUF, // Image as a pixbuf
    IMAGE_RESOURCE, // Image from a resource
    IMAGE_ANIMATION // Image as an animation
} ImageConfigType;


#endif