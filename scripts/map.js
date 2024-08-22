// Public domain
function MapCompat(compareFunction) {
    this.keyArray = [];
    this.valArray = [];
    this.compareFunction = compareFunction;
}

MapCompat.prototype = new Object();

MapCompat.prototype.put = function(key, val) {
    var elementIndex = this.findKey(key);
    if (elementIndex === (-1)) {
        this.keyArray.push(key);
        this.valArray.push(val);
    } else {
        this.valArray[elementIndex] = val;
    }
};

MapCompat.prototype.get = function(key, def) {
    var result = def;
    var elementIndex = this.findKey(key);
    if (elementIndex !== (-1)) {
        result = this.valArray[elementIndex];
    }
    return result;
};

MapCompat.prototype.remove = function(key) {
    var result = null;
    var elementIndex = this.findKey(key);
    if (elementIndex !== (-1)) {
        this.keyArray = this.keyArray.removeAt(elementIndex);
        this.valArray = this.valArray.removeAt(elementIndex);
    }
    return;
};

MapCompat.prototype.size = function() {
    return (this.keyArray.length);
};

MapCompat.prototype.clear = function() {
    for ( var i = 0; i < this.keyArray.length; i++) {
        this.keyArray.pop();
        this.valArray.pop();
    }
};

MapCompat.prototype.getKeys = function() {
    return (this.keyArray);
};

MapCompat.prototype.getValues = function() {
    return (this.valArray);
};

MapCompat.prototype.toString = function() {
    var result = "";
    for ( var i = 0; i < this.keyArray.length; i++) {
        result += "Key: " + this.keyArray[i] + "\tValue: " + this.valArray[i]
                + "\n";
    }
    return result;
};

MapCompat.prototype.hasKey = function(key) {
    return this.findKey(key)!==-1;
};

MapCompat.prototype.findKey = function(key) {
    var result = (-1);
    if (isNull(this.keyArray)) {
        console.trace();
    }

    for ( var i = 0; i < this.keyArray.length; i++) {
        if (typeof(this.compareFunction)!=="undefined") {
            if (this.compareFunction(this.keyArray[i], key)) {
                result = i;
                break;
            }
        }
        else {
            if (this.keyArray[i] == key) {
                result = i;
                break;
            }
        }
    }
    return result;
};

