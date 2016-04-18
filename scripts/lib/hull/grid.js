function Grid(points) {
    var _cells = [];

    points.forEach(function(point) {
        var cellXY = this.point2CellXY(point),
            x = cellXY[0],
            y = cellXY[1];
        if (_cells[x] === undefined) {
            _cells[x] = [];
        }
        if (_cells[x][y] === undefined) {
            _cells[x][y] = [];
        }
        _cells[x][y].push(point);
    }, this);

    this.cellPoints = function(x, y) { // (Number, Number) -> Array
        return (_cells[x] !== undefined && _cells[x][y] !== undefined) ? _cells[x][y] : [];
    };

    this.removePoint = function(point) { // (Array) -> Array
        var cellXY = this.point2CellXY(point),
            cell = _cells[cellXY[0]][cellXY[1]],
            pointIdxInCell;
        
        for (var i = 0; i < cell.length; i++) {
            if (cell[i][0] === point[0] && cell[i][1] === point[1]) {
                pointIdxInCell = i;
                break;
            }
        }

        cell.splice(pointIdxInCell, 1);

        return cell;
    };
}

Grid.prototype = {
    point2CellXY: function(point) { // (Array) -> Array
        var x = parseInt(point[0] / Grid.CELL_SIZE),
            y = parseInt(point[1] / Grid.CELL_SIZE);
        return [x, y];
    },

    rangePoints: function(bbox) { // (Array) -> Array
        var tlCellXY = this.point2CellXY([bbox[0], bbox[1]]),
            brCellXY = this.point2CellXY([bbox[2], bbox[3]]),
            points = [];

        for (var x = tlCellXY[0]; x <= brCellXY[0]; x++) {
            for (var y = tlCellXY[1]; y <= brCellXY[1]; y++) {
                points = points.concat(this.cellPoints(x, y));
            }
        }

        return points;
    },

    addBorder2Bbox: function(bbox, border) { // (Array, Number) -> Array
        return [
            bbox[0] - (border * Grid.CELL_SIZE),
            bbox[1] - (border * Grid.CELL_SIZE),
            bbox[2] + (border * Grid.CELL_SIZE),
            bbox[3] + (border * Grid.CELL_SIZE)
        ];
    }
};

function grid(points) {
    return new Grid(points);
}

Grid.CELL_SIZE = 10;

//module.exports = grid;
