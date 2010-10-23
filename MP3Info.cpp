
#include "stdafx.h"
//#include <fstream.h>
#include <stdio.h>

#include "MP3Info.h"

/* ----------------------------------------------------------
   CMP3Info class is your complete guide to the 
   MP3 file format in the C++ language. It's a large class
   with three different, quite large "sub-classes" so it's
   a fair amount of code to look into.

   This code will be well commented, so that everyone can
   understand, as it's made for the public and not for
   private use, although private use is allowed. :)

   all functions specified both in the header and .cpp file
   will have explanations in both locations.

   everything here by: Gustav "Grim Reaper" Munkby
                       http://home.swipnet.se/grd/
                       grd@swipnet.se
   ---------------------------------------------------------- */

#define ERR_FILEOPEN    0x0001
#define ERR_NOSUCHFILE  0x0002
#define ERR_NOMP3FILE   0x0004
#define ERR_ID3TAG      0x0008

int CMP3Info::loadInfo( char srcMP3[256] ) {
    
    // open input-file stream to the specified file, name
    ifstream* ifile = new ifstream(srcMP3, ios::in | ios::binary);
    
    if (ifile) { // if the file was opened correctly

        // get file size, by setting the pointer in the end and tell the position
        ifile->seekg(0,ios::end);
        fileSize = ifile->tellg();

        // get srcMP3 into fileName variable
        strcpy(fileName,srcMP3);

        int pos = 0; // current position in file...


        /******************************************************/
        /* search and load the first frame-header in the file */
        /******************************************************/
        
        char headerchars[4]; // char variable used for header-loading

        do {
            // if no header has been found after 200kB
            // or the end of the file has been reached
            // then there's probably no mp3-file
            if ( pos>(1024*200) || ifile->eof() ) {
                showErrorMessage(ERR_NOMP3FILE, srcMP3);
                ifile->close();
                delete ifile;
                return ERR_NOMP3FILE;
            }

            // read in four characters
            ifile->seekg(pos);
            ifile->read (headerchars, 4);

            // move file-position forward
            pos++;
            
            // convert four chars to CFrameHeader structure
            header.loadHeader(headerchars);

        }
        while ( !header.isValidHeader() );  // test for correct header

        // to correct the position to be right after the frame-header
        // we'll need to add another 3 to the current position
        pos += 3;


        /******************************************************/
        /* check for an vbr-header, to ensure the info from a */
        /* vbr-mp3 is correct                                 */
        /******************************************************/

        char vbrchars[12];
        
        // determine offset from first frame-header
        // it depends on two things, the mpeg-version
        // and the mode(stereo/mono)

        if( header.getVersionIndex()==3 ) {  // mpeg version 1

            if( header.getModeIndex()==3 ) pos += 17; // Single Channel
            else                           pos += 32;

        } else {                             // mpeg version 2 or 2.5

            if( header.getModeIndex()==3 ) pos +=  9; // Single Channel
            else                           pos += 17;

        }

        // read next twelve bits in
        ifile->seekg(pos);
        ifile->read (vbrchars, 12);

        // turn 12 chars into a CVBitRate class structure
        VBitRate = vbr.loadHeader(vbrchars);        


        /******************************************************/
        /* get tag from the last 128 bytes in an .mp3-file    */
        /******************************************************/
        
        char tagchars[128]; // load tag as string

        // get last 128 bytes
        ifile->seekg ( -128, ios::end );
        ifile->read ( tagchars, 128 );

        // turn 128 chars into a CId3Tag structure
        Tagged = tag.loadTag(tagchars);

    }
    else {
        showErrorMessage(ERR_NOSUCHFILE, srcMP3);
        ifile->close();
        delete ifile;
        return ERR_NOSUCHFILE;
    }

    ifile->close();
    delete ifile;
    return 0;

}

