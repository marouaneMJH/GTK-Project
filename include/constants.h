#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H


/* macros constant */
// set the maximum size of label content
#define MAX_COLOR_SIZE 10
#define MAX_TOOLTIP_SIZE 100
#define MAX_ICON_NAME_SIZE 50
#define MAX_URI_SIZE 256
#define MAX_PROPERTY_SIZE 50
// The maximum size of the xml tag value, it's big cuz of multi line paragraph  
#define MAX_VALUE_SIZE 1024
#define MAX_ICON_PATH_SIZE 50
// The maximum size of the signale function handler name (string)
#define MAX_SIGNAL_NAME_SIZE 100

#define MAX_TAG_SIZE 50
#define MAX_VIEW_ID_SIZE 50
#define PARAM_COUNT 4 // The maximum parameter can signal function have


#define MAX_LABEL_SIZE 100
#define MAX_FONT_FAMILY_SIZE 30 // Maximum characters in  font family name

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