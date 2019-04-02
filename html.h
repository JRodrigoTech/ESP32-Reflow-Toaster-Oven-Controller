// WEB MAIN PAGE HEADER /w STYLE CSS //
static const String header  = "<!DOCTYPE html><html><head>"
  "<title>Reflow Control Panel</title><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
  "<link rel=\"shortcut icon\" href=\"https://www.jrodrigo.net/files/favicon.ico\">"                              
  "<style>"
      "*{box-sizing: border-box;}"
      ".menu{"
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
    "@media only screen and (max-width:800px){"
      ".main{"
      "width: 80%;"
      "padding: 0;}"
      ".right{"
      "width: 100%;"
    "}}"
    "@media only screen and (max-width:500px){"
      ".menu, .main, .right{"
      "width: 100%;}}"
  "</style>"
  "</head><body style=\"font-family:Verdana;\">";

// WEB MAIN TOP TITLE //
static const String title = "<div style=\"background-color:#f1f1f1;padding:15px;\"><h2>Reflow Control Panel</h2></div>";

// WEB HOME - MAIN LEFT MENU //
String menu(int IP1, int IP2, int IP3, int IP4){

    String menu  = "<div style=\"overflow:auto\"><div class=\"menu\">"
                    "<div class=\"menuitem\">Current Profile <select onchange=\"javascript:location.href = this.value;\"";

                    if(REFLOW_STATUS == true){ menu += " disabled"; }
                    
          menu  += "><option value=\"/set/1\"";
                    
                    if(current_profile == 1){ menu += " selected"; }
                    
          menu  += ">1 : "+ String(profile1)+"</option><option value=\"/set/2\"";
          
                    if(current_profile == 2){ menu += " selected"; }
          
          
          menu  += ">2 : "+ String(profile2)+"</option><option value=\"/set/3\"";

                    if(current_profile == 3){ menu += " selected"; }

          menu  += ">3 : "+ String(profile3)+"</option><option value=\"/set/4\"";

                    if(current_profile == 4){ menu += " selected"; }

          menu  += ">4 : "+ String(profile4)+"</option>"        

                    "</select></div>"
                    "<div class=\"menuitem\">Current Temp.: <span id=\"temp\">00,0 &deg;C</span></div>"
                    "<div class=\"menuitem\">Current IP:  "+String(IP1)+"."+String(IP2)+"."+String(IP3)+"."+String(IP4)+"</div>"
                    "<div class=\"menuitem\"> </div>";
                    
         if(REFLOW_STATUS == false){         
          menu  += "<div class=\"menuitem\"><input type=\"submit\" value=\"Start Reflow\" onclick=\"window.location.href='/start'\"></div>";
         } else {
          menu  += "<div class=\"menuitem\"><input type=\"submit\" value=\"STOP Reflow\" onclick=\"window.location.href='/stop'\"></div>";
         }
                    
          menu  += "<div class=\"menuitem\"> </div>"
                    "<div class=\"menuitem\"><a href=\"/settings/profile/1\">Settings</a></div>"
                    "</div>";
    
    return menu;
}

// WEB HOME - CANVAS ZONE //
String mainhome(){
  
  String mainhome  = "<div class=\"main\"><h3>Profile ";
  
     switch (current_profile) {
        case 1:
          mainhome += "1 : "+String(profile1);
          break;
        case 2:
          mainhome += "2 : "+String(profile2);
          break;
        case 3:
          mainhome += "3 : "+String(profile3);
          break;
        case 4:
          mainhome += "4 : "+String(profile4);
          break;
    }    
                 
  mainhome += "</h3><p><canvas id=\"graph\"></canvas></p></div></div>";
  return mainhome;
}

