#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "decode_zhr.h"

short table[65] = {
  32767,  32729,  32610,  32413,  32138,  31786,  31357,  30853,  30274,  29622,  28899,  28106,  27246,  26320,  25330,  24279,
  23170,  22006,  20788,  19520,  18205,  16846,  15447,  14010,  12540,  11039,   9512,   7962,   6393,   4808,   3212,   1608,
      0,  -1608,  -3212,  -4808,  -6393,  -7962,  -9512, -11039, -12540, -14010, -15447, -16846, -18205, -19520, -20788, -22006,
 -23170, -24279, -25330, -26320, -27246, -28106, -28899, -29622, -30274, -30853, -31357, -31786, -32138, -32413, -32610, -32729, -32768L };

short slope[64] = {
 -26887,  -8812,  -5323,  -3813,  -2979,  -2444,  -2081,  -1811,  -1608,  -1450,  -1322,  -1219,  -1132,  -1059,   -998,   -946,
   -901,   -861,   -827,   -797,   -772,   -750,   -730,   -713,   -699,   -687,   -677,   -668,   -662,   -657,   -654,   -652,
   -652,   -654,   -657,   -662,   -668,   -677,   -687,   -699,   -713,   -730,   -750,   -772,   -797,   -827,   -861,   -901,
   -946,   -998,  -1059,  -1132,  -1219,  -1322,  -1450,  -1608,  -1811,  -2081,  -2444,  -2979,  -3813,  -5323,  -8812, -26887};

short table2[64] = {
  32767,  32729,  32610,  32413,  32138,  31786,  31357,  30853,  30274,  29622,  28899,  28106,  27246,  26320,  25330,  24279,
  23170,  22006,  20788,  19520,  18205,  16846,  15447,  14010,  12540,  11039,   9512,   7962,   6393,   4808,   3212,   1608,
      0,  -1608,  -3212,  -4808,  -6393,  -7962,  -9512, -11039, -12540, -14010, -15447, -16846, -18205, -19520, -20788, -22006,
 -23170, -24279, -25330, -26320, -27246, -28106, -28899, -29622, -30274, -30853, -31357, -31786, -32138, -32413, -32610, -32729 };

short slope_cos[64] = {
   -632,  -1893,  -3150,  -4399,  -5638,  -6863,  -8072,  -9261, -10428, -11570, -12684, -13767, -14817, -15832, -16808, -17744,
 -18637, -19486, -20287, -21039, -21741, -22390, -22986, -23526, -24009, -24435, -24801, -25108, -25354, -25540, -25664, -25726,
 -25726, -25664, -25540, -25354, -25108, -24801, -24435, -24009, -23526, -22986, -22390, -21741, -21039, -20287, -19486, -18637,
 -17744, -16808, -15832, -14817, -13767, -12684, -11570, -10428,  -9261,  -8072,  -6863,  -5638,  -4399,  -3150,  -1893,   -632 };

short slope_acos[64] = {
 -26887,  -8812,  -5323,  -3813,  -2979,  -2444,  -2081,  -1811,  -1608,  -1450,  -1322,  -1219,  -1132,  -1059,   -998,   -946,
   -901,   -861,   -827,   -797,   -772,   -750,   -730,   -713,   -699,   -687,   -677,   -668,   -662,   -657,   -654,   -652,
   -652,   -654,   -657,   -662,   -668,   -677,   -687,   -699,   -713,   -730,   -750,   -772,   -797,   -827,   -861,   -901,
   -946,   -998,  -1059,  -1132,  -1219,  -1322,  -1450,  -1608,  -1811,  -2081,  -2444,  -2979,  -3813,  -5323,  -8812, -26887};

short lspcb1[128][10] = {
{ 1486,  2168,  3751,  9074, 12134, 13944, 17983, 19173, 21190, 21820},{ 1730,  2640,  3450,  4870,  6126,  7876, 15644, 17817, 20294, 21902},
{ 1568,  2256,  3088,  4874, 11063, 13393, 18307, 19293, 21109, 21741},{ 1733,  2512,  3357,  4708,  6977, 10296, 17024, 17956, 19145, 20350},
{ 1744,  2436,  3308,  8731, 10432, 12007, 15614, 16639, 21359, 21913},{ 1786,  2369,  3372,  4521,  6795, 12963, 17674, 18988, 20855, 21640},
{ 1631,  2433,  3361,  6328, 10709, 12013, 13277, 13904, 19441, 21088},{ 1489,  2364,  3291,  6250,  9227, 10403, 13843, 15278, 17721, 21451},
{ 1869,  2533,  3475,  4365,  9152, 14513, 15908, 17022, 20611, 21411},{ 2070,  3025,  4333,  5854,  7805,  9231, 10597, 16047, 20109, 21834},
{ 1910,  2673,  3419,  4261, 11168, 15111, 16577, 17591, 19310, 20265},{ 1141,  1815,  2624,  4623,  6495,  9588, 13968, 16428, 19351, 21286},
{ 2192,  3171,  4707,  5808, 10904, 12500, 14162, 15664, 21124, 21789},{ 1286,  1907,  2548,  3453,  9574, 11964, 15978, 17344, 19691, 22495},
{ 1921,  2720,  4604,  6684, 11503, 12992, 14350, 15262, 16997, 20791},{ 2052,  2759,  3897,  5246,  6638, 10267, 15834, 16814, 18149, 21675},
{ 1798,  2497,  5617, 11449, 13189, 14711, 17050, 18195, 20307, 21182},{ 1009,  1647,  2889,  5709,  9541, 12354, 15231, 18494, 20966, 22033},
{ 3016,  3794,  5406,  7469, 12488, 13984, 15328, 16334, 19952, 20791},{ 2203,  3040,  3796,  5442, 11987, 13512, 14931, 16370, 17856, 18803},
{ 2912,  4292,  7988,  9572, 11562, 13244, 14556, 16529, 20004, 21073},{ 2861,  3607,  5923,  7034,  9234, 12054, 13729, 18056, 20262, 20974},
{ 3069,  4311,  5967,  7367, 11482, 12699, 14309, 16233, 18333, 19172},{ 2434,  3661,  4866,  5798, 10383, 11722, 13049, 15668, 18862, 19831},
{ 2020,  2605,  3860,  9241, 13275, 14644, 16010, 17099, 19268, 20251},{ 1877,  2809,  3590,  4707, 11056, 12441, 15622, 17168, 18761, 19907},
{ 2107,  2873,  3673,  5799, 13579, 14687, 15938, 17077, 18890, 19831},{ 1612,  2284,  2944,  3572,  8219, 13959, 15924, 17239, 18592, 20117},
{ 2420,  3156,  6542, 10215, 12061, 13534, 15305, 16452, 18717, 19880},{ 1667,  2612,  3534,  5237, 10513, 11696, 12940, 16798, 18058, 19378},
{ 2388,  3017,  4839,  9333, 11413, 12730, 15024, 16248, 17449, 18677},{ 1875,  2786,  4231,  6320,  8694, 10149, 11785, 17013, 18608, 19960},
{  679,  1411,  4654,  8006, 11446, 13249, 15763, 18127, 20361, 21567},{ 1838,  2596,  3578,  4608,  5650, 11274, 14355, 15886, 20579, 21754},
{ 1303,  1955,  2395,  3322, 12023, 13764, 15883, 18077, 20180, 21232},{ 1438,  2102,  2663,  3462,  8328, 10362, 13763, 17248, 19732, 22344},
{  860,  1904,  6098,  7775,  9815, 12007, 14821, 16709, 19787, 21132},{ 1673,  2723,  3704,  6125,  7668,  9447, 13683, 14443, 20538, 21731},
{ 1246,  1849,  2902,  4508,  7221, 12710, 14835, 16314, 19335, 22720},{ 1525,  2260,  3862,  5659,  7342, 11748, 13370, 14442, 18044, 21334},
{ 1196,  1846,  3104,  7063, 10972, 12905, 14814, 17037, 19922, 22636},{ 2147,  3106,  4475,  6511,  8227,  9765, 10984, 12161, 18971, 21300},
{ 1585,  2405,  2994,  4036, 11481, 13177, 14519, 15431, 19967, 21275},{ 1778,  2688,  3614,  4680,  9465, 11064, 12473, 16320, 19742, 20800},
{ 1862,  2586,  3492,  6719, 11708, 13012, 14364, 16128, 19610, 20425},{ 1395,  2156,  2669,  3386, 10607, 12125, 13614, 16705, 18976, 21367},
{ 1444,  2117,  3286,  6233,  9423, 12981, 14998, 15853, 17188, 21857},{ 2004,  2895,  3783,  4897,  6168,  7297, 12609, 16445, 19297, 21465},
{ 1495,  2863,  6360,  8100, 11399, 14271, 15902, 17711, 20479, 22061},{ 2484,  3114,  5718,  7097,  8400, 12616, 14073, 14847, 20535, 21396},
{ 2424,  3277,  5296,  6284, 11290, 12903, 16022, 17508, 19333, 20283},{ 2565,  3778,  5360,  6989,  8782, 10428, 14390, 15742, 17770, 21734},
{ 2727,  3384,  6613,  9254, 10542, 12236, 14651, 15687, 20074, 21102},{ 1916,  2953,  6274,  8088,  9710, 10925, 12392, 16434, 20010, 21183},
{ 3384,  4366,  5349,  7667, 11180, 12605, 13921, 15324, 19901, 20754},{ 3075,  4283,  5951,  7619,  9604, 11010, 12384, 14006, 20658, 21497},
{ 1751,  2455,  5147,  9966, 11621, 13176, 14739, 16470, 20788, 21756},{ 1442,  2188,  3330,  6813,  8929, 12135, 14476, 15306, 19635, 20544},
{ 2294,  2895,  4070,  8035, 12233, 13416, 14762, 17367, 18952, 19688},{ 1937,  2659,  4602,  6697,  9071, 12863, 14197, 15230, 16047, 18877},
{ 2071,  2663,  4216,  9445, 10887, 12292, 13949, 14909, 19236, 20341},{ 1740,  2491,  3488,  8138,  9656, 11153, 13206, 14688, 20896, 21907},
{ 2199,  2881,  4675,  8527, 10051, 11408, 14435, 15463, 17190, 20597},{ 1943,  2988,  4177,  6039,  7478,  8536, 14181, 15551, 17622, 21579},
{ 1825,  3175,  7062,  9818, 12824, 15450, 18330, 19856, 21830, 22412},{ 2464,  3046,  4822,  5977,  7696, 15398, 16730, 17646, 20588, 21320},
{ 2550,  3393,  5305,  6920, 10235, 14083, 18143, 19195, 20681, 21336},{ 3003,  3799,  5321,  6437,  7919, 11643, 15810, 16846, 18119, 18980},
{ 3455,  4157,  6838,  8199,  9877, 12314, 15905, 16826, 19949, 20892},{ 3052,  3769,  4891,  5810,  6977, 10126, 14788, 15990, 19773, 20904},
{ 3671,  4356,  5827,  6997,  8460, 12084, 14154, 14939, 19247, 20423},{ 2716,  3684,  5246,  6686,  8463, 10001, 12394, 14131, 16150, 19776},
{ 1945,  2638,  4130,  7995, 14338, 15576, 17057, 18206, 20225, 20997},{ 2304,  2928,  4122,  4824,  5640, 13139, 15825, 16938, 20108, 21054},
{ 1800,  2516,  3350,  5219, 13406, 15948, 17618, 18540, 20531, 21252},{ 1436,  2224,  2753,  4546,  9657, 11245, 15177, 16317, 17489, 19135},
{ 2319,  2899,  4980,  6936,  8404, 13489, 15554, 16281, 20270, 20911},{ 2187,  2919,  4610,  5875,  7390, 12556, 14033, 16794, 20998, 21769},
{ 2235,  2923,  5121,  6259,  8099, 13589, 15340, 16340, 17927, 20159},{ 1765,  2638,  3751,  5730,  7883, 10108, 13633, 15419, 16808, 18574},
{ 3460,  5741,  9596, 11742, 14413, 16080, 18173, 19090, 20845, 21601},{ 3735,  4426,  6199,  7363,  9250, 14489, 16035, 17026, 19873, 20876},
{ 3521,  4778,  6887,  8680, 12717, 14322, 15950, 18050, 20166, 21145},{ 2141,  2968,  6865,  8051, 10010, 13159, 14813, 15861, 17528, 18655},
{ 4148,  6128,  9028, 10871, 12686, 14005, 15976, 17208, 19587, 20595},{ 4403,  5367,  6634,  8371, 10163, 11599, 14963, 16331, 17982, 18768},
{ 4091,  5386,  6852,  8770, 11563, 13290, 15728, 16930, 19056, 20102},{ 2746,  3625,  5299,  7504, 10262, 11432, 13172, 15490, 16875, 17514},
{ 2248,  3556,  8539, 10590, 12665, 14696, 16515, 17824, 20268, 21247},{ 1279,  1960,  3920,  7793, 10153, 14753, 16646, 18139, 20679, 21466},
{ 2440,  3475,  6737,  8654, 12190, 14588, 17119, 17925, 19110, 19979},{ 1879,  2514,  4497,  7572, 10017, 14948, 16141, 16897, 18397, 19376},
{ 2804,  3688,  7490, 10086, 11218, 12711, 16307, 17470, 20077, 21126},{ 2023,  2682,  3873,  8268, 10255, 11645, 15187, 17102, 18965, 19788},
{ 2823,  3605,  5815,  8595, 10085, 11469, 16568, 17462, 18754, 19876},{ 2851,  3681,  5280,  7648,  9173, 10338, 14961, 16148, 17559, 18474},
{ 1348,  2645,  5826,  8785, 10620, 12831, 16255, 18319, 21133, 22586},{ 2141,  3036,  4293,  6082,  7593, 10629, 17158, 18033, 21466, 22084},
{ 1608,  2375,  3384,  6878,  9970, 11227, 16928, 17650, 20185, 21120},{ 2774,  3616,  5014,  6557,  7788,  8959, 17068, 18302, 19537, 20542},
{ 1934,  4813,  6204,  7212,  8979, 11665, 15989, 17811, 20426, 21703},{ 2288,  3507,  5037,  6841,  8278,  9638, 15066, 16481, 21653, 22214},
{ 2951,  3771,  4878,  7578,  9016, 10298, 14490, 15242, 20223, 20990},{ 3256,  4791,  6601,  7521,  8644,  9707, 13398, 16078, 19102, 20249},
{ 1827,  2614,  3486,  6039, 12149, 13823, 16191, 17282, 21423, 22041},{ 1000,  1704,  3002,  6335,  8471, 10500, 14878, 16979, 20026, 22427},
{ 1646,  2286,  3109,  7245, 11493, 12791, 16824, 17667, 18981, 20222},{ 1708,  2501,  3315,  6737,  8729,  9924, 16089, 17097, 18374, 19917},
{ 2623,  3510,  4478,  5645,  9862, 11115, 15219, 18067, 19583, 20382},{ 2518,  3434,  4728,  6388,  8082,  9285, 13162, 18383, 19819, 20552},
{ 1726,  2383,  4090,  6303,  7805, 12845, 14612, 17608, 19269, 20181},{ 2860,  3735,  4838,  6044,  7254,  8402, 14031, 16381, 18037, 19410},
{ 4247,  5993,  7952,  9792, 12342, 14653, 17527, 18774, 20831, 21699},{ 3502,  4051,  5680,  6805,  8146, 11945, 16649, 17444, 20390, 21564},
{ 3151,  4893,  5899,  7198, 11418, 13073, 15124, 17673, 20520, 21861},{ 3960,  4848,  5926,  7259,  8811, 10529, 15661, 16560, 18196, 20183},
{ 4499,  6604,  8036,  9251, 10804, 12627, 15880, 17512, 20020, 21046},{ 4251,  5541,  6654,  8318,  9900, 11686, 15100, 17093, 20572, 21687},
{ 3769,  5327,  7865,  9360, 10684, 11818, 13660, 15366, 18733, 19882},{ 3083,  3969,  6248,  8121,  9798, 10994, 12393, 13686, 17888, 19105},
{ 2731,  4670,  7063,  9201, 11346, 13735, 16875, 18797, 20787, 22360},{ 1187,  2227,  4737,  7214,  9622, 12633, 15404, 17968, 20262, 23533},
{ 1911,  2477,  3915, 10098, 11616, 12955, 16223, 17138, 19270, 20729},{ 1764,  2519,  3887,  6944,  9150, 12590, 16258, 16984, 17924, 18435},
{ 1400,  3674,  7131,  8718, 10688, 12508, 15708, 17711, 19720, 21068},{ 2322,  3073,  4287,  8108,  9407, 10628, 15862, 16693, 19714, 21474},
{ 2630,  3339,  4758,  8360, 10274, 11333, 12880, 17374, 19221, 19936},{ 1721,  2577,  5553,  7195,  8651, 10686, 15069, 16953, 18703, 19929}
};


