#include "./OleanderStemmingLibrary-master/stemming/english_stem.h"
#include <string>
#include <iostream>

std::string OSLstemmer(std::string ANSIWord){
    
    std::wstring word;
    /*create an instance of a "english_stem" class. The template argument for the
    stemmers are the type of std::basic_string that you are trying to stem, by default 
    std::wstring (Unicode strings). As long as the char type of your basic_string is wchar_t,
    then you can use any type of basic_string. This is to say, if your basic_string has a custom
    char_traits or allocator, then just specify it in your template argument to the stemmer. For example:

    typedef std::basic_string<wchar_t, myTraits, myAllocator> myString;
    myString word(L"documentation");
    stemming::english_stem<myString> StemEnglish;
    StemEnglish(word);*/
    stemming::english_stem<> StemEnglish;
    
    /*if you are using std::string (ANSI strings) then convert it to a temporary
    wchar_t buffer, assign that to a std::wstring, and then stem that.*/
    wchar_t* UnicodeTextBuffer = new wchar_t[ANSIWord.length()+1];
    std::wmemset(UnicodeTextBuffer, 0, ANSIWord.length()+1);
    std::mbstowcs(UnicodeTextBuffer, ANSIWord.c_str(), ANSIWord.length());
    word = UnicodeTextBuffer;
    StemEnglish(word);
    std::string r;
    //converting wstring to string
    for(char x:word){
    	r+=x;
    }
    return r;
}
