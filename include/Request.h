//
// Created by Meraj on 3/23/2021.
//

#ifndef REQUEST_REQUEST_H
#define REQUEST_REQUEST_H

#include <iostream>
#include "curl/curl.h"

class Response{
public:
    std::string url;
    std::string body;
};

class Request {
private:
    std::string userAgent;
    CURL *curl;
public:
    int GET = 0;
    int POST = 1;
    Request();
    void setUserAgent(std::string userAgent_str);
    void setMethod(std::string method);
    void setMethod(int method);
    void setUrl(std::string url);
    Response execute();
};



#endif //REQUEST_REQUEST_H