// Live Canvas Graphing Scripts //
static const String mainscripts = "<script src=\"data:text/javascript;base64,Ly8gVXBkYXRlIHRoZXJtb2NvdXBsZSB0ZW1wCnZhciB0ZW1wdGltbWVyID0gc2V0SW50ZXJ2YWwoZnVuY3Rpb24oKSB7CiAgdmFyIHhodHRwID0gbmV3IFhNTEh0dHBSZXF1ZXN0KCk7CiAgeGh0dHAub25yZWFkeXN0YXRlY2hhbmdlID0gZnVuY3Rpb24oKSB7CiAgICBpZiAodGhpcy5yZWFkeVN0YXRlID09IDQgJiYgdGhpcy5zdGF0dXMgPT0gMjAwKSB7CiAgICAgIGRvY3VtZW50LmdldEVsZW1lbnRCeUlkKCJ0ZW1wIikuaW5uZXJIVE1MID0KICAgICAgdGhpcy5yZXNwb25zZVRleHQgKyAiICZkZWc7QyI7CiAgICB9CiAgfTsKICB4aHR0cC5vcGVuKCJHRVQiLCAiL3RlbXAiLCB0cnVlKTsKICB4aHR0cC5zZW5kKCk7Cn0sIDI1NTEpOwoKdmFyIGdyYXBoID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoJ2dyYXBoJyk7CnZhciBjb250ZXh0ID0gZ3JhcGguZ2V0Q29udGV4dCgnMmQnKTsKdmFyCXdpZHRoID0gZ3JhcGgud2lkdGggPSA2NTY7CnZhcgloZWlnaHQgPSBncmFwaC5oZWlnaHQgPSA0MjU7CmNvbnRleHQuZmlsbFN0eWxlID0gJyNmNmY2ZjYnOwpjb250ZXh0LmZpbGxSZWN0KDAsIDAsIHdpZHRoLCBoZWlnaHQpOwpjb250ZXh0LmZpbGxTdHlsZSA9ICIjMDAwMDAwIjsKY29udGV4dC5mb250ID0gIjEycHggQXJpYWwiOwp2YXIgaSA9IDI1Owpmb3IoOyBpIDwgaGVpZ2h0OykgewoJLy8gVGVtcCBWYWx1ZQoJY29udGV4dC5maWxsVGV4dChpLDEsaGVpZ2h0LWkpOwoJLy8gTGluZWFzIEhvcml6b250YWxlcwoJY29udGV4dC5iZWdpblBhdGgoKTsKCWNvbnRleHQubW92ZVRvKDIyLCBoZWlnaHQtaS00KTsJIC8vIFhpLFlpCgljb250ZXh0LmxpbmVUbyh3aWR0aC0zMCwgaGVpZ2h0LWktNCk7IC8vIFhmLFlmCgljb250ZXh0LmxpbmVXaWR0aCA9IDAuMjU7Cgljb250ZXh0LmxpbmVDYXAgPSAncm91bmQnOwoJY29udGV4dC5zdHJva2VTdHlsZSA9ICcjM2IzYjNiJzsKCWNvbnRleHQuc3Ryb2tlKCk7CglpID0gaSsyNTsKfQpjb250ZXh0LmZvbnQgPSAiOXB4IEFyaWFsIjsKY29udGV4dC5maWxsVGV4dChTdHJpbmcuZnJvbUNoYXJDb2RlKDE4NikrIkMiLDExLDEwKTsKY29udGV4dC5maWxsU3R5bGUgPSAiIzAwMDAwMCI7CmNvbnRleHQuZm9udCA9ICIxMnB4IEFyaWFsIjsKY29udGV4dC50ZXh0QWxpZ24gPSAiY2VudGVyIjsKdmFyIGkgPSAwOwpmb3IoOyBpIDwgKHdpZHRoLTMwKTspIHsKCS8vIFRlbXAgVmFsdWUKCWNvbnRleHQuZmlsbFRleHQoaSwyNStpLGhlaWdodC0xMCk7CgkKCS8vIExpbmVhcyBIb3Jpem9udGFsZXMKCWNvbnRleHQuYmVnaW5QYXRoKCk7Cgljb250ZXh0Lm1vdmVUbyhpKzI1LCAyMCk7CSAvLyBYaSxZaQoJY29udGV4dC5saW5lVG8oaSsyNSwgaGVpZ2h0LTI1KTsgLy8gWGYsWWYKCWNvbnRleHQubGluZVdpZHRoID0gMC4yNTsKCWNvbnRleHQubGluZUNhcCA9ICdyb3VuZCc7Cgljb250ZXh0LnN0cm9rZVN0eWxlID0gJyMzYjNiM2InOwoJY29udGV4dC5zdHJva2UoKTsKCWkgPSBpKzMwOwp9CmNvbnRleHQuZm9udCA9ICI5cHggQXJpYWwiOwpjb250ZXh0LmZpbGxUZXh0KCJzZWMiLHdpZHRoLTEyLGhlaWdodC0xMCk7CmNvbnRleHQudHJhbnNsYXRlKDI1LCAtMjUpOwovLyBQcmludCBSZWZsb3cgUHJvZmlsZQp2YXIgcHJldl9zdGF0ID0gdGVtcHNbMF0sCglwcmV2X2xlZnQgPSB0aW1lc1swXTsKZm9yKHN0YXQgaW4gdGVtcHMpIHsKCXRoZV9zdGF0ID0gdGVtcHNbc3RhdF07Cgl0aGVfdGltZSA9IHRpbWVzW3N0YXRdCgljb250ZXh0LmJlZ2luUGF0aCgpOwoJY29udGV4dC5tb3ZlVG8ocHJldl9sZWZ0LCBoZWlnaHQtcHJldl9zdGF0KzIxKTsJIC8vIFhpLFlpCgljb250ZXh0LmxpbmVUbyh0aGVfdGltZSwgaGVpZ2h0LXRoZV9zdGF0KzIxKTsgLy8gWGYsWWYKCWNvbnRleHQubGluZVdpZHRoID0gMjsKCWNvbnRleHQubGluZUNhcCA9ICdyb3VuZCc7Cgljb250ZXh0LnN0cm9rZSgpOwoJcHJldl9zdGF0ID0gdGhlX3N0YXQ7CglwcmV2X2xlZnQgPSB0aGVfdGltZTsKfQoKCnZhciB4ID0gMTsKdmFyIHBsb3RkYXRhID0gWzBdOwp2YXIgcGxvdHRpbW1lciA9IHNldEludGVydmFsKGZ1bmN0aW9uKCkgewoKICAgICB2YXIgeG1saHR0cHBsb3Q9bmV3IFhNTEh0dHBSZXF1ZXN0KCk7CiAgICAgeG1saHR0cHBsb3Qub25yZWFkeXN0YXRlY2hhbmdlPWZ1bmN0aW9uKCl7CiAgICAgICAgIGlmICh4bWxodHRwcGxvdC5yZWFkeVN0YXRlPT00ICYmIHhtbGh0dHBwbG90LnN0YXR1cz09MjAwKXsKICAgICAgICAgICAgIAoJCQkgcGxvdGRhdGEgPSB4bWxodHRwcGxvdC5yZXNwb25zZVRleHQuc3BsaXQoIiwiKTsKCQkJCQkJCQkKCQkJIAlmb3IoOyB4IDwgKHBsb3RkYXRhLmxlbmd0aC8yKTsgeCsrKSB7CgkJCQkKCQkJCQljb250ZXh0LmJlZ2luUGF0aCgpOwoJCQkJCWNvbnRleHQubW92ZVRvKHBsb3RkYXRhW3gqMisxXSxoZWlnaHQtcGxvdGRhdGFbeCoyXSsyMCk7CSAvLyBYaSxZaQoJCQkJCWNvbnRleHQubGluZVRvKHBsb3RkYXRhWyh4LTEpKjIrMV0sIGhlaWdodC1wbG90ZGF0YVsoeC0xKSoyXSsyMCk7IAkvLyBYZixZZgoJCQkJCWNvbnRleHQubGluZVdpZHRoID0gMTsKCQkJCQljb250ZXh0LmxpbmVDYXAgPSAncm91bmQnOwoJCQkJCWNvbnRleHQuc3Ryb2tlU3R5bGUgPSAnI2ZmMDAwMCc7CgkJCQkJY29udGV4dC5zdHJva2UoKTsKCQkJCQkKCQkJfQkvLyBFTkQgRk9SCgkJCSAKCQkJIAogICAgICAgICB9CiAgICAgfSAgCiAgICAgeG1saHR0cHBsb3Qub3BlbigiR0VUIiwiL3JlZmxvd2RhdGEiLHRydWUpOwogICAgIHhtbGh0dHBwbG90LnNlbmQoKTsKCQp9LCA0MTExKTsgLy8gRU5EIFRJTU1FUg==\"></script>";
// WEB BOTTOM PROJECT PAGE DATA //
static const String bottom = "<div style=\"background-color:#f1f1f1;text-align:center;padding:10px;margin-top:7px;font-size:12px;\"> WiFi Reflow Controller - ESP32 - Version 0.0.1a - <a href=\"https://github.com/JRodrigoTech/ESP32-Reflow-Toaster-Oven-Controller\"  target=\"_blank\">GitHub</a></div>";

