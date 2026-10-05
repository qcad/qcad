/**
 * Headless test for the QCAD Simple API modification functions
 * (scripts/simple_modify.js, scripts/simple_info.js).
 *
 * Run from qcad/release:
 *
 *   ./QCAD-Pro.app/Contents/MacOS/QCAD-Pro -allow-multiple-instances \
 *       -autostart /abs/path/to/qcad/scripts/Tests/SimpleApiTest.js
 *
 * Prints PASS/FAIL per check and a RESULT line.
 */
include("scripts/simple.js");

var di = createDocumentInterface();
var doc = di.getDocument();

// headless: route the simple API to our off-screen document interface
getDocumentInterface = function() { return di; };

var nPass = 0, nFail = 0;
function check(name, cond) {
    if (cond) { nPass++; print("PASS " + name); }
    else { nFail++; print("FAIL " + name); }
}
function near(a, b, tol) { if (isNull(tol)) tol = 1e-6; return Math.abs(a-b) < tol; }
function vnear(v, x, y) { return isValidVector(v) && near(v.x, x) && near(v.y, y); }
function clearDoc() {
    ids = doc.queryAllEntities();
    var op = new RDeleteObjectsOperation();
    for (var i=0; i<ids.length; i++) { op.deleteObject(doc.queryEntity(ids[i])); }
    di.applyOperation(op);
}
function count() { return doc.queryAllEntities().length; }
function lines() {
    var ret = [];
    ids = doc.queryAllEntities();
    for (var i=0; i<ids.length; i++) { var e = doc.queryEntity(ids[i]); if (isLineEntity(e)) ret.push(e); }
    return ret;
}
function arcs() {
    var ret = [];
    ids = doc.queryAllEntities();
    for (var i=0; i<ids.length; i++) { var e = doc.queryEntity(ids[i]); if (isArcEntity(e)) ret.push(e); }
    return ret;
}
function hasLine(x1,y1,x2,y2) {
    var ls = lines();
    for (var i=0; i<ls.length; i++) {
        var s = ls[i].getStartPoint(), e = ls[i].getEndPoint();
        if ((vnear(s,x1,y1) && vnear(e,x2,y2)) || (vnear(s,x2,y2) && vnear(e,x1,y1))) return true;
    }
    return false;
}
function getLineById(id) { return doc.queryEntity(id); }

// ---- getEntity / getShape / getClosestEntity
var c, ids, pl, res;
clearDoc();
var l1 = addLine(0,0, 10,0);
var l2 = addLine(5,-5, 5,5);
check("addLine returns entity with id", isEntity(l1) && l1.getId()!==RObject.INVALID_ID);
var ce = getClosestEntity(8, 0.1);
check("getClosestEntity(x,y)", !isNull(ce) && ce.getId()===l1.getId());
check("getClosestEntity([x,y])", getClosestEntity([5,4]).getId()===l2.getId());
check("getEntity(id)", getEntity(l1.getId()).getId()===l1.getId());
check("getEntity(entity)", getEntity(l2).getId()===l2.getId());
check("getEntity(pos)", getEntity([5,4]).getId()===l2.getId());
check("getShape(id) is RLine", isLineShape(getShape(l1.getId())));
check("getShape(pos) is RLine", isLineShape(getShape([8,0])));
var sh = new RLine(0,0,1,1);
check("getShape(shape) is same", getShape(sh)===sh);

// ---- move / rotate / scale / mirror with positions
clearDoc();
l1 = addLine(0,0, 10,0);
var moved = move([2,0], [0,5]);
check("move by position", !isNull(moved) && hasLine(0,5,10,5));
check("move keeps id", moved.getId()===l1.getId());
rotate(l1.getId(), 90, [0,5]);
check("rotate entity deg", hasLine(0,5,0,15));
var shp = new RLine(0,0,10,0);
rotate(shp, 90);
check("rotate shape deg", vnear(shp.getEndPoint(), 0, 10));
clearDoc();
l1 = addLine(0,0, 10,0);
scale([5,0], 2, [0,0]);
check("scale by position", hasLine(0,0,20,0));
scale(l1.getId(), [1,2], [0,0]);
check("scale by vector factor", hasLine(0,0,20,0));
mirror(l1, [0,0],[0,1]);
check("mirror 3-arg form", hasLine(0,0,-20,0));
mirror(l1.getId(), 0,0, 1,0);
check("mirror 5-arg form", hasLine(0,0,-20,0));
mirror([-10,0], [[0,0],[0,1]]);
check("mirror by position", hasLine(0,0,20,0));

