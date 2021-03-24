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
    struct curl_slist *chunk = NULL;
    bool isSetMethod = false;
    int methodType = 0;
    bool hasParameters = false;
    std::vector<std::string> parameterNames;
    std::vector<std::string> parameterValues;
    std::string generateParameterString();
public:
    int GET = 0;
    int POST = 1;
    Request();
    /**
     * set browser user agent
     * @param userAgent_str std::string - user agent string
     * @author Meraj
     * @since 0.1.0
     */
    Request setUserAgent(std::string userAgent_str);

    /**
     * set request method
     * @param method std::string - get / post
     * @author Meraj
     * @since 0.1.0
     */
    Request setMethod(std::string method);

    /**
     * set request Method
     * @param method std::string - 0 -> get / 1 -> post
     * @author Meraj
     * @since 0.1.0
     */
    Request setMethod(int method);

    /**
     * set url
     * @param url std::string
     * @author Meraj
     * @since 0.1.0
     */
    Request setUrl(std::string url);

    /**
     * set url
     * @param url char
     * @author Meraj
     * @since 0.1.0
     */
    Request setUrl(char url);

    /**
     * set timeout of request
     * @param milliseconds int
     * @author Meraj
     * @since 0.1.0
     */
    Request setTimeOut(int milliseconds);

    /**
     * verify host or not
     * for sending secure request set this to true
     * if you get 0 in response code set it to false
     * (if you set this to false request in NOT secure)
     * @param milliseconds int
     * @author Meraj
     * @since 0.1.0
     */
    Request verifyHost(bool doVerify);

    /**
     * follow redirects ?
     * @param doFollow bool
     * @author Meraj
     * @since 0.1.0
     */
    Request followRedirects(bool doFollow);

    /**
     * max redirects
     * @param maxRedirects_int int
     * @author Meraj
     * @since 0.1.0
     */
    Request maxRedirects(int maxRedirects_int);

    /**
     * do debug ?
     * this function set CURLOPT_VERBOSE to true or false
     * @param shallWe bool
     * @author Meraj
     * @since 0.1.0
     */
    Request doDebug(bool shallWe);

    /**
     * add Parameter to current request
     * @param name std::string
     * @param value std::string
     * @author Meraj
     * @since 0.1.0
     */
    Request addParameter(std::string name,std::string value);

    /**
     * add Custom headers to current request
     * @param name std::string
     * @param value std::string
     * @example addParameter("name","value"); -> name: value
     * @example addParameter("name",""); -> name:
     * @author Meraj
     * @since 0.1.1
     */
    Request addHeader(std::string name,std::string value);

    /**
     * add Custom header to current request
     * @param name std::string
     * @example addHeader("name"); -> name;
     * @author Meraj
     * @since 0.1.1
     */
    Request addHeader(std::string name);

    /**
     * execute request
     * @author Meraj
     * @since 0.1.0
     */
    Response execute();

    /**
     * reset curl (run this after every request)
     * @author Meraj
     * @since 0.1.0
     */
    void reset();
    //
    /**
     * get request
     * @param url std::string
     * @author Meraj
     * @since 0.1.0
     */
    static Response get(std::string url);

    /**
     * get request
     * @param url std::string
     * @param verifyHost bool
     * @author Meraj
     * @since 0.1.0
     */
    static Response get(std::string url,bool verifyHost);

    /**
     * get request
     * @param url std::string
     * @param verifyHost bool
     * @param maxRedirects int
     * @author Meraj
     * @since 0.1.0
     */
    static Response get(std::string url,bool verifyHost,int maxRedirects);
    //
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
};



#endif //REQUEST_REQUEST_H