// WEB END CODE //
static const String webend = "</body></html>";

// SETTINGS - LEFT MENU //
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

// SETTINGS - Wi-Fi //
// Custom URL string call to save Wi-Fi credentials :: /wifi/{SSID}/{PASSWORD}
// and custom form with stored parameters
static const String wifisettings1 = "<script src=\"data:text/javascript;base64,ZnVuY3Rpb24gc2F2ZXdpZmkoKSB7CiAgICB2YXIgc3NpZCA9IGRvY3VtZW50LmdldEVsZW1lbnRCeUlkKCJzc2lkIik7Cgl2YXIgcHdkID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoInB3ZCIpOwkKICAgIHZhciBnb3VybCA9ICJodHRwOi8vIiArIHdpbmRvdy5sb2NhdGlvbi5ob3N0ICsgIi93aWZpLyIgKyBzc2lkLnZhbHVlICsgIi8iICsgcHdkLnZhbHVlOwogICAgd2luZG93LmxvY2F0aW9uID0gZ291cmw7CQp9\"></script>"
                               "<div class=\"main\"><h3>WiFi Configuration</h3><div>SSID:<br><input type=\"text\" id=\"ssid\" value=\"";
static const String wifisettings2 = "\"><br>Password:<br><input type=\"text\" id=\"pwd\" value=\"";
static const String wifisettings3 =  "\"><br><br><input type=\"submit\" value=\"Save\" onClick=\"savewifi()\"></div></div></div>";

