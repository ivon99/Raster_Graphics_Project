#include "Session.hpp"
#include <cstring>
#include <iostream>
using namespace std;

int Session::m_sessionID = 0;

Session::Session()
{
    m_loaded_images = List<IImage *>();
    m_pending_commands = List<Command *>();
    m_sessionID++;
    cout << "Session with ID:" << m_sessionID << " started." << endl;
}

IImage *Session::get_loaded_image(int index)
{
    return m_loaded_images[index];
}

IImage* Session::get_loaded_image_by_filename(const char* filename)
{
    int size = m_loaded_images.getSize();
    for(int i=0; i<size;i++)
    {
        const char* filename_at_index= m_loaded_images[i]->getFilename();
        if(strcmp(filename,filename_at_index)==0)
        {
            return m_loaded_images[i];
        }
    }
    cout<<"Unable to find an image loaded from given filename "<<endl;
    IImage* null_image = new PBM();
    return null_image;
}

 int Session::get_index_of_loaded_image_by_filename(const char* filename)
 {
    int size = m_loaded_images.getSize();
    for(int i=0; i<size;i++)
    {
        const char* filename_at_index= m_loaded_images[i]->getFilename();
        if(strcmp(filename,filename_at_index)==0)
        {
            return i;
        }
    }
    return -1;
 }

// loads a new image by firstly reading magic number of image
// then assigning an IImage pointer to a new object of respective type
IImage *Session::load(const char *filename)
{
    std::ifstream infile;
    infile.open(filename);
    if (infile)
    {
        char magic_number[3];
        infile >> magic_number;
        if (strcmp(magic_number, "P1") == 0)
        {
            IImage *new_PBM = &readPBMFromASCIIFile(infile);
            new_PBM->setFilname(filename);
            m_loaded_images.addElement(new_PBM); 
            infile.close();
            cout<<"Image \""<<filename<<"\" added."<<endl;
            return new_PBM;
        }
        if (strcmp(magic_number, "P4") == 0)
        {
            infile.close();
            std::ifstream binfile;
            binfile.open(filename, std::ios::binary);
            binfile>>magic_number;
            IImage *new_PBM = &readPBMFromBinaryFile(binfile);
            new_PBM->setFilname(filename);
            m_loaded_images.addElement(new_PBM); 
            binfile.close();
            cout<<"Image \""<<filename<<"\" added."<<endl;
            return new_PBM;
        }
        if (strcmp(magic_number, "P2") == 0)
        {
            IImage *new_PGM = &readPGMFromASCIIFile(infile);
            new_PGM->setFilname(filename);
            m_loaded_images.addElement(new_PGM);
            infile.close();
            cout<<"Image \""<<filename<<"\" added."<<endl;
            return new_PGM;
        }
        if (strcmp(magic_number, "P5") == 0)
        {
            IImage *new_PGM = &readPGMFromBinaryFile(infile);
            new_PGM->setFilname(filename);
            m_loaded_images.addElement(new_PGM);
            infile.close();
            cout<<"Image \""<<filename<<"\" added."<<endl;
            return new_PGM;
        }
        if (strcmp(magic_number, "P3") == 0)
        {
            IImage *new_PPM = &readPPMFromASCIIFile(infile);
            new_PPM->setFilname(filename);
            m_loaded_images.addElement(new_PPM);
            infile.close();
            cout<<"Image \""<<filename<<"\" added."<<endl;
            return new_PPM;
        }
        if (strcmp(magic_number, "P6") == 0)
        {
            IImage *new_PPM = &readPPMFromBinaryFile(infile);
            new_PPM->setFilname(filename);
            m_loaded_images.addElement(new_PPM);
            infile.close();
            cout<<"Image \""<<filename<<"\" added."<<endl;
            return new_PPM;
        }
    }
    else
    { //creates a new empty file
        std::ofstream tmpfile;
        tmpfile.open(filename);
        infile.open(filename);
        cout << "Error in reading " << filename << ". A new filename with this name was generated" << endl;
        if (infile)
        {
            infile.close();
            PBM *null_PBM = new PBM();
            return null_PBM;
        }
        else
        {
            cout << "Error:can't read from newly generated file." << endl;
            PBM *null_PBM = new PBM();
            return null_PBM;
        }
    }
    cout << "Error in loading file" << endl;
    PBM *null_PBM = new PBM();
    return null_PBM;
}

void Session::close(const char* filename) //FIXME:
{
    int index = get_index_of_loaded_image_by_filename(filename);
    m_loaded_images.deleteElement(index);
    cout << "Succesfully closed "<<filename << endl;
}

