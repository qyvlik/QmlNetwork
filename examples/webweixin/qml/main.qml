
import QtQuick 2.0
import QtQuick.Layouts 1.1

import Sparrow 1.0
import Sparrow.PopupLayer 1.0

import Network 1.0

PageStackWindow {

    id: mainWindow

    initialPage: Page {
        id: mainView
        pageStackWindow: mainWindow

        topBar: TopBar {
            id: topbar
            RowLayout {
                anchors.fill: parent

                SampleButton {
                    text: qsTr("关于")
                    Layout.fillHeight: true
                    Layout.margins: topbar.height * 0.1
                    Layout.alignment: Qt.AlignLeft
                    onClicked: {
                        about.switchState();
                        console.log(o.supperCall())
                    }
                }
            }
        }


        Image {
            id:  showqrcode
            anchors.centerIn: parent
            width: parent.width * 0.8
            height: this.width
        }

        bottomBar: BottomBar {
            id: bottombar
            height: topbar.height
            RowLayout {
                anchors.fill: parent
                SampleButton {
                    text: qsTr("开始")
                    Layout.fillHeight: true
                    // Layout.margins: bottombar.height * 0.1
                    Layout.alignment: Qt.AlignLeft
                    onClicked: {
                        webWeiXin.start();
                    }
                }
            }
        }

        PopupLayer {
            id: about
            parent: mainView
            SampleButton {
                text: qsTr("大魔王")
                anchors.centerIn: parent
            }
        }

        PopupLayer {
            id: alert
            parent: mainView
            SampleButton {
                text: qsTr("拿到微信cookie了")
                anchors.centerIn: parent
            }
        }
    }

    WebWeiXin {
        id: webWeiXin
        Ticker { id: tick }
        NetworkAccessManager { id: networkmanager }
        NetworkRequest { id: request }
        NetworkResponse { id: response }
        Buffer { id: buffer }

        property string cookie: ""

        function start() {
            webWeiXin.getWebWeiXinS1essionsID(function(uuid){
                webWeiXin.whenGetUUID(uuid, function() {
                    tick.ticking(function(){
                        // 这里开始需要拿 cookie 了
                        webWeiXin.polling(uuid, function(redirect_uri){
                            tick.stop();
                            console.log(redirect_uri);
                            webWeiXin.getCookie(redirect_uri,
                                                whenGetWeiXinCookie);
                        });
                    });
                });
            });
        }

        function whenGetUUID(uuid, callback) {
            callback = callback || function() { }
            var url = "https://login.weixin.qq.com/qrcode/"+uuid+"?t=webwx";
            console.log("get qrcode image")
            showqrcode.source = url;
            callback();
        }

        // @function(weixincookie)
        function getCookie(url,callback) {
            request.clear();
            request.url = url;

            connectSignalOnce(response.finished,function() {
                cookie = response.getResponseHeader("Set-Cookie");
                callback(cookie);
            });

            networkmanager.get(request, response);
        }

        function whenGetWeiXinCookie(weixincookie) {
            console.log("Set-Cookie:", weixincookie);
            alert.open();
            //getWeiXinFriendList(weixincookie);
            getWeiXinWxsidAndWxuid(weixincookie, initWebWeiXinInfo);
        }

        // callback(wxsid, wxuid)
        function getWeiXinWxsidAndWxuid(weixincookie, callback) {
            // wxuin=579618255; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
            // wxsid=gJe6gbccB+Sm+cWK; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
            var wxuin = "";
            var wxsid = "";
            var wxuinIndex = -1;
            var wxsidIndex = -1;
            var cookieList = weixincookie.split("\n");
            var singleCookie;
            for(var iter in cookieList) {
                singleCookie = cookieList[iter].split("; ");
                //! singleCookie[i]
                //! wxsid=gJe6gbccB+Sm+cWK
                //! Domain=wx2.qq.com
                for(var i in singleCookie) {
                    wxuinIndex = singleCookie[i].search("wxuin=");
                    if(wxuinIndex != -1) {
                        wxuin = singleCookie[i].substring(wxuinIndex+"wxuin=".length,
                                                          singleCookie[i].length);
                        continue;
                    }

                    wxsidIndex = singleCookie[i].search("wxsid=");
                    if(wxsidIndex != -1) {
                        wxsid = singleCookie[i].substring(wxsidIndex+"wxsid=".length,
                                                          singleCookie[i].length);
                    }
                }
            }
            callback(wxuin, wxsid);
        }

        function initWebWeiXinInfo(wxuin, wxsid) {
            var url = "https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxinit?r=" + Date.now();
            var data = {
                "BaseRequest": {
                    "Uid": wxuin,
                    "Sid": wxsid,
                    "Skey": "",
                    "DeviceID": "e" + Date.now()
                }
            };

//            console.log(JSON.stringify(data))

            if(buffer.isOpen()) {
                buffer.close();
            }
            buffer.data = JSON.stringify(data);
            if(!buffer.open(IODevice.ReadOnly)) {
                console.log(buffer.errorString());
            }

            request.clear();
            request.url = url;
            request.setHeader("Cookie", cookie);
            request.setHeader("Content-Type", "application/json")
            request.ioDevice = buffer;

            connectSignalOnce(response.finished,function() {
                console.log("data:", buffer.data)
                console.log("init wei xin");
                /*
                    {'Ret': 0,'ErrMsg': ''} 成功
                    {'Ret': -14,'ErrMsg': ''} ticket 错误
                    {'Ret': 1,'ErrMsg': ''} 传入参数 错误
                    {'Ret': 1100'ErrMsg': ''}未登录提示
                    {'Ret': 1101,'ErrMsg': ''}（可能：1未检测到登陆？）
                    {'Ret': 1102,'ErrMsg': ''}（可能：cookie值无效？）
                */
                var headers = response.getAllResponseHeaders();
                for(var iter in headers) {
                    console.log(headers[iter]);
                }
                console.log(response.responseContent);
            });

            networkmanager.post(request, response);
        }

        function getWeiXinFriendList(weixincookie) {
            // https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgetcontact?r=1377482079876
            request.url = "https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgetcontact?r="
                    + Date.now();
            request.clear();
            request.setHeader("Set-Cookie", weixincookie);
            request.ioDevice = buffer;
            buffer.data = "{}";

            connectSignalOnce(response.finished,function() {
                console.log(response.responseContent);
            });

            console.log(networkmanager.post(request, response));
        }
    }

    function connectSignalOnce(signalObject, callback) {
        function internal() {
            signalObject.disconnect(internal);
            // console.debug("emit signal and trigged internal funciton and callback");
            callback();
        }
        signalObject.connect(internal);
        return internal;
    }


    Component.onCompleted: {
//        var o = (function(id){
//          function MyObject(id) { this.__id = id; };
//          MyObject.prototype = {
//              supperCall: function() {
//                  return FactoryObject.supperCall(this.__id);
//              }
//          }
//          return new MyObject(id);
//        })(12);
//        console.log(o.supperCall());

//        console.log(FactoryObject);


        var cookies = "wxuin=579618255; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
        wxsid=gJe6gbccB+Sm+cWK; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
        wxloadtime=1453262967; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
        mm_lang=zh_CN; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
        webwx_data_ticket=AQfpXWpOo7FFdNHDjmM/OydG; Domain=.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT"

        // webWeiXin.getWeiXinWxsidAndWxuid(cookies, webWeiXin.initWebWeiXinInfo);
    }
}


