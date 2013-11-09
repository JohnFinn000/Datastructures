/*
 * =====================================================================================
 *
 *       Filename:  hilbert_tables.h
 *
 *    Description:  To clear up clutter these tables have been seperated to their
 *                  own header file. They are referenced by functions from pointer.
 *
 *        Version:  1.0
 *        Created:  04/17/2013 01:44:25 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  John Finn (), johnvincentfinn@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

// These are the base tables that are used to generate larger tables
const uint8_t hilbert_table[] = {
    0, 1, 3, 2,
    0, 3, 1, 2,
    2, 3, 1, 0,
    2, 1, 3, 0,
};

const uint8_t hilbert_state_table[] = {
    1, 0, 3, 0,
    0, 2, 1, 1,
    2, 1, 2, 3,
    3, 3, 0, 2,
};


const uint8_t xy_table_4[] = {
    0, 1, 3, 2,
    0, 2, 3, 1,
    3, 2, 0, 1,
    3, 1, 0, 2,
};

const uint8_t xy_state_table_4[] = {
    1, 0, 0, 3,
    0, 1, 1, 2,
    3, 2, 2, 1,
    2, 3, 3, 0,
};

/*
              old_state                                                 new_state                                                                                    
             /               partial hilbert value                      /                                  
        ____/                /                                     ____/   X       Y                      
        |   |_______________/                                      |   |_______|________                 
        |   |               |                                      |   |       |       |                
index   |0 0|0 0 0 0 0 0 0 0|                              value   |0 0|0 0 0 0|0 0 0 0|               
        |___|_______________|                                      |___|_______|_______|              

*/

    /*
     * 
     * the xy_state_table gets bitshifted 8 spaces left so instead of doing that the whole table contains that number already shifted
     * x values are symetric so this could potentially be halved
     */
    // this uses 2048 bytes of memory
    // personally my computer has enough ram that I can actually 
    // install and then run battlefield 2 from a ram drive so I don't view this large of a table as a problem
    // The lookup tables for just one hilbert value is 32 bytes this is 
    // 32 times larger to cut the number of lookups by a fourth so it would be a good idea
    // to see if I should instead waste this amount of space for a better cause or if this is really worth it
    