int CMP3Info::saveTag( char* title, char* artist, char* album, char* year, char* comment, char* tracknumber, char* genre) {

    int error = 0;

    if (strcmp(title,"n/a"))       tag.setTitle(title);
    if (strcmp(artist,"n/a"))      tag.setArtist(artist);
    if (strcmp(album,"n/a"))       tag.setAlbum(album);
    if (strcmp(year,"n/a"))        tag.setYear(atoi(year));
    if (strcmp(comment,"n/a"))     tag.setComment(comment);
    if (strcmp(tracknumber,"n/a")) tag.setTrackNumber(atoi(tracknumber));
    if (strcmp(genre,"n/a"))       tag.genreString(genre, false);

    char id3tagstring[128] ={""};

    if ( tag.saveTag(id3tagstring) ) {

        ofstream* ofile = new ofstream(fileName, ios::in | ios::out | ios::binary);

        if (ofile) {

            // variable to ensure correct, file, position
            int posalter = (Tagged)?-128:0;
            
            // seek up the correct location
            ofile->seekp(posalter, ios::end);
        
            // write the tag to the file
            ofile->write(id3tagstring, 128);

        } else error = ERR_FILEOPEN;

        ofile->close();

        delete ofile;

    } else error = ERR_ID3TAG;

    if (!error) showErrorMessage(error);
    return error;

}




int CMP3Info::getBitrate() {

    if (VBitRate) {

        // get average frame size by deviding fileSize by the number of frames
        float medFrameSize = (float)fileSize / (float)getNumberOfFrames();
        
        /* Now using the formula for FrameSizes which looks different,
           depending on which mpeg version we're using, for mpeg v1:
        
           FrameSize = 12 * BitRate / SampleRate + Padding (if there is padding)

           for mpeg v2 the same thing is:

           FrameSize = 144 * BitRate / SampleRate + Padding (if there is padding)

           remember that bitrate is in kbps and sample rate in Hz, so we need to
           multiply our BitRate with 1000.

           For our purpose, just getting the average frame size, will make the
           padding obsolete, so our formula looks like:

           FrameSize = (mpeg1?12:144) * 1000 * BitRate / SampleRate;
        */

        return (int)( 
                     ( medFrameSize * (float)header.getFrequency() ) / 
                     ( 1000.0 * ( (header.getLayerIndex()==3) ? 12.0 : 144.0))
                    );

    }
    else return header.getBitrate();

}

int CMP3Info::getLengthInSeconds() {

    // kiloBitFileSize to match kiloBitPerSecond in bitrate...
    int kiloBitFileSize = (8 * fileSize) / 1000;
    
    return (int)(kiloBitFileSize/getBitrate());

}

void CMP3Info::getFormattedLength(char* input) {

    //  s  = complete number of seconds
    int s  = getLengthInSeconds();

    //  ss = seconds to display
    int ss = s%60;

    //  m  = complete number of minutes
    int m  = (s-ss)/60;

    //  mm = minutes to display
    int mm = m%60;

    //  h  = complete number of hours
    int h = (m-mm)/60;

    char szTime[16]; // temporary string

    // make a "hh:mm:ss" if there is any hours, otherwise
    // make it   "mm:ss"
    if (h>0) sprintf(szTime,"%02d:%02d:%02d", h,mm,ss);
    else     sprintf(szTime,     "%02d:%02d",   mm,ss);

    // copy to the inputstring
    strcpy(input, szTime);

}

int CMP3Info::getNumberOfFrames() {

    if (!VBitRate) {

        /* Now using the formula for FrameSizes which looks different,
           depending on which mpeg version we're using, for layer 1:
        
           FrameSize = 12 * BitRate / SampleRate + Padding (if there is padding)

           for layer 2 & 3 the same thing is:

           FrameSize = 144 * BitRate / SampleRate + Padding (if there is padding)

           remember that bitrate is in kbps and sample rate in Hz, so we need to
           multiply our BitRate with 1000.

           For our purpose, just getting the average frame size, will make the
           padding obsolete, so our formula looks like:

           FrameSize = (layer1?12:144) * 1000 * BitRate / SampleRate;
        */
           
        float medFrameSize = (float)( 
                                     ( (header.getLayerIndex()==3) ? 12 : 144 ) *
                                     (
                                      (1000.0 * (float)header.getBitrate() ) /
                                      (float)header.getFrequency()
                                     )
                                    );
        
        return (int)(fileSize/medFrameSize);

    }
    else return vbr.getNumberOfFrames();

}

void CMP3Info::getVersion(char* input) {

    char versionchar[32]; // temporary string
    char tempchar2[4]; // layer

    // call CFrameHeader member function
    float ver = header.getVersion();

    // create the layer information with the amounts of I
    for( int i=0; i<header.getLayer(); i++ ) tempchar2[i] = 'I';
    tempchar2[i] = '\0';

    // combine strings
    sprintf(versionchar,"MPEG %g Layer %s", (double)ver, tempchar2);

    // copy result into inputstring
    strcpy(input, versionchar);

}