//    function echo(url){
//        var xhr = new XMLHttpRequest();
//        xhr.onreadystatechange = function() {
//            if(xhr.readyState == xhr.HEADERS_RECEIVED) {
//                console.log("----------HEADERS_RECEIVED-------------")
//                console.log(xhr.getResponseHeader("Set-Cookie"));

//                console.log(xhr.getAllResponseHeaders());
//            } else if(xhr.readyState == xhr.DONE) {
//                console.log("----------DONE-------------")
//                console.log(xhr.responseText);
//            }
//        }
//        xhr.open("GET", url);
//        xhr.setRequestHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
//        xhr.setRequestHeader("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64; rv:43.0) Gecko/20100101 Firefox/43.0")
//        xhr.send()
//    }

//var cookies = "wxuin=579618255; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
//wxsid=gJe6gbccB+Sm+cWK; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
//wxloadtime=1453262967; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
//mm_lang=zh_CN; Domain=wx2.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
//webwx_data_ticket=AQfpXWpOo7FFdNHDjmM/OydG; Domain=.qq.com; Path=/; Expires=Wed, 20-Jan-2016 16:09:27 GMT
//webwxuvid=d7c70972b04393edb2acbbc731e822576718dccc65e7a5fe129502e7405be3bbdddf7c27462d5b9759fc1ea79c3e6d54; Domain=wx2.qq.com; Path=/; Expires=Sat, 17-Jan-2026 04:09:27 GMT"
//webWeiXin.getWeiXinWxsidAndWxuid(cookies, function(wxsid, wxuid){
//    console.log("wxsid: ", wxsid, " wxuid: ", wxuid)
//});
