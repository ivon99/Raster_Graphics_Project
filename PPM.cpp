#include "PPM.hpp"
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;
const int MAX_COMMENT_SIZE = 1000;
/// constants representing intensity(amount of perceived light)
/// for every of the RGB colours
const float R_LUMINANCE = 0.2126; ///< perceived luminance for red colour
const float G_LUMINANCE = 0.7152; ///< perceived luminance for green colour
const float B_LUMINANCE = 0.0722; ///<perceived luminance for blue colour

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

/// writes number value to a byte
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
    // std::cout << "PPM constructor called, created map with dimensions rows:" << m_rows << "x col:" << m_col << endl;
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

Pixel PPM::getAtIndex(int row, int col, int unused) const
{
    unused--;
    return m_bitmap[row][col];
}

char PPM::getAtIndex(int row, int col) const
{
    row++;
    col--;
    return 0;
}

//==setters
// not defined for PPM as pixels encoded as RGB
void PPM::setAtIndex(int row, int col, char value)
{
    row--;
    col++;
    value--;
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
void PPM::grayscale()
{
    PPM *tmp = new PPM(m_rows, m_col);
    delete[] tmp->m_filename;
    tmp->m_filename = new char[strlen(this->m_filename) + 1];
    strcpy(tmp->m_filename, this->m_filename);
    tmp->m_colourscale = this->m_colourscale;

    int greyscale_pixels = 0;
    int all_pixels = 0;
    for (int i = 0; i < m_rows; i++) //checks if picture is already in greyscale
    {
        for (int j = 0; j < m_col; j++)
        {
            all_pixels++;
            if (m_bitmap[i][j].isGrey())
            {
                greyscale_pixels++;
            }
        }
    }
    if (greyscale_pixels == (all_pixels))
    {
        cout << "Image " << m_filename << "is already in greyscale!" << endl;
        return;
    }

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
    cout << "Successfully applied grayscale to " << m_filename << "." << endl;
    *this = *tmp;
}

void PPM::negative()
{
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_col; j++)
        {
            //m_bitmap[i][j] = m_bitmap[i][j].minus(m_colourscale);
            m_bitmap[i][j] = m_bitmap[i][j] - m_colourscale;
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
            if (m_bitmap[i][j].isWhite() == false) //if not a white pixel
            {
                m_bitmap[i][j] = {0, 0, 0}; //turn to black
            }
        }
    }
    cout << "Succesfully applied monochrome to image " << m_filename << endl;
}

IImage *PPM::rotate(const char *direction)
{
    PPM *new_PPM = new PPM(m_col, m_rows);
    new_PPM->m_filename = new char[strlen(m_filename) + 1];
    strcpy(new_PPM->m_filename, m_filename);
    new_PPM->m_colourscale = m_colourscale;

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
        cout << "Successfully performed left rotation on image " << m_filename << endl;
        return new_PPM;
    }

    if (strcmp(direction, "right") == 0)
    {
        int tmp_row;
        for (int i = 0; i < new_PPM->m_rows; i++)
        {
            tmp_row = m_rows - 1;
            for (int j = 0; j < new_PPM->m_col; j++)
            {
                new_PPM->m_bitmap[i][j] = m_bitmap[tmp_row][i];
                tmp_row--;
            }
        }
        cout << "Successfully performed right rotation on image" << m_filename << endl;
        return new_PPM;
    }
    else
    {
        cout << "Invalid rotational drection: options are \"right\" and \"left\" for image " << m_filename << endl;
        return this;
    }
}

