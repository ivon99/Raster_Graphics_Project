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

unsigned char fromIntToCharPGM(int num) 
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
   // std::cout << "PGM constructor called, created map with dimensions rows:" << m_rows << "xcol:" << m_col << endl;
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

// undefined method as PGM doesn't encode in RGB
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
            if (m_bitmap[i][j] < m_grayscale) //if shade of grey
            {
                m_bitmap[i][j] = m_grayscale - m_bitmap[i][j]; //invert shade 
                continue;
            }
        }
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
        {
            if (m_bitmap[i][j] < m_grayscale) //if grey convert to black
            {
                m_bitmap[i][j] = 0;
            }
        }
    }
    cout << "Succesfully applied monochrome to image " << m_filename << endl;
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
        return new_PGM;
    }

    if (strcmp(direction, "right") == 0)
    {
        int tmp_row;
        for (int i = 0; i < new_PGM->m_rows; i++)
        {
            tmp_row = m_rows - 1;
            for (int j = 0; j < new_PGM->m_col; j++)
            {
                new_PGM->m_bitmap[i][j] = m_bitmap[tmp_row][i];
                tmp_row--;
            }
        }
        cout << "I have performed right rotation for image " << m_filename << endl;
        return new_PGM;
    }
    else
    {
        cout << "Invalid rotation direction for image " << m_filename << endl;
        return this;
    }
}

IImage *PGM::collage(const char *direction, IImage *second_image)
{
    int first_image_num_rows = m_rows;
    int first_image_num_col = m_col;
    int second_image_num_rows = second_image->getNumRows();
    int second_image_num_col = second_image->getNumCol();    
    if ((first_image_num_rows != second_image_num_rows)  //checks if dimensons of images are the same
       || (first_image_num_col != second_image_num_col) 
       || (strcmp("PBM", second_image->getType())!=0))      //checks if types of images are the same
    {
        cout << "Unable to apply collage for images " << m_filename << " and " << second_image->getFilename() << " ."
             << "Collage images should be of the same type and dimensions!" << endl;
             return this;
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
        return this;
    }
}

//==file methods

PGM &readPGMFromASCIIFile(std::ifstream &infile)
{
    //== reads comments, dimensions and grayscale max value
    char newline;
    char space;
    int num_col;
    int num_rows;
    int grayscale;
    infile.get(newline);
    if (infile.peek() == '#')
    {
        char hash;
        infile.get(hash);
        infile.get(space);
        char comment[MAX_COMMENT_SIZE];
        infile.getline(comment, MAX_COMMENT_SIZE);
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        infile >> grayscale;
        infile.get(newline);
    }
    else
    {
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        infile >> grayscale;
        infile.get(newline);
    }

    PGM *new_PGM = new PGM(num_rows, num_col);
    new_PGM->m_grayscale = grayscale;

    //==inputting bitmap
    int value;
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_col; j++)
        {
            infile >> value;
            new_PGM->m_bitmap[i][j] = fromIntToCharPGM(value);
        }
    }
    cout<<"Succesfully read PGM image from file."<<endl;
    return *new_PGM;
}

PGM &readPGMFromBinaryFile(std::ifstream &infile)
{
    char newline;
    char space;
    infile.get(newline);

    //== reads comments and dimensions
    int num_col;
    int num_rows;
    int grayscale;

    if (infile.peek() == '#')
    {
        char hash;
        infile.get(hash);
        infile.get(space);
        char comment[MAX_COMMENT_SIZE];
        infile.getline(comment, MAX_COMMENT_SIZE);
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        infile >> grayscale;
        infile.get(newline);
    }
    else
    {
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        infile >> grayscale;
        infile.get(newline);
    }

    PGM *new_PGM = new PGM(num_rows, num_col);
    new_PGM->m_grayscale = grayscale;

    //==reading bitmap

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_col; j++)
        {
            char *value_ptr = new char;
            infile.read(value_ptr, 1);
            new_PGM->m_bitmap[i][j] = *value_ptr;
        }
    }

    std::cout << "Successfully read PGM image from file." << endl;
    return *new_PGM;
}

void PGM::writeToASCIIFile(std::ofstream &outfile)
{
    //==writes magic number
    const char magic_number[3] = "P2"; //magic number for ASCII encoded PGM image
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
    std::cout << "Successfully wrote PGM to ASCII encoded file." << endl;
}


void PGM::writeToBinaryFile(std::ofstream &outfile)
{
    //==writes magic number
    const char magic_number[3] = "P5"; //magic number for binary encoded PGM file
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

    //==writes bitmap
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            outfile << m_bitmap[i][j];
        }
    }
    cout<<"Successfully wrote PGM to binary encoded file."<<endl;
}