// ---- color is preserved by modifications
clearDoc();
l1 = addLine(0,0,10,0, undefined);
var le = doc.queryEntity(l1.getId());
le.setColor(new RColor(255,0,0));
di.applyOperation(new RAddObjectOperation(le, false));
move(l1.getId(), [0,1]);
check("move keeps color", doc.queryEntity(l1.getId()).getColor().red()===255);

// ---- trim
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(5,-5, 5,5);
var t = trim(l1.getId(), [8,0], l2.getId(), [5,3]);
check("trim returns transaction", !isNull(t));
check("trim result", hasLine(5,0,10,0) && hasLine(5,-5,5,5));
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(5,-5, 5,5);
trim([2,0], [5,3]);
check("trim by positions", hasLine(0,0,5,0) && hasLine(5,-5,5,5));
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(5,-5, 5,5);
trimBoth([2,0], [5,3]);
check("trimBoth by positions", hasLine(0,0,5,0) && hasLine(5,0,5,5) && count()===2);
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(5,-5, 5,5);
trim(l1, 8,0, l2, 5,3, true);
check("trim 7-arg form", hasLine(5,0,10,0) && hasLine(5,0,5,5));
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(5,-5, 5,5);
trim(l1.getId(), l2.getId());
check("trim default positions (midpoint kept)", count()===2);
// shapes only
var s1 = new RLine(0,0,10,0), s2 = new RLine(5,-5,5,5);
var res = trim(s1, new RVector(8,0), s2, new RVector(5,3), true);
check("trim shapes returns array", isArray(res) && res.length===2 && vnear(res[0].getStartPoint(),5,0) && vnear(res[1].getStartPoint(),5,0));
check("trim shapes leaves originals", vnear(s1.getStartPoint(),0,0));
// extend by trim (no intersection on segment)
clearDoc();
l1 = addLine(0,0, 3,0);
l2 = addLine(5,-5, 5,5);
trim(l1.getId(), [1,0], l2.getId());
check("trim extends", hasLine(0,0,5,0));

// ---- lengthen
clearDoc();
l1 = addLine(0,0, 10,0);
lengthen(l1.getId(), 5);
check("lengthen default end", hasLine(0,0,15,0));
lengthen(l1.getId(), true, 5);
check("lengthen start bool", hasLine(-5,0,15,0));
lengthen(l1.getId(), [-5,0], -2);
check("lengthen pos start shorten", hasLine(-3,0,15,0));
lengthen([14,0], 1);
check("lengthen by position", hasLine(-3,0,16,0));
var ls = new RLine(0,0,10,0);
lengthen(ls, false, 2);
check("lengthen shape in place", vnear(ls.getEndPoint(), 12, 0));

// ---- breakOut / autoTrim
clearDoc();
l1 = addLine(0,0, 10,0);
addLine(3,-1, 3,1);
addLine(7,-1, 7,1);
breakOut(l1.getId(), [5,0]);
check("breakOut removes middle", hasLine(0,0,3,0) && hasLine(7,0,10,0) && count()===4);
clearDoc();
l1 = addLine(0,0, 10,0);
addLine(3,-1, 3,1);
addLine(7,-1, 7,1);
breakOut([5,0], false);
check("breakOut keeps segment", hasLine(0,0,3,0) && hasLine(3,0,7,0) && hasLine(7,0,10,0) && count()===5);
clearDoc();
l1 = addLine(0,0, 10,0);
addLine(3,-1, 3,1);
addLine(7,-1, 7,1);
autoTrim(l1, 5, 0);
check("autoTrim keeps only middle", hasLine(3,0,7,0) && count()===3);
// breakOut shape
var bs = new RLine(0,0,10,0);
res = breakOut(bs, [5,0]);
check("breakOut shape returns rest shapes", isArray(res) && res.length===2 && vnear(res[0].getEndPoint(),3,0) && vnear(res[1].getStartPoint(),7,0));
res = autoTrim(bs, [5,0]);
check("autoTrim shape returns segment", isArray(res) && res.length===1 && vnear(res[0].getStartPoint(),3,0) && vnear(res[0].getEndPoint(),7,0));

