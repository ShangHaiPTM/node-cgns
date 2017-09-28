let CgnsDoc = require('bindings')('cgns').CgnsDoc;
let path = require('path');

let cgns = new CgnsDoc();
let filePath = path.resolve(__dirname, './sqnz_s.hdf.cgns');
cgns.open(filePath);

console.log(JSON.stringify(cgns));