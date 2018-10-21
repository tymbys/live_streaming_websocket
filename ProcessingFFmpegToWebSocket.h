#ifndef PROCESSING_H
#define PROCESSING_H

#ifdef __cplusplus
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libavutil/log.h>
#include <unistd.h>
#endif

#ifdef __cplusplus
};
#endif



#include <cstdio>
#include <cstdlib>

#include "WebServer.h"

class Processing {
public:

    Processing();
    ~Processing();
    std::string base64Encode(const void* data, size_t length);
    //void my_log_callback(void *ptr, int level, const char *fmt, va_list vargs);

    static void threadServer();
    void InitServer();
    int ProcessingFFmpegToWebSocket();


    void SetVerbose(bool v);
    void SetPort(int port);
    void SetVideo(string dev);
    void SetVideoSize_in(string video_size);

private:
    //const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const char *cb64;

    thread server;

    shared_ptr<PrintfLogger> logger;
    shared_ptr<MyServer> ws_server;
    shared_ptr<MyHandler> handler;

    string input_name; // = "video4linux2";
    string file_name; // = "/dev/video0";
    string out_file;
    int port;
    bool verbose;
    
    string video_size_in;
    string video_size_out;
};




#endif /* FFMPEGCONVERTOR_H */

