let [width, height] = readline().split(' ').map(n => n)
let grid = []
while(height--) {
  grid.push(readline().split(' ').map(n => +n))
}
let exit = +readline()
let discarded = []

// For a given stone type and an incoming direction,
// returns move on map and new direction
let paths = {
  '1T': {y: 1, dir: 'T'},
  '1L': {y: 1, dir: 'T'},
  '1R': {y: 1, dir: 'T'},
  '2L': {x: 1, dir: 'L'},
  '2R': {x: -1, dir: 'R'},
  '3T': {y: 1, dir: 'T'},
  '4T': {x: -1, dir: 'R'},
  '4R': {y: 1, dir: 'T'},
  '5T': {x: 1, dir: 'L'},
  '5L': {y: 1, dir: 'T'},
  '6L': {x: 1, dir: 'L'},
  '6R': {x: -1, dir: 'R'},
  '7T': {y: 1, dir: 'T'},
  '7R': {y: 1, dir: 'T'},
  '8L': {y: 1, dir: 'T'},
  '8R': {y: 1, dir: 'T'},
  '9T': {y: 1, dir: 'T'},
  '9L': {y: 1, dir: 'T'},
  '10T': {x: -1, dir: 'R'},
  '11T': {x: 1, dir: 'L'},
  '12R': {y: 1, dir: 'T'},
  '13L': {y: 1, dir: 'T'}
}

// For a given stone type and a turn,
// returns the new stone type
let turns = {
  '2L': 3,
  '2R': 3,
  '3L': 2,
  '3R': 2,
  '4L': 5,
  '4R': 5,
  '5L': 4,
  '5R': 4,
  '6L': 9,
  '6R': 7,
  '7L': 6,
  '7R': 8,
  '8L': 7,
  '8R': 9,
  '9L': 8,
  '9R': 6,
  '10L': 13,
  '10R': 11,
  '11L': 10,
  '11R': 12,
  '12L': 11,
  '12R': 13,
  '13L': 12,
  '13R': 10
}

/**
 * Find all combination available at a given position, trying to turn the stone
 * and evaluating the next position
 *
 * @param {Object} pos - checked position, with x, y and dir
 * @return {Array<Object>} list (that may be empty) of actions at position
 * and the next position
 */
let findNext = ({x, y, dir}) => {
  let stone = grid[y][x]
  let possibles = [{
    // normal move without moving stonr
    move: paths[Math.abs(stone) + dir]
  }]
  if (stone > 0) {
    // turn it left, twice left, right
    possibles.push({
      turn: 'LEFT',
      move: paths[turns[stone + 'L'] + dir]
    }, {
      turn: 'LEFT',
      move: paths[turns[turns[stone + 'L'] + 'L'] + dir]
    }, {
      turn: 'RIGHT',
      move: paths[turns[stone + 'R'] + dir]
    })
  }
  return possibles.map(({turn, move}) =>
    move ? {
      x: x,
      y: y,
      dir: dir,
      turn: turn,
      next: {
        x: x + (move.x || 0),
        y: y + (move.y || 0),
        dir: move.dir
      }
    } : null
  ).filter(n => n)
}

/**
 * Find a path from a given position to the exit.
 * @param {Object} pos - checked position, with x, y and dir
 * @param {Array<Object>} - existing path to extend - internal usage only
 * @return {Array<Object>} positions (and turn instruction) toward end.
 * Null if no path found
 */
let findExit = (pos, path = []) => {
  if (pos.x === exit && pos.y === grid.length) {
    // found the exit
    return path
  }
  if (pos.y >= grid.length || pos.x < 0 || pos.x > grid[0].length) {
    // leave the map
    return null
  }
  let idx = path.length - 1
  // compute possible moves of current position and check them
  for (let possible of findNext(pos)) {
    path.push(possible)
    let exit = findExit(possible.next, path)
    if (exit) {
      // found a path to exit
      return path
    }
    // backtrack possibility
    path.splice(idx, path.length)
  }
  // no exit found
  return null
}

/**
 * Find path that a rock will follow from a given position
 * @param {Array<Object>} path - path the rock will use
 * @return {Object} x, y and turn of the stone to turn to crush rock
 */
let rockPath = ({x, y, dir}, path = []) => {
  if (y >= grid.length || x < 0 || x >= grid[0].length) {
    return path
  }
  path.push({x: x, y: y, dir: dir})
  let move = paths[Math.abs(grid[y][x]) + dir]
  if (!move) {
    return path
  }
  return rockPath({
    x: x + (move.x || 0),
    y: y + (move.y || 0),
    dir: move.dir
  }, path)
}

/**
 * Find the nearest turnable stone that can be used to crush the rock
 * @param {Array<Object>} path - path the rock will use
 * @return {Object} x, y and turn of the stone to turn to crush rock
 */
let crushRock = (path) => path.slice(1).map(({x, y, dir}) => {
  let stone = grid[y][x]
  if (stone > 1) {
    if (!paths[turns[stone + 'L'] + dir]) {
      return {x:x, y:y, turn: 'LEFT'}
    }
    return {x:x, y:y, turn: 'RIGHT'}
  }
  return null
}).filter(s => s)

/**
 * Displays grid content with columns/rows indices
 */
let printGrid = () => {
  printErr(grid.map(row => row.map(cell => cell >= 0 && cell < 10 ? '  ' + cell : cell >= 10 || cell > -10 ? ' ' + cell : cell).join(" ")).join("\n"))
}

// Game loop
while (true) {
  // update Indy's position
  let [x, y, direction] = readline().split(' ')
  let indy = {
    x: +x,
    y: +y,
    dir: direction[0]
  }

  // let's find where rocks are
  let n = +readline()
  let rocks = []
  while(n--) {
    let [x, y, direction] = readline().split(' ')
    rocks.push(rockPath({x: +x, y: +y, dir: direction[0]}))
  }
  // computes path of each rocks that can be cruseh
  rocks = rocks.map(crushRock).filter(p => p.length > 0)

  // find the exit from current position (it must be reachable)
  let path = findExit(indy)
  let turnable = path.find(step => step.turn)

  while (rocks.length > 0 && path.indexOf(turnable) > 1) {
    // if enought time before next turn, get rocks with smallest crush possibilities
    let crushed = rocks.sort((a, b) => a.length - b.length)[0]
    let tile = crushed[0]
    if (indy.x === tile.x && indy.y === tile.y || discarded.find(({x, y}) => x === tile.x && y === tile.y)) {
      // but check that we did not already moved that part !
      rocks.splice(rocks.indexOf(crushed), 1)
    } else {
      turnable = tile
      discarded.push(turnable)
    }
  }


  if (turnable) {
    // turn the first turnable stone
    let {x, y, turn} = turnable
    grid[y][x] = turns[grid[y][x] + turn[0]]
    print(x, y, turn)
  } else {
    // or just do nothing
    print('WAIT')
  }
}
