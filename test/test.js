let CgnsDoc = require('bindings')('cgns').Doc;
let path = require('path');

let cgns = new CgnsDoc();
let filePath = path.resolve('./test.cgns');
cgns.open(filePath);

console.log(JSON.stringify(cgns));