short lspcb2[32][10] = {       /// Q13
{ -435,  -815,  -742,  1033,  -518,   582, -1201,   829,    86,   385},{ -833,  -891,   463,    -8, -1251,  1450,    72,  -231,   864,   661},
{-1021,   231,  -306,   321,  -220,  -163,  -526,  -754, -1633,   267},{   57,  -198,  -339,   -33, -1468,   573,   796,  -169,  -631,   816},
{  171,  -350,   294,  1660,   453,   519,   291,   159,  -640, -1296},{ -701,  -842,   -58,   950,   892,  1549,   715,   527,  -714,  -193},
{  584,    31,  -289,   356,  -333,  -457,   612,  -283, -1381,  -741},{ -109,  -808,   231,    77,   -87,  -344,  1341,  1087,  -654,  -569},
{ -859,  1236,   550,   854,   714,  -543, -1752,  -195,   -98,  -276},{ -877,  -954, -1248,  -299,   212,  -235,  -728,   949,  1517,   895},
{  -77,   344,  -620,   763,   413,   502,  -362,  -960,  -483,  1386},{ -314,  -307,  -256, -1260,  -429,   450,  -466,  -108,  1010,  2223},
{  711,   693,   521,   650,  1305,   -28,  -378,   744, -1005,   240},{ -112,  -271,  -500,   946,  1733,   271,   -15,   909,  -259,  1688},
{  575,   -10,  -468,  -199,  1101, -1011,   581,   -53,  -747,   878},{  145,  -285, -1280,  -398,    36,  -498, -1377,    18,  -444,  1483},
{-1133,  -835,  1350,  1284,   -95,  1015,  -222,   443,   372,  -354},{-1459, -1237,   416,  -213,   466,   669,   659,  1640,   932,   534},
{  -15,    66,   468,  1019,  -748,  1385,  -182,  -907,  -721,  -262},{ -338,   148,  1445,    75,  -760,   569,  1247,   337,   416,  -121},
{  389,   239,  1568,   981,   113,   369, -1003,  -507,  -587,  -904},{ -312,   -98,   949,    31,  1104,    72,  -141,  1465,    63,  -785},
{ 1127,   584,   835,   277, -1159,   208,   301,  -882,   117,  -404},{  539,  -114,   856,  -493,   223,  -912,   623,   -76,   276,  -440},
{ 2197,  2337,  1268,   670,   304,  -267,  -525,   140,   882,  -139},{-1596,   550,   801,  -456,   -56,  -697,   865,  1060,   413,   446},
{ 1154,   593,   -77,  1237,   -31,   581, -1037,  -895,   669,   297},{  397,   558,   203,  -797,  -919,     3,   692,  -292,  1050,   782},
{  334,  1475,   632,   -80,    48, -1061,  -484,   362,  -597,  -852},{ -545,  -330,  -429,  -680,  1133, -1182,  -744,  1340,   262,    63},
{ 1320,   827,  -398,  -576,   341,  -774,  -483, -1247,   -70,    98},{ -163,   674,   -11,  -886,   531, -1125,  -265,  -242,   724,   934}
};
short fg[2][4][10] = {       ///Q15
  {
    { 8421,  9109,  9175,  8965,  9034,  9057,  8765,  8775,  9106,  8673},    { 7018,  7189,  7638,  7307,  7444,  7379,  7038,  6956,  6930,  6868},
    { 5472,  4990,  5134,  5177,  5246,  5141,  5206,  5095,  4830,  5147},    { 4056,  3031,  2614,  3024,  2916,  2713,  3309,  3237,  2857,  3473}
  },
  {
    { 7733,  7880,  8188,  8175,  8247,  8490,  8637,  8601,  8359,  7569},
    { 4210,  3031,  2552,  3473,  3876,  3853,  4184,  4154,  3909,  3968},
    { 3214,  1930,  1313,  2143,  2493,  2385,  2755,  2706,  2542,  2919},
    { 3024,  1592,   940,  1631,  1723,  1579,  2034,  2084,  1913,  2601}
  }
};
short fg_sum[2][10] = {{ 7798,  8447,  8205,  8293,  8126,  8477,  8447,  8703,  9043,  8604},{14585, 18333, 19772, 17344, 16426, 16459, 15155, 15220, 16043, 15708}};/* Q15 */
short fg_sum_inv[2][10]={{17210, 15888, 16357, 16183, 16516, 15833, 15888, 15421, 14840, 15597},{ 9202,  7320,  6788,  7738,  8170,  8154,  8856,  8818,  8366,  8544}};/* Q12 */

