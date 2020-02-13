/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

/**
 * \return The argument after the first one of the given flags or the given default value.
 *
 * \param args Array of strings (program arguments)
 * \param shortFlag E.g. "-o"
 * \param longFlag E.g. "-output"
 */
function getArgument(args, shortFlag, longFlag, def) {
    // make sure undefined can be returned as default:
    if (def===undefined) {
        var ret = getArguments(args, shortFlag, longFlag);
        if (ret.length===0) {
            return def;
        }
        return RSettings.getArgument(args, shortFlag, longFlag);
    }

    return RSettings.getArgument(args, shortFlag, longFlag, def);
}

/**
 * \return Array of all arguments after the given flags or an empty array.
 *
 * \param args Array of strings (program arguments)
 * \param shortFlag E.g. "-o"
 * \param longFlag E.g. "-output"
 */
function getArguments(args, shortFlag, longFlag) {
    return RSettings.getArguments(args, shortFlag, longFlag);

//    var ret = [];

//    for (var k=0; k<args.length; k++) {
//        if (args[k]===shortFlag) {
//            if (k+1 < args.length) {
//                ret.push(args[k+1]);
//            }
//        }

//        if (args[k].indexOf(longFlag+"=")===0) {
//            var j=args[k].indexOf("=");
//            ret.push(args[k].substr(j+1));
//        }
//    }

//    return ret;
}

function getIntArgument(args, shortFlag, longFlag, def) {
    // make sure undefined can be returned as default:
    if (def===undefined) {
        var ret = getArgument(args, shortFlag, longFlag);
        if (ret===undefined) {
            return def;
        }
        return RSettings.getIntArgument(args, shortFlag, longFlag, -1);
    }

    return RSettings.getIntArgument(args, shortFlag, longFlag, def);
}

function getIntListArgument(args, shortFlag, longFlag, def) {
    // make sure undefined can be returned as default:
    if (def===undefined) {
        var ret = RSettings.getIntListArgument(args, shortFlag, longFlag, []);
        if (ret.length===0) {
            return def;
        }
        return ret;
    }

    return RSettings.getIntListArgument(args, shortFlag, longFlag, def);

//    var arg = getArgument(args, shortFlag, longFlag);
//    if (arg===undefined) {
//        return def;
//    }

//    var ret = [];
//    var tokens = arg.split(",");

//    var singleInt = false;
//    if (tokens.length===1) {
//        singleInt = true;
//    }

//    for (var i=0; i<tokens.length; i++) {
//        var token = tokens[i];
//        var range = token.split("-");
//        var start, stop;

//        if (range.length===1) {
//            start = singleInt ? 0 : parseInt(range[0]);
//            stop = parseInt(range[0]);
//        }
//        else if (range.length===2) {
//            start = parseInt(range[0]);
//            stop = parseInt(range[1]);
//        }
//        else {
//            qWarning("invalid token in list: ", token);
//            continue;
//        }

//        for (var k=start; k<=stop; k++) {
//            ret.push(k);
//        }
//    }
//    return ret;
}

function getFloatArgument(args, shortFlag, longFlag, def) {
    // make sure undefined can be returned as default:
    if (def===undefined) {
        var ret = getArgument(args, shortFlag, longFlag);
        if (ret===undefined) {
            return def;
        }
        return RSettings.getFloatArgument(args, shortFlag, longFlag);
    }
    return RSettings.getFloatArgument(args, shortFlag, longFlag, def);
}

function getColorArgument(args, shortFlag, longFlag, def) {
    // make sure undefined can be returned as default:
    if (def===undefined) {
        var ret = getArgument(args, shortFlag, longFlag);
        if (ret===undefined) {
            return def;
        }
        return RSettings.getColorArgument(args, shortFlag, longFlag);
    }
    return RSettings.getColorArgument(args, shortFlag, longFlag, def);
}

function getVectorArgument(args, shortFlag, longFlag, def) {
    // make sure undefined can be returned as default:
    if (def===undefined) {
        var ret = getArgument(args, shortFlag, longFlag);
        if (ret===undefined) {
            return def;
        }
        return RSettings.getVectorArgument(args, shortFlag, longFlag);
    }
    return RSettings.getVectorArgument(args, shortFlag, longFlag, def);
}

function getBoxArgument(args, shortFlag, longFlag, def) {
    // make sure undefined can be returned as default:
    if (def===undefined) {
        var ret = getArgument(args, shortFlag, longFlag);
        if (ret===undefined) {
            return def;
        }
        return RSettings.getBoxArgument(args, shortFlag, longFlag);
    }
    return RSettings.getBoxArgument(args, shortFlag, longFlag, def);

//    var parts = ret.split(',');
//    if (parts.length!==4) {
//        return def;
//    }
//    for (var i=0; i<parts.length; i++) {
//        parts[i] = parseFloat(parts[i]);
//    }

//    return new RBox(new RVector(parts[0], parts[1]), new RVector(parts[0] + parts[2], parts[1] + parts[3]));
}

/**
 * \return True if the given arguments contain one of the given flags.
 */
function testArgument(args, shortFlag, longFlag) {
    return RSettings.testArgument(args, shortFlag, longFlag);
//    if (shortFlag!=="" && args.indexOf(shortFlag)!==-1) {
//        return true;
//    }
//    if (longFlag!=="") {
//        if (args.indexOf(longFlag)!==-1) {
//            return true;
//        }
//        for (var k=0; k<args.length; k++) {
//            if (args[k].indexOf(longFlag+"=")===0) {
//                return true;
//            }
//        }
//    }

//    return false;
}

function printArgument(name, prop) {
    var spc = "";
    if (name.length<32) {
        spc = new Array(32 - name.length).join(" ");
    }

    print(" ", name, spc, ":", prop);
}

function printGenericUsage() {
    if (RS.getSystemId()==="osx") {
        print();
        print("macOS specific options:\n");
        print("  -no-dock-icon           Don't show icon in dock. This should only be used\n"
            + "                          in combination with -no-gui."  );
    }

    if (RS.getSystemId()==="linux") {
        print();
        print("Qt/X11 platform arguments:");
        print();
        print("  -platform offscreen     Run without requiring an X11 server or display.");
        print("                          Use this argument to run this command line tool in a ");
        print("                          Linux server environment.");
        print();
        print("Qt/X11 environment variables:");
        print();
        print("  QT_QPA_FONTDIR          Set to fonts directory in a server environment, e.g. 'fonts/qt'.");
    }
}

