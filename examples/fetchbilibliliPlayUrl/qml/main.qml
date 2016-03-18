import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtMultimedia 5.5

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("BililBili Player")
    menuBar: MenuBar {
        Menu {
            title: "AV"
            MenuItem {
                text: "Input AV"
                onTriggered: {
                    inputDialog.open();
                }
            }
        }
    }

    property string av: ""

    Dialog {
        id: inputDialog
        title: "Blue sky dialog"

        contentItem: Rectangle {
            color: "lightskyblue"
            implicitWidth: 400
            implicitHeight: 100
            TextField {
                anchors.centerIn: parent
                onAccepted: {
                    av = text;
                    fecth.getBilibiliUrl(text, function(res){
                        console.log("urls count:", res.length);
                        for(var iter in res) {
                            video.playUrls.push(res[iter]);
                            console.log("url:", res[iter]);
                        }
                        video.source = res[0];
                        video.play();
                        // DirectShowPlayerService::doSetUrlSource: Unresolved error code 800c0005
                    });
                }
            }
        }
    }



    BiliBiliFecthPlayUrl {
        id: fecth
    }

    Video {
        id: video

        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            onClicked: {
                video.play()
            }
        }

        onErrorChanged: {
            if(video.error === MediaPlayer.ResourceError) {
                ++playUrlIndex;
                if(playUrlIndex < playUrls.length) {
                    video.source = playUrls[playUrlIndex];
                    video.play();
                } else {
                    console.log("Can't Play Video")
                    page.title = "Can't Play Video";
                }
            }
        }

        readonly property var playUrls:[]
        property int playUrlIndex: 0

        focus: true
        Keys.onSpacePressed: video.playbackState == MediaPlayer.PlayingState ? video.pause() : video.play()
        Keys.onLeftPressed: video.seek(video.position - 5000)
        Keys.onRightPressed: video.seek(video.position + 5000)
    }






}

