//bitmaps.h
//collection of small images.
typedef const rom char rconst;
#define _USE_TDS
/*
#ifdef _USE_SYMMETRICAL_SYMBOL
rconst bmwSymbolSmall[]={22,23,0,62,0,
192,193,1,
32,62,2,
144,255,12,
232,255,11,
244,193,23,
114,24,39,
58,120,46,
58,248,46,
29,248,93,
29,248,93,
221,255,93,
221,15,92,
221,15,92,
186,15,46,
58,15,46,
114,12,39,
244,193,23,
232,255,11,
152,255,12,
32,62,2,
192,193,1,
0,62,0,
};
#else
rconst bmwSymbolSmall[]={22,21,0,31,0,
224,224,0,
16,31,1,
208,127,3,
232,255,2,
244,224,5,
50,140,9,
26,60,11,
26,124,11,
29,252,22,
13,252,22,
237,255,22,
237,7,22,
237,7,23,
218,7,11,
154,7,11,
50,134,9,
244,224,5,
232,255,2,
216,127,3,
16,31,1,
224,224,0,
0,31,0};
#endif

*/

rconst SmallBall[]={6,7,
28,
62,
123,
125,
127,
62,
28
};

#ifdef _USECHECKIMAGE
rconst BMWCheck[]={0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,192,7,0,0,
0,240,31,0,0,
0,248,127,0,0,
0,252,127,0,0,
0,62,248,0,0,
0,30,240,0,0,
0,15,224,1,0,
0,15,224,1,0,
0,15,224,1,0,
0,15,224,1,0,
0,15,224,1,0,
0,15,224,1,0,
0,30,240,0,0,
0,30,240,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,255,255,1,0,
0,255,255,1,0,
0,255,255,1,0,
0,255,255,1,0,
0,192,3,0,0,
0,192,3,0,0,
0,192,3,0,0,
0,192,3,0,0,
0,192,3,0,0,
0,255,255,1,0,
0,255,255,1,0,
0,255,255,1,0,
0,255,255,1,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,255,255,1,0,
0,255,255,1,0,
0,255,255,1,0,
0,255,255,1,0,
0,207,227,1,0,
0,207,227,1,0,
0,207,227,1,0,
0,207,227,1,0,
0,207,227,1,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,192,7,0,0,
0,240,31,0,0,
0,248,127,0,0,
0,252,127,0,0,
0,62,248,0,0,
0,30,240,0,0,
0,15,224,1,0,
0,15,224,1,0,
0,15,224,1,0,
0,15,224,1,0,
0,15,224,1,0,
0,15,224,1,0,
0,30,240,0,0,
0,30,240,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,255,255,1,0,
0,255,255,1,0,
0,255,255,1,0,
0,255,255,1,0,
0,128,3,0,0,
0,224,15,0,0,
0,240,31,0,0,
0,248,63,0,0,
0,254,254,0,0,
0,63,248,1,0,
0,31,240,1,0,
0,15,224,1,0,
0,3,128,1,0,
0,1,0,1,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,0,0,0,
};
#endif

