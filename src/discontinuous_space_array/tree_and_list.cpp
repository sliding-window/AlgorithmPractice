#include<glog/logging.h>


int main(int arc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::INFO);
    google::SetLogDestination(google::INFO, "./log/log_info");
    google::SetLogDestination(google::ERROR, "./log/log_rr");
    google::SetLogDestination(google::FATAL, "./log/log_fatal");
    LOG(INFO) << "test"<<std::endl;
    LOG(ERROR) << "test"<<std::endl;

    return 0;

}