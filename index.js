const addon = require("bindings")("pythonMethod");

const str = addon.pythonMethod();

console.log(str);