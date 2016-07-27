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
                "LoRaMacCrypto.c",
                "crypto/aes.c",
                "crypto/cmac.c"
            ],
            "include_dirs": [
                "crypto"
            ],
            "link_settings": {
                "libraries": [ ]
            }
        }
    ]
}