// ---- divide
clearDoc();
l1 = addLine(0,0, 10,0);
divide(l1.getId(), [4,0]);
check("divide once", hasLine(0,0,4,0) && hasLine(4,0,10,0) && count()===2);
clearDoc();
l1 = addLine(0,0, 10,0);
divide(l1, 2,0, 8,0);
check("divide twice (x,y form)", hasLine(0,0,2,0) && hasLine(2,0,8,0) && hasLine(8,0,10,0) && count()===3);
clearDoc();
c = addCircle([0,0], 5);
divide(c.getId(), [5,0], [-5,0]);
check("divide circle two positions", count()===2 && arcs().length===2);
clearDoc();
pl = addPolyline([[0,0],[10,0],[10,10],[0,10]], true);
divide(pl.getId(), [5,0], [5,10]);
ids = doc.queryAllEntities();
check("divide closed polyline two positions", ids.length===2 && isPolylineEntity(doc.queryEntity(ids[0])));
clearDoc();
l1 = addLine(0,0, 10,0);
divide([6,0]);
check("divide by position", hasLine(0,0,6,0) && hasLine(6,0,10,0));
res = divide(new RLine(0,0,10,0), [4,0]);
check("divide shape", isArray(res) && res.length===2 && vnear(res[0].getEndPoint(),4,0));

// ---- round
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(10,0, 10,10);
t = round(l1.getId(), [5,0], l2.getId(), [10,5], 2);
check("round transaction", !isNull(t));
check("round trims lines", hasLine(0,0,8,0) && hasLine(10,2,10,10));
check("round adds arc", arcs().length===1 && near(arcs()[0].getRadius(), 2));
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(10,0, 10,10);
round([5,0], [10,5], 1);
check("round by positions", hasLine(0,0,9,0) && hasLine(10,1,10,10) && arcs().length===1);
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(10,0, 10,10);
round(l1, 5,0, l2, 10,5, 3, false);
check("round no trim", hasLine(0,0,10,0) && hasLine(10,0,10,10) && arcs().length===1);
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(10,0, 10,10);
round(l1.getId(), l2.getId(), 2);
check("round default positions", hasLine(0,0,8,0) && hasLine(10,2,10,10) && arcs().length===1);
res = round(new RLine(0,0,10,0), new RVector(5,0), new RLine(10,0,10,10), new RVector(10,5), 2);
check("round shapes", isArray(res) && res.length===3 && isArcShape(res[1]) && vnear(res[0].getEndPoint(),8,0));
// polyline corner
clearDoc();
pl = addPolyline([[0,0],[10,0],[10,10]], false);
round(pl.getId(), [5,0], pl.getId(), [10,5], 2);
ids = doc.queryAllEntities();
check("round within polyline", ids.length===1 && isPolylineEntity(doc.queryEntity(ids[0])) && doc.queryEntity(ids[0]).countSegments()===3);

// ---- bevel / chamfer
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(10,0, 10,10);
bevel(l1.getId(), [5,0], l2.getId(), [10,5], 2);
check("bevel trims lines + adds line", hasLine(0,0,8,0) && hasLine(10,2,10,10) && hasLine(8,0,10,2) && count()===3);
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(10,0, 10,10);
chamfer(l1.getId(), l2.getId(), 1, 3);
check("chamfer d1 d2 defaults", hasLine(0,0,9,0) && hasLine(10,3,10,10) && hasLine(9,0,10,3));
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(10,0, 10,10);
bevel([5,0], [10,5], 2, false);
check("bevel no trim", hasLine(0,0,10,0) && hasLine(10,0,10,10) && hasLine(8,0,10,2));
res = bevel(new RLine(0,0,10,0), new RVector(5,0), new RLine(10,0,10,10), new RVector(10,5), 2);
check("bevel shapes", isArray(res) && res.length===3 && isLineShape(res[1]) && vnear(res[1].getStartPoint(),8,0));

