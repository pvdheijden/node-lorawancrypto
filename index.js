'use strict';

const lorawanCrypto = require('./build/Release/lorawancrypto.node');


module.exports.computeMic = lorawanCrypto.computeMic;

module.exports.payloadDecrypt = function(encBuffer, size, key, address, dir, sequenceCounter) {
    var decBuffer = Buffer.alloc(size);
    lorawanCrypto.payloadDecrypt(encBuffer, size, key, address, dir, sequenceCounter, decBuffer);
                
    return decBuffer;
};

module.exports.payloadEncrypt = function(decBuffer, size, key, address, dir, sequenceCounter) {
    var encBuffer = Buffer.alloc(size);
    lorawanCrypto.payloadEncrypt(decBuffer, size, key, address, dir, sequenceCounter, encBuffer);
                
    return encBuffer;
};

module.exports.joinComputeMic = lorawanCrypto.joinComputeMic;

module.exports.joinDecrypt = function(buffer, size, key) {
    var decBuffer = Buffer.alloc(size);
    lorawanCrypto.joinDecrypt(buffer, size, key, decBuffer);

    return decBuffer;
};

module.exports.joinEncrypt = function(buffer, size, key) {
    var encBuffer = Buffer.alloc(size);
    lorawanCrypto.joinEncrypt(buffer, size, key, encBuffer);

    return encBuffer;
};

module.exports.joinComputeSKeys = function(key, appNonce, devNonce) {
    var nwkSKey = Buffer.alloc(16);
    var appSKey = Buffer.alloc(16);
    lorawanCrypto.joinComputeSKeys(key, appNonce, devNonce, nwkSKey, appSKey);

    return {
        NwkSKey: nwkSKey,
        AppSKey: appSKey
    };
};
