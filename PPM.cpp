#include "PPM.hpp"
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;
const int MAX_COMMENT_SIZE = 1000;
const float R_LUMINANCE = 0.2126;
const float G_LUMINANCE = 0.7152;
const float B_LUMINANCE = 0.0722;

//==helper functions
void PPM::copyFrom(const PPM &other)
{
    m_rows = other.m_rows;
    m_col = other.m_col;
    m_colourscale = other.m_colourscale;

    m_filename = new char[strlen(other.m_filename) + 1];
    strcpy(m_filename, other.m_filename);

    Pixel **m_bitmap = new Pixel *[m_rows];
    for (int i = 0; i < m_rows; ++i)
    {
        m_bitmap[i] = new Pixel[m_col];
        for (int j = 0; j < m_col; j++)
        {
            m_bitmap[i][j] = other.m_bitmap[i][j];
        }
    }
}

int *extractBitsPPM(char *ch)
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

char convertBinaryToCharPPM(int int_sequence[])
{
    char value = 0;
    int exponent = 0;
    for (int i = 7; i >= 0; i--)
    {
        value += int_sequence[i] * pow(2, exponent);
        exponent++;
    }
    std::cout << "Final value after binary to char conversion is " << value << endl;
    return value;
}

unsigned char fromIntToChar(int num)
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

//==The big 4
PPM::PPM()
{
    m_rows = 0;
    m_col = 0;
    m_colourscale = 0;
    m_filename = nullptr;
    m_bitmap = nullptr;
}

PPM::PPM(int rows, int col)
{
    m_rows = rows;
    m_col = col;
    m_colourscale = 1;

    m_filename = new char[strlen("nofile") + 1];
    strcpy(m_filename, "nofile");

    m_bitmap = new Pixel *[m_rows];
    for (int i = 0; i < m_rows; i++)
    {
        m_bitmap[i] = new Pixel[m_col];
        for (int j = 0; j < m_col; j++)
        {
            m_bitmap[i][j] = {0, 0, 0};
        }
    }
    std::cout << "PPM constructor called, created map with dimensions rows:" << m_rows << "xcol:" << m_col << endl;
}

PPM::PPM(const PPM &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
}

PPM &PPM::operator=(const PPM &other)
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
const char *PPM::getType() const
{
    return "PPM";
}

const char *PPM::getFilename() const
{
    return m_filename;
}

int PPM::getNumRows() const 
{
   return m_rows;
}

int PPM::getNumCol() const
{
return m_col;
}

Pixel PPM::getAtIndex(int row, int col, int unused) const //FIXME: 
{
    unused--;
    return m_bitmap[row][col];
}

char PPM::getAtIndex(int row, int col) const
{
    row++; col--; 
    return 0;
}

//==setters
void PPM::setAtIndex(int row, int col, char value)
{
    cout<<"!!Unable !!"<<endl;
    row--;col++; value--;
}

void PPM::setFilname(const char *filename)
{
    strcpy(m_filename, filename);
}

void PPM::print()
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            cout << (int)m_bitmap[i][j].m_R << " "
                 << (int)m_bitmap[i][j].m_G << " "
                 << (int)m_bitmap[i][j].m_B << "| ";
        }
        cout << endl;
    }
}

//==image methods
void PPM::grayscale() //TODO:check if it is all grey
{
    PPM *tmp = new PPM(m_rows, m_col);
    delete[] tmp->m_filename;
    tmp->m_filename = new char[strlen(this->m_filename) + 1];
    strcpy(tmp->m_filename, this->m_filename);
    tmp->m_colourscale = this->m_colourscale;

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            float luminance = R_LUMINANCE * (m_bitmap[i][j].m_R) + G_LUMINANCE * (m_bitmap[i][j].m_G) + B_LUMINANCE * (m_bitmap[i][j].m_B);
            tmp->m_bitmap[i][j].m_R = luminance;
            tmp->m_bitmap[i][j].m_G = luminance;
            tmp->m_bitmap[i][j].m_B = luminance;
        }
    }
    cout<<"I've succesfully applied grayscale to "<<m_filename<<"."<<endl;
    *this = *tmp;
}


void PPM::negative()
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            m_bitmap[i][j] = m_bitmap[i][j].minus(m_colourscale);
        }
    }
    cout << "Succesfully negated image " << m_filename << endl;
}

