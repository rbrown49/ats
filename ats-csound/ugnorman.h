/* header file for all of the ATScsound functions by Alex Norman
*/

typedef struct atsdataloc
{
	double amp;
	double freq;
} ATS_DATA_LOC;

typedef struct _randiats
{ //the data for the randi UG
  int   size; //size of the frame in samples this should be sr/freq.
  float a1;   //first amplitude value
  float a2;   //next  amplitude value
  int   cnt;  //sample position counter
} RANDIATS;

typedef struct _atsnzaux
{
	double   buf[25];
	float   phaseinc[25];
	float   nfreq[25];
	RANDIATS randinoise[25];
} atsnzAUX;

typedef struct atsstruct
{
	double  magic;  /* ats magic number */
	double  sampr;  /* sampling rate */
	double  frmsz;  /* frame size in samples */
	double  winsz;  /* window size in samples */
	double  npartials;      /* number of partials */
	double  nfrms;  /* number of frames */
	double  ampmax; /* max amplitude */
	double  freqmax;        // max frequency
	double  dur;    /* duration seconds */
	double  type;   /* Ats Frame type 1-4 */
} ATSSTRUCT;


typedef struct _atsinfo
{
	OPDS    h;
	float   *ireturn, *ifileno, *ilocation; //the return value, the ats file and a location selection
}	ATSINFO;


/* structures to pass data to the opcodes */

typedef struct _atsread
{
	OPDS    h;
	float   *kfreq, *kamp, *ktimpnt, *ifileno, *ipartial; //outputs (2) and inputs
	int  maxFr;	// indicates the maximun frame
	int	prFlg;	//a flag used to indicate if we've steped out of the time range of the data, so we don't print too many warnings
	double * datastart;	//points to the start of the data
	int	partialloc, frmInc;	//tells the location of the partal to output and the number of doubles to increment to get to the next frame
	MEMFIL * atsmemfile;
	double timefrmInc;
	int swapped;	//indicates if the data file is byte swapped or not
} ATSREAD;

typedef struct _atsreadnz
{
	OPDS    h;
	float   *kenergy, *ktimpnt, *ifileno, *inzbin; //outputs (1) and inputs
	int  maxFr;
	int	prFlg;	//a flag used to indicate if we've steped out of the time range of the data, so we don't print too many warnings
	double * datastart;	//points to the start of the data
	int nzbandloc, frmInc;
	MEMFIL * atsmemfile;
	double  timefrmInc;
	int swapped;	//indicates if the data file is byte swapped or not
} ATSREADNZ;

typedef struct _atsadd
{
	OPDS    h;
	float   *aoutput, *ktimpnt, *kfmod, *ifileno, *ifn, *iptls; // audio output and k & i inputs
	float   *iptloffset, *iptlincr, *igatefun; // optional arguments
	
	FUNC    *ftp, *AmpGateFunc;     // pointer to table with wave to synthesize sound
	AUXCH   auxch;
	MEMFIL * atsmemfile;
	     
	double  maxFr;
	int	prFlg;	//a flag used to indicate if we've steped out of the time range of the data, so we don't print too many warnings
	double  timefrmInc;
	double	MaxAmp;         // maximum amplitude in anaylsis file
	int firstpartial, partialinc, frmInc;
	double * datastart;
	int memsize;	//stores the size of memeory in the aux alloc
	double  *oscphase;      // oscillator phase
	ATS_DATA_LOC * buf;
	int swapped;	//indicates if the data file is byte swapped or not
} ATSADD;

typedef struct _atsaddnz
{  
	OPDS    h;
	float   *aoutput, *ktimpnt, *ifileno, *ibands; // audio output and k & i inputs
	float   *ibandoffset, *ibandincr; // optional arguments
        
	MEMFIL  *atsmemfile;   // a pointer into the ATS file
        
	double  maxFr;
	int	prFlg;
	int     frmInc;         // amount to increment frame pointer to get to next frame
	double  timefrmInc;
	double  winsize;        // size of windows in analysis file, used to compute RMS amplitude from energy in noise band
	
	double * datastart;
	double firstband;

	double  buf[25];           // stores band information for passing data
	double   phaseinc[25];       // to create an array of noise
	double	oscphase[25];       //the phase of all the oscilators
	RANDIATS randinoise[25];	// a pointer to the interpolated random noise info
	double	nfreq[25];
	ATSSTRUCT atshead;
	int swapped;	//indicates if the data file is byte swapped or not
} ATSADDNZ;

