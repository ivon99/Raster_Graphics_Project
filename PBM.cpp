#include "PBM.hpp"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
const int MAX_COMMENT_SIZE = 1000;

//==helper functions
void PBM::copyFrom(const PBM &other)
{
  m_rows = other.m_rows;
  m_col = other.m_col;

  m_filename = new char[strlen(other.m_filename) + 1];
  strcpy(m_filename, other.m_filename);

  char **m_bitmap = new char *[m_rows];
  for (int i = 0; i < m_rows; ++i)
  {
    m_bitmap[i] = new char[m_col];
    for (int j = 0; j < m_col; j++)
    {
      m_bitmap[i][j] = other.m_bitmap[i][j];
    }
  }
}

char PBM::convertBinaryToChar(int int_sequence[])
{
  char value = 0;
  int exponent = 0;
  for (int i = 7; i >= 0; i--)
  {
    value += int_sequence[i] * pow(2, exponent);
    exponent++;
  }
  return value;
}

//==The big 4

PBM::PBM()
{
  m_rows = 1;
  m_col = 1;
  m_filename = new char[strlen("nofile") + 1];
  strcpy(m_filename, "nofile");
  m_bitmap = new char *[m_rows];
  for (int i = 0; i < m_rows; i++)
  {
    m_bitmap[i] = new char[m_col];
    for (int j = 0; j < m_col; j++)
    {
      m_bitmap[i][j] = 0;
    }
  }
}

PBM::PBM(int rows, int col)
{
  m_rows = rows;
  m_col = col;

  m_filename = new char[strlen("nofile") + 1];
  strcpy(m_filename, "nofile");

  m_bitmap = new char *[m_rows];
  for (int i = 0; i < m_rows; i++)
  {
    m_bitmap[i] = new char[m_col];
    for (int j = 0; j < m_col; j++)
    {
      m_bitmap[i][j] = 0;
    }
  }
  //std::cout << "PBM constructor called, created map with dimensions rows:" << m_rows << "xcol:" << m_col << endl;
}

PBM::PBM(const PBM &other)
{
  if (this != &other)
  {
    copyFrom(other);
  }
}

PBM &PBM::operator=(const PBM &other)
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

//=getters
const char *PBM::getType() const
{
  return "PBM";
}

const char *PBM::getFilename() const
{
  return m_filename;
}

int PBM::getNumRows() const
{
  return m_rows;
}

int PBM::getNumCol() const
{
  return m_col;
}

char PBM::getAtIndex(int row, int col) const
{
  return m_bitmap[row][col];
}

// not used as PBM not encoded in RGB pixels
Pixel PBM::getAtIndex(int row, int col, int unused) const
{
  row++;
  col++;
  unused++;
  return {0, 0, 0};
}

//==setters

void PBM::setAtIndex(int row, int col, char value)
{
  m_bitmap[row][col] = value;
}

void PBM::setFilname(const char *filename)
{
  strcpy(m_filename, filename);
}

void PBM::print()
{
  for (int i = 0; i < m_rows; i++)
  {
    for (int j = 0; j < m_col; j++)
    {
      cout << (int)m_bitmap[i][j];
    }
    cout << endl;
  }
}

//==image methods
void PBM::grayscale()
{
  cout << "Can't do grayscale on a .pbm image " << m_filename << " !" << endl;
}

void PBM::monochrome()
{
  cout << "Can't do monochrome on a .pbm image" << m_filename << " !" << endl;
}

void PBM::negative()
{
  for (int i = 0; i < m_rows; i++)
  {
    for (int j = 0; j < m_col; j++)
    {
      if (m_bitmap[i][j] == 0) // if white pixel
      {
        m_bitmap[i][j] = 1; //turn it to black
        continue;
      }
      if (m_bitmap[i][j] == 1) //if black pixel
      {
        m_bitmap[i][j] = 0; //turn it to white
        continue;
      }
    }
  }
  cout << "Succesfully negated image " << m_filename << endl;
}

