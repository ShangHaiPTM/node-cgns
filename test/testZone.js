let cgns = require('..');
let path = require('path');
let expect = require('chai').expect;
let testFile1 = path.resolve(__dirname, './sqnz_s.hdf.cgns');

describe('First zone in sqnz file', function() {
    let doc = new cgns.CgnsDoc(testFile1);
    let bases = doc.bases;
    let zone = bases[0].zones[0];

    it('Should have a magic number id', function() {

    })
});