IImage *PPM::collage(const char *direction, IImage *second_image)
{
    int first_image_num_rows = m_rows;
    int first_image_num_col = m_col;
    int second_image_num_rows = second_image->getNumRows();
    int second_image_num_col = second_image->getNumCol();
    if ((first_image_num_rows != second_image_num_rows)                                                    //checks dimensions of images are the same
        || (first_image_num_col != second_image_num_col) || (strcmp("PPM", second_image->getType()) != 0)) //checks if types are the same
    {
        cout << "Unable to apply collage for images " << m_filename << " and " << second_image->getFilename() << " ."
             << "Collage images should be of the same type and dimensions!" << endl;
    }
    //==horizontal collage
    if (strcmp(direction, "horizontal") == 0)
    {
        int new_size = first_image_num_col + second_image_num_col;
        PPM *new_PPM = new PPM(first_image_num_rows, new_size);
        new_PPM->m_colourscale = m_colourscale;
        //==joining first table
        for (int i = 0; i < first_image_num_rows; i++)
        {
            for (int j = 0; j < first_image_num_col; j++)
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
                new_PPM->m_bitmap[i][j] = second_image->getAtIndex(i, col_num, 0);
                col_num++;
            }
        }
        cout << "Successfully completed horizontal collage" << endl;
        return new_PPM;
    }

    //==vertical collage
    if (strcmp(direction, "vertical") == 0)
    {
        int new_size = first_image_num_rows + second_image_num_rows;
        PPM *new_PPM = new PPM(new_size, first_image_num_col);
        new_PPM->m_colourscale = m_colourscale;
        //==joining first table
        for (int i = 0; i < first_image_num_rows; i++)
        {
            for (int j = 0; j < first_image_num_col; j++)
            {
                new_PPM->m_bitmap[i][j] = m_bitmap[i][j];
            }
        }

        //==joining second table
        int row_num = 0;
        for (int i = second_image_num_rows; i < new_size; i++)
        {
            for (int j = 0; j < second_image_num_col; j++)
            {
                new_PPM->m_bitmap[i][j] = second_image->getAtIndex(row_num, j, 0);
            }
            row_num++;
        }
        cout << "Successfully completed vertical collage" << endl;
        return new_PPM;
    }

    else
    {
        cout << "Invalid collage direction: options are \"horizontal\" and \"vertical\"." << endl;
        return this;
    }
}

//==file methods

PPM &readPPMFromASCIIFile(std::ifstream &infile)
{
    //== reads comments and dimensions
    char newline;
    char space;
    int num_col;
    int num_rows;
    int colourscale;
    infile.get(newline);
    if (infile.peek() == '#') //if a comment
    {
        char hash;
        infile.get(hash);
        infile.get(space);
        char comment[MAX_COMMENT_SIZE];
        infile.getline(comment, MAX_COMMENT_SIZE);
        infile >> num_col;
        infile >> num_rows;
        infile >> colourscale;
        infile.get(newline);
    }
    else
    {
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        infile >> colourscale;
        infile.get(newline);
    }

    PPM *new_PPM = new PPM(num_rows, num_col);
    new_PPM->m_colourscale = colourscale;

    //==inputting bitmap
    int in_value_R;
    int in_value_G;
    int in_value_B;
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_col; j++)
        {
            infile >> in_value_R;
            infile >> in_value_G;
            infile >> in_value_B;
            unsigned char value_R = fromIntToChar(in_value_R);
            unsigned char value_G = fromIntToChar(in_value_G);
            unsigned char value_B = fromIntToChar(in_value_B);

            new_PPM->m_bitmap[i][j] = {value_R, value_G, value_B};
        }
    }
    std::cout << "Succesfully read PPM from ASCII encoded file" << endl;
    return *new_PPM;
}

PPM &readPPMFromBinaryFile(std::ifstream &infile)
{
    //== reads comments and dimensions
    char newline;
    char space;
    int num_col;
    int num_rows;
    int colourscale;
    infile.get(newline);
    if (infile.peek() == '#') //if a comment
    {
        char hash;
        infile.get(hash);
        infile.get(space);
        char comment[MAX_COMMENT_SIZE];
        infile.getline(comment, MAX_COMMENT_SIZE);
        infile >> num_col;
        infile >> num_rows;
        infile >> colourscale;
        infile.get(newline);
    }
    else
    {
        infile >> num_col;
        infile >> num_rows;
        infile.get(newline);
        infile >> colourscale;
        infile.get(newline);
    }

    PPM *new_PPM = new PPM(num_rows, num_col);
    new_PPM->m_colourscale = colourscale;

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
        }
    }
    std::cout << "Successfully read PPM from binary encoded file." << endl;
    return *new_PPM;
}

void PPM::writeToASCIIFile(std::ofstream &outfile)
{
    //==writes magic number
    const char magic_number[3] = "P3"; //magic number for ASCII encoded PPM file
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

    //==writes bitmap
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col; j++)
        {
            outfile << (int)m_bitmap[i][j].m_R << " "
                    << (int)m_bitmap[i][j].m_G << " "
                    << (int)m_bitmap[i][j].m_B << " ";
        }
        outfile << endl;
    }
    std::cout << "Successfully wrote PPM to ASCII encoded file" << endl;
}

// Binary
void PPM::writeToBinaryFile(std::ofstream &outfile)
{
    //==writes magic number
    const char magic_number[3] = "P6"; //magic number for binary encoded PPM file
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
    }
    cout << "Successfully wrote PPM to binary encoded file" << endl;
}