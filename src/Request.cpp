//
// Created by Meraj on 3/23/2021.
//

#include "../include/Request.h"

Request::Request() {
    this->curl = curl_easy_init();
}
void Request::setMethod(std::string method) {
    std::for_each(method.begin(), method.end(), [](char & c) {
        c = ::tolower(c);
    });

   if(method == "get"){
    this->setMethod(Request::GET);
   }else if(method == "post"){
       this->setMethod(Request::POST);
   }
}
void Request::setMethod(int method) {
    switch (method) {
        case 0:
            curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "GET");
            break;
        case 1:
            curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "POST");
            break;
    }
}

Response Request::execute() {

}