void PPM::monochrome()
{
    if ((m_colourscale == 1) || (m_colourscale == 0))
    {
        cout << "Image " << m_filename << " is already monochrome!" << endl;
        return;
    }
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            //if (m_bitmap[i][j] > 0)
            if(m_bitmap[i][j].isWhite()==false)
            {
                //unsigned char m_scale = m_colourscale;
                m_bitmap[i][j] = {0, 0, 0};
            }
        }
    }
    cout << "Succesfully applied monochrome to image " << m_filename << endl;
}

IImage* PPM::rotate(const char *direction)
{
    PPM *new_PPM = new PPM(m_col, m_rows);
    new_PPM->m_filename= new char[strlen(m_filename)+1];
    strcpy(new_PPM->m_filename,m_filename);
    new_PPM->m_colourscale=m_colourscale;

    if (strcmp(direction, "left") == 0)
    {
        int tmp = m_col - 1;
        for (int i = 0; i < new_PPM->m_rows; i++)
        {
            for (int j = 0; j < new_PPM->m_col; j++)
            {
                new_PPM->m_bitmap[i][j] = m_bitmap[j][tmp];
            }

            tmp--;
        }
        cout << "I have performed left rotation on image " << m_filename << endl;
        //*this = *new_PPM;
        //return true;
       return new_PPM;
    }

    if (strcmp(direction, "right") == 0)
    {
        int tmp_row;
        cout << "I will be performinf right" << endl;
        for (int i = 0; i < new_PPM->m_rows; i++)
        {
            tmp_row = m_rows - 1;
            for (int j = 0; j < new_PPM->m_col; j++)
            {
                new_PPM->m_bitmap[i][j] = m_bitmap[tmp_row][i];
                cout << "[" << i << "][" << j << "]"
                     << "="
                     << "[" << tmp_row << "][" << i << "] ";
                tmp_row--;
            }
            cout << endl;
        }
        cout << "I have performed right rotation on image" << m_filename << endl;
        //*this = *new_PPM;
       // return true;
       return new_PPM;
    }
    else
    {
        cout << "Invalid rotational drection: options are \"right\" and \"left\" for image " << m_filename << endl;
         //return false;
        return this;
    }
}

IImage* PPM::collage(const char* direction,IImage* second_image) 
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
        int new_size =first_image_num_col+second_image_num_col;
        PPM *new_PPM = new PPM(first_image_num_rows, new_size);
         new_PPM->m_colourscale=m_colourscale;
        //==joining first table
        for (int i = 0; i <first_image_num_rows; i++)
        {
            for (int j = 0; j <first_image_num_col; j++)
            {
                new_PPM->m_bitmap[i][j] = m_bitmap[i][j];
            }
        }

        //==joining second table
        int col_num;
        for (int i = 0; i < second_image_num_rows; i++)
        {
            col_num = 0;
            for (int j = second_image_num_col; j < new_size; j++)
            {
                new_PPM->m_bitmap[i][j] =second_image->getAtIndex(i,col_num,0);
                col_num++;
            }
        }
        cout << "Ive sucesfully completed horizontal collage" << endl;
        return new_PPM;
    }

    //==vertical collage
    if (strcmp(direction, "vertical") == 0)
    {
        int new_size =first_image_num_rows+second_image_num_rows ;
        PPM *new_PPM = new PPM(new_size,first_image_num_col);
        new_PPM->m_colourscale=m_colourscale;
        //==joining first table
        for (int i = 0; i <first_image_num_rows; i++)
        {
            for (int j = 0; j <first_image_num_col; j++)
            {
                new_PPM->m_bitmap[i][j] = m_bitmap[i][j];
            }
        }

        //==joining second table
        int row_num = 0;
        for (int i =second_image_num_rows; i < new_size; i++)
        {
            for (int j = 0; j <second_image_num_col; j++)
            {
                new_PPM->m_bitmap[i][j] =second_image->getAtIndex(row_num,j,0);
            }
            row_num++;
        }
        cout << "Ive sucesfully completed horizontal collage" << endl;
        return new_PPM;
    }

    else
    { 
        cout << "Invalid collage direction: options are \"horizontal\" and \"vertical\"." << endl;
        return this;
    }
}

//==file methods //TODO: to be able to have comments anywhere

