#include <iostream>
#include <fstream>
#include <string>
#include "TextFile.h"
#include "cstring.h"
using namespace std;
namespace sdds {
   Line::Line(){
      m_value = nullptr;
   }
   Line::operator const char* () const {
      return (const char*)m_value;
   }
   Line& Line::operator=(const char* lineValue) {
      if(m_value != nullptr)
         delete[] m_value;
      m_value = new char[strLen(lineValue) + 1];
      strCpy(m_value, lineValue);
      return *this;
   }
   Line::~Line() {
      if(m_value != nullptr)
         delete[] m_value;
   }
   void TextFile::setEmpty()
   {
      if(m_textLines)
         delete[] m_textLines;
      m_textLines = nullptr;
      if(m_filename && strLen(m_filename) > 0)
         delete[] m_filename;
      m_filename = nullptr;
      m_noOfLines = 0;
   }
   void TextFile::setFilename(const char* fname, bool isCopy)
   {
      m_filename = new char[strLen(fname) + 3];
      if(isCopy)
      {
         strCpy(m_filename, "C_");
         strCat(m_filename, fname);
      }
      else
      {
         strCpy(m_filename, fname);
      }
   }
   void TextFile::setNoOfLines()
   {
      ifstream fin(m_filename);
      char ch;
      while(fin >> noskipws >> ch)
      {
         if(ch == '\n')
            m_noOfLines++;
      }
      fin.close();
      if(m_noOfLines == 0)
      {
         m_filename = nullptr;
      }
      else
         m_noOfLines++;
   }
   void TextFile::loadText()
   {
      if(m_filename != nullptr)
      {
         m_textLines = new Line[m_noOfLines];
         ifstream file(m_filename);
         string temp_line;
         int count = 0;
         while(getline(file, temp_line))
         {
            m_textLines[count] = temp_line.c_str();
            count++;
         }
         m_noOfLines = count;
         file.close();
      }
   }
   void TextFile::saveAs(const char* fileName) const
   {
      ofstream fout(fileName);
      for(unsigned i = 0; i<m_noOfLines; i++)
      {
         fout << m_textLines[i] << endl;
      }
      fout.close();
   }
   TextFile::TextFile(unsigned pageSize = 15)
   {
      m_filename = nullptr;
      m_textLines = nullptr;
      m_noOfLines = 0;
      m_pageSize = pageSize;
   }
   TextFile::TextFile(const char* filename, unsigned pageSize = 15)
   {
      m_filename = nullptr;
      m_textLines = nullptr;
      m_noOfLines = 0;
      m_pageSize = pageSize;
      if(filename != nullptr)
      {
         setFilename(filename);
         setNoOfLines();
         loadText();
      }
   }
   TextFile::TextFile(const TextFile& other)
   {
      m_filename = nullptr;
      m_textLines = nullptr;
      m_noOfLines = 0;
      m_pageSize = other.m_pageSize;
      ifstream file(other.m_filename);
      if(file.good())
      {
         setFilename(other.m_filename, true);
         other.saveAs(m_filename);
         setNoOfLines();
         loadText();
      }
   }



   TextFile& TextFile::operator=(const TextFile& other)
   {
      ifstream file1(m_filename);
      ifstream file2(other.m_filename);
      if(file1.good() && file2.good())
      {
         m_textLines = nullptr;
         other.saveAs(m_filename);
         setNoOfLines();
         loadText(); 
      }
      return *this;
   }
   TextFile::~TextFile()
   {
      if(m_filename && strLen(m_filename) > 0)
         delete[] m_filename;
      delete[] m_textLines;
   }
   unsigned TextFile::lines() const
   {
      return m_noOfLines;
   }
   std::ostream& TextFile::view(std::ostream& ostr) const
   {
      if(m_textLines == nullptr || m_filename == nullptr || m_noOfLines == 0)
      {
         return ostr;
      }
      ostr << m_filename << endl;
      for(int i = 0; m_filename[i] != '\0'; i++)
      {
         ostr << "=";
      }
      ostr << endl;
      for(unsigned i = 0; i<m_noOfLines; i++)
      {
         ostr << m_textLines[i] << endl;
         if((i+1) % m_pageSize == 0)
         {
            ostr << "Hit ENTER to continue...";
            getchar();
         }
      }
      return ostr;
   }
   std::istream& TextFile::getFile(std::istream& istr)
   {
      string temp;
      getline(istr, temp);
      setFilename(temp.c_str());
      setNoOfLines();
      loadText();
      return istr;
   }
   const char* TextFile::operator[](unsigned index) const
   {
      if(m_textLines == nullptr || m_filename == nullptr || m_noOfLines == 0)
      {
         return nullptr;
      }
      unsigned idx = 0;
      char *res = nullptr;
      for(unsigned i = 0; i<=index; i++)
      {
         if(idx >= m_noOfLines)
         {
            idx = 0;
         }
         res = m_textLines[idx].m_value;
         idx++;
      }
      return res;
   }
   TextFile::operator bool() const
   {
      if(m_textLines == nullptr || m_filename == nullptr || m_noOfLines == 0)
      {
         return false;
      }
      return true;
   }

   const char* TextFile::name() const
   {
      return m_filename;
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