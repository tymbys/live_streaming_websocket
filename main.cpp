#include "ProcessingFFmpegToWebSocket.h"

const char usage[] = "Usage: %s [-d video] [-p PORT] [-v] DIR\n"
        "   Serves files from DIR over HTTP on port PORT\n";

int main(int argc, char** argv) {

//    const struct option longopts[] ={
//        {"verbose", no_argument, 0, 'v'},
//        {"video", required_argument, 0, 'd'},
//        {"port", required_argument, 0, 'p'},
//        {"size_in", required_argument, 0, 'i'},
//        {"size_out", required_argument, 0, 'o'},
//        {0, 0, 0, 0},
//    };

    int opt;

    int port = 9090;
    bool is_verbose = false;
    string dev = "/dev/video0";
    bool is_skip_frame = true;

    int w_in = 640;
    int h_in = 480;
    int w_out = 640;
    int h_out = 480;

    while ((opt = getopt(argc, argv, "vpd:")) != -1) {
        switch (opt) {
            case 'v': is_verbose = true;
                break;
            case 'p': port = atoi(optarg);
                break;
            case 'd':
                dev = optarg;
                break;
            case 's':
                is_skip_frame = true;
                break;
                
            default:
                fprintf(stderr, usage, argv[0]);

                //exit(1);
        }
    }
    if (optind >= argc) {
        fprintf(stderr, usage, argv[0]);
        //exit(1);
    }


    Processing processing;
    
    std::cout << "!!!!!!!!!!!!!!!is_verbose: " << is_verbose << std::endl;
    std::cout << "!!!!!!!!!!!!!!!port: " << port << std::endl;
    std::cout << "!!!!!!!!!!!!!!!dev: " << dev << std::endl;
    std::cout << "!!!!!!!!!!!!!!!is_skip_frame: " << is_skip_frame << std::endl;

    processing.SetPort(port);
    processing.SetVerbose(is_verbose);    
    processing.SetVideo(dev);
    processing.SetSkipFrame(is_skip_frame);


    processing.ProcessingFFmpegToWebSocket();


    return 0;
}

