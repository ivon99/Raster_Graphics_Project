#include "PGM.hpp"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
const int MAX_COMMENT_SIZE = 1000;

//==helper functions
void PGM::copyFrom(const PGM &other)
{
    m_rows = other.m_rows;
    m_col = other.m_col;
    m_grayscale = other.m_grayscale;

    m_filename = new char[strlen(other.m_filename) + 1];
    strcpy(m_filename, other.m_filename);

    unsigned char **m_bitmap = new unsigned char *[m_rows];
    for (int i = 0; i < m_rows; ++i)
    {
        m_bitmap[i] = new unsigned char[m_col];
        for (int j = 0; j < m_col; j++)
        {
            m_bitmap[i][j] = other.m_bitmap[i][j];
        }
    }
}

int *extractBitsPGM(char *ch)
{
    int size = sizeof(ch);
    int *bit_value = new int[size];
    for (int i = 0; i < size; i++)
    {
        bit_value[i] = 0;
    }
    int value = int(*ch);
    int tmp = value;
    for (int i = 0; value > 0; i++)
    {
        bit_value[i] = value % 2;
        std::cout << bit_value[i];
        value = value / 2;
    }
    std::cout << "Binary of the given number" << tmp << "= ";
    for (int i = size - 1; i >= 0; i--)
    {
        std::cout << bit_value[i];
    }
    return bit_value;
}

unsigned char convertBinaryToCharPGM(int int_sequence[])
{
    unsigned char value = 0;
    int exponent = 0;
    for (int i = 7; i >= 0; i--)
    {
        value += int_sequence[i] * pow(2, exponent);
        exponent++;
    }
    std::cout << "Final value after binary to char conversion is " << value << endl;
    return value;
}

unsigned char fromIntToCharPGM(int num) //FIXME:
{
    int digit;
    int exponent = 0;
    unsigned char value = 0;
    while (num > 0)
    {
        digit = num % 10;
        value += digit * pow(10, exponent);
        exponent++;
        num /= 10;
    }
    return value;
}

//==the big 4
PGM::PGM()
{
    m_rows = 0;
    m_col = 0;
    m_grayscale = 0;
    m_filename = nullptr;
    m_bitmap = nullptr;
}

PGM::PGM(int rows, int col)
{
    m_rows = rows;
    m_col = col;
    m_grayscale = 1;

    m_filename = new char[strlen("nofile") + 1];
    strcpy(m_filename, "nofile");

    m_bitmap = new unsigned char *[m_rows];
    for (int i = 0; i < m_rows; i++)
    {
        m_bitmap[i] = new unsigned char[m_col];
        for (int j = 0; j < m_col; j++)
        {
            m_bitmap[i][j] = 0;
        }
    }
    std::cout << "PGM constructor called, created map with dimensions rows:" << m_rows << "xcol:" << m_col << endl;
}

PGM::PGM(const PGM &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
}

PGM &PGM::operator=(const PGM &other)
{
    if (this != &other)
    {
        for (int i = 0; i < m_rows; i++)
        {
            delete[] m_bitmap[i];
        }
        delete[] m_bitmap;
        delete[] m_filename;
        copyFrom(other);
    }
    return *this;
}

//==getters
const char *PGM::getType() const
{
    return "PGM";
}

const char *PGM::getFilename() const
{
    return m_filename;
}

int PGM::getNumRows() const
{
    return m_rows;
}

int PGM::getNumCol() const
{
    return m_col;
}

char PGM::getAtIndex(int row, int col) const
{
    return m_bitmap[row][col];
}

Pixel PGM::getAtIndex(int row, int col, int unused) const
{
    row++;
    col++;
    unused++;
    return {0, 0, 0};
}

//==setters
void PGM::setAtIndex(int row, int col, char value)
{
    m_bitmap[row][col] = value;
}

void PGM::setFilname(const char *filename)
{
    strcpy(m_filename, filename);
}

void PGM::print()
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            cout << (int)m_bitmap[i][j] << " ";
        }
        cout << endl;
    }
}

void PGM::grayscale()
{
    cout << "Unable to perform grayscale on " << m_filename << " because file already in greyscale!" << endl;
}

void PGM::negative()
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            //m_bitmap[i][j]= m_grayscale- m_bitmap[i][j];
            /*if (m_bitmap[i][j] > m_grayscale)
            {
                m_bitmap[i][j] = m_bitmap[i][j] - m_grayscale;
            }
            else
            {
                m_bitmap[i][j] = 0;
            } */
            if (m_bitmap[i][j] == 0) //if black turn white
            {
                m_bitmap[i][j] = m_grayscale;
                continue;
            }
            if (m_bitmap[i][j] == m_grayscale) //if white turn black
            {
                m_bitmap[i][j] = 0;
                continue;
            }
            if (m_bitmap[i][j] < m_grayscale)
            {
                m_bitmap[i][j] = m_grayscale - m_bitmap[i][j];
                continue;
            }
            cout << (int)m_bitmap[i][j] << " ";
        }
        cout << endl;
    }
    cout << "I've successsfully negated image " << m_filename << endl;
}

