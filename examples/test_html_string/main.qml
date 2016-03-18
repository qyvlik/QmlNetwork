import QtQuick 2.5
import QtQuick.Controls 1.4
import Network 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    NetworkAccessManager { id: networkmanager }
    NetworkRequest { id: request }
    NetworkResponse { id: response }

    function connectSignalOnce(signalObject, callback) {
        function internal() {
            signalObject.disconnect(internal);
            // console.debug("emit signal and trigged internal funciton and callback");
            callback();
        }
        signalObject.connect(internal);
        return internal;
    }

    function fetchUrl(url) {
        connectSignalOnce(response.finished, function(){
            console.log(response.responseContent)
        });
        request.url = url;
        networkmanager.get(request, response);
    }

    Component.onCompleted: {
        fetchUrl("http://news-at.zhihu.com/");
    }

}

