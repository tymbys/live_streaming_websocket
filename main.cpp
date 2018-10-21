#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/StringUtil.h"
#include "seasocks/WebSocket.h"
#include "seasocks/util/Json.h"


#include <iostream>
#include <cstdio>
#include <chrono>
#include <cstdlib>
#include <getopt.h>
#include <memory>
#include <cstring>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>

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

using namespace std::chrono;
using namespace seasocks;
using namespace std;

char *input_name = "video4linux2";
char *file_name = "/dev/video0";
char *out_file = "yuv420.yuv";



/////////////////////////////////////////////////////////////////////////////////////////////////

class MyServer : public Server{
public:
    using Server::Server;
private:
    virtual void checkThread() const override{
    
    };
};


class MyHandler : public WebSocket::Handler {
public:

    explicit MyHandler(MyServer* server) : _server(server), _currentValue(0) {
        //setValue(1);
        //        std::thread t([this]() {
        //            while (1) {
        //                
        //                for (auto c : this->_connections) {
        //                    c->send(this->_currentSetValue);
        //                }
        //                std::cout << "thread function\n";
        //                sleep(1);
        //            }
        //        });
        //
        //        t.detach();
        //cout << "setCanvas length: " << imgBase64.length() << endl;
        //c->send(_currentSetValue);
        //cout << "setCanvas getRequestUri: " << c->getRequestUri() << endl;
        //cout << "setCanvas getRequestUri: " << c->getHeader() << endl;
        //cout << "setCanvas ok!" << endl;


        //    }
        //sleep(1);

    }

    virtual void onConnect(WebSocket* connection) {

        cout << "onConnect getRequestUri: " << connection->getRequestUri() << endl;
        //cout << "onConnect getRequestUri: " << connection->getHeader() << endl;

        //_connections.insert(connection);
        _connections.insert(connection);
        //connection->send(_currentSetValue);
        //sleep(1);
        cout << "Connected: " << connection->getRequestUri()
                << " : " << formatAddress(connection->getRemoteAddress())
                << endl;
        cout << "Credentials: " << *(connection->credentials()) << endl;
    }

    virtual void onData(WebSocket* connection, const char* data) {
        //        if (0 == strcmp("die", data)) {
        //            _server->terminate();
        //            return;
        //        }
        //        if (0 == strcmp("close", data)) {
        //            cout << "Closing.." << endl;
        //            connection->close();
        //            cout << "Closed." << endl;
        //            return;
        //        }
        //
        //        int value = atoi(data) + 1;
        //        if (value > _currentValue) {
        //            setValue(value);
        //            for (auto c : _connections) {
        //                c->send(_currentSetValue.c_str());
        //            }
        //        }

        cout << "onData " << endl;
    }

    virtual void onDisconnect(WebSocket* connection) {
        _connections.erase(connection);
        cout << "Disconnected: " << connection->getRequestUri()
                << " : " << formatAddress(connection->getRemoteAddress())
                << endl;


    }

    void setCanvas(string imgBase64) noexcept {
        //_currentSetValue = to_json(imgBase64);
        //_mutex.lock();
        _currentSetValue = imgBase64;
        //sleep(1);
        //_currentSetValue = "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";
        //_currentSetValue = "/9j//gAQTGF2YzU2LjYwLjEwMAD/2wBDAAgGBgcGBwgICAgICAkJCQoK";
        //_mutex.unlock();

        cout << "setCanvas length: " << imgBase64.length() << endl;
        for (auto c : _connections) {
            //cout << "setCanvas length: " << imgBase64.length() << endl;
            //c->send(_currentSetValue);
            //noexcept(c->send(_currentSetValue.c_str()));
            c->send(_currentSetValue.c_str());
            //cout << "setCanvas getRequestUri: " << c->getRequestUri() << endl;
            //cout << "setCanvas getRequestUri: " << c->getHeader() << endl;
            //cout << "setCanvas ok!" << endl;


        }


    }

