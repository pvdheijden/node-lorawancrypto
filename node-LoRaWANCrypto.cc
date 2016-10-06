#include <stdio.h>

#include <v8.h>
#include <node.h>
#include <node_buffer.h>

extern "C" {
    #include "LoRaMacCrypto.h"
}

using namespace v8;

/*!
 * Computes the LoRaMAC frame MIC field
 *
 * \param [IN]  buffer          - Data buffer
 * \param [IN]  size            - Data buffer size
 * \param [IN]  key             - AES key to be used
 * \param [IN]  address         - Frame address
 * \param [IN]  dir             - Frame direction [0: uplink, 1: downlink]
 * \param [IN]  sequenceCounter - Frame sequence counter
 * \param [OUT] mic             - Computed MIC field
 */
void computeMic(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 6) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    // Check the argument types
    if (    !node::Buffer::HasInstance(args[0]) ||
            !args[1]->IsNumber()                ||
            !node::Buffer::HasInstance(args[2]) ||
            !args[3]->IsNumber()                ||
            !args[4]->IsNumber()                ||
            !args[5]->IsNumber()    )
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    const uint8_t* buffer = (const uint8_t *)node::Buffer::Data(args[0]);
    uint16_t size = args[1]->NumberValue();
    const uint8_t* key = (const uint8_t *)node::Buffer::Data(args[2]);
    uint32_t address = args[3]->NumberValue();
    uint8_t dir = args[4]->NumberValue();
    uint32_t sequenceCounter = args[5]->NumberValue();
    uint32_t mic;

    LoRaMacComputeMic( buffer, size, key, address, dir, sequenceCounter, &mic );

    Local<Number> retval = v8::Number::New(isolate, mic);
    args.GetReturnValue().Set(retval); 
}


/*!
 * Computes the LoRaMAC payload encryption
 *
 * Wrapper for: LoRaMacPayloadEncrypt
 * \param [IN]  buffer          - Data buffer
 * \param [IN]  size            - Data buffer size
 * \param [IN]  key             - AES key to be used
 * \param [IN]  address         - Frame address
 * \param [IN]  dir             - Frame direction [0: uplink, 1: downlink]
 * \param [IN]  sequenceCounter - Frame sequence counter
 * \param [OUT] encBuffer       - Encrypted buffer
 */
void payloadEncrypt(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 7) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    // Check the argument types
    if (    !node::Buffer::HasInstance(args[0]) ||
            !args[1]->IsNumber()                ||
            !node::Buffer::HasInstance(args[2]) ||
            !args[3]->IsNumber()                ||
            !args[4]->IsNumber()                ||
            !args[5]->IsNumber()                ||
            !node::Buffer::HasInstance(args[6]) )
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    const uint8_t* buffer = (const uint8_t *)node::Buffer::Data(args[0]);
    uint16_t size = args[1]->NumberValue();
    const uint8_t* key = (const uint8_t *)node::Buffer::Data(args[2]);
    uint32_t address = args[3]->NumberValue();
    uint8_t dir = args[4]->NumberValue();
    uint32_t sequenceCounter = args[5]->NumberValue();
    uint8_t* encBuffer = (uint8_t *)node::Buffer::Data(args[6]);

    args.GetReturnValue().SetNull();

    LoRaMacPayloadEncrypt( buffer, size, key, address, dir, sequenceCounter, encBuffer );
}

/*!
 * Computes the LoRaMAC payload decryption
 *
 * Wrapper for: LoRaMacPayloadDecrypt
 * \param [IN]  buffer          - Data buffer
 * \param [IN]  size            - Data buffer size
 * \param [IN]  key             - AES key to be used
 * \param [IN]  address         - Frame address
 * \param [IN]  dir             - Frame direction [0: uplink, 1: downlink]
 * \param [IN]  sequenceCounter - Frame sequence counter
 * \param [OUT] decBuffer       - Decrypted buffer
 */
void payloadDecrypt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 7) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    // Check the argument types
    if (    !node::Buffer::HasInstance(args[0]) ||
            !args[1]->IsNumber()                ||
            !node::Buffer::HasInstance(args[2]) ||
            !args[3]->IsNumber()                ||
            !args[4]->IsNumber()                ||
            !args[5]->IsNumber()                ||
            !node::Buffer::HasInstance(args[6]) )
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    const uint8_t* buffer = (const uint8_t *)node::Buffer::Data(args[0]);
    uint16_t size = args[1]->NumberValue();
    const uint8_t* key = (const uint8_t *)node::Buffer::Data(args[2]);
    uint32_t address = args[3]->NumberValue();
    uint8_t dir = args[4]->NumberValue();
    uint32_t sequenceCounter = args[5]->NumberValue();
    uint8_t* decBuffer = (uint8_t *)node::Buffer::Data(args[6]);

    args.GetReturnValue().SetNull();

    LoRaMacPayloadDecrypt(buffer, size, key, address, dir, sequenceCounter, decBuffer);
}

