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
//    app().registerHandler("/test?username={name}",
//          [](const HttpRequestPtr& req,
//             std::function<void (const HttpResponsePtr &)> &&callback,
//                 const std::string &name)
//          {
//              Json::Value json;
//              json["result"]="ok";
//              json["message"]=std::string("hello,")+name;
//              auto resp=HttpResponse::newHttpJsonResponse(json);
//              callback(resp);
//          },
//          {Get,"LoginFilter"});


    app().registerHandler("/api/list",
          [&](const HttpRequestPtr& req,
             std::function<void (const HttpResponsePtr &)> &&callback)
          {
              Json::Value json;
              json["result"]="ok";

              std::vector<std::string> names = m_screen_manager_ptr->list_screens();
              for(const auto & name : names)
              {
                 json["screen_list"].append(name);
              }

              auto resp=HttpResponse::newHttpJsonResponse(json);
              callback(resp);
          } /*,
          {Get,"LoginFilter"}*/ );


    app().registerHandler("/api/screen={name}",
          [&](const HttpRequestPtr& req,
             std::function<void (const HttpResponsePtr &)> &&callback,
             const std::string &name)
          {
              LOG_DEBUG << "screen=" << name;

              bool set_screen_result {false};
              bool draw_current_screen_result {false};

              if(m_screen_manager_ptr)
              {

                  if(name != "all")
                  {
                      set_screen_result = m_screen_manager_ptr->set_screen(name);
                      if(set_screen_result)
                      {
                          draw_current_screen_result = m_screen_manager_ptr->draw_current_screen();
                          m_screen_manager_ptr->send_to_display();
                      }
                  }
                  else
                  {
                      const auto names = m_screen_manager_ptr->list_screens();
                      for(const auto & name : names)
                      {
                          set_screen_result = m_screen_manager_ptr->set_screen(name);
                          if(set_screen_result)
                          {
                              draw_current_screen_result = m_screen_manager_ptr->draw_current_screen();
                          }
                      }
                      m_screen_manager_ptr->send_to_display();
                  }
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

    app().registerHandler("/api/clear={value}",
              [&](const HttpRequestPtr& req,
                  std::function<void (const HttpResponsePtr &)> &&callback,
                  const std::string &value)
              {
                  LOG_DEBUG << "display=" << value;

                  const uint8_t pixel_value = std::stoi(value);

                  bool clear_current_screen_result {false};
                  bool draw_current_screen_result {false};

                  if(m_screen_manager_ptr)
                  {
                      clear_current_screen_result = m_screen_manager_ptr->clear_current_screen(pixel_value);
                      m_screen_manager_ptr->send_to_display();
                  }

                  Json::Value json;
                  json["result"]="ok";
                  json["clear"]=value;
                  json["clear_current_screen_result"] = clear_current_screen_result;
                  json["draw_current_screen_result"] = draw_current_screen_result;
                  auto resp=HttpResponse::newHttpJsonResponse(json);
                  callback(resp);
              },
              {Get,"LoginFilter"});


    app().registerHandler("/api/draw_current_screen",
              [&](const HttpRequestPtr& req,
                  std::function<void (const HttpResponsePtr &)> &&callback
                  )
              {

                  bool draw_current_screen_result {false};

                  if(m_screen_manager_ptr)
                  {
                      draw_current_screen_result = m_screen_manager_ptr->draw_current_screen();
                      m_screen_manager_ptr->send_to_display();
                  }

                  Json::Value json;
                  json["result"]="ok";
                  json["draw_current_screen_result"] = draw_current_screen_result;
                  auto resp=HttpResponse::newHttpJsonResponse(json);
                  callback(resp);
              },
              {Get,"LoginFilter"});

    app().registerHandler("/api/shutdown",
          [&](const HttpRequestPtr& req,
              std::function<void (const HttpResponsePtr &)> &&callback)
          {
              LOG_DEBUG << "shutdown";

              Json::Value json;
              json["result"]="ok";
              json["shutdown"]=true;
              auto resp=HttpResponse::newHttpJsonResponse(json);
              callback(resp);
              drogon::app().quit();
          },
          {Get,"LoginFilter"});

    // Log port number
    // Log endpoints being services

    //Run HTTP framework,the method will block in the internal event loop
// Assumes this is called elsewhere:    drogon::app().run();

#endif
}

waveshare_web_service::~waveshare_web_service() {}

/**
 * Notes:
 * - https://gist.github.com/samtherussell/335bf9ba75363bd167d2470b8689d9f2
 */

}
