let cgns = require('..');
let path = require('path');
let expect = require('chai').expect;
let testFile1 = path.resolve(__dirname, './sqnz_s.hdf.cgns');

describe('Bases in sqnz file', function() {
    let doc = new cgns.CgnsDoc(testFile1);
    console.log(JSON.stringify(doc));
    let bases = doc.bases;
    it('id should be a magic number', function() {
        expect(bases[0].id).to.be.equals(4.778309726736501e-299); // I don't known what this id means.
    });
    it('cellDimension should be 3', function() {
        expect(bases[0].cellDimension).to.be.equals(3);
    });
    it('physicalDimension should be 3', function() {
        expect(bases[0].physicalDimension).to.be.equals(3);
    });
    it('should have 3 zone', function() {
        expect(bases[0].zones.length).to.be.equals(3);
    });
})