void CMP3Info::getMode(char* input) {

    char modechar[32]; // temporary string

    // call CFrameHeader member function
    header.getMode(modechar);

    // copy result into inputstring
    strcpy(input, modechar);

}

void CMP3Info::getTitle(char* input) {

    char titlechar[32]; // temporary string

    // call CFrameHeader member function
    tag.getTitle(titlechar);

    // copy result into inputstring
    strcpy(input, titlechar);

}

void CMP3Info::getArtist(char* input) {

    char artistchar[32]; // temporary string

    // call CFrameHeader member function
    tag.getArtist(artistchar);

    // copy result into inputstring
    strcpy(input, artistchar);

}

void CMP3Info::getAlbum(char* input) {

    char albumchar[32]; // temporary string

    // call CFrameHeader member function
    tag.getAlbum(albumchar);

    // copy result into inputstring
    strcpy(input, albumchar);

}

void CMP3Info::getComment(char* input) {

    char commentchar[32]; // temporary string

    // call CFrameHeader member function
    tag.getComment(commentchar);

    // copy result into inputstring
    strcpy(input, commentchar);

}

void CMP3Info::getGenre(char* input) {

    char genrechar[32]; // temporary string

    // call CFrameHeader member function
    tag.genreString(genrechar, true);

    // copy result into inputstring
    strcpy(input, genrechar);

}

void CMP3Info::getFileName(char* input) {

    strcpy(input, fileName);

}

void CMP3Info::showErrorMessage(UINT msg, char* szMsgPlus) {

    switch(msg) {

        case ERR_NOSUCHFILE:
            {
                //MessageBox(0,"You tried to open a file\nthat didn't work", szMsgPlus, MB_OK|MB_SYSTEMMODAL);
                return;
            }
        case ERR_NOMP3FILE:
            {
                //MessageBox(0,"The file that was opened\nwas no correct .mp3-file", szMsgPlus, MB_OK|MB_SYSTEMMODAL);
                return;
            }
        case ERR_FILEOPEN:
            {
                //MessageBox(0,"You tried to open a file\nthat didn't work", szMsgPlus, MB_OK|MB_SYSTEMMODAL);
                return;
            }
        case ERR_ID3TAG:
            {
                //MessageBox(0,"No valid ID3-tag could be\ncreated", szMsgPlus, MB_OK|MB_SYSTEMMODAL);
                return;
            }

    }

}

// This function is quite easy to understand, it loads
// 4 chars of information into the CFrameHeader class
// The validity is not tested, so qith this function
// an invalid FrameHeader could be retrieved
void CFrameHeader::loadHeader(char c[4]) {

    // this thing is quite interesting, it works like the following
    // c[0] = 00000011
    // c[1] = 00001100
    // c[2] = 00110000
    // c[3] = 11000000
    // the operator << means that we'll move the bits in that direction
    // 00000011 << 24 = 00000011000000000000000000000000
    // 00001100 << 16 =         000011000000000000000000
    // 00110000 << 24 =                 0011000000000000
    // 11000000       =                         11000000
    //                +_________________________________
    //                  00000011000011000011000011000000

    bithdr = (unsigned long)(
                              ( (c[0] & 255) << 24) |
                              ( (c[1] & 255) << 16) |
                              ( (c[2] & 255) <<  8) |
                              ( (c[3] & 255)      )
                            ); 

}


// This function is a supplement to the loadHeader
// function, the only purpose is to detect if the
// header loaded by loadHeader is a valid header
// or just four different chars
BOOL CFrameHeader::isValidHeader() {

    return ( ((getFrameSync()      & 2047)==2047) &&
             ((getVersionIndex()   &    3)!=   1) &&
             ((getLayerIndex()     &    3)!=   0) && 
             ((getBitrateIndex()   &   15)!=   0) &&  // due to lack of support of the .mp3 format
                                                      // no "public" .mp3's should contain information
                                                      // like this anyway... :)
             ((getBitrateIndex()   &   15)!=  15) &&
             ((getFrequencyIndex() &    3)!=   3) &&
             ((getEmphasisIndex()  &    3)!=   2)    );

}

// this returns the MPEG version [1.0-2.5]
float CFrameHeader::getVersion() {

    // a table to convert the indexes into
    // something informative...
    float table[4] = {
                      2.5, 0.0, 2.0, 1.0
                     };

    // return modified value
    return table[getVersionIndex()];

}


