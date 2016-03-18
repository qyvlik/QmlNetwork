import QtQuick 2.0
import Network 1.0

QObject {

    //! [url](https://github.com/Vespa314/bilibili-api/blob/master/GetVideoUrl/biliDownLoad.py)

    /* [Example]
    Component.onCompleted: {
        manager.getBilibiliUrl("http://www.bilibili.com/video/av" + avId, function(res){

            console.log("urls count:", res.length);
            for(var iter in res) {
                video.playUrls.push(res[iter]);
            }
            video.source = res[0];
            video.play();
            // DirectShowPlayerService::doSetUrlSource: Unresolved error code 800c0005
        });
    }
    */

    function getBilibiliUrl(avId, callable) {
        manager.getBilibiliUrl("http://www.bilibili.com/video/av" + avId, callable);
    }

    NetworkRequest { id: request }
    NetworkResponse { id: response }
    NetworkAccessManager {
        id: manager

        readonly property string user_agent: 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.99 Safari/537.36'
        readonly property string appkey: "876fe0ebd0e67a0f"
        readonly property string appsec: "f487b808dc82abb7464a00935d4bb247"

        // function callable();
        function urlFetch(url, callable) {
            request.url = url;
            request.setHeader("User-Agent", user_agent);
            //request.setHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");

            response.finished.connect(function(){
                response.finished.disconnect(arguments.callee);
                callable(response.responseContent);
            });
            manager.get(request, response);
        }

        function getSign(params,appkey,AppSecret) {
            params['appkey'] = appkey;

            var data = "";

            var s_keys = [];
            for (var i in params) {
                s_keys.push(i);
            }
            s_keys.sort();

            for(var para in params) {
                if(data != "") {
                    data += "&";
                }
                data += (para + "=" + params[para]);
            }

            if(typeof AppSecret == "undefined") {
                return data;
            }

            return data+'&sign='+Qt.md5(data+AppSecret);
        }


        // callback(urls);
        function getBilibiliUrl(url, callback) {

            callback = callback || function(urls) {
                for(var i in urls) {
                    console.log(urls[i]);
                }
            }

            // 如果在海外
            // 但是我现在在墙内啊。。。。
            var overseas = false;

            var url_get_media = "";
            if(!overseas) {
                url_get_media = 'http://interface.bilibili.com/playurl?';
            } else {
                url_get_media = 'http://interface.bilibili.com/v_cdn_play?';
            }
            var regex = new RegExp('http:/*[^/]+/video/av(\\d+)(/|/index.html|/index_(\\d+).html)?(\\?|#|$)');
            var regex_match = url.match(regex);;

            var aid = regex_match[1];
            var pid = regex_match[3] || '1';

            //            console.log("AV ID:", aid);
            //            console.log("P ID:", pid);


            // 必须要有顺序
            var cid_args = {
                'appkey': appkey ,
                'id': aid,
                'page': pid,
                'type': 'json'
            };
            var sign_0 = getSign(cid_args, appkey, appsec);

            //            console.log(sign_0);

            urlFetch('http://api.bilibili.com/view?'+sign_0, function(resp_cid){

                resp_cid = JSON.parse(resp_cid);
                var cid = resp_cid['cid'];

                var media_args = {
                    'appkey': appkey,
                    'cid': cid,
                    'otype': 'json',
                    'quality': 4,
                    'type': 'mp4',
                };
                var sign_1 = getSign(media_args,appkey,appsec)

                //                console.log(sign_1);

                urlFetch(url_get_media+sign_1, function(resp_media){
                    console.log(resp_media);
                    try {
                        resp_media = JSON.parse(resp_media);
                    } catch(e) {
                        // 一般是返回了网页
                        console.log(e);
                        throw e;
                    }

                    var res = [];
                    var durls = resp_media['durl'];

                    for(var media_url in durls) {
                        res.push(durls[media_url]['url']);
                        var backup_urls = durls[media_url]['backup_url']
                        for(var i in backup_urls) {
                            res.push(backup_urls[i]);
                        }
                    }
                    callback(res);
                });
            });
        }
    }
}

