#include <iostream>
#include "../include/Request.h"

int main() {
    Request request;
    Response response = request.setUrl(
            "http://google.com").execute(); // get request to 'http://google.com' without following redirects and verify ssl host

    request.reset(); // reset request curl

    Response response1 = request.setUrl("http://google.com").setMethod(request.GET).followRedirects(true).maxRedirects(
            5).execute(); // get request to 'http://google.com' with following redirects with max redirect 5 without verify ssl host

    Response response2 = Request::get("http://google.com"); // static function to get request
    Response response3 = Request::get("http://google.com", true); // static function to get request with verify host
    Response response4 = Request::get("http://google.com", false,
                                      5); // static function to get request without verify host and mac redirect 5


    // post request
    request.reset();
    Response response5 = request.setUrl("http://google.com").setMethod(request.POST)
            .addParameter("name", "test")
            .addParameter("pass", "test2")
            .execute();
    // Print data
    std::cout << response.body << std::endl; // content of webpage
    std::cout << response.response_code << std::endl; // response code
    std::cout << response.url << std::endl; // request url
}