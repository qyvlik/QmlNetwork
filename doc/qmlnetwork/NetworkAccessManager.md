# 封装到 QML 中的 Qt 网络模块

封装如下类到 QML。

```
QNetworkAccessManager -> QmlNetworkAccessManager -> NetworkAccessManager
QNetworkRequest -> QmlNetworkRequest -> NetworkRequest
QNetworkReply -> QmlNetworkReply -> NetworkResponse
```

NetworkAccessManager 的方法如下：

`bool NetworkAccessManager::deleteResource(NetworkRequest request, NetworkResponse response);`

传入 request 和 response 进行 `delete` 操作。此函数为异步请求函数，响应操作会阻塞 UI 线程。

---

`bool NetworkAccessManager::post(NetworkRequest request, NetworkResponse response);`

传入 request 和 response 进行 `post` 操作。此函数为异步请求函数，响应操作会阻塞 UI 线程。

```
import Network 1.0
import QtQuick 2.0

Item {

    id: network
    
    property bool isFinished: true
    
    NetworkAccessManager{ id: manager }
    
    NetworkResponse { id: response }
    
    NetworkRequest { id: request; ioDevice: fileIO }
    
    FileIO {
        id: fileIO
        fileName: "e:/Test/file.txt"
    }
    
    /**
     * @method doPost
     * @return {void}
     */
    function doPost() {
        if(network.isFinished) {
            network.isFinished = false;
            request.url = "http://YOUR_WANT_GET_RUI";
            request.setRawHeader("Content-Type", "text/html");

            connectSignalOnce(response.finished, function(){
                network.isFinished = true;
                
                var headers = response.getAllResponseHeaders();
                for(var iter in headers) {
                    console.log(headers[iter]);
                }
            });

            if(manager.post(request, response)) {
                console.log("send get resource request success!")
            } else {
                console.log("send get resource request faile!");
            }
        } else {
            console.log("Please wait for response...")
        }
    }
    
    /**
     * @method connectSignalOnce
     * @param {signal} signalObject 要链接的信号对象
     * @param {function(void)-> void} callback 完成时的回调函数
     * @return {void}
     */
    function connectSignalOnce(signalObject, callback) {
        function internal() {
            signalObject.disconnect(internal);
            // console.debug("emit signal and trigged internal funciton and callback");
            callback();
        }
        signalObject.connect(internal);
    }
}
```

上诉代码是将 request 指定的 IODevice 打开，将数据 post 到指定的 url。

---

`bool NetworkAccessManager::get(NetworkRequest request, NetworkResponse response);`

传入 request 和 response 进行 `get` 操作。此函数为异步请求函数，响应操作会阻塞 UI 线程。

```
import Network 1.0
import QtQuick 2.0

Item {

    id: network
    
    property bool isFinished: true
    
    NetworkAccessManager{ id: manager }
    
    NetworkResponse { id: response }
    
    NetworkRequest { id: request }
    
    /**
     * @method doGet
     * @return {void}
     */
    function doGet() {
        if(network.isFinished) {
            network.isFinished = false;
            request.url = "http://YOUR_WANT_GET_RUI";
            request.setRawHeader("Content-Type", "text/html");

            connectSignalOnce(response.finished, function(){
                network.isFinished = true;
                
                var headers = response.getAllResponseHeaders();
                for(var iter in headers) {
                    console.log(headers[iter]);
                }
                console.log(response.responseContent)
            });

            if(manager.get(request, response)) {
                console.log("send get resource request success!")
            } else {
                console.log("send get resource request faile!");
            }
        } else {
            console.log("Please wait for response...")
        }
    }
    
    /**
     * @method connectSignalOnce
     * @param {signal} signalObject 要链接的信号对象
     * @param {function(void)-> void} callback 完成时的回调函数
     * @return {void}
     */
    function connectSignalOnce(signalObject, callback) {
        function internal() {
            signalObject.disconnect(internal);
            // console.debug("emit signal and trigged internal funciton and callback");
            callback();
        }
        signalObject.connect(internal);
    }
}
```

---

`bool NetworkAccessManager::head(NetworkRequest request, NetworkResponse response);`

传入 request 和 response 进行 `head` 操作。此函数为异步请求函数，响应操作会阻塞 UI 线程。

---

`bool NetworkAccessManager::put(NetworkRequest request, NetworkResponse response);`

传入 request 和 response 进行 `put` 操作。此函数为异步请求函数，响应操作会阻塞 UI 线程。


