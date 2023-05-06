#ifndef INTERFACE_GDK_LAYER_H
#define INTERFACE_GDK_LAYER_H

#include <iostream>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <Magick++.h>
#include "core_image.h"

void create_main_menu(const GtkWidget *window);

static void on_load_image_button_clicked(GtkWidget *button, gpointer data);

static void on_save_image_button_clicked(GtkWidget *button, gpointer data);

static void on_exit_button_clicked(GtkWidget *button, gpointer data);


// class Image and Watermark used here.
static void on_rotate_45degrees_btn_clicked(GtkWidget *button, gpointer data);

static void on_resize_to800x800_btn_clicked(GtkWidget *button, gpointer data);

static void on_add_watermark_btn_clicked(GtkWidget *button, gpointer data);

#endif /* INTERFACE_GDK_LAYER_H */

