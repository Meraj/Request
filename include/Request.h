//
// Created by Meraj on 3/23/2021.
//

#ifndef REQUEST_REQUEST_H
#define REQUEST_REQUEST_H

#include <iostream>
#include "curl/curl.h"
#include <vector>
class Response{
public:
    std::string url;
    std::string body;
    long response_code;
};

class Request {
private:
    std::string userAgent = "c++ Request";
    std::string url;
    CURL *curl;
    bool isSetMethod = false;
    bool hasParameters = false;
    std::vector<std::string> parameterNames;
    std::vector<std::string> parameterValues;
    std::string generateParameterString();
public:
    int GET = 0;
    int POST = 1;
    Request();
    Request setUserAgent(std::string userAgent_str);
    Request setMethod(std::string method);
    Request setMethod(int method);
    Request setUrl(std::string url);
    Request setUrl(char url);
    Request setTimeOut(int milliseconds);
    Request verifyHost(bool doVerify);
    Request followRedirects(bool doFollow);
    Request maxRedirects(int maxRedirects_int);
    Request addParameter(std::string name,std::string value);
    Response execute();

    void reset();
    //
    static Response get(std::string url);
    static Response get(std::string url,bool verifyHost);
    static Response get(std::string url,bool verifyHost,int maxRedirects);
    //
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
};



#endif //REQUEST_REQUEST_H
