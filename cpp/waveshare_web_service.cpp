//
// Created by Dave on 12/30/20.
//

#ifdef ENABLE_DROGON
#include <drogon/drogon.h>
#endif

#include "waveshare_web_service.h"


waveshare_web_service::waveshare_web_service()
{

#ifdef ENABLE_DROGON
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0",80);
    //Load config file
    //drogon::app().loadConfigFile("../config.json");

// https://drogon.docsforge.com/master/getting-started/#a-very-simple-example
    using namespace drogon;
    app().registerHandler("/test?username={name}",
          [](const HttpRequestPtr& req,
             std::function<void (const HttpResponsePtr &)> &&callback,
                 const std::string &name)
          {
              Json::Value json;
              json["result"]="ok";
              json["message"]=std::string("hello,")+name;
              auto resp=HttpResponse::newHttpJsonResponse(json);
              callback(resp);
          },
          {Get,"LoginFilter"});


        //Run HTTP framework,the method will block in the internal event loop
        drogon::app().run();
#endif
}

