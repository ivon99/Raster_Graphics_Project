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

IImage* Session::get_loaded_image(int index)
{
    return m_loaded_images[index];
}


IImage *Session::load(const char *filename) //FIXME:it wille be more like add image, load image to be for the system
{
    std::ifstream infile;
    infile.open(filename);
    if (infile)
    {
        char magic_number[3];
        infile >> magic_number;
        //cout<<magic_number;
        if (strcmp(magic_number, "P1") == 0)
        {
            IImage *new_PBM = &readPBMFromASCIIFile(infile);
            new_PBM->setFilname(filename);
            m_loaded_images.addElement(new_PBM); //FIXME: test
            cout << "Succesfully read from txt .pbm from " << filename << endl;
            infile.close();
            return new_PBM;
        }
        if (strcmp(magic_number, "P4") == 0)
        {
            IImage *new_PBM = &readPBMFromBinaryFile(infile);
            new_PBM->setFilname(filename);
            m_loaded_images.addElement(new_PBM); //FIXME: test
            cout << "Succesfully read from binary .pbm from " << filename << endl;
            infile.close();
            return new_PBM;
        }
        if (strcmp(magic_number, "P2") == 0)
        {
            cout<<"P2 motherfuckers!"<<endl;
            IImage *new_PGM = &readPGMFromASCIIFile(infile);
            new_PGM->setFilname(filename);
            m_loaded_images.addElement(new_PGM);
            cout << "Succesfully read from txt .pgm from " << filename << endl;
            infile.close();
            return new_PGM;
        }
        if (strcmp(magic_number, "P5") == 0)
        {
            IImage *new_PGM = &readPGMFromBinaryFile(infile);
            new_PGM->setFilname(filename);
            m_loaded_images.addElement(new_PGM);
            cout << "Succesfully read from binary .pgm from " << filename << endl;
            infile.close();
            return new_PGM;
        }
        if (strcmp(magic_number, "P3") == 0)
        {
            IImage *new_PPM = &readPPMFromASCIIFile(infile);
            new_PPM->setFilname(filename);
            m_loaded_images.addElement(new_PPM);
            cout << "Succesfully read from txt .ppm from " << filename << endl;
            infile.close();
            return new_PPM;
        }
        if(strcmp(magic_number,"P6")==0)
        {
            IImage *new_PPM = &readPPMFromBinaryFile(infile);
            new_PPM->setFilname(filename);
            m_loaded_images.addElement(new_PPM);
            cout << "Succesfully read from binary .ppm from " << filename << endl;
            infile.close();
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

void Session::close() //FIXME:
{
    cout << "Succesfully closed current session" << endl;
    delete this;
}

/*applies all the commands to the loaded images in the session*/
void Session::save()
{
    int num_loaded = m_loaded_images.getSize();
    int num_pending_commands = m_pending_commands.getSize();
    cout << "Will be performing loop on " << num_pending_commands << " commands and " << num_loaded << " images." << endl;
    for (int i = 0; i < num_pending_commands; i++)
    {
        const char *pending_command = m_pending_commands[i]->getCommand();
        cout << "For this loop command is " << pending_command << endl;
        for (int j = 0; j < num_loaded; j++)
        {
            if (strcmp(pending_command, "grayscale") == 0)
            {
                // cout<<m_loaded_images[j]->getFilename()<<" ";
                //cout<<"grayscale()"<<endl;
                //cout<<"Before grayscale image was:"<<endl;
                //m_loaded_images[j]->print();
                m_loaded_images[j]->grayscale();
                //cout<<"After grayscale image is: "<<endl;
                //m_loaded_images[j]->print();

                const char *filename = m_loaded_images[j]->getFilename();
                std::ofstream outfile;
                outfile.open(filename);
                if (outfile)
                {
                    m_loaded_images[j]->writeToASCIIFile(outfile);
                }
                else
                {
                    cout<<"Unable to save "<<filename<<endl;
                }
                outfile.close();
                continue;
            }
            if (strcmp(pending_command, "monochrome") == 0)
            {
                //cout<<m_loaded_images[j]->getFilename()<<" ";
                //cout<<"monochrome"<<endl;
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
                    cout<<"Unable to save "<<filename<<endl;
                }
                outfile.close();
                continue;
            }
            if (strcmp(pending_command, "negative") == 0)
            {
                //cout<<m_loaded_images[j]->getFilename()<<" ";
                //cout<<"negative()"<<endl;
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
                    cout<<"Unable to save "<<filename<<endl;
                }
                outfile.close();
                continue;
            }
            if (strcmp(pending_command, "rotate") == 0)
            {
                const char *direction = m_pending_commands[i]->getDirection();
                //cout<<m_loaded_images[j]->getFilename()<<" ";
                //cout<<"rotate() -"<< direction<<endl;
               IImage* rotated_image= m_loaded_images[j]->rotate(direction);
                //const char *filename = m_loaded_images[j]->getFilename();
                //saveToASCIIFile(filename, m_loaded_images[j]);
                const char *filename = m_loaded_images[j]->getFilename();
                std::ofstream outfile;
                outfile.open(filename);
                if (outfile)
                {
                    rotated_image->writeToASCIIFile(outfile);
                }
                else
                {
                    cout<<"Unable to save "<<filename<<endl;
                }
                outfile.close();
                continue;
            }
        }
    }
}
void Session::save_as()
{
    int size= m_loaded_images.getSize();
    for(int i=0;i<size;i++){
      const char *filename = m_loaded_images[i]->getFilename();
                std::ofstream outfile;
                outfile.open(filename);
                if (outfile)
                {
                    m_loaded_images[i]->writeToASCIIFile(outfile);
                }
                else
                {
                    cout<<"Unable to save "<<filename<<endl;
                }
                outfile.close();
    }
}
void Session::help()
{
}
void Session::exit()
{
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

void Session::collage(IImage* first_image,const char* direction,IImage* second_image)
{
   IImage* collaged= first_image->collage(direction,second_image);

  // int size= m_loaded_images.getSize();
   m_loaded_images.addElement(collaged);
}

void Session::undo()
{
    int size_pending_commands = m_pending_commands.getSize();
    m_pending_commands.deleteElement(size_pending_commands - 1);
}
/*
void Session::addImage()
{

} */

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
        cout << ", ";
    }
    cout << endl;
}

/*
void Session::switchSession(int sessionID)
{
}
*/