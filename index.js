'use strict';

var lorawanCrypto = require('./build/Release/lorawancrypto.node');

module.exports.payloadDecrypt = lorawanCrypto.payloadDecrypt;
module.exports.payloadEncrypt = lorawanCrypto.payloadEncrypt;