#include "interface_gdk_layer.h"


void create_main_menu(const GtkWidget *window) {
    // Main window.
    gtk_window_set_title(GTK_WINDOW(window), "Image Editor");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    // Creating a vertical container for buttons.
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Button "Rotate image on 45 degrees".
    GtkWidget *rotate_45degrees_btn = gtk_button_new_with_label("Rotate image on 45 degrees");
    gtk_box_pack_start(GTK_BOX(vbox), rotate_45degrees_btn, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(rotate_45degrees_btn), "clicked", G_CALLBACK(on_rotate_45degrees_btn_clicked), NULL);
        
    // Button "Resize to 800x800".
    GtkWidget *resize_to800x800_btn = gtk_button_new_with_label("Resize to 800x800");
    gtk_box_pack_start(GTK_BOX(vbox), resize_to800x800_btn, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(resize_to800x800_btn), "clicked", G_CALLBACK(on_resize_to800x800_btn_clicked), NULL);
    
    // Button "Add watermark to image".
    GtkWidget *add_watermark_btn = gtk_button_new_with_label("Add watermark to image");
    gtk_box_pack_start(GTK_BOX(vbox), add_watermark_btn, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(add_watermark_btn), "clicked", G_CALLBACK(on_add_watermark_btn_clicked), NULL);

    // Button "Load image to view".
    GtkWidget *load_image_button = gtk_button_new_with_label("Load image to view");
    gtk_box_pack_start(GTK_BOX(vbox), load_image_button, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(load_image_button), "clicked", G_CALLBACK(on_load_image_button_clicked), NULL);
    
    // Button "Exit".
    GtkWidget *exit_button = gtk_button_new_with_label("Exit");
    gtk_box_pack_start(GTK_BOX(vbox), exit_button, TRUE, TRUE, 0);
    g_signal_connect(G_OBJECT(exit_button), "clicked", G_CALLBACK(on_exit_button_clicked), NULL);
}

static void on_load_image_button_clicked(GtkWidget *button, gpointer data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Open Image", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
        "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL
    );

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        // получение пути к выбранному файлу
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        // загрузка изображения из файла
        GError *error = NULL;
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, &error);
        if (error != NULL) {
            g_print("Error loading file: %s\n", error->message);
            g_error_free(error);
            return;
        }

        // вывод изображения в новом окне
        GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "Loaded Image");
        gtk_container_add(GTK_CONTAINER(window), image);
        gtk_widget_show_all(window);

        // освобождение памяти
        g_object_unref(pixbuf);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

static void on_exit_button_clicked(GtkWidget *button, gpointer data) {
    gtk_main_quit();
}




static void on_rotate_45degrees_btn_clicked(GtkWidget *button, gpointer data) {
    core::Image img;
    
    img.load();
    img.rotate(45);
    img.save();
}

static void on_resize_to800x800_btn_clicked(GtkWidget *button, gpointer data) {
    core::Image img;
    
    img.load();
    img.resize(800, 800);
    img.save();
}

static void on_add_watermark_btn_clicked(GtkWidget *button, gpointer data) {
    core::Image image;
    image.load(); // Upload image you want to cover with watermark.
     
    // Stores once uploaded watermark image.
    core::Watermark wtm = core::GlobalConfig::getInstance().getWatermark();
    
    // Covering an image with a watermark.
    core::Image watermaeked_image = wtm.addWatermarkTo(image);
    
    watermaeked_image.save();
}