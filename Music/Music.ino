/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5StickC-Plus sample source code
*                          配套  M5StickC-Plus 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/m5stickc_plus
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/m5stickc_plus
*
* Describe: WIFI AP.  wifi热点
* Date: 2021/9/18
*******************************************************************************
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on
it. 创建一个WiFi接入点，并在其上提供一个网络服务器 And can send requests to
M5StickCPlus through the web page 并可通过网页向 M5StickCPlus 发送请求
*/

#include <M5StickCPlus.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 10

const char* SSID = "PC_M5Stick";
WiFiServer server(80);

void setup() {
    M5.begin();
    M5.lcd.setRotation(3);
    M5.lcd.println("WIFI ACCESS POINT");  // Screen print string. 屏幕打印字符串
    M5.lcd.printf("Please connect:%s \nThen access to:", SSID);
    WiFi.softAP(
        SSID);  // You can remove the password parameter if you want the AP
                    // to be open.  如果你想建立开放式热点,可以删除密码
    IPAddress myIP = WiFi.softAPIP();  // Get the softAP interface IP address.
                                       // 获取AP接口IP地址
    M5.lcd.println(myIP);
    server.begin();  // Start the established Internet of Things network server.
                     // 启动建立的物联网网络服务器
    // PC Start
    // Set the LED pin as an output
    pinMode(LED_BUILTIN, OUTPUT);
    // Turn the led off
    digitalWrite(LED_BUILTIN, HIGH);
    // PC Stop
}

void loop() {
    WiFiClient client =
        server
            .available();  // listen for incoming clients.
                           // 检查有没有设备通过网络向M5Stack网络服务器发送请求

    if (client) {  // if you get a client.  如果收到请求
        M5.lcd.print("New Client:");
        String currentLine =
            "";  // make a String to hold incoming data from the client.
                 // 创建一个String来保存来自客户端的传入数据
        while (client.connected()) {  // loop while the client's
                                      // connected,continuously receiving data.
                                      // 在客户端连接时进行循环,不断接收数据
            if (client.available()) {  // if there's bytes to read from the
                                       // client.  如果有数据可读取
                char c =
                    client.read();  // store the read a byte.  存储读取到的数据
                Serial.write(c);
                if (c == '\n') {  // if the byte is a newline character.
                                  // 如果读取到的字节为换行符
                    // \n is the end of the client'S HTTP request, indicating
                    // that the client has sent a new request \n
                    // 是客户端HTTP请求的结尾，说明客户端发来新请求:
                    if (currentLine.length() == 0) {
                        // Here are the instructions to create a page.
                        // 下面是创建一个页面的指令

                        // HTTP headers always start with a response code (e.g.
                        // HTTP/1.1 200 OK) HTTP的开头总是以响应代码开始(例如
                        // HTTP/1.1 200 OK) and a content-type so the client
                        // knows what's coming, then a blank line:
                        //然后是content-type，这样客户端就知道接下来会发生什么，然后是空行:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        // the content of the HTTP response follows the header:
                        // HTTP页面显示的内容跟在开头后面:
                        // /High and /Low are the data received when clicking
                        // the corresponding connection, which can be replaced.
                        //  /High和/Low 为点击对应连接时接收到的数据,可更换
                        client.print(
                            "<button onclick=\"window.location.href='/Play'\">Turn LED ON</button>");

                        // The HTTP response ends with another blank line:
                        // HTTP响应以空行结束:
                        client.println();
                        // break out of the while loop:退出循环
                        break;
                    } else {  // if you got a newline, then clear
                              // currentLine:如果得到新的一行,那么清除当前行
                        currentLine = "";
                    }
                } else if (c !=
                           '\r') {  // if you got anything else but a carriage
                                    // return character.
                                    // 如果你得到了除了回车符以外的其他字符，
                    currentLine += c;  // add it to the end of the currentLine.
                                       // 将它添加到currentLine的末尾
                }

                // Check to see if the client request was "GET /H" or "GET /L":
                // 检查客户端请求是“GET /High”还是“GET /Low”:
                if (currentLine.endsWith("GET /Play")) {
                    M5.Lcd.print("Playing Music...\n");
                    // PC Change Bellow
                    // TODO: Play Music Function
                }
            }
        }
        client.stop();  // close the connection.  关闭连接
    }
}

void playMusic(){
    // Notes:
    // EE E CE G g

    // Key: 
    //   c     262 Hz
    //   d     294 Hz
    //   e     330 Hz
    //   f     349 Hz
    //   g     392 Hz
    //   a     440 Hz
    //   b     494 Hz
    //   C     523 Hz
}