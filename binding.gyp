{
    "targets": [
        {
            "target_name": "lorawan-crypto",
            "type": "<(library)",
            "cflags": [
                "Wall",
                "Wextra"
            ],
            "define": [ ],
            "sources": [
                "LoRaMac/LoRaMacCrypto.c",
                "LoRaMac/crypto/aes.c",
                "LoRaMac/crypto/cmac.c"
            ],
            "include_dirs": [
                "LoRaMac/crypto"
            ],
            "link_settings": {
                "libraries": [ ]
            }
        }
    ]
}
