import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import Network 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    RowLayout {
        Label {
            id: lable
        }
        Button{
            text: "test get"
            onClicked: {
                getGithunZen();
            }
        }
    }

    function getGithunZen() {
        var url = "https://api.github.com/zen"
        request.url = url;
        // request.setHeader("")
        connectSignalOnce(response.finished, function(){
            lable.text = response.responseContent;
        });
        manager.get(request, response);
    }

    NetworkAccessManager { id: manager }
    NetworkResponse {  id: response  }
    NetworkRequest { id: request }

    function connectSignalOnce(signalObject, callable) {
        function internal() {
            signalObject.disconnect(internal);
            callable();
        }
        signalObject.connect(internal);
    }
}