const uint16_t xy_table_256[1024] = {
00000,0X110,0X111,0X201,0X102,0X003,0X013,0X312,0X122,0X023,0X033,0X332,0X231,0X321,0X320,0X030,
0X140,0X041,0X051,0X350,0X060,0X170,0X171,0X261,0X062,0X172,0X173,0X263,0X353,0X252,0X242,0X143,
0X144,0X045,0X055,0X354,0X064,0X174,0X175,0X265,0X066,0X176,0X177,0X267,0X357,0X256,0X246,0X147,
0X237,0X327,0X326,0X036,0X335,0X234,0X224,0X125,0X315,0X214,0X204,0X105,0X006,0X116,0X117,0X207,
0X108,0X009,0X019,0X318,0X028,0X138,0X139,0X229,0X02A,0X13A,0X13B,0X22B,0X31B,0X21A,0X20A,0X10B,
0X00C,0X11C,0X11D,0X20D,0X10E,0X00F,0X01F,0X31E,0X12E,0X02F,0X03F,0X33E,0X23D,0X32D,0X32C,0X03C,
0X04C,0X15C,0X15D,0X24D,0X14E,0X04F,0X05F,0X35E,0X16E,0X06F,0X07F,0X37E,0X27D,0X36D,0X36C,0X07C,
0X37B,0X27A,0X26A,0X16B,0X25B,0X34B,0X34A,0X05A,0X259,0X349,0X348,0X058,0X168,0X069,0X079,0X378,
0X188,0X089,0X099,0X398,0X0A8,0X1B8,0X1B9,0X2A9,0X0AA,0X1BA,0X1BB,0X2AB,0X39B,0X29A,0X28A,0X18B,
0X08C,0X19C,0X19D,0X28D,0X18E,0X08F,0X09F,0X39E,0X1AE,0X0AF,0X0BF,0X3BE,0X2BD,0X3AD,0X3AC,0X0BC,
0X0CC,0X1DC,0X1DD,0X2CD,0X1CE,0X0CF,0X0DF,0X3DE,0X1EE,0X0EF,0X0FF,0X3FE,0X2FD,0X3ED,0X3EC,0X0FC,
0X3FB,0X2FA,0X2EA,0X1EB,0X2DB,0X3CB,0X3CA,0X0DA,0X2D9,0X3C9,0X3C8,0X0D8,0X1E8,0X0E9,0X0F9,0X3F8,
0X2F7,0X3E7,0X3E6,0X0F6,0X3F5,0X2F4,0X2E4,0X1E5,0X3D5,0X2D4,0X2C4,0X1C5,0X0C6,0X1D6,0X1D7,0X2C7,
0X3B7,0X2B6,0X2A6,0X1A7,0X297,0X387,0X386,0X096,0X295,0X385,0X384,0X094,0X1A4,0X0A5,0X0B5,0X3B4,
0X3B3,0X2B2,0X2A2,0X1A3,0X293,0X383,0X382,0X092,0X291,0X381,0X380,0X090,0X1A0,0X0A1,0X0B1,0X3B0,
0X0C0,0X1D0,0X1D1,0X2C1,0X1C2,0X0C3,0X0D3,0X3D2,0X1E2,0X0E3,0X0F3,0X3F2,0X2F1,0X3E1,0X3E0,0X0F0,


0X100,0X001,0X011,0X310,0X020,0X130,0X131,0X221,0X022,0X132,0X133,0X223,0X313,0X212,0X202,0X103,
0X004,0X114,0X115,0X205,0X106,0X007,0X017,0X316,0X126,0X027,0X037,0X336,0X235,0X325,0X324,0X034,
0X044,0X154,0X155,0X245,0X146,0X047,0X057,0X356,0X166,0X067,0X077,0X376,0X275,0X365,0X364,0X074,
0X373,0X272,0X262,0X163,0X253,0X343,0X342,0X052,0X251,0X341,0X340,0X050,0X160,0X061,0X071,0X370,
0X080,0X190,0X191,0X281,0X182,0X083,0X093,0X392,0X1A2,0X0A3,0X0B3,0X3B2,0X2B1,0X3A1,0X3A0,0X0B0,
0X1C0,0X0C1,0X0D1,0X3D0,0X0E0,0X1F0,0X1F1,0X2E1,0X0E2,0X1F2,0X1F3,0X2E3,0X3D3,0X2D2,0X2C2,0X1C3,
0X1C4,0X0C5,0X0D5,0X3D4,0X0E4,0X1F4,0X1F5,0X2E5,0X0E6,0X1F6,0X1F7,0X2E7,0X3D7,0X2D6,0X2C6,0X1C7,
0X2B7,0X3A7,0X3A6,0X0B6,0X3B5,0X2B4,0X2A4,0X1A5,0X395,0X294,0X284,0X185,0X086,0X196,0X197,0X287,
0X088,0X198,0X199,0X289,0X18A,0X08B,0X09B,0X39A,0X1AA,0X0AB,0X0BB,0X3BA,0X2B9,0X3A9,0X3A8,0X0B8,
0X1C8,0X0C9,0X0D9,0X3D8,0X0E8,0X1F8,0X1F9,0X2E9,0X0EA,0X1FA,0X1FB,0X2EB,0X3DB,0X2DA,0X2CA,0X1CB,
0X1CC,0X0CD,0X0DD,0X3DC,0X0EC,0X1FC,0X1FD,0X2ED,0X0EE,0X1FE,0X1FF,0X2EF,0X3DF,0X2DE,0X2CE,0X1CF,
0X2BF,0X3AF,0X3AE,0X0BE,0X3BD,0X2BC,0X2AC,0X1AD,0X39D,0X29C,0X28C,0X18D,0X08E,0X19E,0X19F,0X28F,
0X37F,0X27E,0X26E,0X16F,0X25F,0X34F,0X34E,0X05E,0X25D,0X34D,0X34C,0X05C,0X16C,0X06D,0X07D,0X37C,
0X27B,0X36B,0X36A,0X07A,0X379,0X278,0X268,0X169,0X359,0X258,0X248,0X149,0X04A,0X15A,0X15B,0X24B,
0X23B,0X32B,0X32A,0X03A,0X339,0X238,0X228,0X129,0X319,0X218,0X208,0X109,0X00A,0X11A,0X11B,0X20B,
0X10C,0X00D,0X01D,0X31C,0X02C,0X13C,0X13D,0X22D,0X02E,0X13E,0X13F,0X22F,0X31F,0X21E,0X20E,0X10F,


0X2FF,0X3EF,0X3EE,0X0FE,0X3FD,0X2FC,0X2EC,0X1ED,0X3DD,0X2DC,0X2CC,0X1CD,0X0CE,0X1DE,0X1DF,0X2CF,
0X3BF,0X2BE,0X2AE,0X1AF,0X29F,0X38F,0X38E,0X09E,0X29D,0X38D,0X38C,0X09C,0X1AC,0X0AD,0X0BD,0X3BC,
0X3BB,0X2BA,0X2AA,0X1AB,0X29B,0X38B,0X38A,0X09A,0X299,0X389,0X388,0X098,0X1A8,0X0A9,0X0B9,0X3B8,
0X0C8,0X1D8,0X1D9,0X2C9,0X1CA,0X0CB,0X0DB,0X3DA,0X1EA,0X0EB,0X0FB,0X3FA,0X2F9,0X3E9,0X3E8,0X0F8,
0X3F7,0X2F6,0X2E6,0X1E7,0X2D7,0X3C7,0X3C6,0X0D6,0X2D5,0X3C5,0X3C4,0X0D4,0X1E4,0X0E5,0X0F5,0X3F4,
0X2F3,0X3E3,0X3E2,0X0F2,0X3F1,0X2F0,0X2E0,0X1E1,0X3D1,0X2D0,0X2C0,0X1C1,0X0C2,0X1D2,0X1D3,0X2C3,
0X2B3,0X3A3,0X3A2,0X0B2,0X3B1,0X2B0,0X2A0,0X1A1,0X391,0X290,0X280,0X181,0X082,0X192,0X193,0X283,
0X184,0X085,0X095,0X394,0X0A4,0X1B4,0X1B5,0X2A5,0X0A6,0X1B6,0X1B7,0X2A7,0X397,0X296,0X286,0X187,
0X377,0X276,0X266,0X167,0X257,0X347,0X346,0X056,0X255,0X345,0X344,0X054,0X164,0X065,0X075,0X374,
0X273,0X363,0X362,0X072,0X371,0X270,0X260,0X161,0X351,0X250,0X240,0X141,0X042,0X152,0X153,0X243,
0X233,0X323,0X322,0X032,0X331,0X230,0X220,0X121,0X311,0X210,0X200,0X101,0X002,0X112,0X113,0X203,
0X104,0X005,0X015,0X314,0X024,0X134,0X135,0X225,0X026,0X136,0X137,0X227,0X317,0X216,0X206,0X107,
0X008,0X118,0X119,0X209,0X10A,0X00B,0X01B,0X31A,0X12A,0X02B,0X03B,0X33A,0X239,0X329,0X328,0X038,
0X148,0X049,0X059,0X358,0X068,0X178,0X179,0X269,0X06A,0X17A,0X17B,0X26B,0X35B,0X25A,0X24A,0X14B,
0X14C,0X04D,0X05D,0X35C,0X06C,0X17C,0X17D,0X26D,0X06E,0X17E,0X17F,0X26F,0X35F,0X25E,0X24E,0X14F,
0X23F,0X32F,0X32E,0X03E,0X33D,0X23C,0X22C,0X12D,0X31D,0X21C,0X20C,0X10D,0X00E,0X11E,0X11F,0X20F,


0X3FF,0X2FE,0X2EE,0X1EF,0X2DF,0X3CF,0X3CE,0X0DE,0X2DD,0X3CD,0X3CC,0X0DC,0X1EC,0X0ED,0X0FD,0X3FC,
0X2FB,0X3EB,0X3EA,0X0FA,0X3F9,0X2F8,0X2E8,0X1E9,0X3D9,0X2D8,0X2C8,0X1C9,0X0CA,0X1DA,0X1DB,0X2CB,
0X2BB,0X3AB,0X3AA,0X0BA,0X3B9,0X2B8,0X2A8,0X1A9,0X399,0X298,0X288,0X189,0X08A,0X19A,0X19B,0X28B,
0X18C,0X08D,0X09D,0X39C,0X0AC,0X1BC,0X1BD,0X2AD,0X0AE,0X1BE,0X1BF,0X2AF,0X39F,0X29E,0X28E,0X18F,
0X27F,0X36F,0X36E,0X07E,0X37D,0X27C,0X26C,0X16D,0X35D,0X25C,0X24C,0X14D,0X04E,0X15E,0X15F,0X24F,
0X33F,0X23E,0X22E,0X12F,0X21F,0X30F,0X30E,0X01E,0X21D,0X30D,0X30C,0X01C,0X12C,0X02D,0X03D,0X33C,
0X33B,0X23A,0X22A,0X12B,0X21B,0X30B,0X30A,0X01A,0X219,0X309,0X308,0X018,0X128,0X029,0X039,0X338,
0X048,0X158,0X159,0X249,0X14A,0X04B,0X05B,0X35A,0X16A,0X06B,0X07B,0X37A,0X279,0X369,0X368,0X078,
0X277,0X367,0X366,0X076,0X375,0X274,0X264,0X165,0X355,0X254,0X244,0X145,0X046,0X156,0X157,0X247,
0X337,0X236,0X226,0X127,0X217,0X307,0X306,0X016,0X215,0X305,0X304,0X014,0X124,0X025,0X035,0X334,
0X333,0X232,0X222,0X123,0X213,0X303,0X302,0X012,0X211,0X301,0X300,0X010,0X120,0X021,0X031,0X330,
0X040,0X150,0X151,0X241,0X142,0X043,0X053,0X352,0X162,0X063,0X073,0X372,0X271,0X361,0X360,0X070,
0X180,0X081,0X091,0X390,0X0A0,0X1B0,0X1B1,0X2A1,0X0A2,0X1B2,0X1B3,0X2A3,0X393,0X292,0X282,0X183,
0X084,0X194,0X195,0X285,0X186,0X087,0X097,0X396,0X1A6,0X0A7,0X0B7,0X3B6,0X2B5,0X3A5,0X3A4,0X0B4,
0X0C4,0X1D4,0X1D5,0X2C5,0X1C6,0X0C7,0X0D7,0X3D6,0X1E6,0X0E7,0X0F7,0X3F6,0X2F5,0X3E5,0X3E4,0X0F4,
0X3F3,0X2F2,0X2E2,0X1E3,0X2D3,0X3C3,0X3C2,0X0D2,0X2D1,0X3C1,0X3C0,0X0D0,0X1E0,0X0E1,0X0F1,0X3F0,
};