    void setCanvas(const uint8_t* data, size_t length) {
        //_currentSetValue = to_json(imgBase64);
        for (auto c : _connections) {
            c->send(data, length);
            cout << "setCanvas length: " << length << endl;
        }

    }



private:
    set<WebSocket*> _connections;
    Server* _server;
    int _currentValue;
    string _currentSetValue;
    std::mutex _mutex;

    void setValue(int value) {
        _currentValue = value;
        _currentSetValue = makeExecString("set", _currentValue);
    }
};





namespace seasocks {
    namespace {
        const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    }

    std::string base64Encode(const void* data, size_t length) {
        std::string output;
        const auto dataPtr = reinterpret_cast<const uint8_t*> (data);
        for (auto i = 0u; i < length; i += 3) {
            const auto bytesLeft = length - i;
            const auto b0 = dataPtr[i];
            const auto b1 = bytesLeft > 1 ? dataPtr[i + 1] : 0;
            const auto b2 = bytesLeft > 2 ? dataPtr[i + 2] : 0;
            output.push_back(cb64[b0 >> 2]);
            output.push_back(cb64[((b0 & 0x03) << 4) | ((b1 & 0xf0) >> 4)]);
            output.push_back((bytesLeft > 1 ? cb64[((b1 & 0x0f) << 2) | ((b2 & 0xc0) >> 6)] : '='));
            output.push_back((bytesLeft > 2 ? cb64[b2 & 0x3f] : '='));
        }
        return output;
    }
}

namespace {


    shared_ptr<PrintfLogger> logger;
    MyServer *ws_server;
    shared_ptr<MyHandler> handler;

}

//void threadServer() {
//
//    logger = std::make_shared<PrintfLogger>(Logger::Level::DEBUG);
//    ws_server = new Server(logger);
//
//    ws_server->setClientBufferSize(100 * 1024 * 1020);
//    ws_server->setLameConnectionTimeoutSeconds(60);
//
//    //shared_ptr<MyHandler> handler = std::make_shared<MyHandler>(ws_server);
//    handler = std::make_shared<MyHandler>(ws_server);
//    //handler->chooseProtocol();
//    ws_server->addWebSocketHandler("/ws", handler);
//
//    ws_server->serve(".", 9090);
//
//
//}
/////////////////////////////////////////////////////////////////////////////////////////////////

void my_log_callback(void *ptr, int level, const char *fmt, va_list vargs) {
    vprintf(fmt, vargs);
}