#ifdef _USE_TDS
rconst WelcomeImage[]={0,0,0,0,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,0,0,
0,0,0,0,0,
0,128,65,0,0,
0,192,65,56,0,
0,128,67,63,0,
192,128,195,7,0,
224,128,195,0,0,
112,142,67,0,0,
112,142,67,0,0,
112,142,67,24,0,
112,206,3,63,0,
112,254,1,39,0,
240,251,1,32,0,
240,251,0,56,0,
224,115,0,63,0,
224,1,0,7,0,
0,0,0,0,0,
0,128,3,56,0,
0,128,3,63,0,
192,192,3,7,0,
96,224,3,2,0,
112,224,3,3,0,
112,240,3,3,0,
112,184,3,56,0,
112,156,3,63,0,
240,159,227,39,0,
240,143,227,33,0,
224,135,3,49,0,
224,1,0,31,0,
0,0,0,14,0,
0,128,1,0,0,
0,192,3,28,0,
0,140,3,62,0,
192,143,3,35,0,
240,143,3,33,0,
240,143,3,49,0,
240,143,3,31,0,
112,206,3,14,0,
112,254,1,0,0,
112,254,1,56,0,
112,252,0,63,0,
112,120,192,39,0,
112,0,192,32,0,
112,0,64,32,0,
0,0,64,56,0,
128,225,193,31,0,
128,255,131,7,0,
240,255,3,0,0,
240,255,3,56,0,
240,31,3,63,0,
240,1,67,7,0,
128,1,67,0,0,
128,1,0,28,0,
128,1,0,62,0,
0,248,1,39,0,
0,254,3,37,0,
0,255,3,37,0,
0,255,3,23,0,
128,7,3,6,0,
128,1,1,0,0,
128,129,3,32,0,
128,249,3,38,0,
192,255,3,47,0,
248,255,3,61,0,
248,255,0,25,0,
248,7,0,1,0,
120,192,1,0,0,
0,142,3,28,0,
0,31,3,62,0,
0,63,3,39,0,
128,63,3,37,0,
128,57,3,37,0,
128,249,3,23,0,
128,241,1,6,0,
128,241,1,0,0,
128,227,0,56,0,
128,3,0,63,0,
0,0,224,7,0,
0,0,224,0,0,
0,0,0,0,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,0,0,
};
#else

