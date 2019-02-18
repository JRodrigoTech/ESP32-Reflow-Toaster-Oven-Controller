static const String header  = "<!DOCTYPE html><html><head><title>Reflow Control Panel</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                              "<link rel=\"shortcut icon\" href=\"https://www.jrodrigo.net/wp-content/uploads/2017/11/jrodrigo-logo-1.ico\">"                              
							  "<style>"
                              "*{box-sizing: border-box;}"
                              ".menu {"
                              "float: left;"
                              "width: 30%;}"
                              ".menuitem{"
                              "padding: 8px;"
                              "margin-top: 7px;"
                              "border-bottom: 1px solid #f1f1f1;}"
                              ".main{"
                              "float: left;"
                              "width: 70%;"
                              "padding: 0 20px;"
                              "overflow: hidden;}"
							  "graph{"
              				  "margin: 10px auto;"
              				  "border-style: solid;"
              				  "border-width: 1px;"
              				  "width: 650px;"
              				  "height: 400px;}"
                              "@media only screen and (max-width:800px) {"
                              ".main {"
                              "width: 80%;"
                              "padding: 0;}"
                              ".right{"
                              "width: 100%;"
                              "}}"
                              "@media only screen and (max-width:500px) {"
                              ".menu, .main, .right {"
                              "width: 100%;}}"
                              "</style></head><body style=\"font-family:Verdana;\">";

static const String title = "<div style=\"background-color:#f1f1f1;padding:15px;\"><h2>Reflow Control Panel</h2></div>";

/*static const String menu  = "<div style=\"overflow:auto\"><div class=\"menu\">"
                            "<div class=\"menuitem\">Profile: </div>"
                            "<div class=\"menuitem\">Current Temp.: <span id=\"temp\">00,0 &deg;C</span></div>"
                            "<div class=\"menuitem\">IP : 192.168.4.1</div>"
                            "<div class=\"menuitem\"> </div>"
                            "<div class=\"menuitem\"><input type=\"submit\" value=\"Start Reflow\"></div>"
                            "<div class=\"menuitem\"> </div>"
                            "<div class=\"menuitem\"><a href=\"/settings/wifi\">Settings</a></div>"
                            "</div>";

*/
String menu(int profilenum,char pro1[32],char pro2[32],char pro3[32], char pro4[32]){



    
    String menu  = "<div style=\"overflow:auto\"><div class=\"menu\">"
                    "<div class=\"menuitem\">Current Profile <select><option value=\"1\"";
                    
                    if(profilenum == 1){ menu += " selected"; }
                    
          menu  += ">1 : "+ String(pro1)+"</option><option value=\"2\"";
          
                    if(profilenum == 2){ menu += " selected"; }
          
          
          menu  += ">2 : "+ String(pro2)+"</option><option value=\"3\"";

                    if(profilenum == 3){ menu += " selected"; }

          menu  += ">3 : "+ String(pro3)+"</option><option value=\"4\"";

                    if(profilenum == 3){ menu += " selected"; }

          menu  += ">4 : "+ String(pro4)+"</option>"        

                    "</select></div>"
                    "<div class=\"menuitem\">Current Temp.: <span id=\"temp\">00,0 &deg;C</span></div>"
                    "<div class=\"menuitem\"> </div>"
                    "<div class=\"menuitem\"><input type=\"submit\" value=\"Start Reflow\"></div>"
                    "<div class=\"menuitem\"> </div>"
                    "<div class=\"menuitem\"><a href=\"/settings/profile/1\">Settings</a></div>"
                    "</div>";
    
    return menu;
    
}

                            
static const String main  = "<div class=\"main\">"
                            "<h3>Profile 2 : LeadFree</h3>"
                            "<p><canvas id=\"graph\"></canvas></p></div></div>";

static const String bottom = "<div style=\"background-color:#f1f1f1;text-align:center;padding:10px;margin-top:7px;font-size:12px;\"> WiFi Reflow Controller - ESP32 - Version 0.0.1a - <a href=\"https://github.com/JRodrigoTech/ESP32-Reflow-Toaster-Oven-Controller\"  target=\"_blank\">GitHub</a></div>";

