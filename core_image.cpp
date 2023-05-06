#include "core_image.h"

namespace core
{
    
    std::string Image::load(){
        filename.clear();
        filename = GtkImageSaveLoader::load();
        
        m_image.read(filename.c_str());
        
        return filename;
    }
    
    void Image::save() {
        GtkImageSaveLoader::save(m_image);
    }
        
    void Image::rotate(const int degrees) {
        m_image.rotate(degrees);
    }
    
    void Image::resize(int cols, int rows) {
        Magick::Geometry newSize(cols, rows);
        m_image.resize(newSize);
    }
    
    std::string Image::getFilename() {
        return filename;
    }
    
    
    
    void Watermark::prepareWatermark() {
        m_watermark.read(m_watermark_filename.c_str());
        m_watermark.resize(Magick::Geometry(200, 100));
        //m_watermark.rotate(45); - removed cuz method removes the transparency of the image.
    }
    
    Watermark::Watermark(std::string wtm_flnm): GtkImageSaveLoader() { 
        m_watermark_filename = wtm_flnm;
        prepareWatermark(); // Make size 200x100.
    }
    
    std::string Watermark::load() {
        m_watermark_filename = GtkImageSaveLoader::load();
        prepareWatermark(); // Make size 200x100.
        
        return m_watermark_filename;
    }
    
    void Watermark::save() {
        GtkImageSaveLoader::save(m_watermark);
    }
    
    core::Image Watermark::addWatermarkTo(core::Image img) {
        Magick::Image loaded_image(img.getFilename());
        
        loaded_image.composite(m_watermark, x, y, Magick::OverCompositeOp);
        
        return loaded_image;
    }
    
    
    
    std::string GtkImageSaveLoader::load() {
        std::string filename = "";
        
        // Creating dialog for file choosing.
        GtkWidget *dialog = gtk_file_chooser_dialog_new(
            "Open Image", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
            "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL
        );

        try {
            
            // Choosing file in dialog.
            gint response = gtk_dialog_run(GTK_DIALOG(dialog));
            if (response == GTK_RESPONSE_ACCEPT) {
                filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
                        
                // Load picture.
                GError *error = NULL;
                GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename.c_str(), &error);
                if (error != NULL) {
                    g_print("Error loading file: %s\n", error->message);
                    g_error_free(error);
                                    
                    g_object_unref(pixbuf);

                    throw std::runtime_error("Error loading file");
                }

                // Output image in separate window.
                GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
                GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                gtk_window_set_title(GTK_WINDOW(window), "Loaded Image");
                gtk_container_add(GTK_CONTAINER(window), image);
                gtk_widget_show_all(window);

                g_object_unref(pixbuf);
            } 
            
        } catch (const std::runtime_error& e) {
                g_print("Error: %s\n", e.what());
                
                gtk_widget_destroy(dialog);
                
                return "error";
        }

        gtk_widget_destroy(dialog);
        
        return filename;
    }
    
    void GtkImageSaveLoader::save(Magick::Image& image) {
        
        // Create dialog.
        GtkWidget *dialog = gtk_file_chooser_dialog_new(
            "Save Image", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
            "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL
        );

        // Seting the filter.
        GtkFileFilter *filter = gtk_file_filter_new();
        gtk_file_filter_set_name(filter, "PNG files");
        gtk_file_filter_add_pattern(filter, "*.png");
        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

        // Selecting file to save.
        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        if (response == GTK_RESPONSE_ACCEPT) {
            
            char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            
            image.write(filename);
            
            g_free(filename);
        }

        gtk_widget_destroy(dialog);
    }
    
    
    
    void GlobalConfig::setWatermarkFilename(const char* wtm_flnm) {
        m_watermark_filename = wtm_flnm;
        
        if (nullptr != m_watermark) {
            delete m_watermark;
        }
        
        m_watermark = new Watermark(m_watermark_filename);
    }
    
    const char* GlobalConfig::getWatermarkFilename() {
        return m_watermark_filename;
    }
    
    Watermark& GlobalConfig::getWatermark() {
        return *m_watermark;
    }

}
