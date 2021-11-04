# Simplified blockchain

# Veikimas

1. Paleidus programą pradedamas blokų kasimas ir į konsolę išvedamas dabar kasamo bloko numeris.
2. Sukuriami 5 potencialūs blokai sudaryti is ~100 atsitiktinai parinktų transakcijų.
3. Tuomet atsitiktinai pasirinkamas vienas iš tų penkių blokų-kandidatų ir su juo fiksuojant
maksimalų hash'ų bandymų skaičių atliekamas kasimo procesas. Jeigu po to
bandymų, nebuvo šiam atsitiktinai pasirinktam blokui-kandidatui surastas hash'as, tenkinantis Difficulty Targer reikalavimą, tas procesas
pakartojamas su kitu atsitiktinai pasirinktu likusiu kandidatu.
4. Jeigu procesą pakartojus su visais penkiais naujais blokais-kandidatais, nebuvo surastas reikiamų savybių hash'as, tuomet sumažinamas Difficulty Target.
       
       Mining block: 0
       - All blocks failed, reducing difficulty -
       Success, winner block: 0
       ----------------------------------
       Mining block: 1
       Success, winner block: 2
       ----------------------------------
       Mining block: 2
       Success, winner block: 0
       ...
      
Iškasus visus 10 blokų išvedama jų pagrindinė informacija, bei visos transakcijos.

       -----------------------------------------------
       Block 0 info:
                          Timestamp: 2021-11-04 23:07:43
             Number of transactions: 100
                         Difficulty: 2
                        Merkle root: 07c5ed654e0b3b5c9bece3f19ab6cf7c7dd1afdcf5cbb61509e6d9a09e5fae67
                              Nonce: 945952115
                            Version: v0.2

       Block 0 transactions:
       d596d360f9eef223b85ce6aea88d1a160dbd6f455671a26a05877f2a96b3aa34 -> 9152b93d721b6bc23ce0efa2b8be67c61c992b03b34935319f7fb86a26f4a330   amount: 42062
       19da5995fa95614ab480472a32b4ef4ebcf1a38db9c1bdd1f7f73260ae7c4bb8 -> e6a7fdf2c76fa7178124a4f70cfabc1b505e7057ff9e8a7554c40ca67b49e885   amount: 40777
       b374ec5f943e9de45e1301c4dbe089e84fbb4d26e56b5764b191db9c4816d552 -> 8041955c61092db12bcc0e91a67056b5f8b81af17538241dbe6ea62c15e3822f   amount: 24484
       4c0d7df82dc7a77de7a4aa5d64fa1271d054d6bffff4e0f55a2a64a6d1af6eeb -> 3bfc5ec71cb5b46cd685794c52070160b123c5ad0ce3dfd6291952b3c09e4dda   amount: 8637
       a263e49e832e11d34d1b40b3cb6478d747fa3c16695a466cf080cb103705d441 -> 2aeb53360ba50b5bc58ae83b425ef05fb692b49d53d2cedb9808420abf8d4cc9   amount: 59324
       6e2f75fa4fe7279f09acac7f847a3493d856f8df7f1602fd5c4c8426f3c1600d -> 8041c7ef29ffb9a59d9885cb36f0bcc1b8a1ee756738244f41269cb8095555ef   amount: 63579
       19da2ba5fa92824ab452572a3fd5ef4e8e01a38adac1bda307f73f81ae7c1bb8 -> 6e2f713a4fe7eb9f09a8ec7f843e3493d496f8df331602f99c4c84eaf3c1600d   amount: 97114
       19da4215fa94f94ab479c72a314cef4ea571a38c41c1bdca77f731f8ae7c3bb8 -> 8041b71c610b49b12beece91a89c56b51a781af39138243f7e6ea84815e3a22f   amount: 20316
       b374c8bf943c53e45eff61c4d9a689e82b1b4d24ab6b57401191d9524816b552 -> 8041f4ef292cb9a5ca9885f836f0e9c1b8deee759438247c4126c9b8098255ef   amount: 52213
       9152c38d721c00c23cfa3fa2b95367c626e92b045849354bef7fb90f26f4b330 -> 6e2f911a4fe9e99f09c8cc7f863c3493f476f8d1311602197c4c86e8f3c1800d   amount: 70395
       ...
       -----------------------------------------------
       Block 1 info:
                          Timestamp: 2021-11-04 23:07:43
             Number of transactions: 100
                         Difficulty: 3
                        Merkle root: faa79f5c52b654021b1a5a853a2f49cd022910a1f0834fae824305d847c0483b
                              Nonce: 619002262
                            Version: v0.2

       Block 1 transactions:
       3bfc6eb71cb6b36cd695694c53060160c113c5ae0be3dfe6191953b2c09e5dda -> 6e2f731a4fe7099f09aacc7f845c3493d676f8df511602fb7c4c8408f3c1600d   amount: 28787
       a263d59e832d21d34d0c40b3ca7478d738fa3c15795a465df080ca203705c441 -> e6a70de2c760a617813494f70df9bc1b604e7058fe9e8a8544c40da57b49f885   amount: 82766
       5d1ea0bcf6d88672766552a403cd959e858abb424005f1281ef37585d63e22bc -> 6e2f94cd07cc97836a76639814de89af967ecc533416021c2f046996e72233cd   amount: 45282
       3bfc40b71cb4d36cd677694c51260160a313c5ac2be3dfc8191951d2c09e3dda -> 2aeb5ca60ba5925bc583583b42e5f05fbf02b49dead2ced408084291bf8d4cc9   amount: 97597
       9152d9f03a01cab6afa996dd4701ced2c9b3ff86794935515237aec91a6766f0 -> 4c0d5c282dc59a7de783da5d62ed1271bf84d6bde2f4e0d48a2a6299d1af4eeb   amount: 82332
       6e2f9f3a4fe9cb9f09c6ec7f861e3493f296f8d1131602179c4c86caf3c1800d -> 8041991c610969b12bc0ce91a6bc56b5fc781af1b13824117e6ea66815e3822f   amount: 79394
       7f30b22b50fbfaa01ae9dd80984d45a4158709e34227133a8d5d98f904d2a11e -> c4850a90a54071f56f3142d5edc49af96dfc5e38c97c6882f2a2ed705927f663   amount: 78057
       3bfc7db71cb7a36cd6a4694c54f60160d013c5affbe3dff5191954a2c09e6dda -> 5d1e90e93ed9d68ef8c79b6e76292382f345e7c12e05f1184b3b76d5e2b08ffc   amount: 6148
       804103ef293bb9a5d998850736f0f8c1b8edee75a338248b4126d8b8099155ef -> f7b81773d8714f28924e25081e92cd2c7adf816997af9b9fd5d51e4e8c5a0996   amount: 91412
       8041c43c610c1bb12bfbee91a96e56b527981af46338244c9e6ea91a15e3b22f -> 7f30960b50f938a01acdbd80968b45a4f96709e18027131e6d5d963704d2811e   amount: 21185
       a263ba6e832b7ed34de110b3c8c178d71dca3c13c65a4632c080c87d3705a441 -> d596fbd1b65f8506702283e6fcd8ab0a5e3d6f47dd8d797333b3fc846a38e774   amount: 21121
       ...

# How to run:
        
Naudojant cmake:

       cmake build
       build/main