IImage *PBM::rotate(const char *direction)
{
  PBM *new_PBM = new PBM(m_col, m_rows); //makes a new image with inversed dimensions
  new_PBM->m_filename = new char[strlen(m_filename) + 1];
  strcpy(new_PBM->m_filename, m_filename);

  if (strcmp(direction, "left") == 0)
  {
    int tmp = m_col - 1;
    for (int i = 0; i < new_PBM->m_rows; i++)
    {
      for (int j = 0; j < new_PBM->m_col; j++)
      {
        new_PBM->m_bitmap[i][j] = m_bitmap[j][tmp]; //maps left rotated values to new image
      }
      tmp--;
    }
    cout << "Succesfully performed left rotation on image " << m_filename << endl;
    return new_PBM;
  }

  if (strcmp(direction, "right") == 0)
  {
    int tmp_row;
    for (int i = 0; i < new_PBM->m_rows; i++)
    {
      tmp_row = m_rows - 1;
      for (int j = 0; j < new_PBM->m_col; j++)
      {
        new_PBM->m_bitmap[i][j] = m_bitmap[tmp_row][i]; //writes right rotated values to new image
        tmp_row--;
      }
    }
    cout << "Succesfully performed right rotation on image" << m_filename << endl;
    return new_PBM;
  }
  else
  {
    cout << "Error in performing " << direction << " rotation for image " << m_filename << "!" << endl;
    return this;
  }
}

IImage *PBM::collage(const char *direction, IImage *second_image)
{
  int first_image_num_rows = m_rows;
  int first_image_num_col = m_col;
  int second_image_num_rows = second_image->getNumRows();
  int second_image_num_col = second_image->getNumCol();
  if ((first_image_num_rows != second_image_num_rows)                                                    //checks if dimensons of images is not the same
      || (first_image_num_col != second_image_num_col) || (strcmp("PBM", second_image->getType()) != 0)) //checks if types of images is not the same
  {
    cout << "Unable to apply collage for images " << m_filename << " and " << second_image->getFilename() << " ."
         << "Collage images should be of the same type and dimensions!" << endl;
    return this;
  }
  if (strcmp(direction, "horizontal") == 0)
  {
    int new_size = first_image_num_col + second_image_num_col;
    PBM *new_PBM = new PBM(first_image_num_rows, new_size);
    //==joining first table
    for (int i = 0; i < first_image_num_rows; i++)
    {
      for (int j = 0; j < first_image_num_col; j++)
      {
        new_PBM->m_bitmap[i][j] = m_bitmap[i][j];
      }
    }

    //==joining second table
    int col_num = 0;
    for (int i = 0; i < second_image_num_rows; i++)
    {
      col_num = 0;
      for (int j = first_image_num_col; j < new_size; j++)
      {
        new_PBM->m_bitmap[i][j] = second_image->getAtIndex(i, col_num);
        col_num++;
      }
    }
    cout << "Successfully completed horizontal collage" << endl;
    return new_PBM;
  }

  if (strcmp(direction, "vertical") == 0)
  {
    int new_size = first_image_num_rows + second_image_num_rows;
    PBM *new_PBM = new PBM(new_size, first_image_num_col);
    //==joining first table
    for (int i = 0; i < first_image_num_rows; i++)
    {
      for (int j = 0; j < first_image_num_col; j++)
      {
        new_PBM->m_bitmap[i][j] = m_bitmap[i][j];
      }
    }

    //==joining second table
    int row_num = 0;
    for (int i = first_image_num_rows; i < new_size; i++)
    {
      for (int j = 0; j < first_image_num_col; j++)
      {
        new_PBM->m_bitmap[i][j] = second_image->getAtIndex(row_num, j);
      }
      row_num++;
    }
    cout << "Successfully completed vertical collage" << endl;
    return new_PBM;
  }

  else
  {
    cout << "Invalid collage direction" << endl;
    return this;
  }
}

//==file methods
PBM &readPBMFromASCIIFile(std::ifstream &infile)
{
  //== reads comments and dimensions
  char newline;
  char space;
  int num_col;
  int num_rows;
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
    infile.get(newline);
  }
  else
  {
    infile >> num_col;
    infile >> num_rows;
    infile.get(newline);
  }

  PBM *new_PBM = new PBM(num_rows, num_col);

  //==inputting bitmap
  int value;
  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_col; j++)
    {
      infile >> value;
      new_PBM->m_bitmap[i][j] = value;
    }
  }
  std::cout << "Succesfully read PBM image from ASCII encoded file" << endl;
  return *new_PBM;
}

