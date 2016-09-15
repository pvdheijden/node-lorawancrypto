'use strict';

var assert = require('assert');

/*jshint -W016 */
var payload = Buffer.from([64,160,198,0,20,128,1,0,2,76,47,251,70,206,90]);
var buffer = Buffer.from([76,47]);
var size = 2;
var key = Buffer.from('00112233445566778899AABBCCDDEEFF', 'hex');
var address = payload.readUInt32LE(1);
var dir = 0;
var sequenceCounter = payload[6] + (payload[7]<<8);
/*jshint +W016 */


var lorawanCrypto = require('../index');
var encBuffer = Buffer.alloc(size);
var decBuffer = Buffer.alloc(size);

describe('LoRaWANCrypto', function() {
    before(function() {

    });

    describe('payloadDecrypt()', function() {
        it('should return <Buffer 12 34>', function() {

            lorawanCrypto.payloadDecrypt(
                buffer, size,
                key,
                address,
                dir,
                sequenceCounter,
                encBuffer
            );

            // should be: hex 12 34
            assert.equal(encBuffer.compare(Buffer.from([0x12, 0x34])), 0);
        });
    });

    describe('payloadEncrypt', function() {

        it('should return <Buffer 4c 2f>', function() {

            lorawanCrypto.payloadEncrypt(
                encBuffer, size,
                key,
                address,
                dir,
                sequenceCounter,
                decBuffer
            );

            // should be: hex 4c 2f
            assert.equal(decBuffer.compare(Buffer.from([0x4c, 0x2f])), 0);
        });
    });
});
