// Public domain
function Map(compareFunction) {
    this.keyArray = [];
    this.valArray = [];
    this.compareFunction = compareFunction;
}

Map.prototype.put = function(key, val) {
    var elementIndex = this.findKey(key);
    if (elementIndex === (-1)) {
        this.keyArray.push(key);
        this.valArray.push(val);
    } else {
        this.valArray[elementIndex] = val;
    }
};

Map.prototype.get = function(key, def) {
    var result = def;
    var elementIndex = this.findKey(key);
    if (elementIndex !== (-1)) {
        result = this.valArray[elementIndex];
    }
    return result;
};

Map.prototype.remove = function(key) {
    var result = null;
    var elementIndex = this.findKey(key);
    if (elementIndex !== (-1)) {
        this.keyArray = this.keyArray.removeAt(elementIndex);
        this.valArray = this.valArray.removeAt(elementIndex);
    }
    return;
};

Map.prototype.size = function() {
    return (this.keyArray.length);
};

Map.prototype.clear = function() {
    for ( var i = 0; i < this.keyArray.length; i++) {
        this.keyArray.pop();
        this.valArray.pop();
    }
};

Map.prototype.getKeys = function() {
    return (this.keyArray);
};

Map.prototype.getValues = function() {
    return (this.valArray);
};

Map.prototype.toString = function() {
    var result = "";
    for ( var i = 0; i < this.keyArray.length; i++) {
        result += "Key: " + this.keyArray[i] + "\tValue: " + this.valArray[i]
                + "\n";
    }
    return result;
};

Map.prototype.hasKey = function(key) {
    return this.findKey(key)!==-1;
};

Map.prototype.findKey = function(key) {
    var result = (-1);
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

Array.prototype.removeAt = function(index) {
    var part1 = this.slice(0, index);
    var part2 = this.slice(index + 1);
    return (part1.concat(part2));
};
