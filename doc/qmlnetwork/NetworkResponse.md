# NetworkResponse

封装如下类到 QML。

```
QNetworkReply -> QmlNetworkReply -> NetworkResponse
```

## NetworkResponse 的属性：

`readonly QByteArray responseContent`

只有在 `finished` 时才有内容可以读取。

## NetworkResponse 的方法如下：

`QVariant getResponseHeader(const QByteArray &headerName) const;`

获取指定的响应头。如果响应头中没有指定字段，则返回空。

---

`QJsonArray getAllResponseHeaders() const;`

获取所有的响应头。

```
var headers = post_response.getAllResponseHeaders();
for(var iterz in headers) {
    console.log(headers[iterz]);
}
```

打印如下：

```
qml: Expires:Wed, 20 Jan 2016 10:14:37 GMT
qml: Set-Cookie:JAMCookie=true
USER_FLAG_CHECK=""; Domain=.360buy.com; Expires=Thu, 01-Jan-1970 00:00:10 GMT; Path=/
USER_FLAG_CHECK=""; Domain=.jd.com; Expires=Thu, 01-Jan-1970 00:00:10 GMT; Path=/
abtest=""; Domain=.360buy.com; Expires=Thu, 01-Jan-1970 00:00:10 GMT; Path=/
```

其中，`Set-Cookie` 字段，以换行为一行记录，一行记录内有若干个键值对。

---

`QJsonArray getAllResponseHeaderPairs() const;`

获取所有的响应头。

```
其数据格式如下，可以参照下述格式进行解析。
[
 {
    "header": "Content-Type",
    "value": "text/html"
 },
 {
    "header": "Via",
    "value": "10.67.15.48"
 }
]
```

## NetworkResponse 的信号：

`void finished();`

在进行网络请求后，响应时会触发的信号。

---

`void replyChanged();`

在进行网络请求后，直接触发。

---

`void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);`

在进行网络响应时，是一个过程，会一直更新下载进度。

`bytesReceived` 会进行刷新，而 `bytesTotal` 的值会是 -1，直到非负数才是本次响应的数据量大小。

---

`void encrypted();`

参考 `QNetworkReply::encrypted()`。

---

`void error(QNetworkReply::NetworkError code);`

此次网络请求的响应错误码。

参考 `QNetworkReply::encrypted()`。

---

`void metaDataChanged();`

参考 `QNetworkReply::metaDataChanged()`。

---

`void preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator * authenticator);`

参考 `QNetworkReply::preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator * authenticator)`。

---

`void sslErrors(const QList<QSslError> & errors);`

参考 `QNetworkReply::sslErrors(const QList<QSslError> & errors)`。

---

`void uploadProgress(qint64 bytesSent, qint64 bytesTotal);`

在进行 `post` 或者 `put` 操作时，从客户端发送数据到服务的进度（上传进度）。

参数 `bytesSent` 会一直增大，而 `bytesTotal` 只有在上传完成时才会从 -1 变成非负数。注意如果要获得实际的上传进度，请计算你要上传的数据大小。

---

`void aboutToClose();`

参考 `QNetworkReply::aboutToClose()`。

---

`void bytesWritten(qint64 bytes);`

参考 `QNetworkReply::bytesWritten(qint64 bytes)`。

---

`void readChannelFinished();`

参考 `QNetworkReply::readChannelFinished()`。

---

`void readyRead();`

由于网络响应是个过程，并且并不是将所有的内容缓存到内存才调用，而是一段一段的从服务端发送到客户端。

参考 `QNetworkReply::readyRead()`。
