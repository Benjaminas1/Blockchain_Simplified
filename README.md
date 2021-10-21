# Simplified blockchain

# Užduotis

1. Sugeneruoti ~1000 tinklo vartotojų, kurie turėtų bent tris atributus:

- vardą
- viešąjį hash raktą
- valiutos atsitiktinį balansą

2. Sugeneruoti ~10000 naujų transakcijų pool'ą, kurios turėtų šiuos atributus:

- transakcijos ID (kitų transakcijos laukų hash'as)
- siuntėjas (viešasis raktas)
- gavėjas (viešasis raktas)
- suma

3. Iš transakcijų pool'o atsitiktinai pasirinkti 100-ą transakcijų, kurias bandysime įdėti į naują bloką.

4. Realizuokite naujų blokų kasimo (angl. mining) Proof-of-Work (PoW) tipo procesą, kurio tikslas yra surasti naujam blokui hash'ą, tenkinantį `Difficulty Target` reikalavimą, t.y., hash'o pradžioje esančių nulių tam tikrą skaičių.

5. Suradus tokį naujo bloko hash'ą:

- į naują bloką priskirtas transakcijas ištrinkite iš transakcijų pool'o;
- "įvykdykite" transakcijas, t.y., atnaujinkite tinklo vartotojų balansus;
- naują bloką pridėkite prie blockchain grandinės.

6. Kartoti 3-5 žingsnius tol, kol yra laisvų transakcijų.

# Veikimas

Paleidus programą pradedamas blokų kasimas ir į konsolę išvedamas dabar kasamo bloko numeris
       
        Mining block: 0
        Mining block: 1
        Mining block: 2
        ...
      
Iškasus visus 10 blokų išvedama jų pagrindinė informacija.

        Block 0 info:
                                Hash: 0004d15fdac15de56e1848d5a6a18e65f8726e3871a8d511e5666d38cc6fd5a7
                           Timestamp: 2021-10-21 18:53:48
              Number of transactions: 100
                          Difficulty: 3
                         Merkle root: f4f1d7d2e48f27fb2927d8d5b2f05461077f14855786e28bd185b9eb1553f953
                               Nonce: 619851518
                             Version: v0.1
        -----------------------------------------------
        Block 1 info:
                                Hash: 0005c022eac16cd29f1849c479b18e74e5a36e39607be511f4539e38cd5ed5a7
                           Timestamp: 2021-10-21 18:53:49
              Number of transactions: 100
                          Difficulty: 3
                         Merkle root: d4f6f8d4b287e076f4fc92f0a9c882f89e61c468f7d0b648ebee4050c4f3cdf9
                               Nonce: 619940249
                             Version: v0.1
        -----------------------------------------------
        Block 2 info:
                                Hash: 000f1761b54b6f33b74a47e7b6be0c4344fd940381eae66bc1e4ec3a95a10a27
                           Timestamp: 2021-10-21 18:53:49
              Number of transactions: 100
                          Difficulty: 3
                         Merkle root: 69f9371bae7157a7f366b837d526bd782ad4629467c9948313b90c9652a43fac
                               Nonce: 61939763
                             Version: v0.1

# How to run:
        
        g++ includes/functions.cpp main.cpp -o3 -o main