// this returns the Layer [1-3]
int CFrameHeader::getLayer() {

    // when speaking of layers there is a 
    // cute coincidence, the Layer always
    // eauals 4 - layerIndex, so that's what
    // we will return
    return ( 4 - getLayerIndex() );

}


// this returns the current bitrate [8-448 kbps]
int CFrameHeader::getBitrate() {

    // a table to convert the indexes into
    // something informative...
    const int table[2][3][16] = {
        {         //MPEG 2 & 2.5
            {0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160,0}, //Layer III
            {0,  8, 16, 24, 32, 40, 48, 56, 64, 80, 96,112,128,144,160,0}, //Layer II
            {0, 32, 48, 56, 64, 80, 96,112,128,144,160,176,192,224,256,0}  //Layer I
        },{       //MPEG 1
            {0, 32, 40, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,0}, //Layer III
            {0, 32, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,384,0}, //Layer II
            {0, 32, 64, 96,128,160,192,224,256,288,320,352,384,416,448,0}  //Layer I
        }
    };

    // the bitrate is not only dependent of the bitrate index,
    // the bitrate also varies with the MPEG version and Layer version
    return table[(getVersionIndex() & 1)][(getLayerIndex() -1)][getBitrateIndex()];

}


// this returns the current frequency [8000-48000 Hz]
int CFrameHeader::getFrequency() {

    // a table to convert the indexes into
    // something informative...
    int table[4][3] = {

        {32000, 16000,  8000}, //MPEG 2.5
        {    0,     0,     0}, //reserved
        {22050, 24000, 16000}, //MPEG 2
        {44100, 48000, 32000}  //MPEG 1

    };

    // the frequency is not only dependent of the bitrate index,
    // the bitrate also varies with the MPEG version
    return table[getVersionIndex()][getFrequencyIndex()];

}

// the purpose of getMode is to get information about
// the current playing mode, such as:
// "Joint Stereo"
void CFrameHeader::getMode(char* input) {

    // here you could use a array of strings instead
    // but I think this method is nicer, at least
    // when not dealing with that many variations
    switch(getModeIndex()) {
        default:
            strcpy(input, "Stereo");
            break;

        case 1:
            strcpy(input, "Joint Stereo");
            break;

        case 2:
            strcpy(input, "Dual Channel");
            break;

        case 3:
            strcpy(input, "Single Channel");
            break;
    }

}

// flags to know what information who could
// be found in the headers
#define FRAMES_FLAG    0x0001
#define BYTES_FLAG     0x0002
#define TOC_FLAG       0x0004
#define VBR_SCALE_FLAG 0x0008

// This function is quite easy to understand, it loads
// 12 chars of information into the CVBitRate class
BOOL CVBitRate::loadHeader (char inputheader[12]) {

    // The Xing VBR headers always begin with the four
    // chars "Xing" so this tests wether we have a VBR
    // header or not
    if( memcmp(inputheader, "Xing", 4) ) {

        frames = -1;
        return false;

    }
    
    // now we will get the flags and number of frames,
    // this is done in the same way as the FrameHeader
    // is generated in the CFrameHeader class
    // if you're curious about how it works, go and look
    // there

    // here we get the flags from the next four bytes
    int flags = (int)(
                      ( (inputheader[4] & 255) << 24) |
                      ( (inputheader[5] & 255) << 16) |
                      ( (inputheader[6] & 255) <<  8) |
                      ( (inputheader[7] & 255)      )
                     ); 

    // if this tag contains the number of frames, load
    // that number into storage, if not something will
    // be wrong when calculating the bitrate and length
    // of the music
    if( flags & FRAMES_FLAG ) {
        frames = (int)(
                        ( (inputheader[ 8] & 255) << 24) |
                        ( (inputheader[ 9] & 255) << 16) |
                        ( (inputheader[10] & 255) <<  8) |
                        ( (inputheader[11] & 255)      )
                       ); 
    } else {
        
        // returning -1 so an error would be obvious
        // not many people would believe in a bitrate
        // -21 kbps :)
        frames = -1;

        // this function was returning false before
        // as there is an error occuring, but in that
        // case the bitrate wouldn't be unbelievable
        // so that's why I changed my mind and let it
        // return true instead
        return true;

    }

    // if it gets this far, everything went according
    // to plans, so we should return true!
    return true;

}


