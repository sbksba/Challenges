let width = +readline()
let height = +readline()

// array of node object (x, y, wanted links and effective links).
let nodes = []
// grid is an array of lines, each line contains a true boolean at every node positins.
let grid = []

// total number of expected links.
// fill the grid and build nodes.
for (let y = 0; y < height; y++) {
  grid.push(readline().split('').map((c, x) => {
    if (c !== '.') {
      let node = {x:x, y:y, wanted:+c}
      nodes.push(node)
      return true
    }
    return false
  }))
}

/**
 * Search for immadiate neighbour with remaining links
 * on a given axis and a given direction.
 * @param {Object} start - node from which neighbours are searched
 * @param {String} axis - 'x': horizontal, 'y': vertical
 * @param {Boolean=true} direction - true: left/bottom, false: right/top
 * @return {Array<Object>} neighbours, or null if none to be found
 */
let search = (start, axis, direction = true) => {
  let end = {x:start.x, y:start.y}
  let limit = axis === 'x' ? width : height
  while(direction ? (++end[axis] < limit) : (--end[axis] >= 0)) {
    if (grid[end.y][end.x]) {
      return nodes.find(node =>
        node.x === end.x && node.y === end.y && node.wanted > 0
      ) || null
    }
  }
  return null
}

/**
 * Sorting function used to ensure that nodes are always ordered from top-right to bottom-left
 * @param {Object} n1 - first node to compare
 * @param {Object} n2 - second node to compare
 * @return {Number} negative if n1 is upper than n2, positive otherwise
 */
let order = (n1, n2) => n1.x > n2.x || (n1.x === n2.x && n1.y > n2.y) ? [n2, n1] : [n1, n2]

/**
 * Checks if a link has a cross with existing links
 * @param {Array<Object>} link - array of two nodes defining a link
 * @param {Array<Array<Object>} links - array of links, as defined above
 * @return {Boolean} true if link is crossed by at least one contained in links, false otherwise
 */
let isCrossed = (link, links) => {
  let [{x: sx1, y: sy1}, {x: ex1, y:ey1}] = link
  let hasCross = ([{x: sx2, y: sy2}, {x: ex2, y:ey2}]) =>
    // for an horizontal link, checks that the other is vertical and crossing
    sx1 === ex1 ? sy2 === ey2 && sx2 < sx1 && ex2 > sx1 && sy2 > sy1 && sy2 < ey1 :
    // for a vertical link, checks that the other is horizontal and crossing
    sx2 === ex2 && sy2 < sy1 && ey2 > sy1 && sx2 > sx1 && sx2 < ex1
  return links.some(hasCross)
}

// all possible link combination in a array of 4 neighbours
// for a given number of expected link (key) give the possible neighbours index combination (value)
let combinations = {
  1: [[0], [1], [2]],
  2: [[0, 1], [0, 2], [1, 2], [0, 0], [1, 1], [2, 2]],
  3: [[0, 1, 2], [0, 0, 1], [0, 0, 2], [1, 1, 0], [1, 1, 2], [2, 2, 0], [2, 2, 1]],
  4: [[0, 0, 1, 2], [1, 1, 0, 2], [2, 2, 0, 1], [0, 0, 1, 1], [0, 0, 2, 2], [1, 1, 2, 2]],
  5: [[0, 0, 1, 1, 2], [0, 0, 2, 2, 1], [1, 1, 2, 2, 0]],
  6: [[0, 0, 1, 1, 2, 3], [0, 0, 1, 2, 2, 3], [0, 0, 1, 2, 3, 3], [0, 1, 1, 2, 2, 3], [0, 1, 1, 2, 3, 3], [0, 1, 1, 2, 2, 3], [0, 0, 1, 1, 2, 2], [0, 0, 1, 1, 3, 3], [3, 3, 1, 1, 2, 2], [0, 0, 3, 3, 2, 2]]
}

/**
 * Count and return the number of occurence of elem in array, using strict identity
 * @param {Any} elem - searched element
 * @param {Array<Any>} array - array in which elem is searched
 * @return {Number} the number of occurence of elem in array
 */
let count = (elem, array) => array.reduce((sum, e) => sum += e === elem ? 1 : 0, 0)

/**
 * Compute all possible links combination between a given node and its neighbours
 * that respect neighbours expectation and that does not cross existing link
 * @param {Object} node - start node analysed
 * @param {Array<Object>} neighbours - node's immediate neighbours
 * @param {Array<Array<Object>>} links - array of existing links, a link is an array of two nodes
 * @return {Array<Array<Object>>} array (that may be empty) of possible new links between start and its neighbours
 */
let possibleLinks = (node, neighbours, links) =>
  (combinations[node.wanted] || []).filter(ids =>
    // check that possible ids really exists in neighbours array
    // and for ids that are use twice, that matching neighbour has enought space
    ids.every(i => neighbours[i]) && ids.filter(i => count(i, ids) == 2).every(i => neighbours[i].wanted >= 2)
  ).map(ids => ids.map(i => order(node, neighbours[i]))
  ).filter(candidates => !candidates.some(l => isCrossed(l, links)))

/**
 * Check if the solution is complete and does not violates contraints.
 * We do not check about crossed links, because it was already enforced
 * @param {Array<Object>} nodes - all existing nodes
 * @param {Array<Array<Object>>} links - array of solution links, a link is an array of two nodes
 * @return {Boolean} true if solution is valid, false otherwise
 */
let checkContraints = (nodes, links) => {
  // checks if all nodes have their links satisfied
  let unsatisfied = nodes.find(n => n.wanted)
  if (unsatisfied) {
    // unsatisfied node
    return false
  }

  // checks if group is uniq
  let group = [links[0][0]]
  for (let i = 0; i < group.length; i++) {
    let node = group[i]
    for (let linked of links.filter(([n1, n2]) => n1 === node || n2 === node).map(([n1, n2]) => n1 === node ? n2 : n1)) {
      if (group.indexOf(linked) === -1) {
        group.push(linked)
      }
    }
  }
  let uniq = []
  links.forEach(link => link.forEach(n => uniq.indexOf(n) === -1 ? uniq.push(n) : null))
  return uniq.length === group.length
}

/**
 * Backtrack algorithm that compute a valid solution for a given node
 * @param {Object} node - starting node
 * @param {Array<Array<Object>> = []} links - for internal use, partial solution
 * @return {Array<Array<Object>>} solution links, a link is an array of two nodes
 */
let fillNode = (node, links = []) => {
  if (!node) {
    return checkContraints(nodes, links) ? links : null
  } else if (links.length && checkContraints(nodes, links)) {
    return links
  }

  // get all immediate neighbours
  let neighbours = [
    search(node, 'x'),
    search(node, 'y'),
    search(node, 'x', false),
    search(node, 'y', false)
  ].filter(n => n)

  // compute all possible links to these neighbours
  for (let added of possibleLinks(node, neighbours, links)) {
    added.forEach(link => link.forEach (node => node.wanted--))
    // try to fill next free node
    let solution = fillNode(nodes.find(n => n.wanted), links.concat(added))
    if (solution) {
      return solution
    }
    // if we reached this point, we need to backtrack the added linked
    added.forEach(link => link.forEach (node => node.wanted++))
  }
  return null
}

// print links to console for final output.
let result = fillNode(nodes[0]).map(([{x: x1, y: y1}, {x: x2, y:y2}]) => [x1, y1, x2, y2, 1].join(' ')).join('\n')
print(result)
