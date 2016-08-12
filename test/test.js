var payload = Buffer.from([64,160,198,0,20,128,1,0,2,76,47,251,70,206,90]);

var buffer = Buffer.from([76,47]);
var size = 2;
var key = Buffer.from('00112233445566778899AABBCCDDEEFF', 'hex');
var address = payload[1] + (payload[2]<<8) + (payload[3]<<16) + (payload[4]<<24);
var dir = 0;
var sequenceCounter = payload[6] + (payload[7]<<8);

var lorawanCrypto = require('../index');

var encBuffer = Buffer.alloc(size);
var decBuffer = Buffer.alloc(size);

lorawanCrypto.payloadDecrypt(
    buffer, size,
    key,
    address,
    dir,
    sequenceCounter,
    encBuffer
);

console.log(encBuffer); // should be: hex 12 34

lorawanCrypto.payloadEncrypt(
    encBuffer, size,
    key,
    address,
    dir,
    sequenceCounter,
    decBuffer
);

console.log(decBuffer); // should be: hex 4c 2f