short grid[50+1] ={
     32760,     32703,     32509,     32187,     31738,     31164,     30466,     29649,     28714,     27666,     26509,     25248,
     23886,     22431,     20887,     19260,     17557,     15786,     13951,     12062,     10125,      8149,      6140,      4106,
      2057,         0,     -2057,     -4106,     -6140,     -8149,    -10125,    -12062,    -13951,    -15786,    -17557,    -19260,
    -20887,    -22431,    -23886,    -25248,    -26509,    -27666,    -28714,    -29649,    -30466,    -31164,    -31738,    -32187,  -32509,    -32703,    -32760};


short inter_3l[31] = {   29443,   25207,   14701,    3143,   -4402,   -5850,   -2783,    1211,    3130,    2259,       0,   -1652,   -1666,
    -464,     756,    1099,     550,    -245,    -634,    -451,       0,     308,     296,      78,    -120,    -165,     -79,      34,      91,      70,       0};
short pred[4] = { 5571, 4751, 2785, 1556 };
short gbk1[8][2] = {{1 ,1516 }, {1551 ,2425 }, { 1831 ,5022 }, {57 ,5404 },{1921 ,9291 },{3242 ,  9949 }, { 356 , 14756 }, { 2678 , 27162 }};/* Q14      Q13 */
short gbk2[16][2] = { {   826 ,  2005 }, {  1994 ,     0 }, {  5142 ,   592 }, {  6160 ,  2395 }, {  8091 ,  4861 }, {  9120 ,   525 }, { 10573 ,  2966 },
 { 11569 ,  1196 }, { 13260 ,  3256 }, { 14194 ,  1630 }, { 15132 ,  4914 }, { 15161 , 14276 }, { 15434 ,   237 }, { 16112 ,  3392 }, { 17299 ,  1861 }, { 18973 ,  5935 }};/* Q14       Q13 */
short map1[8] = { 5, 1, 4, 7, 3, 0, 6, 2};
short map2[16] = { 4, 6, 0, 2,12,14, 8,10,15,11, 9,13, 7, 3, 1, 5};


short imap1[8] = { 5, 1, 7, 4, 2, 0, 6, 3};
short imap2[16] = { 2,14, 3,13, 0,15, 1,12, 6,10, 7, 9, 4,11, 5, 8};
short b100[3] = {7699, -15398, 7699};      /* Q13 */
short a100[3] = {8192, 15836, -7667};      /* Q13 */
short b140[3] = {1899, -3798, 1899};      /* 1/2 in Q12 */
short a140[3] = {4096, 7807, -3733};      /* Q12 */
short bitsno[11] = {1+7,    5*2,  8, 1, 13, 4, 7,  5,    13, 4, 7};/* MA + 1st stage /* 2nd stage //* first subframe  /* second subframe  */
short tabpow[33] = { 16384, 16743, 17109, 17484, 17867, 18258, 18658, 19066, 19484, 19911, 20347, 20792, 21247, 21713, 22188, 22674,
              23170, 23678, 24196, 24726, 25268, 25821, 26386, 26964, 27554, 28158, 28774, 29405, 30048, 30706, 31379, 32066, 32767 };
short tablog[33] = { 0,  1455,  2866,  4236,  5568,  6863,  8124,  9352, 10549, 11716, 12855, 13967, 15054, 16117, 17156, 18172, 19167, 
               20142, 21097, 22033, 22951, 23852, 24735, 25603, 26455, 27291, 28113, 28922, 29716, 30497, 31266, 32023, 32767 };
short tabsqr[49] = { 32767, 31790, 30894, 30070, 29309, 28602, 27945, 27330, 26755, 26214, 25705, 25225, 24770, 24339, 23930, 23541, 23170, 22817, 22479, 22155,
      21845, 21548, 21263, 20988, 20724, 20470, 20225, 19988, 19760, 19539, 19326, 19119, 18919, 18725, 18536, 18354, 18176, 18004, 17837, 17674, 17515, 17361, 17211, 17064, 16921, 16782, 16646, 16514, 16384 };
static short freq_prev[4][10];  
static short freq_prev_reset[10] = {   2339, 4679, 7018, 9358, 11698, 14037, 16377, 18717, 21056, 23396};  
static short prev_ma;   
static short prev_lsp[10];
static short y2_hi, y2_lo, y1_hi, y1_lo, x0, x1;
static short res2_buf[143+40];
static short *res2;
static short scal_res2_buf[143+40];
static short *scal_res2; 
static short mem_syn_pst[10];
extern short Overflow=0;
extern short Carry=0;
static short old_exc[80+143+11];
static short *exc;    
static short lsp_old[10]={  30000, 26000, 21000, 15000, 8000, 0, -8000,-15000,-21000,-26000};        
static short mem_syn[10];
static short sharp;   
static short old_T0;  
static short gain_code;
static short gain_pitch; 


int Inv_sqrt(int L_x);  
void Log2(  int L_x,   short *exponent,  short *fraction); 
int Pow2( short exponent,  short fraction ); 
void Init_Pre_Process(void);
void Init_Post_Process(void);
void Pre_Process(  short signal[], short lg );  
void Post_Process( short signal[],  short lg);  
void Init_Decod_ld8a(void);
void Decod_ld8a( short  parm[], short  synth[], short  A_t[],  short  *T2); 
void Lsp_Az(  short lsp[],    short a[]     );
void Lsf_lsp(  short lsf[],    short lsp[],    short m       );
void Lsp_lsf(  short lsp[],   short lsf[],     short m       );
void Int_qlpc( short lsp_old[],  short lsp_new[],  short Az[] );
void Weight_Az(  short a[],    short gamma,  short m,      short ap[]  );
void Residu(  short a[],   short x[],   short y[],   short lg   );
void Syn_filt(  short a[],   short x[],   short y[],   short lg,    short mem[],  short update );
void Dec_lag3(  short index,  short pit_min,  short pit_max,  short i_subfr,  short *T0,      short *T0_frac);
void Pred_lt_3(  short   exc[],  short   T0,     short   frac,   short   L_subfr);
short Parity_Pitch(   short pitch_index);
short Check_Parity_Pitch(   short pitch_index,    short parity        );
void Decod_ACELP(  short sign,    short index,   short cod[]  );
void Lsf_lsp2(  short lsf[],  short lsp[],  short m  );
void Lsp_expand_1_2(  short buf[],   short gap );
void Lsp_get_quant(  short lspcb1[][10],   short lspcb2[][10],   short code0,  short code1,  short code2,  short fg[][10],   short freq_prev[][10],  short lspq[],    short fg_sum[] );
void Lsp_stability(  short buf[] );
void D_lsp(  short prm[],   short lsp_q[],   short erase );
void Lsp_decw_reset(  void);
void Lsp_iqua_cs( short prm[],  short lsp_q[], short erase  );
void Lsp_prev_compose(  short lsp_ele[],   short lsp[],   short fg[][10],   short freq_prev[][10],   short fg_sum[] );
void Lsp_prev_extract(  short lsp[10],   short lsp_ele[10],   short fg[4][10],   short freq_prev[4][10],   short fg_sum_inv[10] );
void Lsp_prev_update(  short lsp_ele[10],   short freq_prev[4][10] );
void Dec_gain(  short index,   short code[],  short L_subfr,  short bfi,      short *gain_pit,  short *gain_cod );
void Gain_predict( short past_qua_en[], short code[], short L_subfr, short *gcode0, short *exp_gcode0);
void Gain_update( short past_qua_en[], int L_gbk12  );
void Gain_update_erasure( short past_qua_en[]);
void  prm2bits_ld8k(short prm[], short bits[]);
void  bits2prm_ld8k(short bits[], short prm[]);
void Init_Post_Filter(void);
void Post_Filter(  short *syn,      short *Az_4,     short *T       );
void pit_pst_filt(  short *signal,   short *scal_sig,  short t0_min,    short t0_max,   short L_subfr,  short *signal_pst);
void preemphasis(  short *signal,   short g,         short L        );
void agc( short *sig_in, short *sig_out, short l_trm); 
void Copy(short x[], short y[], short L );
void Set_zero( short x[], short L);  
short Random(void);
short sature(int L_var1);
short add(short var1, short var2);
short sub(short var1, short var2);
short abs_s(short var1);    
short shl(short var1, short var2); 
short shr(short var1, short var2); 
short mult(short var1, short var2);
int L_mult(short var1, short var2);
short negate(short var1);    
short extract_h(int L_var1); 
short extract_l(int L_var1); 
short round(int L_var1);     
int L_mac(int L_var3, short var1, short var2); 
int L_msu(int L_var3, short var1, short var2); 

int L_add(int L_var1, int L_var2); 
int L_sub(int L_var1, int L_var2); 
int L_shl(int L_var1, short var2); 
int L_shr(int L_var1, short var2); 
int L_deposit_h(short var1);  
int L_deposit_l(short var1);  
int L_shr_r(int L_var1, short var2);
short norm_s(short var1);
short div_s(short var1, short var2); 
short norm_l(int L_var1);  
void  L_Extract(int L_32, short *hi, short *lo);
int  L_Comp(short hi, short lo);
int  Mpy_32(short hi1, short lo1, short hi2, short lo2);
int  Mpy_32_16(short hi, short lo, short n);
static void  int2bin(short value, short no_of_bits, short *bitstream);
static short bin2int(short no_of_bits, short *bitstream);
static void  Get_lsp_pol(short *lsp, int *f);



void Set_zero(  short x[], short L )
{
   short i;
   for (i = 0; i < L; i++)     x[i] = 0;
   return;
}
void Copy(  short x[],   short y[],   short L    )
{
   short i;
   for (i = 0; i < L; i++)     y[i] = x[i];
   return;
}

short Random()
{
  static short seed = 21845;  /* seed = seed*31821 + 13849; */
  seed = extract_l(L_add(L_shr(L_mult(seed, 31821), 1), 13849L));
  return(seed);
}

void Pred_lt_3(  short   exc[],  short   T0,     short   frac,   short   L_subfr )
{
  short   i, j, k;
  short   *x0, *x1, *x2, *c1, *c2;
  int  s;

  x0 = &exc[-T0];

  frac = negate(frac);
  if (frac < 0)
  {
    frac = add(frac, 3);
    x0--;
  }

  for (j=0; j<L_subfr; j++)
  {
    x1 = x0++;
    x2 = x0;
    c1 = &inter_3l[frac];
    c2 = &inter_3l[sub(3,frac)];

    s = 0;
    for(i=0, k=0; i< 10; i++, k+=3)
    {
      s = L_mac(s, x1[-i], c1[k]);
      s = L_mac(s, x2[i],  c2[k]);
    }

    exc[j] = round(s);
  }

  return;
}

void Init_Post_Filter(void)
{
  res2  = res2_buf + 143;
  scal_res2  = scal_res2_buf + 143;

  Set_zero(mem_syn_pst, 10);
  Set_zero(res2_buf, 143+40);
  Set_zero(scal_res2_buf, 143+40);

  return;
}


