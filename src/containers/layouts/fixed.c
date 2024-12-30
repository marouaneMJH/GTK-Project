#include "./../../../include/containers/layouts/fixed.h"

FixedConfig *init_fixed()
{
    FixedConfig *fixed_config = NULL;
    SAFE_ALLOC(fixed_config, FixedConfig, 1);

    return fixed_config;
}

GtkWidget *create_fixed(FixedConfig fixed_config)
{
    GtkWidget *fixed = NULL;

    // Creation
    fixed = gtk_fixed_new();
    
    return fixed;
}