# NetworkRequest

封装如下类到 QML。

```
QNetworkRequest -> QmlNetworkRequest -> NetworkRequest
```

## NetworkRequest 的属性如下：

`QUrl url`

`QmlIODevice* ioDevice`

## NetworkRequest 的方法如下：

`void NetworkRequest::clear();`

重置 NetworkRequest 的设置，包括 `url` ，请求头，会触发 `requestChanged` 和 `urlChanged` 两个信号。

---

`void NetworkRequest::setHeader(NetworkRequest::KnownHeaders header, const QVariant & value);`

设置请求头。

---

`bool NetworkRequest::hasRawHeader(const QByteArray & headerName) const;`

查询是否有指定的请求头。

---

`QList<QByteArray> NetworkRequest::rawHeaderList() const;`

返回已经设置的请求头列表。

---

`QByteArray NetworkRequest::rawHeader(const QByteArray & headerName) const;`

返回指定的请求头，如果未设置，返回空串。

## NetworkRequest 的信号如下：

`ioDeviceChanged();`

当设置的 IODevice 改变时会触发该信号。

---

`requestChanged();`

在 `C++` 代码中设置了 request 或者使用 `clear` 函数，就会触发。

---

`urlChanged(const QUrl& url);`

重置 url 或者使用 `clear` 函数，就会触发。