void Post_Filter(  short *syn,    short *Az_4,   short *T     )
{
 short res2_pst[40];  
 short syn_pst[80];   
 short Ap3[11], Ap4[11]; 
 short *Az;                                       
 short t0_max, t0_min; 
 short i_subfr;        
 short h[22];
 short i, j;
 short temp1, temp2;
 int   L_tmp;
    Az = Az_4;
    for (i_subfr = 0; i_subfr < 80; i_subfr += 40)
    {      

      t0_min = sub(*T++, 3);
      t0_max = add(t0_min, 6);
      if (sub(t0_max, 143) > 0) {
        t0_max = 143;
        t0_min = sub(t0_max, 6);
      }
      Weight_Az(Az, 18022, 10, Ap3);
      Weight_Az(Az, 22938, 10, Ap4);
      Residu(Ap3, &syn[i_subfr], res2, 40);
      for (j=0; j<40; j++)      {        scal_res2[j] = shr(res2[j], 2);      }
      pit_pst_filt(res2, scal_res2, t0_min, t0_max, 40, res2_pst);
      Copy(Ap3, h, 10+1);
      Set_zero(&h[10+1], 22-10-1);
      Syn_filt(Ap4, h, h, 22, &h[10+1], 0);
      L_tmp = L_mult(h[0], h[0]);
      for (i=1; i<22; i++) L_tmp = L_mac(L_tmp, h[i], h[i]);
      temp1 = extract_h(L_tmp);

      L_tmp = L_mult(h[0], h[1]);
      for (i=1; i<22-1; i++) L_tmp = L_mac(L_tmp, h[i], h[i+1]);
      temp2 = extract_h(L_tmp);
      if(temp2 <= 0) temp2=0;  else{ temp2 = mult(temp2, 26214); temp2 = div_s(temp2, temp1); }
      preemphasis(res2_pst, temp2, 40);
      Syn_filt(Ap4, res2_pst, &syn_pst[i_subfr], 40, mem_syn_pst, 1);
      agc(&syn[i_subfr], &syn_pst[i_subfr], 40);
      Copy(&res2[40-143], &res2[-143], 143);
      Copy(&scal_res2[40-143], &scal_res2[-143], 143);
      Az += 11;
    }
    Copy(&syn[80-10], &syn[-10], 10);
    Copy(syn_pst, syn, 80);
    return;
}

void pit_pst_filt(  short *signal,   short *scal_sig,   short t0_min,    short t0_max,    short L_subfr,   short *signal_pst)
{
  short i, j, t0;
  short g0, gain, cmax, en, en0;
  short *p, *p1, *deb_sig;
  int corr, cor_max, ener, ener0, temp;
  int L_temp;

  deb_sig = &scal_sig[-t0_min];
  cor_max = (int)0x80000000L;
  t0 = t0_min;             /* Only to remove warning from some compilers */
  for (i=t0_min; i<=t0_max; i++)
  {
    corr = 0;
    p    = scal_sig;
    p1   = deb_sig;
    for (j=0; j<L_subfr; j++)
       corr = L_mac(corr, *p++, *p1++);

    L_temp = L_sub(corr, cor_max);
    if (L_temp > (int)0)
    {
      cor_max = corr;
      t0 = i;
    }
    deb_sig--;
  }
  ener = 1;
  p = scal_sig - t0;
  for ( i=0; i<L_subfr ;i++, p++)  ener = L_mac(ener, *p, *p);
  ener0 = 1;
  p = scal_sig;
  for ( i=0; i<L_subfr; i++, p++)
    ener0 = L_mac(ener0, *p, *p);

  if (cor_max < 0)  {    cor_max = 0;  }

  temp = cor_max;
  if (ener > temp)  {    temp = ener;  }
  if (ener0 > temp)  {    temp = ener0;  }
  j = norm_l(temp);
  cmax = round(L_shl(cor_max, j));
  en = round(L_shl(ener, j));
  en0 = round(L_shl(ener0, j));

  temp = L_mult(cmax, cmax);
  temp = L_sub(temp, L_shr(L_mult(en, en0), 1));

  if (temp < (int)0)           /* if prediction gain < 3 dB   */
  {                               /* switch off pitch postfilter */
    for (i = 0; i < L_subfr; i++)
      signal_pst[i] = signal[i];
    return;
  }

  if (sub(cmax, en) > 0)      /* if pitch gain > 1 */
  {
    g0 = 21845;
    gain = 10923;
  }
  else {
    cmax = shr(mult(cmax, 16384), 1);  /* cmax(Q14) = cmax(Q15) * GAMMAP */
    en = shr(en, 1);          /* Q14 */
    i = add(cmax, en);
    if(i > 0)
    {
      gain = div_s(cmax, i);    /* gain(Q15) = cor_max/(cor_max+ener)  */
      g0 = sub(32767, gain);    /* g0(Q15) = 1 - gain */
    }
    else
    {
      g0 =  32767;
      gain = 0;
    }
  }


  for (i = 0; i < L_subfr; i++)
  {
    /* signal_pst[i] = g0*signal[i] + gain*signal[i-t0]; */

    signal_pst[i] = add(mult(g0, signal[i]), mult(gain, signal[i-t0]));

  }

  return;
}


void preemphasis(  short *signal,    short g,      short L  )
{
  static short mem_pre = 0;
  short *p1, *p2, temp, i;

  p1 = signal + L - 1;
  p2 = p1 - 1;
  temp = *p1;

  for (i = 0; i <= L-2; i++)
  {
    *p1-- = sub(*p1, mult(g, *p2--));
  }

  *p1 = sub(*p1, mult(g, mem_pre));

  mem_pre = temp;

  return;
}


void agc(  short *sig_in,    short *sig_out,   short l_trm  )
{
  static short past_gain=4096;         /* past_gain = 1.0 (Q12) */
  short i, exp;
  short gain_in, gain_out, g0, gain;                     /* Q12 */
  int s;

  short signal[40];

  /* calculate gain_out with exponent */

  for(i=0; i<l_trm; i++)
    signal[i] = shr(sig_out[i], 2);

  s = 0;
  for(i=0; i<l_trm; i++)
    s = L_mac(s, signal[i], signal[i]);

  if (s == 0) {
    past_gain = 0;
    return;
  }
  exp = sub(norm_l(s), 1);
  gain_out = round(L_shl(s, exp));

  /* calculate gain_in with exponent */

  for(i=0; i<l_trm; i++)
    signal[i] = shr(sig_in[i], 2);

  s = 0;
  for(i=0; i<l_trm; i++)
    s = L_mac(s, signal[i], signal[i]);

  if (s == 0) {
    g0 = 0;
  }
  else {
    i = norm_l(s);
    gain_in = round(L_shl(s, i));
    exp = sub(exp, i);

    s = L_deposit_l(div_s(gain_out,gain_in));   /* Q15 */
    s = L_shl(s, 7);           /* s(Q22) = gain_out / gain_in */
    s = L_shr(s, exp);         /* Q22, add exponent */

    /* i(Q12) = s(Q19) = 1 / sqrt(s(Q22)) */
    s = Inv_sqrt(s);           /* Q19 */
    i = round(L_shl(s,9));     /* Q12 */

    /* g0(Q12) = i(Q12) * (1-AGC_FAC)(Q15) */
    g0 = mult(i, (short)3276);       /* Q12 */
  }

  gain = past_gain;
  for(i=0; i<l_trm; i++) {
    gain = mult(gain, 29491);
    gain = add(gain, g0);
    sig_out[i] = extract_h(L_shl(L_mult(sig_out[i], gain), 3));
  }
  past_gain = gain;

  return;
}


void Init_Post_Process(void)
{
	y2_hi = 0;
	y2_lo = 0;
	y1_hi = 0;
	y1_lo = 0;
	x0   = 0;
	x1   = 0;
}


void Post_Process(  short signal[],   short lg)  
{
  short i, x2;
  int L_tmp;

  for(i=0; i<lg; i++)
  {
     x2 = x1;
     x1 = x0;
     x0 = signal[i];
     L_tmp     = Mpy_32_16(y1_hi, y1_lo, a100[1]);
     L_tmp     = L_add(L_tmp, Mpy_32_16(y2_hi, y2_lo, a100[2]));
     L_tmp     = L_mac(L_tmp, x0, b100[0]);
     L_tmp     = L_mac(L_tmp, x1, b100[1]);
     L_tmp     = L_mac(L_tmp, x2, b100[2]);
     L_tmp     = L_shl(L_tmp, 2); 
     signal[i] = round(L_shl(L_tmp, 1));

     y2_hi = y1_hi;
     y2_lo = y1_lo;
     L_Extract(L_tmp, &y1_hi, &y1_lo);
  }
  return;
}




short Parity_Pitch(    short pitch_index)
{
  short temp, sum, i, bit;

  temp = shr(pitch_index, 1);

  sum = 1;
  for (i = 0; i <= 5; i++) {
    temp = shr(temp, 1);
    bit = temp & (short)1;
    sum = add(sum, bit);
  }
  sum = sum & (short)1;


  return sum;
}

short  Check_Parity_Pitch(   short pitch_index,   short parity  )
{
  short temp, sum, i, bit;

  temp = shr(pitch_index, 1);

  sum = 1;
  for (i = 0; i <= 5; i++) {
    temp = shr(temp, 1);
    bit = temp & (short)1;
    sum = add(sum, bit);
  }
  sum = add(sum, parity);
  sum = sum & (short)1;

  return sum;
}




void L_Extract(int L_32, short *hi, short *lo)
{
  *hi  = extract_h(L_32);
  *lo  = extract_l( L_msu( L_shr(L_32, 1) , *hi, 16384));  /* lo = L_32>>1   */
  return;
}



int L_Comp(short hi, short lo)
{
  int L_32;

  L_32 = L_deposit_h(hi);
  return( L_mac(L_32, lo, 1));          /* = hi<<16 + lo<<1 */
}



int Mpy_32(short hi1, short lo1, short hi2, short lo2)
{
  int L_32;

  L_32 = L_mult(hi1, hi2);
  L_32 = L_mac(L_32, mult(hi1, lo2) , 1);
  L_32 = L_mac(L_32, mult(lo1, hi2) , 1);

  return( L_32 );
}



int Mpy_32_16(short hi, short lo, short n)
{
  int L_32;

  L_32 = L_mult(hi, n);
  L_32 = L_mac(L_32, mult(lo, n) , 1);

  return( L_32 );
}





void Lsp_get_quant(  short lspcb1[][10],   short lspcb2[][10],   short code0,    short code1,    short code2,    short fg[][10],   short freq_prev[][10],   short lspq[],   short fg_sum[])
{
  short j;
  short buf[10]; 
  for ( j = 0 ; j < 5 ; j++ ) buf[j] = add( lspcb1[code0][j], lspcb2[code1][j] );
  for ( j = 5 ; j < 10 ; j++ ) buf[j] = add( lspcb1[code0][j], lspcb2[code2][j] );
  Lsp_expand_1_2(buf, 10);
  Lsp_expand_1_2(buf, 5);
  Lsp_prev_compose(buf, lspq, fg, freq_prev, fg_sum);
  Lsp_prev_update(buf, freq_prev);
  Lsp_stability( lspq );
  return;
}


