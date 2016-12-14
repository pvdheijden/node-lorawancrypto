'use strict';

var assert = require('assert');


/*jshint -W016 */
/*

//var payload = Buffer.from([64, 160,198,0,20, 128, 1,0, 2, 76,47, 251,70,206,90]);
var buffer = Buffer.from([76,47]);
var size = 2;
var address = payload.readUInt32LE(1);
var dir = 0;
var sequenceCounter = payload.readUInt16BE(6); //payload[6] + (payload[7]<<8);
var mic = payload.readUInt32LE(payload.length - 4);
*/
/* jshint +W016 */

var payload = Buffer.from('40F17DBE4900020001954378762B11FF0D', 'hex');  // payload => 'test'
/*
MHDR:       40
FHDR:
    DevAddr:    F17DBE49
    Fctl:       00
    Fcnt:       0200
Fport:      01
Data:       95437876
MIC:        2B11FF0D
*/
var address = payload.readUInt32LE(1);
var data = Buffer.from('95437876', 'hex');
var size = 4;
var sequenceCounter = payload.readUInt16LE(6); //payload[6] + (payload[7]<<8);
var dir = 0;
var mic = payload.readUInt32LE(payload.length - 4);

var NwkSKey = Buffer.from('44024241ed4ce9a68c6a8bc055233fd3', 'hex');
var AppSKey = Buffer.from('ec925802ae430ca77fd3dd73cb2cc588', 'hex');


var joinRequestPayload = Buffer.from('001032547698badcfe08871a000ba30400b61289518c80', 'hex');
var AppKey = Buffer.from('6DD49E413402C1C4AC53AB1805F0A714', 'hex');


var lorawanCrypto = require('../index');

describe('LoRaWANCrypto', function() {

    describe('computeMic', function() {
        
        it('should compute the MIC', function() {
            var checkMic = lorawanCrypto.computeMic(payload.slice(0, -4), 13, NwkSKey, address, dir, sequenceCounter); 
            assert.equal(checkMic, mic);
        });

    });

    describe('payloadDecrypt()', function() {
        it('[decrypt] should return \'test\'', function() {

            var decBuffer = lorawanCrypto.payloadDecrypt(data, size, AppSKey, address, dir, sequenceCounter);
            assert.equal(decBuffer.toString('utf-8'), 'test');
        });
    });

    describe('payloadEncrypt', function() {

        it('[decrypt, encrypt] should return original encrypted buffer', function() {

            var encBuffer = lorawanCrypto.payloadEncrypt(
                lorawanCrypto.payloadDecrypt(data, size, AppSKey, address, dir, sequenceCounter), 
                size, AppSKey, address, dir, sequenceCounter);

            // should be: hex 4c 2f
            assert.equal(encBuffer.compare(data), 0);
        });
    });

    describe('joinComputeMic', function() {
        
        it('should compute the Join MIC', function() {
            var joinRequestData = joinRequestPayload.slice(0, -4);
            var joinRequestDataSize = joinRequestData.length;
            var joinRequestMIC = joinRequestPayload.slice(joinRequestDataSize).readUInt32LE();
            console.log('2156679561');
            console.log(joinRequestMIC);

            var calcMIC = lorawanCrypto.joinComputeMic(joinRequestData, joinRequestData.length, AppKey);
            console.log(calcMIC);

            assert.equal(joinRequestMIC, calcMIC);
        });
    });

    describe('joinEncrypt -> joinDecrypt', function() {
        var joinRequest = Buffer.from([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]);
        var joinRequestLength = 16;

        it('should encrypt the join message', function() {
            console.log('ORIGINAL: ', joinRequest);

            encBuffer = lorawanCrypto.joinEncrypt(joinRequest, joinRequestLength, AppSKey);
            console.log('LoRa ENC: ', encBuffer);

            decBuffer = lorawanCrypto.joinDecrypt(encBuffer, encBuffer.length, AppSKey);
            console.log('LoRa DEC: ', decBuffer);

            assert(joinRequest.compare(decBuffer) === 0);
        });

    });
});
