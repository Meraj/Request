//
// Created by Meraj on 3/23/2021.
//

#include "../include/Request.h"

Request::Request() {
    this->curl = curl_easy_init();
}

Request Request::setUrl(std::string url) {
    this->url = std::move(url);
    curl_easy_setopt(this->curl, CURLOPT_URL, this->url.c_str());
    return *this;
}

Request Request::setUrl(char url) {
    this->url = url;
    curl_easy_setopt(this->curl, CURLOPT_URL, this->url.c_str());
    return *this;
}

Request Request::setMethod(std::string method) {
    std::for_each(method.begin(), method.end(), [](char &c) {
        c = ::tolower(c);
    });

    if (method == "get") {
        this->setMethod(Request::GET);
    } else if (method == "post") {
        this->setMethod(Request::POST);
    }
    return *this;
}

Request Request::setMethod(int method) {
    this->isSetMethod = true;
    switch (method) {
        case 0:
            curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "GET");
            break;
        case 1:
            curl_easy_setopt(this->curl, CURLOPT_POST, 1);
            break;
    }
    return *this;
}

Request Request::setTimeOut(int milliseconds) {
    curl_easy_setopt(this->curl, CURLOPT_TIMEOUT_MS, milliseconds);
    return *this;
}

Request Request::verifyHost(bool doVerify) {
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, doVerify);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, doVerify);
    return *this;
}

Request Request::setUserAgent(std::string userAgent_str) {
    this->userAgent = std::move(userAgent_str);
    return *this;
}

Request Request::followRedirects(bool doFollow) {
    curl_easy_setopt(this->curl, CURLOPT_FOLLOWLOCATION, doFollow);
    return *this;
}

Request Request::maxRedirects(int maxRedirects_int) {
    curl_easy_setopt(this->curl, CURLOPT_MAXREDIRS, maxRedirects_int);
    return *this;
}

Response Request::execute() {
    Response response = Response();
    response.url = this->url;
    if(!this->isSetMethod){
        this->setMethod(Request::GET);
    }

    curl_easy_setopt(this->curl, CURLOPT_USERAGENT, this->userAgent.c_str()); // set user agent
    if(this->hasParameters){
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, this->generateParameterString().c_str());
    }
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &response.body);
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    CURLcode res = curl_easy_perform(this->curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.response_code);
    if (res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    return response;
}

void Request::reset() {
    this->isSetMethod = false;
    this->hasParameters = false;
    this->parameterNames = {};
    this->parameterValues = {};
curl_easy_reset(this->curl);
}

Response Request::get(std::string url) {
return Request::get(url,false,5);
}
Response Request::get(std::string url, bool verifyHost) {
    return Request::get(url,verifyHost,5);
}
Response Request::get(std::string url, bool verifyHost, int maxRedirects) {
    Request request;
    return request.setMethod(0).setUrl(url).followRedirects(true).maxRedirects(maxRedirects).verifyHost(verifyHost).execute();
}

Request Request::addParameter(std::string name, std::string value) {
    this->hasParameters = true;
    this->parameterNames.push_back(std::move(name));
    this->parameterValues.push_back(std::move(value));
    return *this;
}

std::string Request::generateParameterString() {
    std::string parameter;
    for(int i = 0; i < this->parameterNames.size(); i++){
        parameter += this->parameterNames[i]+"="+this->parameterValues[i]+"&";
    }
    parameter.erase(std::prev(parameter.end()));
    return parameter;
}

