module.exports = {
    ...require("bindings")("cgns"),
    CgnsSimulationType: {
        Null: 0,
        UserDefined: 1,
        TimeAccurate: 2,
        NonTimeAccurate: 3,
        0: "Null",
        1: "UserDefined",
        2: "TimeAccurate",
        3: "NonTimeAccurate",
    }
};

