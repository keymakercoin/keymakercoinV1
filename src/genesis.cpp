// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2022 The Keymaker Coin developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <genesis.h>
#include <arith_uint256.h>
#include <chain.h>
#include <keymaker.h>
#include <consensus/merkle.h>
#include <primitives/block.h>
#include <uint256.h>
#include <utilstrencodings.h>

#include <bignum.h>
#include <util.h>

bool static ScanHash(const CBlockHeader *pblock, uint32_t &nNonce, uint256 *phash, uint32_t endNonce) {
    while (true) {
        nNonce++;
        if (nNonce % 10000 == 0) {
            printf("nTime %08u: nBits 0x%08x nonce %08u\n", pblock->nTime, pblock->nBits, nNonce);
        }

        // Calculate Keymaker for given block and nonce
        Keymaker(pblock, nNonce, phash);

        // Return the nonce if the hash has at least some zero bits,
        // caller will check if it has enough to reach the target
        if (((uint16_t *) phash)[15] == 0)
            return true;

        // If nothing found after trying for a while, return -1
        if (nNonce > endNonce)
            return false;
    }
}

CBlock CreateGenesisBlock(const char *pszTimestamp, const CScript &genesisOutputScript, uint32_t nTimeTx, uint32_t nTimeBlock, uint32_t nNonce, uint32_t nBits, int32_t nVersion,
                                 const CAmount &genesisReward) {
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig =
            CScript() << 486604799 << CScriptNum(9999) << std::vector<unsigned char>((const unsigned char *) pszTimestamp, (const unsigned char *) pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = 1369000 * COIN;
    txNew.vout[0].scriptPubKey = genesisOutputScript;
    txNew.nTime = nTimeTx;

    CBlock genesis;
    genesis.nTime = nTimeBlock;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}


CBlock CreateGenesisBlock(uint32_t nTimeBlock, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount &genesisReward) {
    const char *pszTimestamp = "NY Times 06/07/2022 Fed Hurtles Toward Another Big Rate Increase as Inflation Lingers";
    const CScript genesisOutputScript = CScript() << ParseHex("0440d24ae67d1eeab11a5a66193cb2760fea9e6d4504b9fcecf9a047074a534956ed79b28e6d3c455e7da37fa739719a3a0e8e56db6262c000fde90673180eeec6") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTimeBlock - 3600, nTimeBlock, nNonce, nBits, nVersion, genesisReward);
}

struct thread_data {
    CBlock block;
    uint256 powLimit;
};

