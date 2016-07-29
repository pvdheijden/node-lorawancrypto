#include <v8.h>
#include <node.h>
#include <node_buffer.h>

extern "C" {
    #include "LoraMac/LoRaMacCrypto.h"
}

using namespace v8;

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
    if (    /*!args[0]->IsBuffer()      || */
            !args[1]->IsNumber()        ||
            /*!args[2]->IsBuffer()      || */
            !args[3]->IsNumber()        ||
            !args[4]->IsNumber()        ||
            !args[5]->IsNumber()        //||
            /*!args[6]->IsBuffer() */  )
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
    if (    /*!args[0]->IsBuffer()      || */
            !args[1]->IsNumber()        ||
            /*!args[2]->IsBuffer()      || */
            !args[3]->IsNumber()        ||
            !args[4]->IsNumber()        ||
            !args[5]->IsNumber()        //||
            /*!args[6]->IsBuffer() */  )
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

    LoRaMacPayloadDecrypt( buffer, size, key, address, dir, sequenceCounter, decBuffer );
}



void init(Handle <Object> exports, Handle<Object> module) {
    NODE_SET_METHOD(exports, "payloadEncrypt", payloadEncrypt);
    NODE_SET_METHOD(exports, "payloadDecrypt", payloadDecrypt);
}

NODE_MODULE(lorawan_crypto, init)