/*applies all the commands to the loaded images in the session*/
void Session::save()
{
    int num_loaded = m_loaded_images.getSize();
    int num_pending_commands = m_pending_commands.getSize();
    if(num_pending_commands==0)  //if no pending transformations, just save images back
    {
        for(int i=0; i<num_loaded;i++)
        {
            const char *filename = m_loaded_images[i]->getFilename();
                std::ofstream outfile;
                outfile.open(filename);
                if (outfile)
                {
                    m_loaded_images[i]->writeToASCIIFile(outfile);
                }
                else
                {
                    cout << "Unable to save " << filename << endl;
                }
                outfile.close();
        }
    }

    for (int i = 0; i < num_pending_commands; i++)
    {
        const char *pending_command = m_pending_commands[i]->getCommand();
        for (int j = 0; j < num_loaded; j++)
        {
            if (strcmp(pending_command, "grayscale") == 0)
            {
                m_loaded_images[j]->grayscale();

                const char *filename = m_loaded_images[j]->getFilename();
                std::ofstream outfile;
                outfile.open(filename);
                if (outfile)
                {
                    m_loaded_images[j]->writeToASCIIFile(outfile);
                }
                else
                {
                    cout << "Unable to save " << filename << endl;
                }
                outfile.close();
                continue;
            }
            if (strcmp(pending_command, "monochrome") == 0)
            {
                m_loaded_images[j]->monochrome();
                const char *filename = m_loaded_images[j]->getFilename();
                std::ofstream outfile;
                outfile.open(filename);
                if (outfile)
                {
                    m_loaded_images[j]->writeToASCIIFile(outfile);
                }
                else
                {
                    cout << "Unable to save " << filename << endl;
                }
                outfile.close();
                continue;
            }
            if (strcmp(pending_command, "negative") == 0)
            {
                m_loaded_images[j]->negative();
                const char *filename = m_loaded_images[j]->getFilename();
                std::ofstream outfile;
                outfile.open(filename);
                if (outfile)
                {
                    m_loaded_images[j]->writeToASCIIFile(outfile);
                }
                else
                {
                    cout << "Unable to save " << filename << endl;
                }
                outfile.close();
                continue;
            }
            if (strcmp(pending_command, "rotate") == 0)
            {
                const char *direction = m_pending_commands[i]->getDirection();
                IImage *rotated_image = m_loaded_images[j]->rotate(direction);
                const char *filename = m_loaded_images[j]->getFilename();
                std::ofstream outfile;
                outfile.open(filename);
                if (outfile)
                {
                    rotated_image->writeToASCIIFile(outfile);
                }
                else
                {
                    cout << "Unable to save " << filename << endl;
                }
                outfile.close();
                continue;
            }
            else
            {
                const char *filename = m_loaded_images[j]->getFilename();
                std::ofstream outfile;
                outfile.open(filename);
                if (outfile)
                {
                    m_loaded_images[j]->writeToASCIIFile(outfile);
                }
                else
                {
                    cout << "Unable to save " << filename << endl;
                }
                outfile.close();
                continue;
            }
        }
    }
}

void Session::save_as(const char* image_filename, const char * save_to_filename)
{
    std::ofstream outfile;
    outfile.open(save_to_filename);
    if (outfile)
    {
       // m_loaded_images[0]->writeToASCIIFile(outfile);
      int index = get_index_of_loaded_image_by_filename(image_filename);
      if(index>=0)
      {
          m_loaded_images[index]->writeToASCIIFile(outfile);
      }
    }
    else
    {
        cout << "Unable to save " << image_filename << endl;
    }
    outfile.close();
}

void Session::grayscale()
{
    Command *grayscale_command = new Command("grayscale");
    m_pending_commands.addElement(grayscale_command);
}

void Session::monochrome()
{
    Command *monochrome_command = new Command("monochrome");
    m_pending_commands.addElement(monochrome_command);
}

void Session::negative()
{
    Command *negative_command = new Command("negative");
    m_pending_commands.addElement(negative_command);
}

void Session::rotate(const char *direction)
{
    Command *rotate_command = new Command("rotate", direction);
    m_pending_commands.addElement(rotate_command);
}

void Session::collage(const char *direction,const char* first_image_filename, const char* second_image_filename, const char* out_filename)
{
    IImage* first_image = get_loaded_image_by_filename(first_image_filename);
    IImage* second_image = get_loaded_image_by_filename(second_image_filename);
    IImage *collaged = first_image->collage(direction, second_image);
    collaged->setFilname(out_filename);
    m_loaded_images.addElement(collaged);
}

void Session::undo()
{
    int size_pending_commands = m_pending_commands.getSize();
    m_pending_commands.deleteElement(size_pending_commands - 1);
}


void Session::sessionInfo()
{
    int num_loaded_image = m_loaded_images.getSize();
    cout << "Name of images in the session: ";
    for (int i = 0; i < num_loaded_image; i++)
    {
        cout << m_loaded_images[i]->getFilename() << " ";
    }
    cout << endl;

    int num_pending_tranformations = m_pending_commands.getSize();
    cout << "Pending transformations: ";
    for (int i = 0; i < num_pending_tranformations; i++)
    {
        m_pending_commands[i]->printCommand();
        cout << " ";
    }
    cout << endl;
}
