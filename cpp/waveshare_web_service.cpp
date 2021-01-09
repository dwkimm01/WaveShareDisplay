//
// Created by Dave on 12/30/20.
//

#ifdef ENABLE_DROGON
#include <drogon/drogon.h>
#endif

#include "waveshare_web_service.h"

namespace waveshare_eink_cpp
{
waveshare_web_service::waveshare_web_service
    ( std::shared_ptr<i_screen_mananger> screen_manager_ptr
    ) : m_screen_manager_ptr(screen_manager_ptr)
{

#ifdef ENABLE_DROGON
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0",8080);
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

    app().registerHandler("/api/display={name}",
          [&](const HttpRequestPtr& req,
             std::function<void (const HttpResponsePtr &)> &&callback,
             const std::string &name)
          {
              LOG_DEBUG << "display=" << name;

              bool set_screen_result {false};
              bool draw_current_screen_result {false};

              if(m_screen_manager_ptr)
              {
                  set_screen_result = m_screen_manager_ptr->set_screen(name);
                  draw_current_screen_result = m_screen_manager_ptr->draw_current_screen();
              }

              Json::Value json;
              json["result"]="ok";
              json["display"]=name;
              json["set_screen_result"] = set_screen_result;
              json["draw_current_screen_result"] = draw_current_screen_result;
              auto resp=HttpResponse::newHttpJsonResponse(json);
              callback(resp);
          },
          {Get,"LoginFilter"});

    // Log port number
    // Log endpoints being services


    //Run HTTP framework,the method will block in the internal event loop
        drogon::app().run();
#endif
}

waveshare_web_service::~waveshare_web_service() {}

}
