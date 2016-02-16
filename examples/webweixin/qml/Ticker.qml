import QtQuick 2.0

Timer {
    id: tick
    interval: 1000
    repeat: true
    running: false
    property var callable
    onTriggered: {
        try {
            console.debug("ticking...");
            callable();
        } catch(e) {
            console.log(e);
        }
    }
    function ticking(call) {
        tick.callable = call;
        tick.start();
    }
}
