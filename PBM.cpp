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

int *extractBits(char *ch)
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

char PBM::convertBinaryToChar(int int_sequence[])
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

//==The big 4

PBM::PBM()
{
  m_rows = 0;
  m_col = 0;
  m_filename = nullptr;
  m_bitmap = nullptr;
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
  std::cout << "PBM constructor called, created map with dimensions rows:" << m_rows << "xcol:" << m_col << endl;
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
      if (m_bitmap[i][j] == 0)
      {
        m_bitmap[i][j] = 1;
        continue;
      }
      if (m_bitmap[i][j] == 1)
      {
        m_bitmap[i][j] = 0;
        continue;
      }
    }
  }
  cout << "Succesfully negated image " << m_filename << endl;
}

IImage *PBM::rotate(const char *direction)
{
  PBM *new_PBM = new PBM(m_col, m_rows);
  new_PBM->m_filename = new char[strlen(m_filename) + 1];
  strcpy(new_PBM->m_filename, m_filename);

  if (strcmp(direction, "left") == 0)
  {
    cout << "Left rotation new bitmap is: " << endl;
    int tmp = m_col - 1;
    for (int i = 0; i < new_PBM->m_rows; i++)
    {
      for (int j = 0; j < new_PBM->m_col; j++)
      {
        new_PBM->m_bitmap[i][j] = m_bitmap[j][tmp];
        cout << (int)new_PBM->m_bitmap[i][j] << " ";
      }
      cout << endl;
      tmp--;
    }
    cout << "I have performed left rotation on image " << m_filename << endl;
    //*this = *new_PBM;
    // return true;
    return new_PBM;
  }

  if (strcmp(direction, "right") == 0)
  {
    int tmp_row;
    cout << "I will be performinf right" << endl;
    for (int i = 0; i < new_PBM->m_rows; i++)
    {
      tmp_row = m_rows - 1;
      for (int j = 0; j < new_PBM->m_col; j++)
      {
        new_PBM->m_bitmap[i][j] = m_bitmap[tmp_row][i];
        cout << "[" << i << "][" << j << "]"
             << "="
             << "[" << tmp_row << "][" << i << "] ";
        tmp_row--;
      }
      cout << endl;
    }
    cout << "I have performed right rotation on image" << m_filename << endl;
    //*this = *new_PBM;
    return new_PBM;
  }
  else
  {
    cout << "Error in performing " << direction << " rotation for image " << m_filename << "!" << endl;
    // PBM *null_PBM = new PBM();
    return this;
  }
}

IImage *PBM::collage(const char *direction, IImage *second_image)
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
  if (strcmp(direction, "horizontal") == 0)
  {
    //int new_size = first_PBM.m_col + other.m_col;
    int new_size = first_image_num_col + second_image_num_col;
    PBM *new_PBM = new PBM(first_image_num_rows, new_size);
    //==joining first table
    for (int i = 0; i < first_image_num_rows; i++)
    {
      for (int j = 0; j < first_image_num_col; j++)
      {
        //new_PBM->m_bitmap[i][j] = first_PBM.m_bitmap[i][j];
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
    cout << "Ive sucesfully completed horizontal collage" << endl;
    return new_PBM;
  }

  if (strcmp(direction, "vertical") == 0)
  {
    // int new_size = first_PBM.m_rows + other.m_rows;
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
    cout << "Ive sucesfully completed horizontal collage" << endl;
    return new_PBM;
  }

  else
  {
    //PBM *null_PBM = new PBM();
    cout << "Invalid collage direction" << endl;
    return this;
  }
}

//==file methods
PBM &readPBMFromASCIIFile(std::ifstream &infile)
{
  std::cout << "Im inside read PBM from ascii file" << endl;
  //== reads comments and dimensions
  char newline;
  char space;
  int num_col;
  int num_rows;
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
    std::cout << "Dimensions are rows" << num_rows << "Xcol" << num_col << endl;
  }
  else
  {
    infile >> num_col;
    infile >> num_rows;
    infile.get(newline);
    std::cout << "Dimensions are rows" << num_rows << "X col" << num_col << endl;
  }

  PBM *new_PBM = new PBM(num_rows, num_col);
  std::cout << "Ill be inputting values" << endl;
  //==inputting bitmap
  //char value;
  int value;
  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_col; j++)
    {
      infile >> value;
      cout << value << " , "; // void writePBMToASCIIFile(std::ofstream &outfile, PBM &obj);
                              // void writePBMToBinaryFile(std::ofstream &outfile, PBM &obj);
      std::cout << "At row[" << i << "] col[" << j << "] = ";
      new_PBM->m_bitmap[i][j] = value;
      std::cout << (int)new_PBM->m_bitmap[i][j] << endl;
    }
    std::cout << endl;
  }
  std::cout << "Ended inputting file" << endl;
  return *new_PBM;
}

