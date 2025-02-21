#ifndef XML_BUILDER
#define XML_BUILDER

#include "./../../../global.h"
#include "xml_writer_globals.h"

void write_widget(FILE *output_file, View *view, int tabs_number);

void build_xml(FILE *output_file);

#endif
