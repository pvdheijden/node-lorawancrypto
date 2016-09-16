'use strict';

var lorawanCrypto = require('./build/Release/lorawancrypto.node');


module.exports.payloadEncrypt = function(decBuffer, size, key, address, dir, sequenceCounter) {
    var encBuffer = Buffer.alloc(size);
    lorawanCrypto.payloadEncrypt(decBuffer, size, key, address, dir, sequenceCounter, encBuffer);
                
    return encBuffer;
};

module.exports.payloadDecrypt = function(encBuffer, size, key, address, dir, sequenceCounter) {
    var decBuffer = Buffer.alloc(size);
    lorawanCrypto.payloadDecrypt(encBuffer, size, key, address, dir, sequenceCounter, decBuffer);
                
    return decBuffer;
};

/*
module.exports.joinComputeMic = lorawanCrypto.joinComputeMic;
*/