PBM &readPBMFromBinaryFile(std::ifstream &infile)
{
  std::cout << "Im inside read PBM from binary file" << endl;
  char newline;
  char space;
  infile.get(newline);
  //==reads magic number
  /*char magic_number[3];
  infile >> magic_number;
  std::cout <<"!and magic number is"<< magic_number;
  infile.get(newline); */

  //== reads comments and dimensions
  int num_col;
  int num_rows;

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
  }
  else
  {
    infile >> num_col;
    infile >> num_rows;
    infile.get(newline);
    std::cout << "Dimensions are" << num_col << "X" << num_rows << endl;
  }

  PBM *new_PBM = new PBM(num_rows, num_col);

  //==reading bitmap
  std::cout << "And bitmap is " << endl;
  int ctr = 0;
  while (!infile.eof())
  {
    char *value_ptr = new char;
    infile.read(value_ptr, 1);
    if ((strcmp(value_ptr, "\n") == 0) || (strcmp(value_ptr, " ") == 0) || (int(*value_ptr) == 0))
      ;
    else
    {
      std::cout << value_ptr << endl;

      int *extracted_bits = extractBits(value_ptr);
      int row = 0;
      for (int j = num_col - 1; j >= 0; j--)
      {
        std::cout << "[" << ctr << "] [" << row << "]:";
        std::cout << extracted_bits[j] << " |";
        new_PBM->m_bitmap[ctr][row] = extracted_bits[j];
        if (new_PBM->m_bitmap[ctr][row] == 0)
        {
          std::cout << '0' << endl;
        }
        if (new_PBM->m_bitmap[ctr][row] == 1)
        {
          std::cout << '1' << endl;
        }
        row++;
      }
      std::cout << endl;
      ctr++;
    }
  }
  std::cout << "Ctr is" << ctr;

  std::cout << "Ended inputting file" << endl;
  return *new_PBM;
}

//============
void PBM::writeToASCIIFile(std::ofstream &outfile)
{
  std::cout << "Im inside write PBMTOASCIIfile" << endl;
  //==writes magic number
  const char magic_number[3] = "P1";
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

  //==writes bitmap
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < col; j++)
    {
      outfile << (int)m_bitmap[i][j] << " ";
      cout << (int)m_bitmap[i][j] << " ";
    }
    outfile << endl;
    cout << endl;
  }
  std::cout << "Ended writing file" << endl;
}

void PBM::writeToBinaryFile(std::ofstream &outfile) //FIXME: how do you read the extra bits
{
  std::cout << "Im inside write PBMToBinaryfile" << endl;
  //==writes magic number
  const char magic_number[3] = "P4";
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

  //==adds extra bits
  int ctr = 0;
  int size_seq = rows * col;
  //using remained theorem n=pq+r
  int p = size_seq / 8;
  int r = size_seq - (p * 8);
  int extra_bits_add = 8 - r;
  cout << "Will add bits" << extra_bits_add;
  int new_size = size_seq + extra_bits_add;
  int bits_sequence[new_size] = {
      0,
  };

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < col; j++)
    {
      bits_sequence[ctr] = m_bitmap[i][j];
      ctr++;
    }
  }
  cout << "Just to be sure" << endl;
  for (int i = 0; i < size_seq; i++)
  {
    std::cout << bits_sequence[i];
  }

  //==output bitmap
  int position = 0;
  for (int i = 0; i < (new_size / 8); i++)
  {
    int tmp_8bits[8];
    cout << "Extractin bits from" << position << "to " << position + 8 << endl;
    cout << "Bit sequence is :" << endl;
    int ctr = 0;
    for (int j = position; j < (position + 8); j++)
    {
      cout << bits_sequence[j];
      tmp_8bits[ctr] = bits_sequence[j];
      ctr++;
    }
    position += 8;
    char ch = convertBinaryToChar(tmp_8bits);
    outfile << ch;
    if (ch == 0)
      cout << "0!" << endl;
    else
      cout << "noo" << endl;
  }
  cout << "Succesfully wrote file" << endl;
}
