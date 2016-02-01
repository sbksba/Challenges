/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

var inputs = readline().split(' ');
var W = parseInt(inputs[0]);
var H = parseInt(inputs[1]);
var IMAGE = readline();

// Write an action using print()
// To debug: printErr('Debug messages...');

String.prototype.repeat = function( num )
{
    return new Array( num + 1 ).join( this );
}

// first top pixel always white

function Notes(img, w, h) {
    this.width = w;
    this.height = h;
    this.parse(img);
    return this;
}

Notes.prototype = {
    parse: function(img) {
        var arr = img.split(' ');
        // convert to array of 1 and 0
        // 0 - white note
        // 1 - black note
        var notes = '';
        for(var i = 0; i < arr.length; i++) {
            var notecolor;
            if (arr[i] == 'W' || arr[i] == 'B')
                notecolor = (arr[i] == 'W') ? '0' : '1';
            else
                notes += notecolor.repeat(parseInt(arr[i]));
        }

        this.columns = [];

        // convert to vertical lines
        for(var i = 0; i < this.width; i++ ) {
            var arr = [];

            for(var j = 0; j < this.height; j++) {
                arr.push(notes[j*this.width + i]);
            }
            this.columns.push(arr.join(''));
        }
    },

    isNotepadPattern: function(line) {
        return this.notepadPatters.indexOf(line) !== -1;
    },


    parseNotepad: function(line) {
        // first always white
        this.notepadPatters = [];

        var color = '0';
        var count = 0;
        var arr = [];
        for(var i = 0; i < line.length; i++) {
            if (line[i] == color) count++;
            else {
                arr.push(count);
                color = line[i];
                count = 1;
            }
        }
        arr.push(count);

        if (arr.length != 11) throw 'LinePattern array is not 11';

        this.lineThick = arr[1];
        this.lineStep = arr[2];
        this.notepadPatters.push(line);

        var dif = (this.lineThick + this.lineStep) / 2;

        var pattern6 = arr.slice();
        pattern6.splice(10, 0, arr[2], arr[1]);
        pattern6[pattern6.length - 1] -= arr[2] + arr[1];

        this.notePositions = [
            arr[0] - dif*2,
            arr[0] - dif,
            arr[0],
            arr[0] + dif,
            arr[0] + dif*2,
            arr[0] + dif*3,
            arr[0] + dif*4,
            arr[0] + dif*5,
            arr[0] + dif*6,
            arr[0] + dif*7,
            arr[0] + dif*8,
            arr[0] + dif*9];

        this.noteNames = ['G', 'F', 'E', 'D', 'C', 'B', 'A',
            'G', 'F', 'E', 'D', 'C', 'B', 'A'];

        pattern6 = pattern6.map(function(e, i, a){
            return ((i % 2 === 0) ? '0' : '1').repeat(e);
        });

        this.notepadPatters.push(pattern6.join(''));
    },

    analyseNotes: function() {
        this.resultNotes = [];

        for(var i = 0; i < this.noteCount; i++) {
            var column = this.notesColumns[i*this.noteWidth + (this.noteWidth/2)];

            var j = 0;
            do {
                j++
            } while (column[j] == this.notepadPatters[0][j]);

            var color = (column[j + this.lineStep/2] == '0') ? 'H' : 'Q';

            var k = 0;

            while (this.notePositions[k+1] < j) {
                k++;
            }

            var noteName = this.noteNames[k];

            this.resultNotes.push(noteName + color);
        }
    },

    splitToNotes: function() {
        // remove all first and last blank columns
        while (this.columns[0].indexOf('1') === -1) {
            this.columns.shift();
        };

        while (this.columns[this.columns.length - 1].indexOf('1') === -1) {
            this.columns.pop();
        };
        // first is notepad example. let's count lines in it, and line width
        this.parseNotepad(this.columns[0]);

        this.notesColumns = [];
        var i = 0;
        this.noteCount = 0;
        var prevNotePadPattern = true;
        for(var i = 0; i < this.columns.length; i++) {
            if (!this.isNotepadPattern(this.columns[i])) {
                this.notesColumns.push(this.columns[i]);
                if (prevNotePadPattern) this.noteCount++;
                prevNotePadPattern = false;
            } else prevNotePadPattern = true;
        }

        this.noteWidth = this.notesColumns.length/this.noteCount;

        this.analyseNotes();
    }
}

var notes = new Notes(IMAGE, W, H)
notes.splitToNotes();
print(notes.resultNotes.join(' '))