typedef struct _atsbufread
{
	OPDS    h;
	float   *ktimpnt, *kfmod, *ifileno, *iptls;
	float   *iptloffset, *iptlincr; // optional arguments
	MEMFIL  *mfp;
	int  maxFr, prFlg;
	/* base Frame (in frameData0) and maximum frame on file, ptr to fr, size */
	AUXCH   auxch;
	ATS_DATA_LOC *table;        //store freq and amp info for later use
	ATS_DATA_LOC *utable;        //store freq and amp info for later use (unsorted)
	int     frmInc;         // amount to increment frame pointer to get to next frame
	int     firstpartial;   // location of first wanted partial in the frame
	int     partialinc;     // amount to increment pointer by to get at the next partial in a frame
	int     memsize;           // memory size of aux channel
	double  timefrmInc;
	float   MaxAmp;         // maximum amplitude in anaylsis file
	double  *datastart;         // pointer to the data (past the header)
	ATSSTRUCT atshead;
	int swapped;	//indicates if the data file is byte swapped or not
} ATSBUFREAD;

typedef struct _atscross
{  	
	OPDS    h;
	float   *aoutput, *ktimpnt, *kfmod, *ifileno, *ifn, *kmyamp, *katsbufamp, *iptls; // audio output and k & i inputs
	float   *iptloffset, *iptlincr, *igatefun; // optional arguments
	
	FUNC    *ftp, *AmpGateFunc;     // pointer to table with wave to synthesize sound
	AUXCH   auxch;
	MEMFIL * atsmemfile;
	     
	double  maxFr;
	int	prFlg;	//a flag used to indicate if we've steped out of the time range of the data, so we don't print too many warnings
	double  timefrmInc;
	double	MaxAmp;         // maximum amplitude in anaylsis file
	int firstpartial, partialinc, frmInc;
	double * datastart;
	int memsize;	//stores the size of memeory in the aux alloc
	double  *oscphase;      // oscillator phase
	ATS_DATA_LOC * buf;
	int swapped;	//indicates if the data file is byte swapped or not
} ATSCROSS;       //modified from atsadd

typedef struct _atssinnoi
{       
	OPDS    h;
	float   *aoutput, *ktimpnt, *ksinamp, *knzamp, *kfreq, *ifileno, *iptls; // audio output and k & i inputs
	float   *iptloffset, *iptlincr, *igatefun; // optional arguments
        
	MEMFIL  *atsmemfile;   // a pointer into the ATS file
	AUXCH   auxch;
        
	double  maxFr;
	int	prFlg;
	int	memsize;
	int	nzmemsize;
	//double  winsize;        // size of windows in analysis file, used to compute RMS amplitude from energy in noise band
	
	double * datastart;
	double * nzdata;
	
	int firstpartial;
	int partialinc;
	int firstband;
	int     frmInc;         // amount to increment frame pointer to get to next frame
	double  timefrmInc;
	int npartials;
        
	ATS_DATA_LOC * oscbuf;           // stores band information for passing data
        
	double  * nzbuf;           // stores band information for passing data
	double * oscphase;       //the phase of all the oscilators
	RANDIATS * randinoise;	// a pointer to the interpolated random noise info
	ATSSTRUCT * atshead;
	char * filename;
	int swapped;	//indicates if the data file is byte swapped or not
} ATSSINNOI;

typedef struct _atspartialtap
{
	OPDS h;
	float *kfreq, *kamp, *iparnum;  //output freq, amp, input: partialnumber
} ATSPARTIALTAP;

typedef struct _atsinterpread
{
	OPDS h;
	float *kamp, *kfreq;  //output amp, input: frequency
	int overflowflag;
} ATSINTERPREAD;