void PGM::monochrome()
{
    if ((m_grayscale == 1) || (m_grayscale == 0))
    {
        cout << "Image " << m_filename << " is already monochrome!" << endl;
        return;
    }
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        { /*
          if(m_bitmap[i][j]>0)
          {
              cout<<"And every value will be converted to"<<m_grayscale<<endl;
              m_bitmap[i][j]=m_grayscale;
          } */
            if (m_bitmap[i][j] < m_grayscale)
            {
                cout << "And every value will be converted to 0" << endl;
                m_bitmap[i][j] = 0;
            }
        }
    }
    cout << "Succesfully applied monochrome to imate " << m_filename << endl;
}

IImage *PGM::rotate(const char *direction)
{
    PGM *new_PGM = new PGM(m_col, m_rows);
    new_PGM->m_filename = new char[strlen(m_filename) + 1];
    strcpy(new_PGM->m_filename, m_filename);
    new_PGM->m_grayscale = m_grayscale;

    if (strcmp(direction, "left") == 0)
    {
        int tmp = m_col - 1;
        for (int i = 0; i < new_PGM->m_rows; i++)
        {
            for (int j = 0; j < new_PGM->m_col; j++)
            {
                new_PGM->m_bitmap[i][j] = m_bitmap[j][tmp];
            }

            tmp--;
        }
        cout << "Succesfully performed left rotation on image " << m_filename << endl;
        //*this = *new_PGM;
        //return true;
        return new_PGM;
    }

    if (strcmp(direction, "right") == 0)
    {
        int tmp_row;
        cout << "I will be performinf right rotation" << endl;
        for (int i = 0; i < new_PGM->m_rows; i++)
        {
            tmp_row = m_rows - 1;
            for (int j = 0; j < new_PGM->m_col; j++)
            {
                new_PGM->m_bitmap[i][j] = m_bitmap[tmp_row][i];
                cout << "[" << i << "][" << j << "]"
                     << "="
                     << "[" << tmp_row << "][" << i << "] ";
                tmp_row--;
            }
            cout << endl;
        }
        cout << "I have performed right rotation for image " << m_filename << endl;
        //  *this = *new_PGM;
        // return true;
        return new_PGM;
    }
    else
    {
        cout << "Invalid rotation direction for image " << m_filename << endl;
        // return false;
        //PGM* null_PGM= new PGM();
        return this;
    }
}

//TODO: to firstly chechk if one dimensions
IImage *PGM::collage(const char *direction, IImage *second_image)
{
    int first_image_num_rows = m_rows;
    int first_image_num_col = m_col;
    int second_image_num_rows = second_image->getNumRows();
    int second_image_num_col = second_image->getNumCol();
    if ((first_image_num_rows != second_image_num_rows) || (first_image_num_col != second_image_num_col) || (strcmp("PBM", second_image->getType())))
    {
        cout << "Unable to apply collage for images " << m_filename << " and " << second_image->getFilename() << " ."
             << "Collage images should be of the same type and dimensions!" << endl;
    }

    //==horizontal collage
    if (strcmp(direction, "horizontal") == 0)
    {

        int new_size = first_image_num_col + second_image_num_col;
        PGM *new_PGM = new PGM(first_image_num_rows, new_size);
        new_PGM->m_grayscale = m_grayscale;
        //==joining first table
        for (int i = 0; i < first_image_num_rows; i++)
        {
            for (int j = 0; j < first_image_num_col; j++)
            {
                new_PGM->m_bitmap[i][j] = m_bitmap[i][j];
            }
        }

        //==joining second table
        int col_num;
        for (int i = 0; i < first_image_num_rows; i++)
        {
            col_num = 0;
            for (int j = first_image_num_col; j < new_size; j++)
            {
                new_PGM->m_bitmap[i][j] = second_image->getAtIndex(i, col_num);
                col_num++;
            }
        }
        cout << "Ive sucesfully completed horizontal collage" << endl;
        return new_PGM;
    }

    //==vertical collage
    if (strcmp(direction, "vertical") == 0)
    {
        int new_size = first_image_num_rows + second_image_num_rows;
        PGM *new_PGM = new PGM(new_size, first_image_num_col);
        new_PGM->m_grayscale = m_grayscale;
        //==joining first table
        for (int i = 0; i < first_image_num_rows; i++)
        {
            for (int j = 0; j < first_image_num_col; j++)
            {
                new_PGM->m_bitmap[i][j] = m_bitmap[i][j];
            }
        }

        //==joining second table
        int row_num = 0;
        for (int i = first_image_num_rows; i < new_size; i++)
        {
            for (int j = 0; j < first_image_num_col; j++)
            {
                new_PGM->m_bitmap[i][j] = second_image->getAtIndex(row_num, j);
            }
            row_num++;
        }
        cout << "Ive sucesfully completed horizontal collage" << endl;
        return new_PGM;
    }
    else
    {
        cout << "Invalid collage direction" << endl;
        // PGM* null_PGM = new PGM();
        return this;
    }
}

//==file methods

