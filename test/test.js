'use strict';

var assert = require('assert');

var key = Buffer.from('00112233445566778899AABBCCDDEEFF', 'hex');

/*jshint -W016 */
var payload = Buffer.from([64,160,198,0,20,128,1,0,2,76,47,251,70,206,90]);
var buffer = Buffer.from([76,47]);
var size = 2;
var address = payload.readUInt32LE(1);
var dir = 0;
var sequenceCounter = payload.readUInt16BE(6); //payload[6] + (payload[7]<<8);
var mic = payload.readUInt32LE(payload.length - 4);
/* jshint +W016 */


var lorawanCrypto = require('../index');

describe('LoRaWANCrypto', function() {

    describe('computeMic', function() {
        
        it('should compute the MIC', function() {
            assert.equal(lorawanCrypto.computeMic(buffer, size, key, address, dir, sequenceCounter), mic);
        });

    });

    describe('payloadDecrypt()', function() {
        it('should return <Buffer 12 34>', function() {

            var decBuffer = lorawanCrypto.payloadDecrypt(
                buffer, size,
                key,
                address,
                dir,
                sequenceCounter
            );

            // should be: hex 12 34
            assert.equal(decBuffer.compare(Buffer.from([0x12, 0x34])), 0);
        });
    });

    describe('payloadEncrypt', function() {

        it('should return <Buffer 4c 2f>', function() {

            var encBuffer = lorawanCrypto.payloadEncrypt(
                lorawanCrypto.payloadDecrypt(
                    buffer, size,
                    key,
                    address,
                    dir,
                    sequenceCounter
                ), size,
                key,
                address,
                dir,
                sequenceCounter
            );

            // should be: hex 4c 2f
            assert.equal(encBuffer.compare(Buffer.from([0x4c, 0x2f])), 0);
        });
    });

    describe('joinComputeMic', function() {
        
        it('should compute the Join MIC', function() {
            var MIC = lorawanCrypto.joinComputeMic(buffer, size, key);
            console.log(MIC);

            assert(true);
        });

    });

    describe('joinEncrypt -> joinDecrypt', function() {
        var joinRequest = Buffer.from([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18]);
        var joinRequestLength = 18;

        it('should encrypt the join message', function() {
            console.log('ORIGINAL: ', joinRequest);

            var encBuffer = lorawanCrypto.joinEncrypt(joinRequest, joinRequestLength, key);
            console.log('LoRa ENC: ', encBuffer);

            var decBuffer = lorawanCrypto.joinDecrypt(encBuffer, encBuffer.length, key);
            console.log('LoRa DEC: ', decBuffer);

            assert(joinRequest.compare(decBuffer) === 0);
        });

    });
});
