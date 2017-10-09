let CgnsDoc = require('..').CgnsDoc;
let path = require('path');
let expect = require('chai').expect;
let testFile1 = path.resolve(__dirname, './sqnz_s.hdf.cgns');

describe('open the file sqnz', function () {
    it(', its version should is 3.21', function () {
        let cgns = new CgnsDoc();
        cgns.open(testFile1);
        console.log(JSON.stringify(cgns));
        expect(cgns.version).to.be.closeTo(3.21, 0.001);
    });
    it('by constructor', function () {
        let cgns = new CgnsDoc(testFile1);
        expect(cgns.version).to.be.closeTo(3.21, 0.001);
    });
    it(', it should contains 1 bases', function() {
        let cgns = new CgnsDoc(testFile1);
        expect(cgns.bases.length).to.be.equals(1);
    });
});

