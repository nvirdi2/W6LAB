
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




    void TextFile::setEmpty() {
        if (m_textLines)
            delete[] m_textLines;
        m_textLines = nullptr;
        if (m_filename && strLen(m_filename) > 0)
            delete[] m_filename;
        m_filename = nullptr;
        m_noOfLines = 0;
    }

    void TextFile::setFilename(const char* fname, bool isCopy) {
        m_filename = new char[strLen(fname) + 3];
        if (isCopy) {
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
        char characters;
        while (fin >> noskipws >> characters) {
            if (characters == '\n')
                m_noOfLines++;
        }

        fin.close();
        if (m_noOfLines == 0) {
            m_filename = nullptr;
        }

        else
            m_noOfLines++;
    }

    void TextFile::loadText() {
        if (m_filename != nullptr) {
            m_textLines = new Line[m_noOfLines];
            ifstream file(m_filename);
            string temp_line;
            int num = 0;
            while (getline(file, temp_line))
            {
                m_textLines[num] = temp_line.c_str();
                num++;
            }
            m_noOfLines = num;
            file.close();
        }
    }

    void TextFile::saveAs(const char* fileName) const {
        ofstream fout(fileName);
        for (unsigned a = 0; a < m_noOfLines; a++) {
            fout << m_textLines[a] << endl;
        }

        fout.close();
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
        if (filename != nullptr) {
            setFilename(filename);
            setNoOfLines();
            loadText();
        }
    }

    TextFile::TextFile(const TextFile& other) {
        m_filename = nullptr;
        m_textLines = nullptr;
        m_noOfLines = 0;
        m_pageSize = other.m_pageSize;
        ifstream file(other.m_filename);
        if (file.good()) {
            setFilename(other.m_filename, true);
            other.saveAs(m_filename);
            setNoOfLines();
            loadText();
        }
    }

    TextFile& TextFile::operator=(const TextFile& other) {
        ifstream file1(m_filename);
        ifstream file2(other.m_filename);
        if (file1.good() && file2.good()) {
            m_textLines = nullptr;
            other.saveAs(m_filename);
            setNoOfLines();
            loadText();
        }

        return *this;
    }

    TextFile::~TextFile() {
        if (m_filename && strLen(m_filename) > 0)
            delete[] m_filename;
        delete[] m_textLines;
    }

    unsigned TextFile::lines() const {
        return m_noOfLines;
    }

    std::ostream& TextFile::view(std::ostream& ostr) const {
        if (m_textLines == nullptr || m_filename == nullptr || m_noOfLines == 0) {
            return ostr;
        }
        ostr << m_filename << endl;
        for (int b = 0; m_filename[b] != '\0'; b++)  {
            ostr << "=";
        }
        ostr << endl;
        for (unsigned c = 0; c < m_noOfLines; c++) {
            ostr << m_textLines[c] << endl;
            if ((c + 1) % m_pageSize == 0) {
                ostr << "Hit ENTER to continue...";
                getchar();
            }
        }

        return ostr;
    }

    std::istream& TextFile::getFile(std::istream& istr) {
        string temp;
        getline(istr, temp);
        setFilename(temp.c_str());
        setNoOfLines();
        loadText();
        return istr;
    }

    const char* TextFile::operator[](unsigned index) const {
        if (m_textLines == nullptr || m_filename == nullptr || m_noOfLines == 0) {
            return nullptr;
        }
        unsigned idex = 0;
        char* a = nullptr;
        for (unsigned d = 0; d <= index; d++) {
            if (idex >= m_noOfLines) {
                idex = 0;
            }
            a = m_textLines[idex].m_value;
            idex++;
        }

        return a;
    }

    TextFile::operator bool() const {
        if (m_textLines == nullptr || m_filename == nullptr || m_noOfLines == 0) {
            return false;
        }

        return true;
    }

    const char* TextFile::name() const {
        return m_filename;
    }

    ostream& operator<<(ostream& ostr, const TextFile& text) {
        text.view(ostr);
        return ostr;
    }

    istream& operator>>(istream& istr, TextFile& text) {
        text.getFile(istr);
        return istr;
    }
}