void Lsp_expand_1_2(  short buf[],   short gap  )
{
  short j, tmp;
  short diff;        /* Q13 */

  for ( j = 1 ; j < 10 ; j++ ) {
    diff = sub( buf[j-1], buf[j] );
    tmp = shr( add( diff, gap), 1 );

    if ( tmp > 0 ) {
      buf[j-1] = sub( buf[j-1], tmp );
      buf[j]   = add( buf[j], tmp );
    }
  }
  return;
}



void Lsp_prev_compose(  short lsp_ele[],   short lsp[],    short fg[][10],   short freq_prev[][10],    short fg_sum[] )
{
  short j, k;
  int L_acc;                 /* Q29 */

  for ( j = 0 ; j < 10 ; j++ ) {
    L_acc = L_mult( lsp_ele[j], fg_sum[j] );
    for ( k = 0 ; k < 4 ; k++ )
      L_acc = L_mac( L_acc, freq_prev[k][j], fg[k][j] );

    lsp[j] = extract_h(L_acc);
  }
  return;
}



////  extract elementary LSP from composed LSP with previous LSP

void Lsp_prev_extract(  short lsp[10],    short lsp_ele[10],   short fg[4][10],    short freq_prev[4][10],   short fg_sum_inv[10] )
{
  short j, k;
  int L_temp;                /* Q19 */
  short temp;                  /* Q13 */


  for ( j = 0 ; j < 10 ; j++ ) {
    L_temp = L_deposit_h(lsp[j]);
    for ( k = 0 ; k < 4 ; k++ )
      L_temp = L_msu( L_temp, freq_prev[k][j], fg[k][j] );

    temp = extract_h(L_temp);
    L_temp = L_mult( temp, fg_sum_inv[j] );
    lsp_ele[j] = extract_h( L_shl( L_temp, 3 ) );

  }
  return;
}


////  update previous LSP parameter

void Lsp_prev_update(  short lsp_ele[10],   short freq_prev[4][10] )
{
  short k;

  for ( k = 4-1 ; k > 0 ; k-- )
    Copy(freq_prev[k-1], freq_prev[k], 10);

  Copy(lsp_ele, freq_prev[0], 10);
  return;
}

void Lsp_stability(  short buf[]  )
{
  short j;
  short tmp;
  int L_diff;
  int L_acc, L_accb;

  for(j=0; j<10-1; j++) {
    L_acc = L_deposit_l( buf[j+1] );
    L_accb = L_deposit_l( buf[j] );
    L_diff = L_sub( L_acc, L_accb );

    if( L_diff < 0L ) {
      /* exchange buf[j]<->buf[j+1] */
      tmp      = buf[j+1];
      buf[j+1] = buf[j];
      buf[j]   = tmp;
    }
  }


  if( sub(buf[0], 40) <0 ) {
    buf[0] = 40;
    printf("lsp_stability warning Low \n");
  }
  for(j=0; j<10-1; j++) {
    L_acc = L_deposit_l( buf[j+1] );
    L_accb = L_deposit_l( buf[j] );
    L_diff = L_sub( L_acc, L_accb );

    if( L_sub(L_diff, 321)<0L ) {
      buf[j+1] = add( buf[j], 321 );
    }
  }

  if( sub(buf[10-1],25681)>0 ) {
    buf[10-1] = 25681;
    printf("lsp_stability warning High \n");
  }
  return;
}

void Lsp_decw_reset(  void)
{
  short i;
  for(i=0; i<4; i++)  Copy( &freq_prev_reset[0], &freq_prev[i][0], 10 );
  prev_ma = 0;
  Copy( freq_prev_reset, prev_lsp, 10);
}


void Lsp_iqua_cs( short prm[],   short lsp_q[],  short erase  )
{
  short mode_index;
  short code0;
  short code1;
  short code2;
  short buf[10];     /* Q13 */

  if( erase==0 ) {  /* Not frame erasure */
    mode_index = shr(prm[0] ,7) & (short)1;
    code0 = prm[0] & (short)(128 - 1);
    code1 = shr(prm[1] ,5) & (short)(32 - 1);
    code2 = prm[1] & (short)(32 - 1);

    /* compose quantized LSP (lsp_q) from indexes */

    Lsp_get_quant(lspcb1, lspcb2, code0, code1, code2, fg[mode_index], freq_prev, lsp_q, fg_sum[mode_index]);

    /* save parameters to use in case of the frame erased situation */

    Copy(lsp_q, prev_lsp, 10);
    prev_ma = mode_index;
  }
  else {           /* Frame erased */
    /* use revious LSP */

    Copy(prev_lsp, lsp_q, 10);

    /* update freq_prev */

    Lsp_prev_extract(prev_lsp, buf,
      fg[prev_ma], freq_prev, fg_sum_inv[prev_ma]);
    Lsp_prev_update(buf, freq_prev);
  }

  return;
}



void D_lsp(  short prm[],   short lsp_q[],   short erase )
{
  short lsf_q[10];  
  Lsp_iqua_cs(prm, lsf_q, erase);
  Lsf_lsp2(lsf_q, lsp_q, 10);
  return;
}


void Lsp_Az(  short lsp[],   short a[] )
{
  short i, j;
  int f1[6], f2[6];
  int t0;

  Get_lsp_pol(&lsp[0],f1);
  Get_lsp_pol(&lsp[1],f2);

  for (i = 5; i > 0; i--)
  {
    f1[i] = L_add(f1[i], f1[i-1]);        /* f1[i] += f1[i-1]; */
    f2[i] = L_sub(f2[i], f2[i-1]);        /* f2[i] -= f2[i-1]; */
  }

  a[0] = 4096;
  for (i = 1, j = 10; i <= 5; i++, j--)
  {
    t0   = L_add(f1[i], f2[i]);                 /* f1[i] + f2[i]             */
    a[i] = extract_l( L_shr_r(t0, 13) );        /* from Q24 to Q12 and * 0.5 */

    t0   = L_sub(f1[i], f2[i]);                 /* f1[i] - f2[i]             */
    a[j] = extract_l( L_shr_r(t0, 13) );        /* from Q24 to Q12 and * 0.5 */

  }

  return;
}


static void Get_lsp_pol(short *lsp, int *f)
{
  short i,j, hi, lo;
  int t0;

   /* All computation in Q24 */

   *f = L_mult(4096, 2048);             /* f[0] = 1.0;             in Q24  */
   f++;
   *f = L_msu((int)0, *lsp, 512);    /* f[1] =  -2.0 * lsp[0];  in Q24  */

   f++;
   lsp += 2;                            /* Advance lsp pointer             */

   for(i=2; i<=5; i++)
   {
     *f = f[-2];

     for(j=1; j<i; j++, f--)
     {
       L_Extract(f[-1] ,&hi, &lo);
       t0 = Mpy_32_16(hi, lo, *lsp);         /* t0 = f[-1] * lsp    */
       t0 = L_shl(t0, 1);
       *f = L_add(*f, f[-2]);                /* *f += f[-2]         */
       *f = L_sub(*f, t0);                   /* *f -= t0            */
     }
     *f   = L_msu(*f, *lsp, 512);            /* *f -= lsp<<9        */
     f   += i;                               /* Advance f pointer   */
     lsp += 2;                               /* Advance lsp pointer */
   }

   return;
}

void Lsf_lsp(  short lsf[],   short lsp[],   short m  )
{
  short i, ind, offset;
  int L_tmp;

  for(i=0; i<m; i++)
  {
    ind    = shr(lsf[i], 8);               /* ind    = b8-b15 of lsf[i] */
    offset = lsf[i] & (short)0x00ff;      /* offset = b0-b7  of lsf[i] */

    /* lsp[i] = table[ind]+ ((table[ind+1]-table[ind])*offset) / 256 */

    L_tmp   = L_mult(sub(table[ind+1], table[ind]), offset);
    lsp[i] = add(table[ind], extract_l(L_shr(L_tmp, 9)));
  }
  return;
}


void Lsp_lsf(  short lsp[],   short lsf[],   short m  )
{
  short i, ind, tmp;
  int L_tmp;

  ind = 63;    /* begin at end of table -1 */

  for(i= m-(short)1; i >= 0; i--)
  {
    /* find value in table that is just greater than lsp[i] */
    while( sub(table[ind], lsp[i]) < 0 )
    {
      ind = sub(ind,1);
    }

    /* acos(lsp[i])= ind*256 + ( ( lsp[i]-table[ind] ) * slope[ind] )/4096 */

    L_tmp  = L_mult( sub(lsp[i], table[ind]) , slope[ind] );
    tmp = round(L_shl(L_tmp, 3));     /*(lsp[i]-table[ind])*slope[ind])>>12*/
    lsf[i] = add(tmp, shl(ind, 8));
  }
  return;
}

void Lsf_lsp2(  short lsf[],   short lsp[],   short m  )
{
  short i, ind;
  short offset;   /* in Q8 */
  short freq;     /* normalized frequency in Q15 */
  int L_tmp;

  for(i=0; i<m; i++)
  {
/*    freq = abs_s(freq);*/
    freq = mult(lsf[i], 20861);          /* 20861: 1.0/(2.0*PI) in Q17 */
    ind    = shr(freq, 8);               /* ind    = b8-b15 of freq */
    offset = freq & (short)0x00ff;      /* offset = b0-b7  of freq */

    if ( sub(ind, 63)>0 ){
      ind = 63;                 /* 0 <= ind <= 63 */
    }

    /* lsp[i] = table2[ind]+ (slope_cos[ind]*offset >> 12) */

    L_tmp   = L_mult(slope_cos[ind], offset);   /* L_tmp in Q28 */
    lsp[i] = add(table2[ind], extract_l(L_shr(L_tmp, 13)));

  }
  return;
}


void Weight_Az(  short a[],    short gamma,   short m,     short ap[] )
{
  short i, fac;

  ap[0] = a[0];
  fac   = gamma;
  for(i=1; i<m; i++)
  {
    ap[i] = round( L_mult(a[i], fac) );
    fac   = round( L_mult(fac, gamma) );
  }
  ap[m] = round( L_mult(a[m], fac) );

  return;
}

void Int_qlpc( short lsp_old[],  short lsp_new[],  short Az[]  )
{
  short i;
  short lsp[10];  

  for (i = 0; i < 10; i++) {
    lsp[i] = add(shr(lsp_new[i], 1), shr(lsp_old[i], 1));
  }

  Lsp_Az(lsp, Az);              /* Subframe 1 */

  Lsp_Az(lsp_new, &Az[11]);    /* Subframe 2 */

  return;
}