// SETTINGS - PROFILE //

// Custom URL string call to save profiles :: /profile/{Profile Num}/{Profile Name}/{Temp1}/{Temp2}/{Temp3}/{Temp4}/{Time1}/{Time2}/{Time3}/{Time4}/
static const String setprojava = "<script src=\"data:text/javascript;base64,ZnVuY3Rpb24gc2F2ZXByb2ZpbGUoKXsKICAgIHZhciBuYW1lID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoIm5hbWUiKTsKCXZhciBwcm9maWxlbnVtID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoInByb2ZpbGVudW0iKTsKCgl2YXIgdGVtcDEgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGVtcDEiKTsJCgl2YXIgdGVtcDIgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGVtcDIiKTsJCgl2YXIgdGVtcDMgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGVtcDMiKTsJCgl2YXIgdGVtcDQgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGVtcDQiKTsJCgoJdmFyIHRpbWUxID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoInRpbWUxIik7CQoJdmFyIHRpbWUyID0gZG9jdW1lbnQuZ2V0RWxlbWVudEJ5SWQoInRpbWUyIik7Cgl2YXIgdGltZTMgPSBkb2N1bWVudC5nZXRFbGVtZW50QnlJZCgidGltZTMiKTsKCXZhciB0aW1lNCA9IGRvY3VtZW50LmdldEVsZW1lbnRCeUlkKCJ0aW1lNCIpOwoKICAgIHZhciBnb3VybCA9ICJodHRwOi8vIiArIHdpbmRvdy5sb2NhdGlvbi5ob3N0ICsgIi9wcm9maWxlLyIgKyBwcm9maWxlbnVtLnZhbHVlICsgIi8iICsgbmFtZS52YWx1ZSArICIvIiArIHRlbXAxLnZhbHVlICsgIi8iICsgdGVtcDIudmFsdWUgKyAiLyIgKyB0ZW1wMy52YWx1ZSArICIvIiArIHRlbXA0LnZhbHVlICsgIi8iICsgdGltZTEudmFsdWUgKyAiLyIgKyB0aW1lMi52YWx1ZSArICIvIiArIHRpbWUzLnZhbHVlICsgIi8iICsgdGltZTQudmFsdWU7CiAgICB3aW5kb3cubG9jYXRpb24gPSBnb3VybDsJCn0=\"></script>";