PBM &readPBMFromBinaryFile(std::ifstream &infile)
{
  char newline;
  char space;
  infile.get(newline);

  //== reads comments and dimensions
  int num_col;
  int num_rows;

  if (infile.peek() == '#') //if a comment (every comment in image starts with #)
  {
    char hash;
    infile.get(hash);
    infile.get(space);
    char comment[MAX_COMMENT_SIZE];
    infile.getline(comment, MAX_COMMENT_SIZE);
    //reading dimensions of image
    infile >> num_col;
    infile >> num_rows;
    infile.get(newline);
  }
  else
  {
    infile >> num_col;
    infile >> num_rows;
    infile.get(newline);
  }

  PBM *new_PBM = new PBM(num_rows, num_col);

  //==reading bitmap
  char* read_byte = new char;
  int ctr_read_bytes=0;
  for (int i = 0; i < num_rows; i++ )
  {
    for (int j = 0; j < num_col; j++ )
    {
      if ( j%8 == 0 ) //if the column is a multiple of 8
      {
       infile.read(read_byte,1); //read a byte from file
        ctr_read_bytes++;
      }
      int bitshift = 0;  
      bitshift = 7-(j % 8);   
      int bit=0;
      bit = (*read_byte >> bitshift) & 1; //extract the bit by shifting by <bitshift>
      new_PBM->m_bitmap[i][j]=bit;
    }
  }

  cout << "Read PBM image from binary encoded file." << endl;
  return *new_PBM;
}

//============
void PBM::writeToASCIIFile(std::ofstream &outfile)
{
  //==writes magic number
  const char magic_number[3] = "P1"; // magic number for ASCII encoded PBM image
  outfile << magic_number << "\n";

  //==writing comment with the filename of image
  const char hash_comment = '#';
  char *comment = new char[MAX_COMMENT_SIZE];
  comment = m_filename;
  outfile << hash_comment << " " << comment << endl;

  //==writing col and rows size
  int col = m_col;
  int rows = m_rows;
  outfile << col << " " << rows << endl;

  //==writing bitmap
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < col; j++)
    {
      outfile << (int)m_bitmap[i][j] << " ";
    }
    outfile << endl;
  }
  std::cout << "Succesfully wrote ASCII encoded PBM image to file." << endl;
}

void PBM::writeToBinaryFile(std::ofstream &outfile)
{
  //==writes magic number
  const char magic_number[3] = "P4"; //magic number for binary encoded PBM file
  outfile << magic_number << "\n";

  //==writes comment
  const char hash_comment = '#';
  char *comment = new char[MAX_COMMENT_SIZE];
  comment = m_filename;
  outfile << hash_comment << " " << comment << endl;

  //==writes col and rows size
  int col = m_col;
  int rows = m_rows;
  outfile << col << " " << rows << " ";

  //==adding extra bits if needed to fill a whole byte
  int ctr = 0;
  int size_seq = rows * col;
  //using remained theorem n=p*q+r
  int p = size_seq / 8;
  int r = size_seq - (p * 8);
  int extra_bits_add = 8 - r;
  int new_size = size_seq + extra_bits_add;
  int bits_sequence[new_size] = {
      //will hold bitmap as an array of bits
      0,
  };

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < col; j++)
    {
      bits_sequence[ctr] = m_bitmap[i][j]; //writing pixels as an array of bits
      ctr++;
    }
  }

  //==output bitmap
  int position = 0;
  for (int i = 0; i < (new_size / 8); i++)
  {
    int tmp_8bits[8]; //will hold an array of 8 bits, constituting a byte
    int ctr = 0;
    for (int j = position; j < (position + 8); j++) //writing 8 bits
    {
      tmp_8bits[ctr] = bits_sequence[j];
      ctr++;
    }
    position += 8;
    char ch = convertBinaryToChar(tmp_8bits); //converting an array of 8 bits to a byte
    outfile << ch;                            //writing the converted byte to file
  }
  cout << "Succesfully wrote binary encoded PBM image to file." << endl;
}