void Gain_predict(   short past_qua_en[],    short code[],    short L_subfr,    short *gcode0,    short *exp_gcode0 )
{
   short  i, exp, frac;
   int  L_tmp;

   L_tmp = 0;
   for(i=0; i<L_subfr; i++) L_tmp = L_mac(L_tmp, code[i], code[i]);

   Log2(L_tmp, &exp, &frac);               
   L_tmp = Mpy_32_16(exp, frac, -24660);   
   L_tmp = L_mac(L_tmp, 32588, 32);        
   L_tmp = L_shl(L_tmp, 10);             
   for(i=0; i<4; i++) L_tmp = L_mac(L_tmp, pred[i], past_qua_en[i]); 
   *gcode0 = extract_h(L_tmp);    
   L_tmp = L_mult(*gcode0, 5439); 
   L_tmp = L_shr(L_tmp, 8);       
   L_Extract(L_tmp, &exp, &frac); 
   *gcode0 = extract_l(Pow2(14, frac)); 
   *exp_gcode0 = sub(14,exp);
}


void Gain_update(   short past_qua_en[],    int  L_gbk12 )
{
   short  i, tmp;
   short  exp, frac;
   int  L_acc;

   for(i=3; i>0; i--){
      past_qua_en[i] = past_qua_en[i-1];         /* Q10 */
   }
   Log2( L_gbk12, &exp, &frac );               /* L_gbk12:Q13       */
   L_acc = L_Comp( sub(exp,13), frac);         /* L_acc:Q16           */
   tmp = extract_h( L_shl( L_acc,13 ) );       /* tmp:Q13           */
   past_qua_en[0] = mult( tmp, 24660 );        /* past_qua_en[]:Q10 */
}


void Gain_update_erasure(   short past_qua_en[]  )
{
   short  i, av_pred_en;
   int  L_tmp;

   L_tmp = 0;                                                     /* Q10 */
   for(i=0; i<4; i++)
      L_tmp = L_add( L_tmp, L_deposit_l( past_qua_en[i] ) );
   av_pred_en = extract_l( L_shr( L_tmp, 2 ) );
   av_pred_en = sub( av_pred_en, 4096 );                          /* Q10 */

   if( sub(av_pred_en, -14336) < 0 ){
      av_pred_en = -14336;                              /* 14336:14[Q10] */
   }

   for(i=3; i>0; i--){
      past_qua_en[i] = past_qua_en[i-1];
   }
   past_qua_en[0] = av_pred_en;
}


void Syn_filt(  short a[],  short x[],   short y[],   short lg,    short mem[],  short update)
{
  short i, j;
  int s;
  short tmp[100];     /* This is usually done by memory allocation (lg+M) */
  short *yy;

  /* Copy mem[] to yy[] */

  yy = tmp;

  for(i=0; i<10; i++)
  {
    *yy++ = mem[i];
  }

  /* Do the filtering. */

  for (i = 0; i < lg; i++)
  {
    s = L_mult(x[i], a[0]);
    for (j = 1; j <= 10; j++)
      s = L_msu(s, a[j], yy[-j]);

    s = L_shl(s, 3);
    *yy++ = round(s);
  }

  for(i=0; i<lg; i++)
  {
    y[i] = tmp[i+10];
  }

  /* Update of memory if update==1 */

  if(update != 0)
     for (i = 0; i < 10; i++)
     {
       mem[i] = y[lg-10+i];
     }

 return;
}

void Residu(  short a[],   short x[],   short y[],   short lg )
{
  short i, j;
  int s;

  for (i = 0; i < lg; i++)
  {
    s = L_mult(x[i], a[0]);
    for (j = 1; j <= 10; j++)
      s = L_mac(s, a[j], x[i-j]);

    s = L_shl(s, 3);
    y[i] = round(s);
  }
  return;
}


int Pow2(    short exponent,   short fraction )
{
  short exp, i, a, tmp;
  int L_x;

  L_x = L_mult(fraction, 32);           /* L_x = fraction<<6           */
  i   = extract_h(L_x);                 /* Extract b10-b15 of fraction */
  L_x = L_shr(L_x, 1);
  a   = extract_l(L_x);                 /* Extract b0-b9   of fraction */
  a   = a & (short)0x7fff;

  L_x = L_deposit_h(tabpow[i]);         /* tabpow[i] << 16        */
  tmp = sub(tabpow[i], tabpow[i+1]);    /* tabpow[i] - tabpow[i+1] */
  L_x = L_msu(L_x, tmp, a);             /* L_x -= tmp*a*2        */

  exp = sub(30, exponent);
  L_x = L_shr_r(L_x, exp);

  return(L_x);
}

void Log2(  int L_x,   short *exponent,   short *fraction )
{
  short exp, i, a, tmp;
  int L_y;

  if( L_x <= (int)0 )
  {
    *exponent = 0;
    *fraction = 0;
    return;
  }

  exp = norm_l(L_x);
  L_x = L_shl(L_x, exp );               /* L_x is normalized */

  *exponent = sub(30, exp);

  L_x = L_shr(L_x, 9);
  i   = extract_h(L_x);                 /* Extract b25-b31 */
  L_x = L_shr(L_x, 1);
  a   = extract_l(L_x);                 /* Extract b10-b24 of fraction */
  a   = a & (short)0x7fff;

  i   = sub(i, 32);

  L_y = L_deposit_h(tablog[i]);         /* tablog[i] << 16        */
  tmp = sub(tablog[i], tablog[i+1]);    /* tablog[i] - tablog[i+1] */
  L_y = L_msu(L_y, tmp, a);             /* L_y -= tmp*a*2        */

  *fraction = extract_h( L_y);

  return;
}




int Inv_sqrt(   int L_x  )
{
  short exp, i, a, tmp;
  int L_y;

  if( L_x <= (int)0) return ( (int)0x3fffffffL);

  exp = norm_l(L_x);
  L_x = L_shl(L_x, exp );               /* L_x is normalize */

  exp = sub(30, exp);
  if( (exp & 1) == 0 )                  /* If exponent even -> shift right */
      L_x = L_shr(L_x, 1);

  exp = shr(exp, 1);
  exp = add(exp, 1);

  L_x = L_shr(L_x, 9);
  i   = extract_h(L_x);                 /* Extract b25-b31 */
  L_x = L_shr(L_x, 1);
  a   = extract_l(L_x);                 /* Extract b10-b24 */
  a   = a & (short)0x7fff;

  i   = sub(i, 16);

  L_y = L_deposit_h(tabsqr[i]);         /* tabsqr[i] << 16          */
  tmp = sub(tabsqr[i], tabsqr[i+1]);    /* tabsqr[i] - tabsqr[i+1])  */
  L_y = L_msu(L_y, tmp, a);             /* L_y -=  tmp*a*2         */

  L_y = L_shr(L_y, exp);                /* denormalization */

  return(L_y);
}


void Init_Decod_ld8a(void)
{
  exc = old_exc + 143 + 11;
  Set_zero(old_exc, 143+11);
  Set_zero(mem_syn, 10);

  sharp  = 3277;
  old_T0 = 60;
  gain_code = 0;
  gain_pitch = 0;

  Lsp_decw_reset();
 return;
}


void Decod_ld8a(  short  parm[],   short  synth[],   short  A_t[],    short  *T2  )
{
  short  *Az;  
  short  lsp_new[10];  
  short  code[40];   
  short  i, j, i_subfr;
  short  T0, T0_frac, index;
  short  bfi;
  int  L_temp;

  short bad_pitch;   
  short bad_lsf;   

  bfi = *parm++;  bad_lsf=0;;
  D_lsp(parm, lsp_new, add(bfi, bad_lsf));
  parm += 2;

  Int_qlpc(lsp_old, lsp_new, A_t);
  Copy(lsp_new, lsp_old, 10);
  Az = A_t;   
  for (i_subfr = 0; i_subfr < 80; i_subfr += 40)
  {

    index = *parm++;            /* pitch index */

    if(i_subfr == 0)
    {
      i = *parm++;              /* get parity check result */
      bad_pitch = add(bfi, i);
      if( bad_pitch == 0)
      {
        Dec_lag3(index, 20, 143, i_subfr, &T0, &T0_frac);
        old_T0 = T0;
      }
      else        /* Bad frame, or parity error */
      {
        T0  =  old_T0;
        T0_frac = 0;
        old_T0 = add( old_T0, 1);
        if( sub(old_T0, 143) > 0) {
            old_T0 = 143;
        }
      }
    }
    else                  /* second subframe */
    {
      if( bfi == 0)
      {
        Dec_lag3(index, 20, 143, i_subfr, &T0, &T0_frac);
        old_T0 = T0;
      }
      else
      {
        T0  =  old_T0;
        T0_frac = 0;
        old_T0 = add( old_T0, 1);
        if( sub(old_T0, 143) > 0) {
            old_T0 = 143;
        }
      }
    }
    *T2++ = T0;

   /*-------------------------------------------------*
    * - Find the adaptive codebook vector.            *
    *-------------------------------------------------*/

    Pred_lt_3(&exc[i_subfr], T0, T0_frac, 40);

   /*-------------------------------------------------------*
    * - Decode innovative codebook.                         *
    * - Add the fixed-gain pitch contribution to code[].    *
    *-------------------------------------------------------*/

    if(bfi != 0)        /* Bad frame */
    {

      parm[0] = Random() & (short)0x1fff;     /* 13 bits random */
      parm[1] = Random() & (short)0x000f;     /*  4 bits random */
    }
    Decod_ACELP(parm[1], parm[0], code);
    parm +=2;

    j = shl(sharp, 1);          /* From Q14 to Q15 */
    if(sub(T0, 40) <0 ) {
        for (i = T0; i < 40; i++) {
          code[i] = add(code[i], mult(code[i-T0], j));
        }
    }
    index = *parm++;  
    Dec_gain(index, code, 40, bfi, &gain_pitch, &gain_code);

    sharp = gain_pitch;
    if (sub(sharp, 13017) > 0) { sharp = 13017;  }
    if (sub(sharp, 3277) < 0) { sharp = 3277;  }

    for (i = 0; i < 40;  i++)
    {
       L_temp = L_mult(exc[i+i_subfr], gain_pitch);
       L_temp = L_mac(L_temp, code[i], gain_code);
       L_temp = L_shl(L_temp, 1);
       exc[i+i_subfr] = round(L_temp);
    }

    Overflow = 0;
    Syn_filt(Az, &exc[i_subfr], &synth[i_subfr], 40, mem_syn, 0);
    if(Overflow != 0)
    {
       for(i=0; i<143+11+80; i++) old_exc[i] = shr(old_exc[i], 2);
	   Syn_filt(Az, &exc[i_subfr], &synth[i_subfr], 40, mem_syn, 1);
    }
    else     Copy(&synth[i_subfr+40-10], mem_syn, 10);
    Az += 11;   
  }
  Copy(&old_exc[80], &old_exc[0], 143+11);
  return;
}

