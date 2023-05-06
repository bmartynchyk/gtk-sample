#ifndef CORE_IMAGE_H
#define CORE_IMAGE_H

#include <Magick++.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

//using namespace Magick;

namespace core
{
    class IImageSaveLoader
    {
    public:
        virtual std::string load() = 0;
        virtual void save(Magick::Image&) = 0;
        
        virtual ~IImageSaveLoader() = default;
    };
    
    
    class IImageManipulator
    {
    public:
        virtual void rotate(const int) = 0;
        virtual void resize(int, int) = 0;
        
        virtual ~IImageManipulator() = default;
    };
    
    
    class GtkImageSaveLoader: public IImageSaveLoader
    {
    //public:
    protected:
        std::string load();
        void save(Magick::Image&);
        
    public:
        virtual ~GtkImageSaveLoader() = default;
    };
  
    
    class Image: public GtkImageSaveLoader, public IImageManipulator 
    {
    private:
        Magick::Image m_image;
        std::string filename;
    public:
        Image(): GtkImageSaveLoader() { }
        Image(const char* flnm) : GtkImageSaveLoader(), filename(flnm), m_image(flnm) { }
        Image(const Magick::Image &img): filename(img.fileName()), m_image(img) { }
        
        std::string load();
        void save();
        
        std::string getFilename();
        void rotate(const int) override;
        void resize(int, int) override;
        
        virtual ~Image() = default;
    };
    
    
    class Watermark: public GtkImageSaveLoader
    {
    private:
        int x = 20; // Default watermark x, y position.
        int y = 10;
        Magick::Image m_watermark;
        std::string m_watermark_filename;
        
        void prepareWatermark();
        
    public:
        //Watermark(): GtkImageSaveLoader() { }
        Watermark(std::string wtm_flnm);//: GtkImageSaveLoader() { m_watermark_filename = wtm_flnm; }
        
        core::Image addWatermarkTo(core::Image img);
        
        std::string load() override;
        void save();
             
        virtual ~Watermark() = default;
    };
    
    
    // Global configuration object.
    class GlobalConfig
    {
    public:
        void setWatermarkFilename(const char*);
        const char* getWatermarkFilename();
        Watermark& getWatermark();
        
        inline static GlobalConfig &getInstance() {
            static GlobalConfig instance;
            return instance;
        }
        
    private:
        
        Watermark *m_watermark = nullptr;
        const char* m_watermark_filename;
        
        GlobalConfig() = default;
        ~GlobalConfig() =  default;
        
        GlobalConfig(const GlobalConfig&) = delete;
        GlobalConfig& operator=(const GlobalConfig&) = delete;
    };
    
}

#endif /* CORE_IMAGE_H */