// this function is specially designed to take
// care of ID3 tags generated with spaces instead
// of null characters as they are supposed to.
void gStrCpy( char* dst, char* src, int length ) {

    // what this does is that it searches for a
    // the first non-space or non-null from the
    // right side (and while doing so replacing)
    // " " with '\0'
    for	( int i = (length-1); i >= 0; i-- ) {

        if ( (src[i] == 0x20) || (src[i] == '\0') ) dst[i] = '\0';

        else break;
            
    }

    // this should copy the remaining part straight over
    memcpy(dst, src, (i+1) );

    // set last byte to zero to ensure string compability
    dst[length] = '\0';

}


BOOL CId3Tag::loadTag( char inputtag[128] ) {

    // in the ID3 tag the first 3 bytes are always TAG
    // so that you can separate a TAGed file from a
    // non TAGed one
    if ( memcmp(inputtag, "TAG", 3) ) return false;

    // using special string-copying routine
    // to copy the title string
    gStrCpy( title, inputtag+3, 30 );

    // using special string-copying routine
    // to copy the artist string
    gStrCpy( artist, inputtag+33, 30 );

    // using special string-copying routine
    // to copy the title string
    gStrCpy( album, inputtag+63, 30 );

    // because I store year as an integer
    // and the ID3 tag stores it as a string
    // the year will be handled like this:
    char yearstr[4];
    memcpy( yearstr, inputtag+93, 4);
    year = atoi( yearstr );

    // now lets detect whether it's version 1.1
    // or 1.0 (if there is tracknumber info or not)
    // if there is some tracknumber info, then it's in
    // the last char of the comment field, and the
    // one before is null
    if ( (inputtag[125]=='\0' ) && (inputtag[126] != '\0') ) {

        version = (float)1.1;
        trackNumber = (int)inputtag[126];

        // using special string-copying routine
        // to copy the comment string
        gStrCpy(comment, inputtag+97, 28);

    } else {
        
        version = (float)1.0;

        // using special string-copying routine
        // to copy the title string
        gStrCpy(comment, inputtag+97, 30);

    }

    genre = inputtag[127];

    return true;

}



BOOL CId3Tag::saveTag (char outputtag[128]) {

    
    // begin with clearing the values of the memory
    // containing the "id3string", mainly to ensure
    // that any "un-set" chars is 0 and nothing else
    memset(outputtag,0,128);

    // to append the rest of the strings I'll
    // use memcpy like this:
    //
    // memcpy(outputtag + [IN-TAG-LOCATION], [SOURCE], [SOURCE-LENGTH]);
    //
    // shouldn't be to hard to understand, look beneath:

    // first of all, we add the identifier
    memcpy(outputtag, "TAG", 3);

    // apending title
    gStrCpy(outputtag+3, title, 30 );
    
    // inserting the artist information
    gStrCpy(outputtag+33, artist, 30 );
    
    // add the album name to the id3 tag
    gStrCpy(outputtag+63, album, 30 );

    // this ones got to be 4 chars long, in my code, just to make the code simpler
    // and exactly who's got music recorded older than 1000 years? (and who's got
    // music recorded from the 101th century?)

    // turn integer into string (using char nr 5 for null)
    char yearstring[5];
    _itoa(year,yearstring,10);

    // add the four chars describing the year
    memcpy(outputtag + 93, yearstring, 4 );

    // add 30 chars of comment
    gStrCpy(outputtag+97, comment, 30 );
    
    if (version==(float)1.1) { // if version equals 1.1 we've got a tracknumber

        // make sure comment[28] == '\0' & then set comment[29] to trackNumber
        outputtag[125] = '\0';
        outputtag[126] = (UCHAR)(UINT)trackNumber;

    }

    // set the char desiding the genre
    outputtag[127] = genre;

    return TRUE;
}


// get title info
void CId3Tag::getTitle(char* input) {

    strcpy (input, title);

}
// set title info
void CId3Tag::setTitle(char* input) {

    strcpy (title, input);

}

// get artist info
void CId3Tag::getArtist(char* input) {

    strcpy (input, artist);

}
// set artist info
void CId3Tag::setArtist(char* input) {

    strcpy (artist, input);

}

// get album info
void CId3Tag::getAlbum(char* input) {

    strcpy (input, album);

}
// set album info
void CId3Tag::setAlbum(char* input) {

    strcpy (album, input);

}

