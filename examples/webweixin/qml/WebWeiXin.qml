import QtQuick 2.0

QObject {
    // callback(sessionsID)
    // err(errorObject{})
    function getWebWeiXinS1essionsID(callback, err) {
        var now = Date.now();
        var url = "https://login.weixin.qq.com/jslogin?appid=wx782c26e4c19acffb"
                +"&redirect_uri=https%3A%2F%2Fwx.qq.com%2Fcgi-bin%2Fmmwebwx-bin%2Fwebwxnewloginpage"
                +"&fun=new&lang=zh_CN"
                +"&_=" + now;

        var xhr = new XMLHttpRequest();

        xhr.onreadystatechange = function() {
            if(xhr.readyState == xhr.DONE){
                var responseText = xhr.responseText;
                // template data
                // window.QRLogin.code = 200; window.QRLogin.uuid = “DeA6idundY9VKn”;
                // .code 为索引
                // " 为索引
                var uuid = responseText.substring(responseText.search('"')+1,
                                                  responseText.lastIndexOf('"'));
                console.log(uuid);

                try {
                    callback(uuid);
                }catch(e) {
                    console.log(e)
                }

            }
        }
        xhr.open("GET", url);
        xhr.send();
    }

    // calback(redirect_uri)
    function polling(uuid, callback) {
        callback = callback || function() { };

        var url = "https://login.weixin.qq.com/cgi-bin/mmwebwx-bin/login?"
                +"uuid=" + uuid
                +"&tip=1&_=" + Date.now();

        var pollxhr = new XMLHttpRequest();
        pollxhr.onreadystatechange = function () {
            if(pollxhr.readyState == pollxhr.DONE) {
                /*
                    如果服务器返回：
                    window.code=201;
                    则说明此时用户在手机端已经完成扫描，但还没有点击确认；
                    如果服务器返回：
                    window.redirect_uri=一个URL地址
                    则说明此时用户已经在手机端完成了授权过程，保存下这个URL地址下一步骤中使用。
                */

                console.log(pollxhr.responseText);

                var responseText = pollxhr.responseText;
                // window.redirect_uri="https://wx2.qq.com/cgi-bin/mmwebwx-bin/webwxnewloginpage?ticket=A7KDrBV-1viQuukTMa--6Xpa@qrticket_0&uuid=Qfy8S3zA2w==&lang=zh_CN&scan=1452594746"
                if(responseText.search("redirect_uri") != -1) {
                    var redirect_uri  =
                            responseText.substring(responseText.search('"')+1,
                                                   responseText.lastIndexOf('"'));
                    try {
                        callback(redirect_uri);
                    } catch(e){

                    }
                }

            }
        }
        pollxhr.open("GET", url);
        pollxhr.send()
    }
}