/*!
 * Computes the LoRaMAC Join Request frame MIC field
 *
 * Wrapper for: LoRaMacJoinComputeMic
 * \param [IN]  buffer          - Data buffer
 * \param [IN]  size            - Data buffer size
 * \param [IN]  key             - AES key to be used
 * \param [OUT] mic             - Computed MIC field
 */
void joinComputeMic(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 3) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    // Check the argument types
    if (    !node::Buffer::HasInstance(args[0]) ||
            !args[1]->IsNumber()                ||
            !node::Buffer::HasInstance(args[2]) )
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    const uint8_t* buffer = (const uint8_t *)node::Buffer::Data(args[0]);
    uint16_t size = args[1]->NumberValue();
    const uint8_t* key = (const uint8_t *)node::Buffer::Data(args[2]);
    uint32_t mic;

    LoRaMacJoinComputeMic(buffer, size, key, &mic);

    Local<Number> retval = v8::Number::New(isolate, mic);
    args.GetReturnValue().Set(retval);
}

/*!
 * Computes the LoRaMAC join frame decryption
 *
 * Wrapper for: LoRaMacJoinEncrypt
 * \param [IN]  buffer          - Data buffer
 * \param [IN]  size            - Data buffer size
 * \param [IN]  key             - AES key to be used
 * \param [OUT] encBuffer       - Encrypted buffer
 */
void joinEncrypt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 4) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    // Check the argument types
    if (    !node::Buffer::HasInstance(args[0]) ||
            !args[1]->IsNumber()                ||
            !node::Buffer::HasInstance(args[2]) ||
            !node::Buffer::HasInstance(args[3]) )
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    const uint8_t* buffer = (const uint8_t *)node::Buffer::Data(args[0]);
    uint16_t size = args[1]->NumberValue();
    const uint8_t* key = (const uint8_t *)node::Buffer::Data(args[2]);
    uint8_t* encBuffer = (uint8_t *)node::Buffer::Data(args[3]);

    args.GetReturnValue().SetNull();

    LoRaMacJoinEncrypt(buffer, size, key, encBuffer);
}

/*!
 * Computes the LoRaMAC join frame decryption
 *
 * Wrapper for: LoRaMacJoinDecrypt
 * \param [IN]  buffer          - Data buffer
 * \param [IN]  size            - Data buffer size
 * \param [IN]  key             - AES key to be used
 * \param [OUT] decBuffer       - Decrypted buffer
 */
void joinDecrypt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 4) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    // Check the argument types
    if (    !node::Buffer::HasInstance(args[0]) ||
            !args[1]->IsNumber()                ||
            !node::Buffer::HasInstance(args[2]) ||
            !node::Buffer::HasInstance(args[3]) )
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    const uint8_t* buffer = (const uint8_t *)node::Buffer::Data(args[0]);
    uint16_t size = args[1]->NumberValue();
    const uint8_t* key = (const uint8_t *)node::Buffer::Data(args[2]);
    uint8_t* decBuffer = (uint8_t *)node::Buffer::Data(args[3]);

    args.GetReturnValue().SetNull();

    LoRaMacJoinDecrypt(buffer, size, key, decBuffer);
}

/*!
 * Computes the LoRaMAC OTAA session keys
 *
 * Wrapper for: LoRaMacJoinComputeSKeys
 * \param [IN]  key             - AES key to be used
 * \param [IN]  appNonce        - Application nonce
 * \param [IN]  devNonce        - Device nonce
 * \param [OUT] nwkSKey         - Network session key
 * \param [OUT] appSKey         - Application session key
 */
void joinComputeSKeys(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 5) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    // Check the argument types
    if (    !node::Buffer::HasInstance(args[0]) ||
            !node::Buffer::HasInstance(args[1]) ||
            !args[2]->IsNumber()                ||
            !node::Buffer::HasInstance(args[3]) ||
            !node::Buffer::HasInstance(args[4]) )
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    const uint8_t* key = (const uint8_t *)node::Buffer::Data(args[0]);
    const uint8_t* appNonce = (const uint8_t *)node::Buffer::Data(args[1]);
    const uint16_t devNonce = args[2]->NumberValue();
    uint8_t* nwkSKey = (uint8_t *)node::Buffer::Data(args[3]);
    uint8_t* appSKey = (uint8_t *)node::Buffer::Data(args[4]);

    args.GetReturnValue().SetNull();

    LoRaMacJoinComputeSKeys(key, appNonce, devNonce, nwkSKey, appSKey);
}

void init(Handle <Object> exports, Handle<Object> module) {
    NODE_SET_METHOD(exports, "computeMic", computeMic);
    NODE_SET_METHOD(exports, "payloadDecrypt", payloadDecrypt);
    NODE_SET_METHOD(exports, "payloadEncrypt", payloadEncrypt);
    NODE_SET_METHOD(exports, "joinComputeMic", joinComputeMic);
    NODE_SET_METHOD(exports, "joinDecrypt", joinDecrypt);
    NODE_SET_METHOD(exports, "joinEncrypt", joinEncrypt);
    NODE_SET_METHOD(exports, "joinComputeSKeys", joinComputeSKeys);
}

NODE_MODULE(lorawan_crypto, init)


