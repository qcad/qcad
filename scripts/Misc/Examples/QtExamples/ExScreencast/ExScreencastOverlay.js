function KeyWidget(parentWidget) {
    QWidget.call(this, parentWidget);

    this.color = new QColor(128, 128, 128);
    this.effect = new QGraphicsOpacityEffect(this);
    this.effect.setOpacity(0);
    this.setGraphicsEffect(this.effect);
    this.move(0,0);
    this.resize(100,100);
};

KeyWidget.prototype = new QWidget();

KeyWidget.prototype.start = function(key) {
    this.key = key;
    qDebug("start: key: ", this.key);

    this.show();
    var a = new QPropertyAnimation(this.effect, "opacity");
    a.duration = 1000;
    a.startValue = 0.0;
    a.endValue = 1.0;
    a.start();

    var t = new QTimer(this);
    t.singleShot = true;
    t.timeout.connect(this, "stop");
    t.start(2000);
};

KeyWidget.prototype.stop = function(key) {
    var a = new QPropertyAnimation(this.effect, "opacity");
    a.duration = 1000;
    a.startValue = 1.0;
    a.endValue = 0.0;
    a.start();
};

KeyWidget.prototype.paintEvent = function(evt) {
    qDebug("paintEvent: key: ", this.key);
    var p = new QPainter();
    p.begin(this);

    p.fillRect(0, 0, this.width, this.height, this.color);

    p.setPen(new QPen(new QColor("black")));
    p.setFont(new QFont("Arial", 32));
    //var opt = new QTextOption(Qt.AlignCenter);
    //p.drawText(new QRectF(0,0,this.width,this.height), this.key, opt);
    p.drawText(0,50, this.key);

    p.end();
};



function MouseWidget(parentWidget) {
    QWidget.call(this, parentWidget);

    this.color = new QColor(128, 128, 128);
    this.effect = new QGraphicsOpacityEffect(this);
    this.effect.setOpacity(0);
    this.setGraphicsEffect(this.effect);
    this.move(0,0);
    this.resize(32,32);
    this.timer = undefined;
    this.stoped = false;
};

MouseWidget.prototype = new QWidget();

MouseWidget.prototype.start = function(widget, e) {
    this.stoped = false;
    this.type = e.type().toString();
    if (e.button()!==Qt.NoButton) {
        this.button = e.button();
    }
    this.buttons = e.buttons();

    var appWin = RMainWindowQt.getMainWindow();
    var pos = widget.mapTo(appWin, e.pos());
    this.move(pos.x()+10, pos.y()+5);

    this.effect.opacity = 1.0;
    this.show();

    if (!isNull(this.timer)) {
        this.timer.stop();
    }

    if (this.type==="MouseButtonRelease") {
        this.timer = new QTimer(this);
        this.timer.singleShot = true;
        this.timer.timeout.connect(this, "stop");
        this.timer.start(1000);
    }
};

MouseWidget.prototype.stop = function(key) {
    if (this.stoped===true) {
        return;
    }

    this.stoped = true;
    var e = new QPropertyAnimation(this.effect, "opacity");
    e.duration = 1000;
    e.startValue = 1.0;
    e.endValue = 0.0;
    e.start();
    this.timer = undefined;
    this.button = undefined;
};

MouseWidget.prototype.paintEvent = function(evt) {
    var p = new QPainter();
    p.begin(this);

    qDebug("button: ", this.button);

//    if (!isNull(this.event.button())) {
//        qDebug("button: ", this.event.button().valueOf());
//    }

    var f = undefined;
    switch (this.button) {
        case Qt.LeftButton:
            f = "mouse_l.svg";
            break;
        case Qt.MidButton:
            f = "mouse_m.svg";
            break;
        case Qt.RightButton:
            f = "mouse_r.svg";
            break;
    }

    if (!isNull(f)/* && this.buttons()!==Qt.NoButton*/) {
        var r = new QSvgRenderer(this);
        r.load(ExScreencastOverlay.includeBasePath + "/" + f);
        r.render(p);
    }

    p.end();
};



function ExScreencastOverlay(parentWidget) {
    QWidget.call(this, parentWidget);

    this.setAttribute(Qt.WA_MouseTracking);
    this.setAttribute(Qt.WA_TransparentForMouseEvents);
    this.setWindowFlags(Qt.WindowStaysOnTopHint);
    // this.setAttribute(Qt.WA_NoMousePropagation);
    this.focusPolicy = Qt.NoFocus;
    this.color = new QColor(128, 128, 255);
    this.opacity = 0.2;

    this.keyLabel = new KeyWidget(this);
    this.mouseLabel = new MouseWidget(this);
    //this.keyLabel.resize(100,100);
    //this.keyLabel.move(0,0);
    //this.keyLabel.hide();

    //this.timer = new QTimer(this);
    //timer.timeout.connect(this, "update");
}

ExScreencastOverlay.prototype = new QWidget();
ExScreencastOverlay.includeBasePath = includeBasePath;

ExScreencastOverlay.prototype.setOpacity = function(opacity) {
    this.opacity = opacity;
};

ExScreencastOverlay.prototype.setColor = function(color) {
    this.color = color;
};

ExScreencastOverlay.prototype.paintEvent = function(evt) {
    var p = new QPainter();
    p.begin(this);

    p.setOpacity(this.opacity);
    p.fillRect(0, 0, this.width, this.height, this.color);

    p.end();
};

ExScreencastOverlay.prototype.eventFilter = function(watched, e) {
    e = e.cast();
    var type = e.type().toString();

    switch (type) {
        case "KeyRelease":
//            qDebug("key: ", e.key());
//            qDebug("watched: ", watched.objectName);
//            qDebug("");
            //this.keyLabel.text = String.fromCharCode(e.key());
            //this.keyLabel.show();
            //var a = new QPropertyAnimation(this.keyLabel, "anim", this.keyLabel);
            //a.setDuration(1000);
            //timer.start(30);
            //this.keyLabel.start(String.fromCharCode(e.key()));

            //this.key = e.key();
            //this.update();
            qDebug("type: ", type);
            break;

        case "MouseButtonPress":
        case "MouseButtonRelease":
        case "MouseMove":
            qDebug("e.buttons(): ", e.buttons());
            //this.raise();
            if (e.buttons().valueOf()===Qt.NoButton.valueOf()) {
                this.mouseLabel.stop();
            }
            else {
                this.mouseLabel.start(watched, e);
            }

//            qDebug("button: ", e.button());
//            qDebug("buttons: ", e.buttons());
            qDebug("type: ", type);
//            qDebug("pos: ", e.pos());
//            qDebug("watched: ", watched.objectName);
//            qDebug("");
            break;

        default:
            break;
    }

//    if (type.contains("Key") || type.contains("Mouse")) {
//        qDebug("event: ", e.type());
//    }
    return false;
};

//ExScreencastOverlay.prototype.mouseMoveEvent = function(evt) {
//    qDebug("mouse move");
//};
