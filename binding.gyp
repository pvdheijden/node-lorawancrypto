{
    "targets": [
        {
            "target_name": "lorawancrypto",
            "define": [ ],
            "sources": [
                "node-LoRaWANCrypto.cc",
                "LoRaMac/LoRaMacCrypto.c",
                "LoRaMac/crypto/aes.c",
                "LoRaMac/crypto/cmac.c"
            ],
            "include_dirs": [
                "./LoRaMac/crypto"
            ],
            "link_settings": {
                "libraries": [ ]
            }
        }
    ]
}