void Decod_ACELP(  short sign,  short index,  short cod[])
{
	short i, j;
	short pos[4];
	
	i      = index & (short)7;
	pos[0] = add(i, shl(i, 2));   
	
	index  = shr(index, 3);
	i      = index & (short)7;
	i      = add(i, shl(i, 2));   
	pos[1] = add(i, 1);
	index  = shr(index, 3);
	i      = index & (short)7;
	i      = add(i, shl(i, 2));   
	pos[2] = add(i, 2);
	index  = shr(index, 3);
	j      = index & (short)1;
	index  = shr(index, 1);
	i      = index & (short)7;
	i      = add(i, shl(i, 2));   
	i      = add(i, 3);
	pos[3] = add(i, j);	

	for (i=0; i<40; i++) {    cod[i] = 0;  }
	for (j=0; j<4; j++)
	{
		i = sign & (short)1;    sign = shr(sign, 1);
		if (i != 0) {
			cod[pos[j]] = 8191;  
		}
		else {
			cod[pos[j]] = -8192;     /* Q13 -1.0 */
		}
	}
	return;
}

void Dec_gain(   short index,   short code[], short L_subfr, short bfi, short *gain_pit,   short *gain_cod)
{
	short  index1, index2, tmp;
	short  gcode0, exp_gcode0;
	int  L_gbk12, L_acc, L_accb;
	

	static short past_qua_en[4] = { -14336, -14336, -14336, -14336 };
	if(bfi != 0){    *gain_pit = mult( *gain_pit, 29491 );   
	     if (sub( *gain_pit, 29491) > 0) *gain_pit = 29491;
         *gain_cod = mult( *gain_cod, 32111 );     ///update table of past quantized energies  (frame erasure) 
		 Gain_update_erasure(past_qua_en);
		 return;
	}
    index1 = imap1[ shr(index,4) ] ;
    index2 = imap2[ index & (16-1) ] ;
    *gain_pit = add( gbk1[index1][0], gbk2[index2][0] );    
    Gain_predict( past_qua_en, code, L_subfr, &gcode0, &exp_gcode0 );    
    L_acc = L_deposit_l( gbk1[index1][1] );
    L_accb = L_deposit_l( gbk2[index2][1] );
    L_gbk12 = L_add( L_acc, L_accb );  
    tmp = extract_l( L_shr( L_gbk12,1 ) );  
    L_acc = L_mult(tmp, gcode0);  
    L_acc = L_shl(L_acc, add( negate(exp_gcode0),(-12-1+1+16) ));
    *gain_cod = extract_h( L_acc );  
    Gain_update( past_qua_en, L_gbk12 );
	return;
}


void Dec_lag3(  short index,    short pit_min,   short pit_max,  short i_subfr,  short *T0,      short *T0_frac)
{
  short i;
  short T0_min, T0_max;

  if (i_subfr == 0)                  /* if 1st subframe */
  {
    if (sub(index, 197) < 0)
    {
      /* *T0 = (index+2)/3 + 19 */

      *T0 = add(mult(add(index, 2), 10923), 19);

      /* *T0_frac = index - *T0*3 + 58 */

      i = add(add(*T0, *T0), *T0);
      *T0_frac = add(sub(index, i), 58);
    }
    else
    {
      *T0 = sub(index, 112);
      *T0_frac = 0;
    }

  }

  else  /* second subframe */
  {
    /* find T0_min and T0_max for 2nd subframe */

    T0_min = sub(*T0, 5);
    if (sub(T0_min, pit_min) < 0)
    {
      T0_min = pit_min;
    }

    T0_max = add(T0_min, 9);
    if (sub(T0_max, pit_max) > 0)
    {
      T0_max = pit_max;
      T0_min = sub(T0_max, 9);
    }

    /* i = (index+2)/3 - 1 */
    /* *T0 = i + t0_min;    */

    i = sub(mult(add(index, 2), 10923), 1);
    *T0 = add(i, T0_min);

    /* t0_frac = index - 2 - i*3; */

    i = add(add(i, i), i);
    *T0_frac = sub(sub(index, 2), i);
  }

  return;
}



void prm2bits_ld8k( short   prm[],   short bits[] )
{
	short i;
	*bits++ = (short)0x6b21;
	*bits++ = (short)80;
	
	for (i = 0; i < 11; i++)
	{
        int2bin(prm[i], bitsno[i], bits);  
        bits += bitsno[i];
	}
	return;
}


static void int2bin( short value,  short no_of_bits, short *bitstream )
{
	short *pt_bitstream;
	short   i, bit;
	
	pt_bitstream = bitstream + no_of_bits;
	for (i = 0; i < no_of_bits; i++)
	{
		bit = value & (short)0x0001;      /* get lsb */
		if (bit == 0)
			*--pt_bitstream = (short)0x007f;
		else
			*--pt_bitstream = (short)0x0081;
		value >>= 1;
	}
}

/// bits2prm_ld8k - converts serial received bits to  encoder parameter vector 
void bits2prm_ld8k( short bits[],  short   prm[] )
{
	short i;
	for (i = 0; i < 11; i++)
	{
        prm[i] = bin2int(bitsno[i], bits); //printf("aaaa==%d\n",bitsno[i]);
        bits  += bitsno[i];
	}
}

///  bin2int - read specified bits from bit array  and convert to integer value 
static short bin2int(  short no_of_bits,  short *bitstream  )
{
	short   value, i;
	short   bit;
	value = 0;
	for (i = 0; i < no_of_bits; i++)
	{
		value <<= 1;
		bit = *bitstream++;
		if (bit == (short)0x0081)  value += 1;
	}
	return(value);
}




short sature(int L_var1)
  {
   short var_out;

   if (L_var1 > 0X00007fffL)
     {
      Overflow = 1;
      var_out = (short)0x7fff;
     }
   else if (L_var1 < (int)0xffff8000L)
     {
      Overflow = 1;
      var_out = (short)0x8000;
     }
   else
     {
      Overflow = 0;
      var_out = extract_l(L_var1);
     }

   return(var_out);
  }


short add(short var1,short var2)
  {
   short var_out;
   int L_somme;

   L_somme = (int) var1 + var2;
   var_out = sature(L_somme);
   return(var_out);
  }


short sub(short var1,short var2)
  {
   short var_out;
   int L_diff;

   L_diff = (int) var1 - var2;
   var_out = sature(L_diff);
   return(var_out);
  }


short abs_s(short var1)
  {
   short var_out;

   if (var1 == (short)0X8000 )
     {
      var_out = (short)0x7fff;
     }
   else
     {
      if (var1 < 0)
        {
         var_out = -var1;
        }
      else
        {
         var_out = var1;
        }
      }
    return(var_out);
  }



short shl(short var1,short var2)
  {
   short var_out;
   int resultat;

   //printf("%08x %08x ",var1,var2);
   if (var2 < 0)
     {
	   var2 = -var2;
      var_out = shr(var1,var2);
     }
   else
     {
      resultat = (int) var1 * ((int) 1 << var2);
     if ((var2 > 15 && var1 != 0) || (resultat != (int)((short) resultat)))
        {
         Overflow = 1;
         var_out = (var1 > 0) ? (short)0x7fff : (short)0x8000;
        }
      else
        {
         var_out = extract_l(resultat);
        }
     }
   //printf("%08x %08x %08x\n",var1,var2,var_out);getch();
   return(var_out);
  }



short shr(short var1,short var2)
  {
   short var_out;

   if (var2 < 0)
     {
	   var2=-var2;
	   var_out = shl(var1, var2);
     }
   else
     {
      if (var2 >= 15)
        {
         var_out = (var1 < 0) ? (short)(-1) : (short)0;
        }
      else
        {
         if (var1 < 0)
           {
     var_out = ~(( ~var1) >> var2 );
           }
         else
           {
            var_out = var1 >> var2;
           }
        }
     }

   return(var_out);
  }



short mult(short var1, short var2)
  {
   short var_out;
   int L_produit;

   L_produit = (int)var1 * (int)var2;

   L_produit = (L_produit & (int) 0xffff8000L) >> 15;

   if (L_produit & (int) 0x00010000L)
     L_produit = L_produit | (int) 0xffff0000L;

   var_out = sature(L_produit);
   return(var_out);
  }



int L_mult(short var1,short var2)
  {
   int L_var_out;

   L_var_out = (int)var1 * (int)var2;
   if (L_var_out != (int)0x40000000L)
     {
      L_var_out *= 2;
     }
   else
     {
      Overflow = 1;
      L_var_out = (int)0x7fffffffL;
     }

   return(L_var_out);
  }




short negate(short var1)
  {
   short var_out;

   var_out = (var1 == (short)0x8000) ? (short)0x7fff : -var1;
   return(var_out);
  }




short extract_h(int L_var1)
  {
   short var_out;

   var_out = (short) (L_var1 >> 16);
   return(var_out);
  }



short extract_l(int L_var1)
  {
   short var_out;

   var_out = (short) L_var1;
   return(var_out);
  }




short round(int L_var1)
  {
   short var_out;
   int L_arrondi;

   L_arrondi = L_add(L_var1, (int)0x00008000);
   var_out = extract_h(L_arrondi);
   return(var_out);
  }




int L_mac(int L_var3, short var1, short var2)
  {
   int L_var_out;
   int L_produit;

   L_produit = L_mult(var1,var2);
   L_var_out = L_add(L_var3,L_produit);
   return(L_var_out);
  }




int L_msu(int L_var3, short var1, short var2)
  {
   int L_var_out;
   int L_produit;

   L_produit = L_mult(var1,var2);
   L_var_out = L_sub(L_var3,L_produit);
   return(L_var_out);
  }





int L_add(int L_var1, int L_var2)
  {
   int L_var_out;

   L_var_out = L_var1 + L_var2;

   if (((L_var1 ^ L_var2) & (int)0x80000000L) == 0)
     {
      if ((L_var_out ^ L_var1) & (int)0x80000000L)
        {
         L_var_out = (L_var1 < 0) ? (int)0x80000000L : (int)0x7fffffffL;
         Overflow = 1;
        }
     }
   return(L_var_out);
  }



int L_sub(int L_var1, int L_var2)
  {
   int L_var_out;

   L_var_out = L_var1 - L_var2;

   if (((L_var1 ^ L_var2) & (int)0x80000000L) != 0)
     {
      if ((L_var_out ^ L_var1) & (int)0x80000000L)
        {
         L_var_out = (L_var1 < 0L) ? (int)0x80000000L : (int)0x7fffffffL;
         Overflow = 1;
        }
     }
   return(L_var_out);
  }


