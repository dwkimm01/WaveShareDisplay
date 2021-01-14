//
// Created by Dave on 1/13/21.
//
#include <drogon/drogon.h>
#include <iostream>
#include <future>
#include "lms_client.h"

namespace waveshare_eink_cpp
{

lms_client::lms_client()
{
    using namespace drogon;
    int count = 0;
    auto client = HttpClient::newHttpClient("http://192.168.31.210:9000");


// From working curl script - that started here: https://forums.slimdevices.com/showthread.php?43880-any-javascript-json-squeezecenter-examples
//  curl -i -X POST -H 'Content-Type: application/json' -d \
//    '{"id":1,"method":"slim.request","params":["piCorePlayer",["status","-",1,"tags:al"]]}' \
//    http://192.168.31.210:9000/jsonrpc.js

    Json::Value tags;
    tags.append("status");
    tags.append("-");
    tags.append(1);
    tags.append("tags:al");

    Json::Value tags_array;
    tags_array.append("piCorePlayer");
    tags_array.append(tags);

    Json::Value params;
    params = tags_array;

    Json::Value data;
    data["id"] = 1;
    data["method"] = "slim.request";
    data["params"] = params;
    auto req = HttpRequest::newHttpJsonRequest(data);
    req->setMethod(drogon::Post);
    req->setPath("/jsonrpc.js");

    std::cout << "req(" << req->getBody() << ")" << std::endl;


    for (int i = 0; i < 1; ++i)
    {
        client->sendRequest(
                req,
                [&count](ReqResult result, const HttpResponsePtr &response) {

                    if(nullptr == response)
                    {
                        std::cerr << "Response is somehow null\n";
                        return;
                    }
                    std::cout << "receive response!" << std::endl;
                    // auto headers=response.
                    ++count;
                    std::cout << "{{{" << response->getBody() << "}}}" << std::endl;
                    auto cookies = response->cookies();
                    for (auto const &cookie : cookies)
                    {
                        std::cout << cookie.first << "="
                                  << cookie.second.value()
                                  << ":domain=" << cookie.second.domain()
                                  << std::endl;
                    }
                    std::cout << "count=" << count << std::endl;
                });
    }


//    std::this_thread::sleep_for(std::chrono::seconds(4));
//    app().run();
    // TODO, need to be able to exit out of this without shutting down entire drogon server


}


void lms_client::play()
{

}

std::string currently_playing()
{
    std::string res;


    return res;
}

}

#if 0
Notes

//    {
//        const std::string rawJson = R"({"id":1,"method":"slim.request","params":["piCorePlayer",["status","-",1,"tags:al"]]})";
//        const auto rawJsonLength = static_cast<int>(rawJson.length());
//
//        JSONCPP_STRING err;
//        Json::Value root;
//
//        Json::CharReaderBuilder builder;
//        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
//        if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root,
//                           &err)) {
//            std::cout << "error" << std::endl;
//        }
//    }

#endif
