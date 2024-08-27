	// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <genesis.h>
#include <consensus/merkle.h>

#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>
#include <memory>

#include <chainparamsseeds.h>
#include <arith_uint256.h>
#include <pthread.h>

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

bool CChainParams::AddCheckPoint(const int &height, const uint256 &hash) const{

    auto it = std::find_if(checkpointData.mapCheckpoints.begin(), checkpointData.mapCheckpoints.end(),
                           [&](std::map<int, uint256>::value_type pair) { return pair.first >= height; });
    if (it != checkpointData.mapCheckpoints.end())
        return false;
    checkpointData.mapCheckpoints.insert(std::pair<const int, uint256>(height, hash));
    return true;
}



const CScript CChainParams::GetMinerScriptPubKey() const {
    return GetScriptForDestination(CBitcoinAddress(consensus.minerAddress).Get());
}
 




class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.powLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");


        consensus.nTargetTimespan = 48 * 60 * 60;  //48 hours between retarget
        consensus.nStakeTargetSpacing = 1 * 60;  //60 Sec
        consensus.nTargetSpacingWorkMax = 1 * consensus.nStakeTargetSpacing;  //60
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing; // 60 sec
        consensus.nStakeMinConfirmations = 30;
        consensus.nCoinbaseMaturity = 40;
        consensus.nDgwPastBlocks = 30;

        consensus.nStartMiningTime = 1667184351; 
  
	    consensus.nPowTargetSpacingCH = 187.5; //460.8 blocks 40%
	    consensus.nPowTargetSpacingGR = 125; //691.2 blocks 60%

	    consensus.powForkTime = 1670094000;  // Sat Dec 03 2022 19:00:00 GMT+0000    Sat Dec 03 2022 13:00:00 GMT-0600 (Central Standard Time)
        // hard fork
        consensus.minerAddress = "KXSKRhXkDrs7HZy2HkZNXo6fCv6fGARwTU ";
	     onsensus.KMForkHeight = 1103357;


        consensus.powTypeLimits.emplace_back(uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));   // curvehash limit
        consensus.powTypeLimits.emplace_back(uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));   // Minox limit

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");



        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x9f67f1835170e36cb4ec265db7d42542743bba39d9f0cc7f0bb73a7b900860f7");
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */

        pchMessageStart[0] = 0x31; //r
        pchMessageStart[1] = 0x8c;
        pchMessageStart[2] = 0xa2;
        pchMessageStart[3] = 0x59;

        vAlertPubKey = ParseHex("0487bc90524104c5ee1fe66cd28e9931f09dbf267d61be7918221c8b5fe02c6b640a63ead9c5fe139affcb0f5d5592e97c137b9a5793809db5e046d526f96bd38d");
        nDefaultPort = 12421;

        genesis = CreateGenesisBlock(1667184351, 500002008, 0x1f00ffff, 1, 0);
	
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x9f67f1835170e36cb4ec265db7d42542743bba39d9f0cc7f0bb73a7b900860f7"));
        assert(genesis.hashMerkleRoot == uint256S("0xed8f603c29caa485d2f1f6d631ef86132104a667a6a58544d36cb99c2ef0a51e"));
        
        //vSeeds.emplace_back("seeder.keymaker.cc");
        //vSeeds.emplace_back("seed.keymaker.cc");
 

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,46);  // Was 46 
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,73);  // Was 73
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,63);  // Was 63

        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E}; // xpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4}; // xprv

        // human readable prefix to bench32 address
        bech32_hrp = "key";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        nMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;