static const String mainscripts = "<script src=\"data:text/javascript;base64,dmFyIGdyYXBoID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoJ2dyYXBoJyksCgkJY29udGV4dCA9IGdyYXBoLmdldENvbnRleHQoJzJkJyksCgkJd2lkdGggPSBncmFwaC53aWR0aCA9IDY1MCwKCQloZWlnaHQgPSBncmFwaC5oZWlnaHQgPSA0MDA7Cgp2YXIgc3RhdHMgPSBbNDAsIDY1LCA3MiwgMTIwLCAxNTAsIDE3NSwgMjAwLCAxMDAsNTAsMjAsMTAsNV07Cgpjb250ZXh0LnRyYW5zbGF0ZSgwLCBoZWlnaHQpOwpjb250ZXh0LnNjYWxlKDEsIC0xKTsKCmNvbnRleHQuZmlsbFN0eWxlID0gJyNmNmY2ZjYnOwpjb250ZXh0LmZpbGxSZWN0KDAsIDAsIHdpZHRoLCBoZWlnaHQpOwoKdmFyIGxlZnQgPSAwLAoJCXByZXZfc3RhdCA9IHN0YXRzWzBdLAoJCW1vdmVfbGVmdF9ieSA9IDUwOwoKZm9yKHN0YXQgaW4gc3RhdHMpIHsKCXRoZV9zdGF0ID0gc3RhdHNbc3RhdF07CgoJY29udGV4dC5iZWdpblBhdGgoKTsKCWNvbnRleHQubW92ZVRvKGxlZnQsIHByZXZfc3RhdCk7Cgljb250ZXh0LmxpbmVUbyhsZWZ0K21vdmVfbGVmdF9ieSwgdGhlX3N0YXQpOwoJY29udGV4dC5saW5lV2lkdGggPSAyOwoJY29udGV4dC5saW5lQ2FwID0gJ3JvdW5kJzsKLyoKCWlmKHRoZV9zdGF0IDwgc3RhdHNbc3RhdC0xXSkgewoJCWNvbnRleHQuc3Ryb2tlU3R5bGUgPSAnI2MwMzkyYic7Cgl9IGVsc2UgewoJCWNvbnRleHQuc3Ryb2tlU3R5bGUgPSAnIzNiM2IzYic7Cgl9CgkqLwoJY29udGV4dC5zdHJva2UoKTsKCglwcmV2X3N0YXQgPSB0aGVfc3RhdDsKCWxlZnQgKz0gbW92ZV9sZWZ0X2J5OwoKfQ==\"></script>"
                             "<script src=\"data:text/javascript;base64,dmFyIG15VmFyID0gc2V0SW50ZXJ2YWwoZnVuY3Rpb24oKSB7CiAgdGVtcGVyYXR1cmVfdXBkYXRlKCk7Cn0sIDI1MDApOwoKZnVuY3Rpb24gdGVtcGVyYXR1cmVfdXBkYXRlKCkgewogIHZhciB4aHR0cCA9IG5ldyBYTUxIdHRwUmVxdWVzdCgpOwogIHhodHRwLm9ucmVhZHlzdGF0ZWNoYW5nZSA9IGZ1bmN0aW9uKCkgewogICAgaWYgKHRoaXMucmVhZHlTdGF0ZSA9PSA0ICYmIHRoaXMuc3RhdHVzID09IDIwMCkgewogICAgICBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGVtcCIpLmlubmVySFRNTCA9CiAgICAgIHRoaXMucmVzcG9uc2VUZXh0ICsgIiAmZGVnO0MiOwogICAgfQogIH07CiAgeGh0dHAub3BlbigiR0VUIiwgIi90ZW1wMSIsIHRydWUpOwogIHhodHRwLnNlbmQoKTsKfQ==\"></script>";
                             
static const String webend = "</body></html>";

// Settings

static const String settingsmenu  = "<div style=\"overflow:auto\"><div class=\"menu\">"
                                    "<div class=\"menuitem\"><h3>Settings</h3></div>"
                                    "<div class=\"menuitem\"><a href=\"/settings/profile/1\">Profile 1</a></div>"
                                    "<div class=\"menuitem\"><a href=\"/settings/profile/2\">Profile 2</a></div>"
                                    "<div class=\"menuitem\"><a href=\"/settings/profile/3\">Profile 3</a></div>"
                                    "<div class=\"menuitem\"><a href=\"/settings/profile/4\">Profile 4</a></div>"
                                    "<div class=\"menuitem\"><a href=\"/settings/wifi\">Wi-Fi Connection</a></div>"
                                    "<div class=\"menuitem\"> </div>"
                                    "<div class=\"menuitem\"><a href=\"/reboot\">Reboot</a></div>"
                                    "<div class=\"menuitem\"> </div>"
                                    "<div class=\"menuitem\"><a href=\"/\">Back</a></div>"                               
                                    "</div>";


