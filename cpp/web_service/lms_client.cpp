//
// Created by Dave on 1/13/21.
//

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <future>
#include <drogon/drogon.h>
#include "lms_client.h"

namespace waveshare_eink_cpp
{

lms_client::lms_client()
{
    // This assumes that drogon::app().run(); is called somewhere else
}


void lms_client::play()
{

    using namespace drogon;

    // Move this to reuse it
    auto client = HttpClient::newHttpClient("http://192.168.31.210:9000");

    // From working curl script - that started here: https://forums.slimdevices.com/showthread.php?43880-any-javascript-json-squeezecenter-examples
    //  curl -i -X POST -H 'Content-Type: application/json' -d \
    //    '{"id":1,"method":"slim.request","params":["piCorePlayer", ["play"]]}' \
    //    http://piCorePlayer:9000/jsonrpc.js

    Json::Value tags;
    tags.append("play");

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


    client->sendRequest(
            req,
            [](ReqResult result, const HttpResponsePtr &response) {

                if(nullptr == response)
                {
                    std::cerr << "Response is somehow null\n";
                    return;
                }
                std::cout << "receive response!" << std::endl;
                // auto headers=response.

                std::cout << "{{{" << response->getBody() << "}}}" << std::endl;
                auto cookies = response->cookies();
                for (auto const &cookie : cookies)
                {
                    std::cout << cookie.first << "="
                              << cookie.second.value()
                              << ":domain=" << cookie.second.domain()
                              << std::endl;
                }
            });
}

void lms_client::pause()
{

    using namespace drogon;

    // Move this to reuse it
    auto client = HttpClient::newHttpClient("http://192.168.31.210:9000");

    // From working curl script - that started here: https://forums.slimdevices.com/showthread.php?43880-any-javascript-json-squeezecenter-examples
    //  curl -i -X POST -H 'Content-Type: application/json' -d \
    //    '{"id":1,"method":"slim.request","params":["piCorePlayer", ["play"]]}' \
    //    http://piCorePlayer:9000/jsonrpc.js

    Json::Value tags;
    tags.append("pause");
//    tags.append("-");
//    tags.append(1);
//    tags.append("tags:al");

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


    client->sendRequest(
            req,
            [](ReqResult result, const HttpResponsePtr &response) {

                if(nullptr == response)
                {
                    std::cerr << "Response is somehow null\n";
                    return;
                }
                std::cout << "receive response!" << std::endl;
                // auto headers=response.

                std::cout << "{{{" << response->getBody() << "}}}" << std::endl;
            });
}



std::string lms_client::currently_playing()
{
    std::string currently_playing_result_string;
    std::mutex mutex;
    std::condition_variable cv;

    using namespace drogon;

    // Move this to reuse it
    auto client = HttpClient::newHttpClient("http://192.168.31.210:9000");

    // From working curl script - that started here: https://forums.slimdevices.com/showthread.php?43880-any-javascript-json-squeezecenter-examples
    //  curl -i -X POST -H 'Content-Type: application/json' -d \
    //    '{"id":1,"method":"slim.request","params":["piCorePlayer",["status","-",1,"tags:al"]]}' \
    //    http://192.168.31.210:9000/jsonrpc.js

    // curl -i -X POST -H 'Content-Type: application/json' -d \
    //    '{"id":1,"method":"slim.request","params":["piCorePlayer",["status","-",1,"tags:gABbehldiqtyrSuoKLN"]]}' \
    //    http://192.168.31.210:9000/jsonrpc.js
    Json::Value tags;
    tags.append("status");
    tags.append("-");
    tags.append(1);
    tags.append("tags:gABbehldiqtyrSuoKLN");

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

    std::cout << "req<<<" << req->getBody() << ">>>" << std::endl;


    client->sendRequest(
            req,
            [&currently_playing_result_string, &mutex, &cv](ReqResult result, const HttpResponsePtr &response) {

                std::string current_title = "Unknown";

                try
                {
                    if(nullptr == response)
                    {
                        std::cerr << "Response is somehow null\n";
                        return;
                    }



                    std::cout << "rep<<<" << response->getBody() << ">>>" << std::endl;

                    auto json_reply = response->getJsonObject();
                    auto json_result = (*json_reply)["result"];
                    auto json_playlist_cur_index = json_result["playlist_cur_index"];
                    std::cout << "json_playlist_cur_index (" << json_playlist_cur_index << ")" << std::endl;

                    // Don't know why asInt doesn't convert "0"
                    const std::string string_cur_index = json_playlist_cur_index.asString();
//                    const int int_cur_index = std::stoi(string_cur_index);
//                    std::cout << "cur_index stripped (" << int_cur_index << ")" << std::endl;

                    auto json_playlist_loop = json_result["playlist_loop"];
                    std::cout << "json_playlist_loop = " << json_playlist_loop << std::endl;
                    auto json_current_song = json_playlist_loop[0]; // just use first always apparently int_cur_index];
                    std::cout << "json_current_song(" << json_current_song << ")" << std::endl;

                    auto json_current_title = json_current_song["title"];
                    std::cout << "json_current_title(" << json_current_title << ")" << std::endl;

                    current_title = json_current_title.asString();
                }
                catch(const std::exception &e)
                {
                    std::cerr << "Exception getting current title: " << e.what() << std::endl;
                    current_title = "Exc: " + std::string((nullptr != e.what())?(e.what()):("null"));
                }

                // Update return value
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    currently_playing_result_string = current_title;
                    cv.notify_all();
                }

                // TODO - need a way to force an update - would be nice to do a partial update
            });

    // TODO, add timeout!
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [&](){ return !currently_playing_result_string.empty(); });
    return currently_playing_result_string;
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
