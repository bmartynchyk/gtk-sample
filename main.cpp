#include <cstdlib>
#include <iostream>

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <Magick++.h>

#include "interface_gdk_layer.h"
#include "core_image.h"

// Build:
// pkg-config --cflags gtk+-2.0
// pkg-config --cflags gtkmm-3.0

// `Magick++-config --cxxflags --cppflags`

// Linker:
// pkg-config --libs gtk+-2.0
// pkg-config --libs gtkmm-3.0

// `Magick++-config --ldflags --libs`

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    Magick::InitializeMagick(*argv);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // The watermark is set once when the application starts AND stores in
    //global singleton object 'GlobalConfig'.
    const char* default_watermark_filename = "pic-samples/watermark/watermark.png";
    
    core::GlobalConfig::getInstance().setWatermarkFilename(default_watermark_filename);
    
     // Create and draw window.
    create_main_menu(window);
    
    // Classes Image and Watermark used in include file interface_gdk_layer.h in funcs:
    // 'on_rotate_45degrees_btn_clicked',
    // 'on_resize_to800x800_btn_clicked',
    // 'on_add_watermark_btn_clicked'.
    
    // GTK mainloop.
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}