int captureOneFrame() {

    AVFormatContext *fmtCtx = NULL;
    AVInputFormat *inputFmt = NULL;
    AVPacket *packet = NULL;
    AVCodecContext *pCodecCtx = NULL;
    struct SwsContext *sws_ctx = NULL;

    int i;
    int ret;
    int videoindex;

    enum AVPixelFormat dst_pix_fmt = AV_PIX_FMT_YUVJ420P;
    const char *dst_size = NULL;
    const char *src_size = NULL;
    uint8_t * src_data[4];
    uint8_t * dst_data[4];
    int src_linesize[4];
    int dst_linesize[4];
    int src_bufsize;
    int dst_bufsize;

    int src_w;
    int src_h; /*
  int dst_w = 1280;
  int dst_h = 720;*/

    int dst_w = 640;
    int dst_h = 480;

    //av_log_set_level(AV_LOG_DEBUG);

    inputFmt = av_find_input_format(input_name);
    if (inputFmt == NULL) {
        std::cout << "can not find input format. " << std::endl;
        return -1;
    }

    const char *videosize1 = "640x480";
    AVDictionary *option = NULL;
    av_dict_set(&option, "video_size", videosize1, 0);

    if (avformat_open_input(&fmtCtx, file_name, inputFmt, &option) < 0) {
        std::cout << "can not open input file." << std::endl;
        return -1;
    }

    //   av_dump_format(fmtCtx, 0, NULL, 0);

    videoindex = -1;
    for (i = 0; i < fmtCtx->nb_streams; i++) {
        if (fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoindex = i;
            break;
        }
    }

    if (videoindex == -1) {
        std::cout << "find video stream failed, now return." << std::endl;
        return -1;
    }

    pCodecCtx = fmtCtx->streams[videoindex]->codec;

    std::cout << "picture width height format" << pCodecCtx->width << pCodecCtx->height << pCodecCtx->pix_fmt << std::endl;

    std::cout << "origin pix_fmt " << pCodecCtx->pix_fmt << std::endl;
    sws_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt
            , dst_w, dst_h, dst_pix_fmt, SWS_BILINEAR, NULL, NULL, NULL);

    src_bufsize = av_image_alloc(src_data, src_linesize, pCodecCtx->width, pCodecCtx->height
            , pCodecCtx->pix_fmt, 16);

    dst_bufsize = av_image_alloc(dst_data, dst_linesize, dst_w, dst_h, dst_pix_fmt, 16);

    packet = (AVPacket *) av_malloc(sizeof (AVPacket));

    uint64_t old_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();


    AVOutputFormat *pOutFormat;
    AVFormatContext *pFormatCtx;
    AVCodecContext *pAVCodecCtx;
    AVStream *pOStream;
    AVCodec *pAVcodec;
    AVFrame *pFrame;

    const char *out_file = "out.jpg";

    pOutFormat = av_guess_format("mjpeg", NULL, NULL);

    if (!pOutFormat) {
        std::cout << "av guess format failed, now return. " << std::endl;
        return -1;
    }


    avformat_alloc_output_context2(&pFormatCtx, NULL, NULL, out_file);
    pOutFormat = pFormatCtx->oformat;

    pOStream = avformat_new_stream(pFormatCtx, NULL);
    if (!pOStream) {
        std::cout << "new stream failed, now return. " << std::endl;
        return -1;
    }

    pAVCodecCtx = pOStream->codec;
    pAVCodecCtx->codec_id = pOutFormat->video_codec;
    pAVCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    pAVCodecCtx->pix_fmt = dst_pix_fmt;
    pAVCodecCtx->width = dst_w;
    pAVCodecCtx->height = dst_h;
    pAVCodecCtx->time_base.num = 1;
    pAVCodecCtx->time_base.den = 25;

    std::cout << "out codec id " << pAVCodecCtx->codec_id << std::endl;

    pAVcodec = avcodec_find_encoder(pAVCodecCtx->codec_id);
    if (!pAVcodec) {
        std::cout << "find avcodec failed. " << std::endl;
        return -1;
    }

    if (avcodec_open2(pAVCodecCtx, pAVcodec, NULL) < 0) {
        std::cout << "avcodec open failed. " << std::endl;
        return -1;
    }

    int size = avpicture_get_size(pAVCodecCtx->pix_fmt, pAVCodecCtx->width, pAVCodecCtx->height);
    std::cout << "size " << size << std::endl;

    pFrame = av_frame_alloc();
    if (!pFrame) {
        std::cout << "out frame alloc failed, now return. " << std::endl;
        return -1;
    }

    int y_size = pAVCodecCtx->width * pAVCodecCtx->height;
    std::cout << "y size " << y_size << std::endl;




    int64_t num_frame = 0;
    string out = "";
    while (av_read_frame(fmtCtx, packet) >= 0) {
        uint64_t now = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
        double diff = (double) 1000000 / (double) (now - old_time);
        std::cout << "Is read FPS:  " << diff << std::endl;
        old_time = now;



        memcpy(src_data[0], packet->data, packet->size);
        sws_scale(sws_ctx, src_data, src_linesize, 0, pCodecCtx->height, dst_data, dst_linesize);



        std::cout << "in save jpeg packet size " << packet->size << std::endl;


        avpicture_fill((AVPicture *) pFrame, dst_data[0], pAVCodecCtx->pix_fmt, pAVCodecCtx->width, pAVCodecCtx->height);


        pAVCodecCtx->qmin = pAVCodecCtx->qmax = 3;
        pAVCodecCtx->mb_lmin = pAVCodecCtx->lmin = pAVCodecCtx->qmin * FF_QP2LAMBDA;
        pAVCodecCtx->mb_lmax = pAVCodecCtx->lmax = pAVCodecCtx->qmax * FF_QP2LAMBDA;
        pAVCodecCtx->flags |= CODEC_FLAG_QSCALE;

        pFrame->quality = 4;
        pFrame->pts = ++i;

        avformat_write_header(pFormatCtx, NULL);


        AVPacket pkt = {0};
        int got_picture;
        av_init_packet(&pkt);


        //Encode  
        ret = avcodec_encode_video2(pAVCodecCtx, &pkt, pFrame, &got_picture);


        if (ret < 0) {
            printf("Encode Error.\n");
            return -1;
        }
        //        if (got_picture == 1) {
        //            pkt.stream_index = pOStream->index;
        //            ret = av_write_frame(pFormatCtx, &pkt);
        //        }

        //        av_free_packet(&pkt);

        //Write Trailer  
        //  av_write_trailer(pFormatCtx); 



        //        if (i < 2) {
        //            /* Write JPEG to file */
        //            char buf[32] = {0};
        //            snprintf(buf, 30, "fram%d.jpeg", i);
        //            FILE *fdJPEG = fopen(buf, "wb");
        //            int bRet = fwrite(pkt.data, sizeof(uint8_t), pkt.size, fdJPEG);
        //            fclose(fdJPEG);
        //
        //            if (bRet <= 0) {
        //                fprintf(stderr, "Error writing jpeg file\n");
        //                return 1;
        //            } else
        //                fprintf(stderr, "jpeg file was writed\n");
        //        }
        //        else
        //            break;

        out = seasocks::base64Encode((const void*) &pkt.data[0], pkt.size);

        handler->setCanvas(out);
        //sleep(2);

        //handler->setCanvas((uint8_t *)out.c_str(), out.length());
        //sleep(1);
        //handler->setCanvas(&pkt.data[0], pkt.size);


        //cout << "!!!!!!!!: " << out.length() << endl;

        //        for(int p=0; p<10; p++){
        //            printf("0X%02X ", pkt.data[p]);
        //        }

        av_free_packet(&pkt);
        
        av_free_packet(packet);
        
    }


    if (pOStream) {
        avcodec_close(pOStream->codec);
        av_free(pFrame);
        //      av_free(pFrame_buf);  
    }
    avio_close(pFormatCtx->pb);
    avformat_free_context(pFormatCtx);

    //av_free_packet(packet);
    av_freep(&dst_data[0]);
    sws_freeContext(sws_ctx);
    avformat_close_input(&fmtCtx);

   
}

int main(int argc, char** argv) {

    //std::thread Server(threadServer);
    thread server([]() {
        logger = std::make_shared<PrintfLogger>(Logger::Level::DEBUG);
        ws_server = new MyServer(logger);

        ws_server->setClientBufferSize(100 * 1024 * 1020);
        ws_server->setLameConnectionTimeoutSeconds(60);

        //shared_ptr<MyHandler> handler = std::make_shared<MyHandler>(ws_server);
        handler = std::make_shared<MyHandler>(ws_server);
        //handler->chooseProtocol();
        ws_server->addWebSocketHandler("/ws", handler);

        ws_server->serve(".", 9090);
    });
    //server.join();

    //sleep(3);

    //av_log_set_level(AV_LOG_ERROR);
    //av_log_set_callback(my_log_callback);

    av_register_all();
    avformat_network_init();
    avcodec_register_all();
    avdevice_register_all();
    //av_log_set_level(AV_LOG_QUIET);

    //auto logger = std::make_shared<PrintfLogger>(Logger::Level::DEBUG);

    if (captureOneFrame() < 0) {
        std::cout << "capture frame failed, now return. " << std::endl;
        return -1;
    }



    return 0;
}

