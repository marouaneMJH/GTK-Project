#ifndef FRAME_H
#define FRAME_H

#include "./../../global.h"

/*  default values */

#define MAX_LABEL_SIZE 50

#define DEFAULT_FRAME_DIMENSIONS \
    {                            \
        .height = 0,             \
        .width = 0}

#define DEFAULT_FRAME_MARGINS \
    {                         \
        .bottom = 0,          \
        .top = 0,             \
        .start = 0,           \
        .end = 0}

#define DEFAULT_FRAME_CONFIG                    \
    {                                           \
        .label = "\0",                          \
        .margins = DEFAULT_FRAME_MARGINS,       \
        .dimensions = DEFAULT_FRAME_DIMENSIONS, \
        .bg_color = "\0",                       \
        .text_color = "\0"}

typedef struct
{
    gchar label[MAX_LABEL_SIZE];
    Margins margins;
    Dimensions dimensions;
    gchar bg_color[MAX_COLOR_SIZE];
    gchar text_color[MAX_COLOR_SIZE];
} FrameConfig;



GtkWidget *create_frame(FrameConfig frame_config);

#endif