// get comment info
void CId3Tag::getComment(char* input) {

    strcpy (input, comment);

}
// set comment info
void CId3Tag::setComment(char* input) {

    strcpy (comment, input);

}

// get/set genre string
// to use this function to get info
// specify true as second parameter
// if you want to set then make it false
void CId3Tag::genreString(char* input, BOOL get = true) {

    // this table of constant strings will be used in all cases..
    const char* table[126] = {
                              "Blues","Classic Rock","Country","Dance","Disco","Funk","Grunge","Hip-Hop","Jazz",
                              "Metal","New Age","Oldies","Other","Pop","R&B","Rap","Reggae","Rock","Techno",
                              "Industrial","Alternative","Ska","Death Metal","Pranks","Soundtrack","Euro-Techno",
                              "Ambient","Trip-Hop","Vocal","Jazz+Funk","Fusion","Trance","Classical","Instrumental",
                              "Acid","House","Game","Sound Clip","Gospel","Noise","AlternRock","Bass","Soul","Punk",
                              "Space","Meditative","Instrumental Pop","Instrumental Rock","Ethnic","Gothic",
                              "Darkwave","Techno-Industrial","Electronic","Pop-Folk","Eurodance","Dream",
                              "Southern Rock","Comedy","Cult","Gangsta","Top 40","Christian Rap","Pop/Funk","Jungle",
                              "Native American","Cabaret","New Wave","Psychadelic","Rave","Showtunes","Trailer",
                              "Lo-Fi","Tribal","Acid Punk","Acid Jazz","Polka","Retro","Musical","Rock & Roll",
                              "Hard Rock","Folk","Folk-Rock","National Folk","Swing","Fast Fusion","Bebob","Latin",
                              "Revival","Celtic","Bluegrass","Avantgarde","Gothic Rock","Progressive Rock",
                              "Psychedelic Rock","Symphonic Rock","Slow Rock","Big Band","Chorus","Easy Listening",
                              "Acoustic","Humour","Speech","Chanson","Opera","Chamber Music","Sonata","Symphony",
                              "Booty Bass","Primus","Porn Groove","Satire","Slow Jam","Club","Tango","Samba",
                              "Folklore","Ballad","Power Ballad","Rhythmic Soul","Freestyle","Duet","Punk Rock",
                              "Drum Solo","Acapella","Euro-House","Dance Hall"
                             };

    if (get) {

        // if get operation then check whether it's supported
        // and if it is set it according table above
        if (genre>=126)    strcpy(input, "not supported");
        else               strcpy (input, table[genre]);

    }
    else {

        for (int i=0; i<126; i++) {

            // search table for match
            if ( !_stricmp(input, table[i]) ) {

                genre=(UCHAR)(UINT)i;
                return; // end function

            }

        }
        // you'll only get here if no match is found

        // alert error message
        char buf[200];
        sprintf(buf,"the genre %s couldn't be found\ndo you want to set it to \"not supported\"?",input);
      //  int ret = //MessageBox(0,buf, "MP3Info Example",MB_YESNO | MB_ICONQUESTION);

        // from the error message you've got two possibilities
        // 1/ answer no and the genre will remain unchanged
        // 2/ answer yes and the genre will be altered to "not supported"
        // set genre to something unspecified (in this case 255)
        //if (ret==IDYES) genre = 255;

    }

}
// set the genre index info
void CId3Tag::setGenreIndex(int input) {

    genre = (UCHAR)(input%256);

}
// set the track number info
// to remove a track number execute this
// function
void CId3Tag::setTrackNumber(int input) {

    // no number avaliable
    if (input==-1) { 
        
        version = (float)1.0;
        trackNumber = -1;

    } else if (input<0 || input>255) {

        // an invalid tracknumber was specified
        //MessageBox(0,"The tracknumber, should be between 0 and 255", "MP3Info Example", MB_OK);

    } else { // no errors, set the tracknumber

        version = (float)1.1;
        trackNumber = input;

    }

}
// set year info
void CId3Tag::setYear(int input) {

    // check whether input is out of range
    if (input<1000 || input>3000) {
         
        char mybuf[200];
        sprintf(mybuf, "The way the year is stored, it's best\nto use a year between 1000 and 3000,\nPersonally I don't think other years is needed\n\n%d seams like a stupid number",input);

        //MessageBox(0, mybuf, "MP3Info Example", MB_OK|MB_ICONEXCLAMATION);

    } else { // everything alright, just set it

        year = input;

    }

}