// WIFI SAVE
static const String wifisettings1 = "<script src=\"data:text/javascript;base64,ZnVuY3Rpb24gc2F2ZXdpZmkoKSB7CiAgICB2YXIgc3NpZCA9IGRvY3VtZW50LmdldEVsZW1lbnRCeUlkKCJzc2lkIik7Cgl2YXIgcHdkID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoInB3ZCIpOwkKICAgIHZhciBnb3VybCA9ICJodHRwOi8vIiArIHdpbmRvdy5sb2NhdGlvbi5ob3N0ICsgIi93aWZpLyIgKyBzc2lkLnZhbHVlICsgIi8iICsgcHdkLnZhbHVlOwogICAgd2luZG93LmxvY2F0aW9uID0gZ291cmw7CQp9\"></script>"
                               "<div class=\"main\"><h3>WiFi Configuration</h3><div>SSID:<br><input type=\"text\" id=\"ssid\" value=\"";
static const String wifisettings2 = "\"><br>Password:<br><input type=\"text\" id=\"pwd\" value=\"";
static const String wifisettings3 =  "\"><br><br><input type=\"submit\" value=\"Save\" onClick=\"savewifi()\"></div></div></div>";



// PROFILE SAVE

static const String setprojava = "<script src=\"data:text/javascript;base64,ZnVuY3Rpb24gc2F2ZXByb2ZpbGUoKXsKICAgIHZhciBuYW1lID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoIm5hbWUiKTsKCXZhciBwcm9maWxlbnVtID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoInByb2ZpbGVudW0iKTsKCgl2YXIgdGVtcDEgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGVtcDEiKTsJCgl2YXIgdGVtcDIgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGVtcDIiKTsJCgl2YXIgdGVtcDMgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGVtcDMiKTsJCgl2YXIgdGVtcDQgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGVtcDQiKTsJCgoJdmFyIHRpbWUxID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoInRpbWUxIik7CQoJdmFyIHRpbWUyID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoInRpbWUyIik7Cgl2YXIgdGltZTMgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGltZTMiKTsKCXZhciB0aW1lNCA9IGRvY3VtZW50LmdldEVsZW1lbnRCeUlkKCJ0aW1lNCIpOwoKICAgIHZhciBnb3VybCA9ICJodHRwOi8vIiArIHdpbmRvdy5sb2NhdGlvbi5ob3N0ICsgIi9wcm9maWxlLyIgKyBwcm9maWxlbnVtLnZhbHVlICsgIi8iICsgbmFtZS52YWx1ZSArICIvIiArIHRlbXAxLnZhbHVlICsgIi8iICsgdGVtcDIudmFsdWUgKyAiLyIgKyB0ZW1wMy52YWx1ZSArICIvIiArIHRlbXA0LnZhbHVlICsgIi8iICsgdGltZTEudmFsdWUgKyAiLyIgKyB0aW1lMi52YWx1ZSArICIvIiArIHRpbWUzLnZhbHVlICsgIi8iICsgdGltZTQudmFsdWU7CiAgICB3aW5kb3cubG9jYXRpb24gPSBnb3VybDsJCn0=\"></script>";

String profileset(int profilenum,char profnam[32],int itemp1,int itemp2,int itemp3,int itemp4,int itime1,int itime2,int itime3,int itime4){

    String printhtml = "<div class=\"main\"><h3>Profile " +String(profilenum)+ " Configuration</h3>"
                       "<div>Profile Name <input type=\"text\" id=\"name\" value=\"" +String(profnam)+ "\"><br>"
                       "<input type=\"hidden\" id=\"profilenum\" value=\"" +String(profilenum)+ "\">"
                       "Temperatures:<br>"

                       "<input type=\"text\" id=\"temp1\" value=\"" +String(itemp1)+ "\">"
                       "<input type=\"text\" id=\"temp2\" value=\"" +String(itemp2)+ "\">"
                       "<input type=\"text\" id=\"temp3\" value=\"" +String(itemp3)+ "\">"
                       "<input type=\"text\" id=\"temp4\" value=\"" +String(itemp4)+ "\">"

                       "<br>Time:<br>"

                       "<input type=\"text\" id=\"time1\" value=\"" +String(itime1)+ "\">"
                       "<input type=\"text\" id=\"time2\" value=\"" +String(itime2)+ "\">"
                       "<input type=\"text\" id=\"time3\" value=\"" +String(itime3)+ "\">"
                       "<input type=\"text\" id=\"time4\" value=\"" +String(itime4)+ "\">"


                       "<br><br><input type=\"submit\" value=\"Save\" onClick=\"saveprofile()\"></div></div></div>";

    return printhtml;
    
}




