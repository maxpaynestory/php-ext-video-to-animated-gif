#include "iostream"
#include "fstream"
#include "phpcpp.h"
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include "gif.h"

Php::Value v2gConvertVideoToGif(Php::Parameters &params){
    std::string sourceFile = params[0];
    std::string destFile = params[1];
    std::int32_t startFrame = params[2];
    std::int32_t endFrame = params[3];

    if(startFrame <= 0){
        startFrame = 0;
    }

    if(endFrame <= 0){
        endFrame = 15;
    }
    
    std::ifstream video_file(sourceFile.c_str());
    
    if(video_file.good() == false){
        throw Php::Exception("Unable to read video file");
        return -1;
    }
    cv::VideoCapture video(sourceFile);

    if(!video.isOpened()){
        throw Php::Exception("Unable to open video file");
        return -1;
    }

    cv::Mat frame;
    cv::Mat rgbaFrame;
    GifWriter writer;
    bool success = video.read(frame);
    GifBegin(&writer, destFile.c_str(), frame.size().width, frame.size().height, 20);
    int32_t frameCounter = 0;
    while(success && frameCounter<=endFrame){
        success = video.read(frame);
        cv::cvtColor(frame, rgbaFrame, CV_BGR2RGBA);
        if(frameCounter >= startFrame){
            GifWriteFrame(&writer,rgbaFrame.data, frame.size().width, frame.size().height, 20);
        }
        frameCounter++;
    }
    GifEnd(&writer);
    video.release();
    return 1;
}

extern "C"
{
    PHPCPP_EXPORT void *get_module() 
    {
        static Php::Extension extension("php_video_2_gif", "0.1");
        extension.add<v2gConvertVideoToGif>("v2gConvertVideoToGif",{
                    Php::ByVal("sourceFile", Php::Type::String),
                    Php::ByVal("destFile", Php::Type::String),
                    Php::ByVal("startFrame", Php::Type::Numeric,false),
                    Php::ByVal("endFrame", Php::Type::Numeric,false)
        });
        return extension.module();
    }
}