rconst WelcomeImage[]={
0,0,0,0,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,6,0,
0,0,0,0,0,
0,0,0,0,0,
0,0,64,0,0,
0,0,64,56,0,
0,0,64,63,0,
0,0,192,7,0,
0,0,192,0,0,
0,0,64,0,0,
0,128,65,0,0,
0,192,65,24,0,
0,128,3,63,0,
192,128,3,39,0,
224,128,3,32,0,
112,142,3,56,0,
112,142,3,63,0,
112,142,3,7,0,
112,206,3,0,0,
112,254,1,56,0,
240,251,1,63,0,
240,251,0,7,0,
224,115,0,2,0,
224,1,0,3,0,
0,0,0,3,0,
0,128,3,56,0,
0,128,3,63,0,
192,192,227,39,0,
96,224,227,33,0,
112,224,3,49,0,
112,240,3,31,0,
112,184,3,14,0,
112,156,3,0,0,
240,159,3,28,0,
240,143,3,62,0,
224,135,3,35,0,
224,1,0,33,0,
0,0,0,49,0,
0,128,1,31,0,
0,192,3,14,0,
0,140,3,0,0,
192,143,3,56,0,
240,143,3,63,0,
240,143,195,39,0,
240,143,195,32,0,
112,206,67,32,0,
112,254,65,56,0,
112,254,193,31,0,
112,252,128,7,0,
112,120,0,0,0,
112,0,0,56,0,
112,0,0,63,0,
0,0,64,7,0,
128,225,65,0,0,
128,255,3,28,0,
240,255,3,62,0,
240,255,3,39,0,
240,31,3,37,0,
240,1,3,37,0,
128,1,3,23,0,
128,1,0,6,0,
128,1,0,0,0,
0,248,1,32,0,
0,254,3,38,0,
0,255,3,47,0,
0,255,3,61,0,
128,7,3,25,0,
128,1,1,1,0,
128,129,3,0,0,
128,249,3,28,0,
192,255,3,62,0,
248,255,3,39,0,
248,255,0,37,0,
248,7,0,37,0,
120,0,0,23,0,
0,0,0,6,0,
0,0,0,0,0,
0,0,0,56,0,
0,0,0,63,0,
0,0,224,7,0,
0,0,224,0,0,
0,0,0,0,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,3,0,
0,0,0,0,0
};
#endif
/*
rconst Style1_Demo[]={0,0,64,0,0,
0,0,88,194,0,
252,255,95,227,0,
254,255,95,177,0,
254,255,95,159,0,
30,254,95,142,0,
30,254,95,0,0,
30,254,95,126,0,
30,254,95,255,0,
30,254,95,129,0,
30,254,95,255,0,
254,255,95,126,0,
254,255,95,0,0,
252,255,95,12,0,
96,24,88,6,0,
96,240,71,255,0,
192,224,79,255,0,
128,31,76,0,0,
0,255,71,0,0,
0,224,67,194,0,
0,0,64,227,0,
176,1,64,177,0,
188,135,79,159,0,
31,222,95,142,0,
27,216,88,0,0,
31,222,90,192,0,
188,199,94,192,0,
176,129,78,0,0,
0,0,64,126,0,
0,0,64,255,0,
0,0,64,129,0,
0,0,64,255,0,
0,0,64,126,0,
0,0,64,0,0,
0,0,64,66,0,
0,0,64,195,0,
0,7,64,137,0,
128,3,64,255,0,
128,3,64,118,0,
192,1,64,0,0,
240,255,71,192,0,
240,255,71,192,0,
240,255,71,0,0,
0,0,64,12,0,
0,0,64,6,0,
0,0,64,255,0,
0,0,64,255,0,
128,255,64,0,0,
224,255,67,0,0,
224,255,67,12,0,
112,0,71,6,0,
48,0,70,255,0,
48,0,70,255,0,
112,0,71,0,0,
224,255,67,0,0,
224,255,67,0,0,
128,255,64,0,0,
0,0,64,0,0,
0,0,64,0,0,
0,0,71,0,0,
0,0,71,0,0,
0,0,71,0,0,
0,0,64,0,0,
0,0,64,0,0,
0,0,64,0,0,
192,128,65,0,0,
224,128,67,0,0,
240,128,71,0,0,
48,12,71,0,0,
48,12,70,0,0,
48,14,70,0,0,
240,31,71,0,0,
224,255,67,0,0,
192,243,67,0,0,
0,224,64,12,0,
0,0,64,6,0,
0,0,64,255,0,
0,0,64,255,0,
0,12,64,0,0,
0,76,80,0,0,
0,236,95,126,0,
0,236,95,255,0,
0,12,80,129,0,
0,12,64,255,0,
0,204,79,126,0,
0,236,95,0,0,
0,44,80,204,0,
0,236,95,204,0,
254,205,79,0,0,
254,13,64,48,0,
0,205,79,44,0,
0,237,95,34,0,
0,45,80,255,0,
0,236,95,255,0,
0,204,79,32,0,
0,12,64,66,0,
0,236,95,195,0,
0,236,95,137,0,
0,12,70,255,0,
0,140,95,118,0,
0,140,89,0,0
};


rconst DemoStyle2[]={0,0,64,0,0,
0,0,64,194,0,
0,31,64,227,0,
0,31,64,177,0,
0,31,64,159,0,
0,31,64,142,0,
0,31,64,0,0,
192,127,64,126,0,
128,63,64,255,0,
0,31,64,129,0,
0,14,64,255,0,
0,4,64,126,0,
0,0,64,0,0,
0,0,64,12,0,
0,0,88,6,0,
252,255,95,255,0,
254,255,95,255,0,
254,255,95,0,0,
30,254,95,0,0,
30,254,95,194,0,
30,254,95,227,0,
30,254,95,177,0,
30,254,95,159,0,
30,254,95,142,0,
254,255,95,0,0,
254,255,95,192,0,
252,255,95,192,0,
96,24,88,0,0,
96,240,71,126,0,
192,224,79,255,0,
128,31,76,129,0,
0,255,71,255,0,
0,224,67,126,0,
0,0,64,0,0,
0,0,64,66,0,
0,0,64,195,0,
0,0,64,137,0,
0,0,64,255,0,
0,0,64,118,0,
0,0,64,0,0,
0,0,64,192,0,
0,0,64,192,0,
0,0,64,0,0,
0,0,64,12,0,
192,225,65,6,0,
224,243,67,255,0,
240,255,71,255,0,
112,30,71,0,0,
48,12,70,0,0,
48,12,70,12,0,
112,30,71,6,0,
240,255,71,255,0,
224,243,67,255,0,
192,225,65,0,0,
0,0,64,0,0,
0,224,64,0,0,
0,240,64,0,0,
0,220,64,0,0,
0,206,64,0,0,
128,195,64,0,0,
224,193,64,0,0,
240,255,71,0,0,
240,255,71,0,0,
240,255,71,0,0,
0,192,64,0,0,
0,192,64,0,0,
0,0,64,0,0,
0,0,64,0,0,
128,255,64,0,0,
224,255,67,0,0,
224,255,67,0,0,
112,0,71,0,0,
48,0,70,0,0,
48,0,70,0,0,
112,0,71,12,0,
224,255,67,6,0,
224,255,67,255,0,
128,255,64,255,0,
0,0,64,0,0,
0,0,64,0,0,
0,0,64,126,0,
0,0,64,255,0,
0,0,64,129,0,
0,0,64,255,0,
0,255,64,126,0,
0,255,64,0,0,
0,48,64,204,0,
0,252,64,204,0,
0,204,64,0,0,
0,0,64,48,0,
0,0,64,44,0,
0,252,64,34,0,
0,252,64,255,0,
0,4,64,255,0,
0,252,64,32,0,
0,252,64,66,0,
0,4,64,195,0,
0,252,64,137,0,
0,248,64,255,0,
0,0,64,118,0,
0,0,64,0,0
};
*/
#ifdef _USE_PRESSURESENSEDEMO
rconst pressureSenseDemo[]={63,0,0,0,0,
0,0,0,0,0,
0,0,195,63,0,
0,192,231,127,0,
0,95,244,255,0,
0,155,55,192,0,
240,31,176,223,0,
252,31,176,223,0,
14,30,176,223,0,
103,28,176,223,0,
147,24,176,223,0,
3,25,176,223,0,
3,25,176,223,0,
67,25,176,223,0,
195,120,176,223,0,
199,121,176,223,0,
14,64,176,223,0,
252,127,176,223,0,
240,127,176,223,0,
0,0,176,223,0,
16,0,176,223,0,
240,7,176,223,0,
240,7,176,223,0,
16,0,176,223,0,
0,0,176,223,0,
240,3,176,223,0,
240,7,176,223,0,
0,4,179,223,0,
240,199,183,223,0,
240,67,180,223,0,
0,128,183,223,0,
240,7,176,223,0,
240,7,52,223,0,
144,1,176,223,0,
240,7,176,223,0,
96,198,180,223,0,
0,64,181,223,0,
240,71,183,223,0,
240,7,176,223,0,
144,4,176,223,0,
240,7,176,223,0,
96,3,176,223,0,
0,0,176,223,0,
192,1,176,223,0,
224,3,176,223,0,
48,6,176,223,0,
16,4,176,223,0,
48,6,176,223,0,
224,3,48,192,0,
192,1,48,192,0,
0,0,48,192,0,
0,0,48,192,0,
0,0,48,192,0,
0,0,48,192,0,
0,0,48,192,0,
0,0,48,192,0,
0,0,48,192,0,
48,0,48,192,0,
24,0,48,192,0,
12,128,52,192,0,
254,207,247,192,0,
254,15,52,192,0,
0,0,48,192,0,
0,0,48,192,0,
0,0,48,192,0,
0,12,48,192,0,
0,12,48,192,0,
0,0,48,192,0,
0,0,48,192,0,
24,12,48,192,0,
28,14,48,192,0,
6,15,48,192,0,
134,13,48,192,0,
198,12,48,192,0,
126,12,48,192,0,
60,12,48,192,0,
0,0,112,224,0,
0,0,240,255,0,
0,0,48,192,0,
0,0,240,255,0,
0,0,112,224,0,
252,3,48,192,0,
252,131,52,192,0,
16,194,55,192,0,
16,2,52,192,0,
240,3,48,192,0,
224,1,244,192,0,
0,0,48,192,0,
160,193,52,192,0,
208,67,53,192,0,
80,66,55,192,0,
240,3,48,192,0,
224,3,48,192,0,
0,0,48,192,0,
240,3,48,192,0,
240,3,48,192,0,
16,0,48,192,0,
16,0,48,192,0,
0,0,112,192,0,
0,0,224,127,0,
0,0,192,63,0,
0,0,0,0,0
};
#endif