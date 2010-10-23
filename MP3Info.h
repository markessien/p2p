#ifndef CMP3INFO_H
#define CMP3INFO_H

#include <windows.h>
//#include "CId3Tag.h"
//#include "CVBitRate.h"

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

class CId3Tag {

    public:

    // this function takes 128 chars and if it's
    // an ID3 tag structure it'll be read into
    // this usable structure
    BOOL loadTag( char inputtag[128] );

    // this function saves the current settings
    // into the 128 chars sent to the function
    BOOL saveTag( char output[128] );

    // function to set & get Title info [ char[30] ]
    void  getTitle(char* input);
    void  setTitle(char* input);

    // function to set & get Artist info [ char[30] ]
    void  getArtist(char* input);
    void  setArtist(char* input);

    // function to set & get Album info [ char[30] ]
    void  getAlbum(char* input);
    void  setAlbum(char* input);

    // function to set & get Comment info [ char[30]/char[28] ]
    void  getComment(char* input);
    void  setComment(char* input);

    // functions to set & get the string for
    // the genre info.
    void  genreString(char* input, BOOL get);

    // functions to set & get the integer 
    // for the genre info
    int   getGenreIndex() { return (int)genre; };
    void  setGenreIndex(int input);

    // functions to set & get the year info [1000->3000]
    int   getYear() { return year; };
    void  setYear(int input);

    // functions to set & get the track number [1->255]
    int  getTrackNumber() { return (version==1.1)?trackNumber:-1; };
    void setTrackNumber(int input); 
    
    // function to get the version [1.0/1.1]
    float getVersion() { return version; };

    private:

    char  title  [31],
          artist [31],
          album  [31],
          comment[31];
    int   year;
    int   trackNumber; //ID3v1.1 specific
    float version;

    UCHAR genre;

};

class CVBitRate {

    public:

    // This function is quite easy to understand, it loads
    // 12 chars of information into the CVBitRate class
    BOOL loadHeader(char inputheader[12]);

    // this is the only value-retrieving function in this class
    // it returns the Number of Frames [0 -> oo] (oo == eternety)
    int getNumberOfFrames() { return frames; };

    private:

    // this is the varable holding the number of frames
    int frames;

};

class CFrameHeader {

    public:

    // This function is quite easy to understand, it loads
    // 4 chars of information into the CFrameHeader class
    // The validity is not tested, so qith this function
    // an invalid FrameHeader could be retrieved
    void loadHeader(char c[4]);

    // This function is a supplement to the loadHeader
    // function, the only purpose is to detect if the
    // header loaded by loadHeader is a valid header
    // or just four different chars
    BOOL isValidHeader();

    // Following är functions to get the "indexes" for the various
    // information avaliable. To know which meaning the different
    // bits you need to look into a table, instead of having to
    // do this everytime these functions get the correct index
    // from the correct bits. :)
    int getFrameSync()     { return ((bithdr>>21) & 2047); };
    int getVersionIndex()  { return ((bithdr>>19) & 3);  };
    int getLayerIndex()    { return ((bithdr>>17) & 3);  };
    int getProtectionBit() { return ((bithdr>>16) & 1);  };
    int getBitrateIndex()  { return ((bithdr>>12) & 15); };
    int getFrequencyIndex(){ return ((bithdr>>10) & 3);  };
    int getPaddingBit()    { return ((bithdr>> 9) & 1);  };
    int getPrivateBit()    { return ((bithdr>> 8) & 1);  };
    int getModeIndex()     { return ((bithdr>> 6) & 3);  };
    int getModeExtIndex()  { return ((bithdr>> 4) & 3);  };
    int getCoprightBit()   { return ((bithdr>> 3) & 1);  };
    int getOrginalBit()    { return ((bithdr>> 2) & 1);  };
    int getEmphasisIndex() { return ((bithdr    ) & 3);  };


    // now comes som function to make life easier once again
    // you don't even have to know what the different indexes
    // means. to get the version, just use the function
    // getVersion. You can't have it easier
       

    // this returns the MPEG version [1.0-2.5]
    float getVersion();

    // this returns the Layer [1-3]
    int  getLayer();

    // this returns the current bitrate [8-448 kbps]
    int  getBitrate();

    // this returns the current frequency [8000-48000 Hz]
    int getFrequency();

    // the purpose of getMode is to get information about
    // the current playing mode, such as:
    // "Joint Stereo"
    void getMode(char* input);

    private:

    // this contains the orginal header (bit-by-bit) information
    // declared private because there is not really any reason
    // to use it, as all the "indexes" functions exists
    unsigned long bithdr;

};



class CMP3Info {

    public:

    // function to load a file into this structure
    // the argument passed is the path to a MP3 file
    int   loadInfo( char srcMP3[256] );

    // function to save tag
    int   saveTag( char* title, char* artist, char* album, char* year, char* comment, char* tracknumber, char* genre);

    // functions used to get information about the "file"
    int   getFileSize() { return fileSize; };
    void  getFileName(char* input);

    // information that is avaliable in FrameHeader & VBR header
    void  getVersion(char* input);
    int   getBitrate();
    int   getFrequency() { return header.getFrequency(); };
    void  getMode(char* input);
    
    int   getNumberOfFrames();

    // functions to calculate the length of the song
    // and to present it nicely
    int   getLengthInSeconds();
    void  getFormattedLength(char* input);

    // information that is avaliable in the ID3 tag
    void  getTitle(char* input);
    void  getArtist(char* input);
    void  getAlbum(char* input);
    void  getComment(char* input);
    void  getGenre(char* input);

    int   getYear() { return tag.getYear(); };
    int   getTrackNumber() { return tag.getTrackNumber(); };

    // just to know what kind of file it is.
    BOOL  isVBitRate() { return VBitRate; };
    BOOL  isTagged() { return Tagged; };
    
    private:

    // this alerts some error messages, so that it's
    // easier to see what's wrong
    void showErrorMessage(UINT msg, char* szMsgPlus = "");

    // these are the "sub-classes"
    CFrameHeader header;
    CVBitRate    vbr;
    CId3Tag      tag;

    // just to know what kind of file it is
    BOOL VBitRate;
    BOOL Tagged;

    // the file information can not be found elsewhere
    char fileName[256];
    int fileSize;

};

#endif