// this takes 5 bit hilbert curve numbers
// I'm fairly confident I can get this smaller and still have a low number of table look ups and a low number of operations
// Still in the process of using this one
const uint16_t xy_table_655356[1024] = {
0000,0X01,0X01,0000,0000,0000,0X01,0X01,0X02,0X02,0X03,0X03,0X03,0X02,0X02,0X03,
0X04,0X04,0X05,0X05,0X06,0X07,0X07,0X06,0X06,0X07,0X07,0X06,0X05,0X05,0X04,0X04,
0X04,0X04,0X05,0X05,0X06,0X07,0X07,0X06,0X06,0X07,0X07,0X06,0X05,0X05,0X04,0X04,
0X03,0X02,0X02,0X03,0X03,0X03,0X02,0X02,0X01,0X01,0000,0000,0000,0X01,0X01,0000,
0000,0X01,0X01,0000,0000,0000,0X01,0X01,0X02,0X02,0X03,0X03,0X03,0X02,0X02,0X03,
0X04,0X04,0X05,0X05,0X06,0X07,0X07,0X06,0X06,0X07,0X07,0X06,0X05,0X05,0X04,0X04,
0X04,0X04,0X05,0X05,0X06,0X07,0X07,0X06,0X06,0X07,0X07,0X06,0X05,0X05,0X04,0X04,
0X03,0X02,0X02,0X03,0X03,0X03,0X02,0X02,0X01,0X01,0000,0000,0000,0X01,0X01,0000,
0000,0000,0X01,0X01,0X02,0X03,0X03,0X02,0X02,0X03,0X03,0X02,0X01,0X01,0000,0000,
0000,0X01,0X01,0000,0000,0000,0X01,0X01,0X02,0X02,0X03,0X03,0X03,0X02,0X02,0X03,
0X04,0X05,0X05,0X04,0X04,0X04,0X05,0X05,0X06,0X06,0X07,0X07,0X07,0X06,0X06,0X07,
0X07,0X07,0X06,0X06,0X05,0X04,0X04,0X05,0X05,0X04,0X04,0X05,0X06,0X06,0X07,0X07,
0X08,0X08,0X09,0X09,0X0A,0X0B,0X0B,0X0A,0X0A,0X0B,0X0B,0X0A,0X09,0X09,0X08,0X08,
0X08,0X09,0X09,0X08,0X08,0X08,0X09,0X09,0X0A,0X0A,0X0B,0X0B,0X0B,0X0A,0X0A,0X0B,
0X0C,0X0D,0X0D,0X0C,0X0C,0X0C,0X0D,0X0D,0X0E,0X0E,0X0F,0X0F,0X0F,0X0E,0X0E,0X0F,
0X0F,0X0F,0X0E,0X0E,0X0D,0X0C,0X0C,0X0D,0X0D,0X0C,0X0C,0X0D,0X0E,0X0E,0X0F,0X0F,
0X0F,0X0E,0X0E,0X0F,0X0F,0X0F,0X0E,0X0E,0X0D,0X0D,0X0C,0X0C,0X0C,0X0D,0X0D,0X0C,
0X0B,0X0B,0X0A,0X0A,0X09,0X08,0X08,0X09,0X09,0X08,0X08,0X09,0X0A,0X0A,0X0B,0X0B,
0X0B,0X0B,0X0A,0X0A,0X09,0X08,0X08,0X09,0X09,0X08,0X08,0X09,0X0A,0X0A,0X0B,0X0B,
0X0C,0X0D,0X0D,0X0C,0X0C,0X0C,0X0D,0X0D,0X0E,0X0E,0X0F,0X0F,0X0F,0X0E,0X0E,0X0F,
0X10,0X10,0X11,0X11,0X12,0X13,0X13,0X12,0X12,0X13,0X13,0X12,0X11,0X11,0X10,0X10,
0X10,0X11,0X11,0X10,0X10,0X10,0X11,0X11,0X12,0X12,0X13,0X13,0X13,0X12,0X12,0X13,
0X14,0X15,0X15,0X14,0X14,0X14,0X15,0X15,0X16,0X16,0X17,0X17,0X17,0X16,0X16,0X17,
0X17,0X17,0X16,0X16,0X15,0X14,0X14,0X15,0X15,0X14,0X14,0X15,0X16,0X16,0X17,0X17,
0X18,0X19,0X19,0X18,0X18,0X18,0X19,0X19,0X1A,0X1A,0X1B,0X1B,0X1B,0X1A,0X1A,0X1B,
0X1C,0X1C,0X1D,0X1D,0X1E,0X1F,0X1F,0X1E,0X1E,0X1F,0X1F,0X1E,0X1D,0X1D,0X1C,0X1C,
0X1C,0X1C,0X1D,0X1D,0X1E,0X1F,0X1F,0X1E,0X1E,0X1F,0X1F,0X1E,0X1D,0X1D,0X1C,0X1C,
0X1B,0X1A,0X1A,0X1B,0X1B,0X1B,0X1A,0X1A,0X19,0X19,0X18,0X18,0X18,0X19,0X19,0X18,
0X18,0X19,0X19,0X18,0X18,0X18,0X19,0X19,0X1A,0X1A,0X1B,0X1B,0X1B,0X1A,0X1A,0X1B,
0X1C,0X1C,0X1D,0X1D,0X1E,0X1F,0X1F,0X1E,0X1E,0X1F,0X1F,0X1E,0X1D,0X1D,0X1C,0X1C,
0X1C,0X1C,0X1D,0X1D,0X1E,0X1F,0X1F,0X1E,0X1E,0X1F,0X1F,0X1E,0X1D,0X1D,0X1C,0X1C,
0X1B,0X1A,0X1A,0X1B,0X1B,0X1B,0X1A,0X1A,0X19,0X19,0X18,0X18,0X18,0X19,0X19,0X18,
0X17,0X17,0X16,0X16,0X15,0X14,0X14,0X15,0X15,0X14,0X14,0X15,0X16,0X16,0X17,0X17,
0X17,0X16,0X16,0X17,0X17,0X17,0X16,0X16,0X15,0X15,0X14,0X14,0X14,0X15,0X15,0X14,
0X13,0X12,0X12,0X13,0X13,0X13,0X12,0X12,0X11,0X11,0X10,0X10,0X10,0X11,0X11,0X10,
0X10,0X10,0X11,0X11,0X12,0X13,0X13,0X12,0X12,0X13,0X13,0X12,0X11,0X11,0X10,0X10,
0X10,0X10,0X11,0X11,0X12,0X13,0X13,0X12,0X12,0X13,0X13,0X12,0X11,0X11,0X10,0X10,
0X10,0X11,0X11,0X10,0X10,0X10,0X11,0X11,0X12,0X12,0X13,0X13,0X13,0X12,0X12,0X13,
0X14,0X15,0X15,0X14,0X14,0X14,0X15,0X15,0X16,0X16,0X17,0X17,0X17,0X16,0X16,0X17,
0X17,0X17,0X16,0X16,0X15,0X14,0X14,0X15,0X15,0X14,0X14,0X15,0X16,0X16,0X17,0X17,
0X18,0X19,0X19,0X18,0X18,0X18,0X19,0X19,0X1A,0X1A,0X1B,0X1B,0X1B,0X1A,0X1A,0X1B,
0X1C,0X1C,0X1D,0X1D,0X1E,0X1F,0X1F,0X1E,0X1E,0X1F,0X1F,0X1E,0X1D,0X1D,0X1C,0X1C,
0X1C,0X1C,0X1D,0X1D,0X1E,0X1F,0X1F,0X1E,0X1E,0X1F,0X1F,0X1E,0X1D,0X1D,0X1C,0X1C,
0X1B,0X1A,0X1A,0X1B,0X1B,0X1B,0X1A,0X1A,0X19,0X19,0X18,0X18,0X18,0X19,0X19,0X18,
0X18,0X19,0X19,0X18,0X18,0X18,0X19,0X19,0X1A,0X1A,0X1B,0X1B,0X1B,0X1A,0X1A,0X1B,
0X1C,0X1C,0X1D,0X1D,0X1E,0X1F,0X1F,0X1E,0X1E,0X1F,0X1F,0X1E,0X1D,0X1D,0X1C,0X1C,
0X1C,0X1C,0X1D,0X1D,0X1E,0X1F,0X1F,0X1E,0X1E,0X1F,0X1F,0X1E,0X1D,0X1D,0X1C,0X1C,
0X1B,0X1A,0X1A,0X1B,0X1B,0X1B,0X1A,0X1A,0X19,0X19,0X18,0X18,0X18,0X19,0X19,0X18,
0X17,0X17,0X16,0X16,0X15,0X14,0X14,0X15,0X15,0X14,0X14,0X15,0X16,0X16,0X17,0X17,
0X17,0X16,0X16,0X17,0X17,0X17,0X16,0X16,0X15,0X15,0X14,0X14,0X14,0X15,0X15,0X14,
0X13,0X12,0X12,0X13,0X13,0X13,0X12,0X12,0X11,0X11,0X10,0X10,0X10,0X11,0X11,0X10,
0X10,0X10,0X11,0X11,0X12,0X13,0X13,0X12,0X12,0X13,0X13,0X12,0X11,0X11,0X10,0X10,
0X0F,0X0E,0X0E,0X0F,0X0F,0X0F,0X0E,0X0E,0X0D,0X0D,0X0C,0X0C,0X0C,0X0D,0X0D,0X0C,
0X0B,0X0B,0X0A,0X0A,0X09,0X08,0X08,0X09,0X09,0X08,0X08,0X09,0X0A,0X0A,0X0B,0X0B,
0X0B,0X0B,0X0A,0X0A,0X09,0X08,0X08,0X09,0X09,0X08,0X08,0X09,0X0A,0X0A,0X0B,0X0B,
0X0C,0X0D,0X0D,0X0C,0X0C,0X0C,0X0D,0X0D,0X0E,0X0E,0X0F,0X0F,0X0F,0X0E,0X0E,0X0F,
0X0F,0X0F,0X0E,0X0E,0X0D,0X0C,0X0C,0X0D,0X0D,0X0C,0X0C,0X0D,0X0E,0X0E,0X0F,0X0F,
0X0F,0X0E,0X0E,0X0F,0X0F,0X0F,0X0E,0X0E,0X0D,0X0D,0X0C,0X0C,0X0C,0X0D,0X0D,0X0C,
0X0B,0X0A,0X0A,0X0B,0X0B,0X0B,0X0A,0X0A,0X09,0X09,0X08,0X08,0X08,0X09,0X09,0X08,
0X08,0X08,0X09,0X09,0X0A,0X0B,0X0B,0X0A,0X0A,0X0B,0X0B,0X0A,0X09,0X09,0X08,0X08,
0X07,0X07,0X06,0X06,0X05,0X04,0X04,0X05,0X05,0X04,0X04,0X05,0X06,0X06,0X07,0X07,
0X07,0X06,0X06,0X07,0X07,0X07,0X06,0X06,0X05,0X05,0X04,0X04,0X04,0X05,0X05,0X04,
0X03,0X02,0X02,0X03,0X03,0X03,0X02,0X02,0X01,0X01,0000,0000,0000,0X01,0X01,0000,
0000,0000,0X01,0X01,0X02,0X03,0X03,0X02,0X02,0X03,0X03,0X02,0X01,0X01,0000,0000,
};

/*
uint16_t get_xy_655356( uint64_t index ) {
    return (index & 0XFFFFFFFFFFFF0000) ? ~xy_table_655356[index & 0X3FF] : xy_table_655356[index & 0X3FF];
};
*/