// Profile Settings Form with EEPROM stored data
String profileset(int profilenum){

    char profnam[32];
    int values[8] = {0,0,0,0, 0,0,0,0};

     switch (profilenum) {
        case 1:
          values[0] = profile_param[0];
          values[1] = profile_param[1];
          values[2] = profile_param[2];
          values[3] = profile_param[3];
          values[4] = profile_param[4];
          values[5] = profile_param[5];
          values[6] = profile_param[6];
          values[7] = profile_param[7];
          strcpy(profnam, profile1);
          break;
        case 2:
          values[0] = profile_param[8];
          values[1] = profile_param[9];
          values[2] = profile_param[10];
          values[3] = profile_param[11];
          values[4] = profile_param[12];
          values[5] = profile_param[13];
          values[6] = profile_param[14];
          values[7] = profile_param[15];
          strcpy(profnam, profile2);
          break;
        case 3:
          values[0] = profile_param[16];
          values[1] = profile_param[17];
          values[2] = profile_param[18];
          values[3] = profile_param[19];
          values[4] = profile_param[20];
          values[5] = profile_param[21];
          values[6] = profile_param[22];
          values[7] = profile_param[23];
          strcpy(profnam, profile3);
          break;
        case 4:
          values[0] = profile_param[24];
          values[1] = profile_param[25];
          values[2] = profile_param[26];
          values[3] = profile_param[27];
          values[4] = profile_param[28];
          values[5] = profile_param[29];
          values[6] = profile_param[30];
          values[7] = profile_param[31];
          strcpy(profnam, profile4);
          break;
    } 

    String printhtml = "<div class=\"main\"><h3>Profile " +String(profilenum)+ " Configuration</h3>"
                       "<div>Profile Name <input type=\"text\" id=\"name\" value=\"" +String(profnam)+ "\" maxlength=\"32\"><br>"
                       "<input type=\"hidden\" id=\"profilenum\" value=\"" +String(profilenum)+ "\">"
                       "Temperatures:<br>"

                       "<input type=\"text\" id=\"temp1\" value=\"" +String(values[0])+ "\">"
                       "<input type=\"text\" id=\"temp2\" value=\"" +String(values[1])+ "\">"
                       "<input type=\"text\" id=\"temp3\" value=\"" +String(values[2])+ "\">"
                       "<input type=\"text\" id=\"temp4\" value=\"" +String(values[3])+ "\">"

                       "<br>Time:<br>"

                       "<input type=\"text\" id=\"time1\" value=\"" +String(values[4])+ "\">"
                       "<input type=\"text\" id=\"time2\" value=\"" +String(values[5])+ "\">"
                       "<input type=\"text\" id=\"time3\" value=\"" +String(values[6])+ "\">"
                       "<input type=\"text\" id=\"time4\" value=\"" +String(values[7])+ "\">"


                       "<br><br><input type=\"submit\" value=\"Save\" onClick=\"saveprofile()\"";
                       
              if(REFLOW_STATUS == true){ printhtml += " disabled"; }
                       
              printhtml += "></div></div></div>";

    return printhtml;
}

// Javascript on reboot :: Auto 5 seconds redirect homepage "/"
static const String jsreboot = "<script src=\"data:text/javascript;base64,cmVkaXJlY3RUaW1lT3V0ID0gIjUwMDAiOwpwYXRoID0gIi8iOwpzZXRUaW1lb3V0KCJsb2NhdGlvbi5ocmVmID0gcGF0aDsiLHJlZGlyZWN0VGltZU91dCk7\"></script>";

String profiledata(int profilenum){
    int ofs = 8*(profilenum-1);
    
    String printjava = "<script>var temps = [25,"+String(profile_param[0+ofs])+","+String(profile_param[1+ofs])+","+String(profile_param[2+ofs])+","+String(profile_param[3+ofs])+"];"
                       "var times = [0,"+String(profile_param[4+ofs])+","+String(profile_param[5+ofs])+","+String(profile_param[6+ofs])+","+String(profile_param[7+ofs])+"];</script>";
    
    return printjava;
}

// PAGE : reflowdata //
String profileplotprint(){

          String printjava = "";
       
          for(int i = 0; i < plotleg; i++){
            if(i != 0){
              printjava += ",";
            }
            printjava += String(plotdata[2*i])+","+String(plotdata[2*i+1]);
          }

          //printjava += "];";
    
    return printjava;
}
