import QtQuick 2.0
import QtQml 2.2
import Network 1.0

QObject {
    id: network

    NetworkAccessManager { id: manager }

    NetworkRequest {
        id: request
        url: "http://m.jd.com"
        ioDevice: fileIO
    }

    NetworkResponse {
        id: post_response
        onDownloadProgress: {
            console.log("bytesReceived: ", bytesReceived, " bytesTotal: ", bytesTotal)
        }
    }

    FileIO {
        id: fileWriter
        fileName: "e:/Test/getpostdata.txt"
    }

    FileIO {
        id: fileIO
        fileName: "e:/Test/file.txt"
    }
    property bool isFinished: true

    /*
        enum KnownHeaders {
            ContentTypeHeader = QNetworkRequest::ContentTypeHeader,
            ContentLengthHeader = QNetworkRequest::ContentLengthHeader,
            LocationHeader = QNetworkRequest::LocationHeader,
            LastModifiedHeader = QNetworkRequest::LastModifiedHeader,
            CookieHeader = QNetworkRequest::CookieHeader,
            SetCookieHeader = QNetworkRequest::SetCookieHeader,
            ContentDispositionHeader = QNetworkRequest::ContentDispositionHeader,  // added for QMultipartMessage
            UserAgentHeader = QNetworkRequest::UserAgentHeader,
            ServerHeader = QNetworkRequest::ServerHeader
        };
    */

    function sendPostData() {
        if(network.isFinished) {
            network.isFinished = false;

            if(!fileIO.open(IODevice.ReadOnly)) {
                console.log("open file fail", fileIO.errorString())
                return ;
            }

            request.setRawHeader("Content-Type", "text/html");

            connectSignalOnce(post_response.finished, function(){
                network.isFinished = true;
                //! 完成后必须关闭
                fileIO.close();

                //console.log(post_response.responseContent);

                network.saveDataToFile(fileWriter,
                                       post_response.responseContent);

                var headers = post_response.getAllResponseHeaders();
                for(var iterz in headers) {
                    console.log(headers[iterz]);
                }
            });

            if(manager.get(request, post_response)) {
                console.log("post success!")
            } else {
                console.log("post faile");
            }
        } else {
            console.log("Please wait for response...")
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

    function saveDataToFile(file, text) {
        if(file.open(FileIO.ReadWrite)) {
            file.write(text);
            file.close();
            return true;
        } else {
            console.log(file.errorString());
            return false;
        }
    }

    Component.onCompleted: {
    }

}