checkpointData = {
            {
                {0, uint256S("0x9f67f1835170e36cb4ec265db7d42542743bba39d9f0cc7f0bb73a7b900860f7")},
                {48511, uint256S("0xc6b561e68dd2c92bac6dbca02da252c3b95e0f2eb5aee5defaf97c62ed6dc16e")},
                {80000, uint256S("0xafb754681e5dcc126999ad3df9829ecc5d56d948170b76daaf96199a493b6a10")},
                {110279, uint256S("0x7155bf9437aff84cbfa9d896d7b601d0d49315155d7bee5e0ec09a4559c45568")},
                {143175, uint256S("0xec75c76a8e6c1dd16e42b62246693c508317989fff9ed9dbfaf2bcf0d82610d6")},
                {248447, uint256S("0x000000202d4e99641a682c14ccaf87518f7994a85dadddde5adef06a0aa8b298")},
                {300000, uint256S("0x0000000d1a98bfe17bbd68a1c95f6160ec43a9695f0414db12e96707289ea893")},
                {400000, uint256S("0xa4db466781db937347125617d27f17715fd993bb7a5018b0d031c3dcfdaa3adf")},
                {500000, uint256S("0x1dced76d5fb2bb24929984af1b1929b8eeb176d6fde092e5108e942cd898a14d")},
                {600000, uint256S("0x7ebcfda11a85a9035ec27070f22a2ed5a4feff589dbbaf16f7f54d41f8523fe")},
                {770801, uint256S("0xfe4ab81368922c47653990d6e73475bd4ecd311619a4c1f6096fdd3de23a0d0d")},
                {1014993, uint256S("0x52387119107a25c18d1a5f8a68e4c0fcd0e1b94dbb981ce0f528bedccac32e5d")},
                {1103348, uint256S("0x19ba26ff2e02db2e218d03a1994fcc28041f0e2f25ef0090ec3173c4d36ab702")},
                {1103356, uint256S("0xd7ee4242ecad8bd994dd22416758ac9adb531bdd7b74596ce28d31bb5c28bb52")}, 
               
            }
        };

       chainTxData = ChainTxData{
			// Data from rpc: getchaintxstats 0
			/* nTime    */   1712052278,
			/* nTxCount */  1759460,
			/* dTxRate  */   0.03936447595984607

         };


    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.BIP16Height = 0;
        consensus.BIP34Height = 0;
        consensus.powLimit = uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.nTargetTimespan = 24 * 60;  // 24 minutes
        consensus.nStakeTargetSpacing = 1 * 60;  // 1-minute block spacing
        consensus.nTargetSpacingWorkMax = 1 * consensus.nStakeTargetSpacing; // 24-minute
	    consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 1;
        consensus.nCoinbaseMaturity = 6; // 6 confirmations
        consensus.nDgwPastBlocks = 30;

	    consensus.nPowTargetSpacingCH = 187.5; //460.8 blocks 40%
	    consensus.nPowTargetSpacingGR = 125; //691.2 blocks 60%

	   consensus.powForkTime = 1670097600; // 12-3-2022 13:00

	   //consensus.isValid = 1666327253;

        consensus.powTypeLimits.emplace_back(uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));   // curvehash limit
        consensus.powTypeLimits.emplace_back(uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));   // Minox limit

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
	    consensus.nStartMiningTime = 1605440641;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xf4;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0xf3;
        pchMessageStart[3] = 0xbe;
        nDefaultPort = 22421;
        vAlertPubKey = ParseHex("048ce4dedd28c868cb39555c94575e92bdd8feba3407eb1f1d4910a01274366e00cf25e6396b7b9e3f12f6bbc0aa6c3530178e91c181c4506bbfcf33e359004b22");

        genesis = CreateGenesisBlock(1660653600, 500021210, 0x1f0fffff, 1, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xab3a9cb18a0e7103e8d087ce5cdb92526b93532f2f1904c21f8ae8a8e9288e8e"));
        assert(genesis.hashMerkleRoot == uint256S("0x6de80f3e1ed227ac5028ce6335c5f6096b7015dd013df7fd7781b98f1cfcd09d"));

        vFixedSeeds.clear();
        vSeeds.clear();

        // nodes with support for servicebits filtering should be at the top

        vFixedSeeds.clear();
        vSeeds.clear();


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,46);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,76);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,63);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // tprv

        // human readable prefix to bench32 address
        bech32_hrp = "tkey";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        nMiningRequiresPeers = 1;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
                {
                {0, uint256S("0xab3a9cb18a0e7103e8d087ce5cdb92526b93532f2f1904c21f8ae8a8e9288e8e")},
            }
        };

        chainTxData = ChainTxData{
                1660653600,
                0,
                0
        };

    }
};

/**
 * Regression test
 */

class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.BIP16Height = 0; // always enforce P2SH BIP16 on regtest
        consensus.BIP34Height = 0; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~arith_uint256(0) >> 28;
        consensus.nTargetTimespan = 3 * 24 * 60 * 60; // two weeks
        consensus.nStakeTargetSpacing = 1 * 60; // 1-minute block spacing
        consensus.nTargetSpacingWorkMax = 1 * consensus.nStakeTargetSpacing; //
        consensus.nPowTargetSpacing = consensus.nStakeTargetSpacing;
        consensus.nStakeMinConfirmations = 1; //
        consensus.nCoinbaseMaturity = 2;
        consensus.nDgwPastBlocks = 3;


        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nStartMiningTime = 1605440641;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0x4e;
        pchMessageStart[2] = 0x5e;
        pchMessageStart[3] = 0x4f;
        nDefaultPort = 32421;
        vAlertPubKey = ParseHex("0406e2cfe8d4858168dac6ed66b84a7a3b44a23180bc1188b0bfdd43b0be91637298897059bf7735b2c9db56d9b49797b7e373067710f49b4ae9c6a51646ea6b3a");

        genesis = CreateGenesisBlock(1660653000, 500010257, 0x1f0fffff, 1, 0);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x36eff81ab9e9e2c4d0d86a72fd5e4436409ad5e2d630b53f1ea9dbb51b22fe4b"));
        assert(genesis.hashMerkleRoot == uint256S("0xf5412d0a27c4dec4ee5705abf3e63c2009125162a3121bfc13da285eba1fd943"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        checkpointData = {
            {
                {0, uint256S("0x36eff81ab9e9e2c4d0d86a72fd5e4436409ad5e2d630b53f1ea9dbb51b22fe4b")},
            }
        };

        chainTxData = ChainTxData{
            1605440641,
            0,
            0
        };
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,50);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,156);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF}; // tpub
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94}; // tprv

        bech32_hrp = "rtkey";

        nMiningRequiresPeers = 0;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
    }
};

static std::unique_ptr <CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr <CChainParams> CreateChainParams(const std::string &chain) {
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string &network) {
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