// ---- offset
clearDoc();
l1 = addLine(0,0, 10,0);
offset(l1.getId(), 1);
check("offset both sides", hasLine(0,1,10,1) && hasLine(0,-1,10,-1) && count()===3);
clearDoc();
l1 = addLine(0,0, 10,0);
offset(l1.getId(), [5,3], 1, 2);
check("offset side pos, number 2", hasLine(0,1,10,1) && hasLine(0,2,10,2) && count()===3);
clearDoc();
l1 = addLine(0,0, 10,0);
offset([5,0], 2);
check("offset by position (both sides)", hasLine(0,2,10,2) && hasLine(0,-2,10,-2));
clearDoc();
c = addCircle([0,0], 5);
offset(c.getId(), 1, 2, RS.RightHand);
check("offset circle number 2", count()===3);
res = offset(new RLine(0,0,10,0), 1, 1, RS.LeftHand);
check("offset shape", isArray(res) && res.length===1 && vnear(res[0].getStartPoint(),0,1));

// ---- reverse
clearDoc();
l1 = addLine(0,0, 10,0);
reverse(l1.getId());
check("reverse entity", vnear(doc.queryEntity(l1.getId()).getStartPoint(), 10, 0));
var rs = new RLine(0,0,10,0);
reverse(rs);
check("reverse shape", vnear(rs.getStartPoint(), 10, 0));

// ---- explode
clearDoc();
pl = addPolyline([[0,0],[10,0],[10,10]], false);
explode(pl.getId());
check("explode polyline", count()===2 && hasLine(0,0,10,0) && hasLine(10,0,10,10));
res = explode(new RPolyline([new RVector(0,0), new RVector(1,0), new RVector(1,1)], false));
check("explode shape", isArray(res) && res.length===2);
clearDoc();
l1 = addLine(0,0,10,0);
var r = explode(l1.getId());
check("explode line fails gracefully", isNull(r) && count()===1);

// ---- stretch
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(0,5, 10,5);
stretch(8,-1, 12,6, 5,0);
check("stretch 6-arg", hasLine(0,0,15,0) && hasLine(0,5,15,5));
clearDoc();
l1 = addLine(0,0, 10,0);
stretch([[-1,-1],[2,1]], [-3,0]);
check("stretch corners array", hasLine(-3,0,10,0));
clearDoc();
l1 = addLine(0,0, 10,0);
stretch(new RBox(new RVector(-1,-1), new RVector(11,1)), new RVector(0,2));
check("stretch moves inside entity", hasLine(0,2,10,2));

// ---- deleteEntity
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(0,5, 10,5);
deleteEntity([5,5]);
check("deleteEntity by position", count()===1 && hasLine(0,0,10,0));
deleteEntity(l1.getId());
check("deleteEntity by id", count()===0);

// ---- transaction mode
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(10,0, 10,10);
var l3 = addLine(0,5, 20,5);
startTransaction(di);
var tr = round(l1.getId(), [5,0], l2.getId(), [10,5], 2);
check("round inside transaction returns undefined", isNull(tr));
offset(l3.getId(), [10,8], 1);
move(l3.getId(), [0,-20]);
check("transaction not applied yet", hasLine(0,0,10,0) && count()===3);
var tt = endTransaction();
check("endTransaction sub: round", hasLine(0,0,8,0) && hasLine(10,2,10,10) && arcs().length===1);
check("endTransaction sub: offset", hasLine(0,6,20,6));
check("endTransaction sub: move", hasLine(0,-15,20,-15));
check("endTransaction applies", !isNull(tt) && hasLine(0,0,8,0) && hasLine(10,2,10,10) && arcs().length===1 && hasLine(0,6,20,6) && hasLine(0,-15,20,-15));
// transaction via getOperation only (bug fix: op stored)
clearDoc();
l1 = addLine(0,0, 10,0);
l2 = addLine(5,-5, 5,5);
startTransaction(di);
trim(l1.getId(), [8,0], l2.getId());
endTransaction();
check("trim-only transaction applied", hasLine(5,0,10,0));

print("");
print("RESULT: " + nPass + " passed, " + nFail + " failed");
