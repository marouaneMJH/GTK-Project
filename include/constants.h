#ifndef DEFAULT_VALUES_H
#define DEFAULT_VALUES_H


/* macros constant */
// set the maximum size of label content
#define MAX_COLOR_SIZE 10
#define MAX_TOOLTIP_SIZE 100
#define MAX_ICON_NAME_SIZE 50

typedef enum 
{
    IMAGE_EMPTY,
    IMAGE_FILE,
    IMAGE_ICON,
    IMAGE_ICON_NAME,
    IMAGE_PIXBUF,
    IMAGE_RESOURCE,
    IMAGE_ANIMATION
} ImageConfigType ;


#endif