PGM &readPGMFromASCIIFile(std::ifstream &infile)
{
    std::cout << "Im inside read PGM from ascii file" << endl;
    //== reads comments and dimensions
    char newline;
    char space;
    int num_col;
    int num_rows;
    int grayscale;
    infile.get(newline);
    if (infile.peek() == '#')
    {
        std::cout << "Im inside a comment!" << endl;
        char hash;
        infile.get(hash);
        infile.get(space);
        char comment[MAX_COMMENT_SIZE];
        infile.getline(comment, MAX_COMMENT_SIZE);
        std::cout << comment;
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        std::cout << "Dimensions are rows" << num_rows << "Xcol" << num_col << "!" << endl;
        infile >> grayscale;
        cout << "Grayscale is " << grayscale << "!!!" << endl;
        infile.get(newline);
    }
    else
    {
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        std::cout << "Dimensions are rows" << num_rows << "X col" << num_col << endl;
        infile >> grayscale;
        infile.get(newline);
    }

    PGM *new_PGM = new PGM(num_rows, num_col);
    new_PGM->m_grayscale = grayscale;

    std::cout << "Ill be inputting values" << endl;
    //==inputting bitmap
    int value;
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_col; j++)
        {
            infile >> value;
            cout << "Read value: " << value << " ";
            std::cout << "At row[" << i << "] col[" << j << "] = ";
            new_PGM->m_bitmap[i][j] = fromIntToCharPGM(value);
            std::cout << (int)new_PGM->m_bitmap[i][j] << endl;
        }
        std::cout << endl;
    }
    std::cout << "Ended inputting file" << endl;
    return *new_PGM;
}

PGM &readPGMFromBinaryFile(std::ifstream &infile)
{
    std::cout << "Im inside read PGM from binary file" << endl;
    char newline;
    char space;
    //==reads magic number
    /* char magic_number[3];
     infile>>magic_number;
     std::cout<<magic_number; */
    infile.get(newline);

    //== reads comments and dimensions
    int num_col;
    int num_rows;
    int grayscale;

    if (infile.peek() == '#')
    {
        std::cout << "Im inside a comment!" << endl;
        char hash;
        infile.get(hash);
        infile.get(space);
        char comment[MAX_COMMENT_SIZE];
        infile.getline(comment, MAX_COMMENT_SIZE);
        std::cout << comment;
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        std::cout << "Dimensions are" << num_col << "X" << num_rows << endl;
        infile >> grayscale;
        infile.get(newline);
    }
    else
    {
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        std::cout << "Dimensions are" << num_col << "X" << num_rows << endl;
        infile >> grayscale;
        infile.get(newline);
    }

    PGM *new_PGM = new PGM(num_rows, num_col);
    new_PGM->m_grayscale = grayscale;

    //==reading bitmap
    std::cout << "And bitmap is " << endl;

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_col; j++)
        {
            char *value_ptr = new char;
            infile.read(value_ptr, 1);
            /*
            if ((strcmp(value_ptr, "\n") == 0) ||
                (strcmp(value_ptr, " ") == 0))
            //(int(*value_ptr) == 0))
            {
                infile.read(value_ptr, 1);
                new_PGM->m_bitmap[i][j] = *value_ptr;
                continue;
            } */
            new_PGM->m_bitmap[i][j] = *value_ptr;
            cout << (int)new_PGM->m_bitmap[i][j] << ",";
        }
        cout << endl;
    }

    std::cout << "Ended inputting file" << endl;
    return *new_PGM;
}

void PGM::writeToASCIIFile(std::ofstream &outfile)
{
    std::cout << "Im inside write PGMTOASCIIfile" << endl;
    //==writes magic number
    const char magic_number[3] = "P2";
    outfile << magic_number << "\n";

    //==writes comment
    const char hash_comment = '#';
    char *comment = new char[MAX_COMMENT_SIZE];
    comment = m_filename;
    outfile << hash_comment << " " << comment << endl;

    //==writes col and rows size
    int col = m_col;
    int rows = m_rows;
    outfile << col << " " << rows << endl;

    //==writes greyscale
    int grayscale = m_grayscale;
    outfile << grayscale << endl;

    //==writes bitmap
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col; j++)
        {
            outfile << (int)m_bitmap[i][j] << " ";
        }
        outfile << endl;
    }
    std::cout << "Ended inputting file" << endl;
}

// Binary
void PGM::writeToBinaryFile(std::ofstream &outfile)
{
    std::cout << "Im inside write PGMToBinaryfile" << endl;
    const char magic_number[3] = "P5";
    outfile << magic_number << "\n";
    //==writes comment
    const char hash_comment = '#';
    char *comment = new char[MAX_COMMENT_SIZE];
    comment = m_filename;
    outfile << hash_comment << " " << comment << endl;

    //==writes col and rows size and grayscale level
    int col = m_col;
    int rows = m_rows;
    outfile << col << " " << rows << endl;
    int grayscale = m_grayscale;
    outfile << grayscale << endl;

    //==prints bitmap
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            outfile << m_bitmap[i][j];
        }
    }
}