int L_shl(int L_var1, short var2)
{
   int L_var_out;   
   L_var_out = 0L;

   if (var2 <= 0)
     {
	   var2=-var2;
	   L_var_out = L_shr(L_var1,var2);
     }
   else
     {
      for(;var2>0;var2--)
        {
         if (L_var1 > (int) 0X3fffffffL)
           {
            Overflow = 1;
            L_var_out = (int)0x7fffffffL;
            break;
           }
         else
           {
            if (L_var1 < (int) 0xc0000000L)
              {
               Overflow = 1;
               L_var_out = (int)0x80000000L;
               break;
              }
           }
         L_var1 *= 2;
         L_var_out = L_var1;
        }
     }
   return(L_var_out);
  }




int L_shr(int L_var1, short var2)
  {
   int L_var_out;

   if (var2 < 0)
     {
	   var2=-var2;
      L_var_out = L_shl(L_var1,var2);
     }
   else
     {
      if (var2 >= 31)
        {
         L_var_out = (L_var1 < 0L) ? -1 : 0;
        }
      else
        {
         if (L_var1<0)
           {
            L_var_out = ~((~L_var1) >> var2);
           }
        else
          {
           L_var_out = L_var1 >> var2;
          }
        }
     }
   return(L_var_out);
  }



int L_deposit_h(short var1)
  {
   int L_var_out;

   L_var_out = (int) var1 << 16;
   return(L_var_out);
  }


int L_deposit_l(short var1)
  {
   int L_var_out;

   L_var_out = (int) var1;
   return(L_var_out);
  }



int L_shr_r(int L_var1,short var2)
  {
   int L_var_out;

   if (var2 > 31)
     {
      L_var_out = 0;
     }
   else
     {
      L_var_out = L_shr(L_var1,var2);
      if (var2 > 0)
        {
         if ( (L_var1 & ( (int)1 << (var2-1) )) != 0)
           {
            L_var_out++;
           }
        }
     }
   return(L_var_out);
  }




short div_s(short var1, short var2)
  {
   short var_out = 0;
   short iteration;
   int L_num;
   int L_denom;

   if ((var1 > var2) || (var1 < 0) || (var2 < 0))
     {
      printf("Division Error var1=%d  var2=%d\n",var1,var2);
      exit(0);
     }

   if (var2 == 0)
     {
      printf("Division by 0, Fatal error \n");
      exit(0);
     }

   if (var1 == 0)
     {
      var_out = 0;
     }
   else
     {
      if (var1 == var2)
        {
         var_out = (short)0x7fff;
        }
      else
        {
         L_num = L_deposit_l(var1);
         L_denom = L_deposit_l(var2);

         for(iteration=0;iteration<15;iteration++)
           {
            var_out <<=1;
            L_num <<= 1;

            if (L_num >= L_denom)
              {
               L_num = L_sub(L_num,L_denom);
               var_out = add(var_out,1);
              }
           }
        }
     }

   return(var_out);
  }




short norm_l(int L_var1)
  {
   short var_out;

   if (L_var1 == 0)
     {
      var_out = 0;
     }
   else
     {
      if (L_var1 == (int)0xffffffffL)
        {
         var_out = 31;
        }
      else
        {
         if (L_var1 < 0)
           {
            L_var1 = ~L_var1;
           }

         for(var_out = 0;L_var1 < (int)0x40000000L;var_out++)
           {
            L_var1 <<= 1;
           }
        }
     }

   return(var_out);
  }


int g729a_decode(unsigned char in[], int len, unsigned char out[])
{
	short  synth_buf[80+10], *synth, parm[11+1], serial[82], Az_dec[11*2], T2[2];	
	int i,j,k, m, n;	
	unsigned char sf[600];
    
	for (i=0; i<10; i++) synth_buf[i] = 0;   synth = synth_buf + 10; 	//bad_lsf = 0;   
	Init_Decod_ld8a();   Init_Post_Filter();   Init_Post_Process();	n=0;
	for(k=0;k<len;)
	{		
		m=in[k+8]+(in[k+9]<<8)+(in[k+10]<<16)+(in[k+11]<<24); k+=12;
		if(m!=20) { for(i=0;i<320;i++)out[i+n]=0;}// for(i=0;i<8;i++)out[i+n+320]=in[i+k];}////////////////////
		else {
			sf[0]=0x21;sf[1]=0x6b;sf[2]=0x50;sf[3]=0x00;		
			for(i=0;i<10;i++)for(j=0;j<8;j++)if((in[i+k]>>(7-j)&1)==1){sf[4+(i*8+j)*2]=0x81;sf[4+(i*8+j)*2+1]=0;}else {sf[4+(i*8+j)*2]=0x7f;sf[4+(i*8+j)*2+1]=0;}
			for(i=0;i<82;i++)serial[i]=(sf[i*2]<<0)+(sf[i*2+1]<<8);		 
			bits2prm_ld8k( &serial[2], &parm[1]);  parm[0] = 0;           
			for (i=2; i < 82; i++)if (serial[i] == 0 ) parm[0] = 1;
			parm[4] = Check_Parity_Pitch(parm[3], parm[4]);
			Decod_ld8a(parm, synth, Az_dec, T2);	  Post_Filter(synth, Az_dec, T2);  	  Post_Process(synth, 80);
			for(i=0;i<80;i++){out[i*2+n]=synth[i]>>8&0xff; out[i*2+n+1]=synth[i]>>0&0xff; }

			sf[0]=0x21;sf[1]=0x6b;sf[2]=0x50;sf[3]=0x00;		
			for(i=0;i<10;i++)for(j=0;j<8;j++)if((in[i+k+10]>>(7-j)&1)==1){sf[4+(i*8+j)*2]=0x81;sf[4+(i*8+j)*2+1]=0;}else {sf[4+(i*8+j)*2]=0x7f;sf[4+(i*8+j)*2+1]=0;}
			for(i=0;i<82;i++)serial[i]=(sf[i*2]<<0)+(sf[i*2+1]<<8);		 
			bits2prm_ld8k( &serial[2], &parm[1]);  parm[0] = 0;           
			for (i=2; i < 82; i++)if (serial[i] == 0 ) parm[0] = 1;
			parm[4] = Check_Parity_Pitch(parm[3], parm[4]);
			Decod_ld8a(parm, synth, Az_dec, T2);	  Post_Filter(synth, Az_dec, T2);  	  Post_Process(synth, 80);
			for(i=0;i<80;i++){out[i*2+n+160]=synth[i]>>8&0xff; out[i*2+n+1+160]=synth[i]>>0&0xff; }
			//for(i=0;i<8;i++)out[i+n+320]=in[i+k];
		}
		n+=320; k+=m;
	}    
	return n;
}


void g729a_decode_zhr(char filename1[],char filename2[])
{	
	int i,  n, ll, len;
	unsigned int t1,t2,t3,t4;
	FILE *fp, *fn;	
	char file[256];
	unsigned char *in1, *in2, *out1, *out2, se[2];
	unsigned char AU_header[24] = {'.','s','n','d',0,0,0,0x18,0xff,0xff,0xff,0xff,0,0,0,0x03,0,0,0x1f,0x40,0,0,0,0x01}; //0x803e0000, 0x401f0000; //16000 or 8000
	
    fp= fopen(filename1,"rb");
	fn= fopen(filename2,"rb");
	if(fp==NULL && fn==NULL){printf("no file\n"); return;}
	if(fp==NULL)
	{
		fseek(fn, 0,SEEK_END);  ll = ftell(fn);  in2 = (unsigned char *)malloc(ll);   rewind(fn);   i = fread(in2,sizeof(char),ll,fn);fclose(fn);
		out2  = (unsigned char*)malloc(ll*20);	 n=g729a_decode(in2, ll,  out2);	
		sprintf(file,"%s.single.au",filename2);
		if((fp= fopen(file,"wb"))==NULL){  printf("OPEN FILE2 FAIL\n");   return ; }
		fwrite(AU_header, 1, 24, fp);
		fwrite(out2, 1, n, fp);
		fclose(fp);
		free(in2);
		free(out2);
		return;
	}

	if(fn==NULL)
	{
		fseek(fp, 0,SEEK_END);  ll = ftell(fp);  in1 = (unsigned char *)malloc(ll);   rewind(fp);   i = fread(in1,sizeof(char),ll,fp);fclose(fp);
		out1  = (unsigned char*)malloc(ll*20);	 n=g729a_decode(in1, ll,  out1);	
		sprintf(file,"%s.single.au",filename1);
		if((fp= fopen(file,"wb"))==NULL){  printf("OPEN FILE1 FAIL\n");   return ; }
		fwrite(AU_header, 1, 24, fp);
		fwrite(out1, 1, n, fp);
		fclose(fp);
		free(in1);
		free(out1);
		return;
	}
	
	fseek(fp, 0,SEEK_END);  ll = ftell(fp);  in1 = (unsigned char *)malloc(ll);   rewind(fp);   i = fread(in1,sizeof(char),ll,fp);fclose(fp);
	out1  = (unsigned char*)malloc(ll*20);	 n=g729a_decode(in1, ll,  out1); len = n;
	fseek(fn, 0,SEEK_END);  ll = ftell(fn);  in2 = (unsigned char *)malloc(ll);   rewind(fn);   i = fread(in2,sizeof(char),ll,fn);fclose(fn);
	out2  = (unsigned char*)malloc(ll*20);	 n=g729a_decode(in2, ll,  out2); ll=n;	
	t1=in1[0]+ (in1[1]<<8)+ (in1[2]<<16)+ (in1[3]<<24);  	t2=in1[4]+ (in1[5]<<8)+ (in1[6]<<16)+ (in1[7]<<24);
	t3=in2[0]+ (in2[1]<<8)+ (in2[2]<<16)+ (in2[3]<<24);	    t4=in2[0]+ (in2[1]<<8)+ (in2[2]<<16)+ (in2[3]<<24);
	//printf("%d %d\n%d %d\n",t1,t2,t3,t4);

	sprintf(file,"%s.paired.au",filename1);
	if((fp= fopen(file,"wb"))==NULL){  printf("OPEN FILE FAIL\n");   return ; }
	AU_header[23]=2;
	fwrite(AU_header, 1, 24, fp);
	if(len>=ll)
	{
		for(i=0;i<ll;i+=2)	{ fwrite(out1+i,1,2,fp); fwrite(out2+i,1,2,fp);	}
		se[0]=0; se[1]=0; 
		for(i=ll;i<len;i+=2){ fwrite(out1+i,1,2,fp);	fwrite(se,1,2,fp);	}
	}
	if(len<ll)
	{
		for(i=0;i<len;i+=2)	{ fwrite(out1+i,1,2,fp); fwrite(out2+i,1,2,fp);	}
		se[0]=0; se[1]=0; 
		for(i=len;i<ll;i+=2){ fwrite(se,1,2,fp);	fwrite(out2+i,1,2,fp);	}
	}
	fclose(fp);
	free(in1); free(in2); free(out1); free(out2);
	return ;
}