PPM &readPPMFromASCIIFile(std::ifstream &infile)
{
    std::cout << "Im inside read PPM from ascii file" << endl;
    //== reads comments and dimensions
    char newline;
    char space;
    int num_col;
    int num_rows;
    int colourscale;
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
        std::cout << "Dimensions are rows" << num_rows << "Xcol" << num_col << endl;
        infile >> colourscale;
        infile.get(newline);
    }
    else
    {
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        std::cout << "Dimensions are rows" << num_rows << "X col" << num_col << endl;
        infile >> colourscale;
        infile.get(newline);
    }

    PPM *new_PPM = new PPM(num_rows, num_col);
    new_PPM->m_colourscale = colourscale;
    cout << "Colourscale is" << new_PPM->m_colourscale << endl;

    std::cout << "Ill be inputting values" << endl;
    //==inputting bitmap
    int in_value_R; //FIXME: test!!
    int in_value_G;
    int in_value_B;
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_col; j++)
        {
            infile >> in_value_R;
            //cout<<value_R<<" ";
            infile >> in_value_G;
            //cout<<value_G<<" ";
            infile >> in_value_B;
            //cout<<value_B<<" ";
            unsigned char value_R = fromIntToChar(in_value_R);
            unsigned char value_G = fromIntToChar(in_value_G);
            unsigned char value_B = fromIntToChar(in_value_B);

            std::cout << "At row[" << i << "] col[" << j << "] = ";
            new_PPM->m_bitmap[i][j] = {value_R, value_G, value_B};
            cout << (int)new_PPM->m_bitmap[i][j].m_R << " "
                 << (int)new_PPM->m_bitmap[i][j].m_G << " "
                 << (int)new_PPM->m_bitmap[i][j].m_B << "| ";
        }
        std::cout << endl;
    }
    std::cout << "Ended inputting file" << endl;
    return *new_PPM;
}

PPM &readPPMFromBinaryFile(std::ifstream &infile)
{
    std::cout << "Im inside read PPM from binary file" << endl;
    //== reads comments and dimensions
    char newline;
    char space;
    int num_col;
    int num_rows;
    int colourscale;
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
        std::cout << "Dimensions are rows" << num_rows << "Xcol" << num_col << endl;
        infile >> colourscale;
        infile.get(newline);
    }
    else
    {
        cout << "No comment to input!" << endl;
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        std::cout << "Dimensions are rows" << num_rows << "X col" << num_col << endl;
        infile >> colourscale;
        infile.get(newline);
    }

    PPM *new_PPM = new PPM(num_rows, num_col);
    new_PPM->m_colourscale = colourscale;
    cout << "Colourscale is" << new_PPM->m_colourscale << endl;

    std::cout << "Ill be inputting values" << endl;
    //==inputting bitmap
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_col; j++)
        {
            char *value_R_ptr = new char;
            char *value_G_ptr = new char;
            char *value_B_ptr = new char;
            infile.read(value_R_ptr, 1);
            infile.read(value_G_ptr, 1);
            infile.read(value_B_ptr, 1);
            new_PPM->m_bitmap[i][j] = {(unsigned char)*value_R_ptr, (unsigned char)*value_G_ptr, (unsigned char)*value_B_ptr};
            cout << (int)new_PPM->m_bitmap[i][j].m_R << " "
                 << (int)new_PPM->m_bitmap[i][j].m_G << " "
                 << (int)new_PPM->m_bitmap[i][j].m_B << "| ";
        }
        std::cout << endl;
    }
    std::cout << "Ended inputting file" << endl;
    return *new_PPM;
}

void PPM::writeToASCIIFile(std::ofstream &outfile)
{
    std::cout << "Im inside write PPMTOASCIIfile" << endl;
    //==writes magic number
    const char magic_number[3] = "P3";
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
    outfile << m_colourscale << endl;
    std::cout << "Writing colourscale " << m_colourscale << endl;

    //==writes bitmap
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col; j++)
        {
            //outfile<<obj.m_bitmap[i][j]<<" ";
            outfile << (int)m_bitmap[i][j].m_R << " "
                    << (int)m_bitmap[i][j].m_G << " "
                    << (int)m_bitmap[i][j].m_B << " ";
        }
        outfile << endl;
    }
    std::cout << "Ended inputting file" << endl;
}

// Binary
void PPM::writeToBinaryFile(std::ofstream &outfile)
{
    std::cout << "Im inside write PPMToBinaryfile" << endl;
    //==writes magic number
    const char magic_number[3] = "P6";
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
    int colourscale = m_colourscale;
    outfile << colourscale << endl;

    //==prints bitmap
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            outfile << m_bitmap[i][j];
        }
        //outfile<<endl;
    }
}