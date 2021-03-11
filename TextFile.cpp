// Name: Navdeep Virdi
// Seneca email: nvirdi2@myseneca.ca
// Student ID: 166485193
// Date: March 11, 2021

//I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.


#include <iostream>
#include <fstream>
#include <string>
#include "TextFile.h"
#include "cstring.h"
using namespace std;
namespace sdds
{
    Line::Line() {
        m_value = nullptr;
    }

    Line::operator const char* () const {
        return (const char*)m_value;
    }

    Line& Line::operator=(const char* lineValue) {
        if (m_value != nullptr)
            delete[] m_value;
        m_value = new char[strLen(lineValue) + 1];
        strCpy(m_value, lineValue);
        return *this;
    }

    Line::~Line() {
        if (m_value != nullptr)
            delete[] m_value;
    }
    
    void TextFile::setFilename(const char* fname, bool isCopy) {
        m_filename = new char[strLen(fname) + 3];

        if(isCopy) {
            strCpy(m_filename, "C_");
            strCat(m_filename, fname);
        }

        else {
            strCpy(m_filename, fname);
        }
    }
    
    void TextFile::setNoOfLines()            
    {
        ifstream fin(m_filename);
        char c;

        while(fin >> noskipws >> c) {

            if(c == '\n') {
                m_noOfLines++;
            }
        }
        fin.close();
        if(m_noOfLines == 0) {
            m_filename = nullptr;
        }

        else {
          m_noOfLines++;
        }
    }
    
    void TextFile::loadText() {
        if(m_filename != nullptr) {

            m_textLines = new Line[m_noOfLines];
            ifstream file(m_filename);
            string tmpline;

            int numbers = 0;

            while(getline(file, tmpline)) {
                m_textLines[numbers] = tmpline.c_str();
                numbers++;
            }

            m_noOfLines = numbers;
            file.close();
        } 
    }

    void TextFile::saveAs(const char* fileName) const
    {
        ofstream fout(fileName);
        unsigned x; 

        for(x = 0; x < m_noOfLines; x++) {
            fout << m_textLines[x] << endl;
        }

        fout.close();
    }

    void TextFile::setEmpty() {
        if (m_textLines)
            delete[] m_textLines;
        m_textLines = nullptr;
        if (m_filename && strLen(m_filename) > 0)
            delete[] m_filename;
        m_filename = nullptr;
        m_noOfLines = 0;
    }

    TextFile::TextFile(unsigned pageSize) {
        m_filename = nullptr;

        m_textLines = nullptr;

        m_noOfLines = 0;

        m_pageSize = pageSize;
    }

    
    
    
   TextFile::TextFile(const char* filename, unsigned pageSize) {
        m_filename = nullptr;

        m_textLines = nullptr;

        m_noOfLines = 0;

        m_pageSize = pageSize;

        if(filename != nullptr) {
            setFilename(filename);
            setNoOfLines();
            loadText();
        } 
    }

    TextFile::TextFile(const TextFile& any) {
        m_filename = nullptr;

        m_textLines = nullptr;

        m_noOfLines = 0;

        m_pageSize = any.m_pageSize;

        ifstream file(any.m_filename);
        if(file.good()) {
            
            setFilename(any.m_filename, true);
            any.saveAs(m_filename);

            setNoOfLines();
            loadText();
        }
    }

    TextFile& TextFile::operator=(const TextFile& any) {
        ifstream file1(m_filename);
        ifstream file2(any.m_filename);

        if(file1.good() && file2.good()) {
            m_textLines = nullptr;

            any.saveAs(m_filename);

            setNoOfLines();
            loadText(); 

        } return *this;
   }

   TextFile::~TextFile() {
        if(m_filename && strLen(m_filename) > 0){
            delete[] m_filename;
        }
        delete[] m_textLines;
    }

    std::ostream& TextFile::view(std::ostream& ostr) const
    {
        if(m_textLines == nullptr || m_filename == nullptr || m_noOfLines == 0) {
            return ostr;
        }
        ostr << m_filename << endl;

        int x;

        for(x = 0; m_filename[x] != '\0'; x++) {
            ostr << "=";
        }
        ostr << endl;

        for(unsigned x = 0; x < m_noOfLines; x++) {
            ostr << m_textLines[x] << endl;

            if((x + 1) % m_pageSize == 0) {
                ostr << "Hit ENTER to continue...";
                getchar();
            }
        } return ostr;
    }
    
    

    std::istream& TextFile::getFile(std::istream& istr)
    {
        string tmp;      

        getline(istr, tmp);    
        setFilename(tmp.c_str());   
   
        setNoOfLines();   
        loadText(); 

        return istr;    
    }
   
    TextFile::operator bool() const
    {
        if(m_textLines == nullptr || m_filename == nullptr || m_noOfLines == 0) {
            return false;       
        } return true;   
    }

    unsigned TextFile::lines() const
    {
        return m_noOfLines;     
    }

    const char* TextFile::name() const
    {
        return m_filename;    
    }

    const char* TextFile::operator[](unsigned index) const
    {
        if(m_textLines == nullptr || m_filename == nullptr
             || m_noOfLines == 0) {
            return nullptr;
        }
        unsigned x; 
        unsigned Index = 0;
        char *file = nullptr;
        for(x = 0; x <= index; x++) {   

            if(Index >= m_noOfLines) {
                Index = 0;
            }

            file = m_textLines[Index].m_value;
            Index++;
        } return file;    
   }


    ostream& operator<<(ostream& ostr, const TextFile& text)
    {
        text.view(ostr);    
            return ostr;   
    }

    istream& operator>>(istream& istr, TextFile& text)
    {
        text.getFile(istr); 
            return istr;    
    }
}
