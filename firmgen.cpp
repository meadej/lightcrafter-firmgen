#include <stdio.h>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include "dlpc350_firmware.h"
#include "dlpc350_firmware.cpp"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

uint8 compression = 5;
uint32 compSize;
char* emptyFrmwFile = (char*)"emptyfrmw.bin";
char* outputFile = (char*)"firmware.bin";

int interpretArgs(int argc, char* argv[])
{
    // Interpreting arguments to the program.
    if (argc > 1)
    {
        for (int i = 0; i < argc; i++)
        {
            if (strcmp(argv[i], "--uncompress") == 0)
            {
                compression = 0;
                std::cout << "Uncompressed set.\n";
            }
            else if (strcmp(argv[i], "--basefile") == 0)
            {
                emptyFrmwFile = (char*)argv[i + 1];
            }
            else if (strcmp(argv[i], "--output") == 0)
            {
		        outputFile = (char*)argv[i + 1];
            }
        }
    }
}

void writeParams()
{
    // Assuming default values. If necessary, we can upload to lightcrafter and change those as well.
    uint32 defaultParam = 0;

    DLPC350_Frmw_WriteApplConfigData((char*)"DEFAULT.LED_ENABLE_MAN_MODE", &defaultParam, 1);
    DLPC350_Frmw_WriteApplConfigData((char*)"DEFAULT.MAN_ENABLE_RED_LED", &defaultParam, 1);
    DLPC350_Frmw_WriteApplConfigData((char*)"DEFAULT.MAN_ENABLE_GRN_LED", &defaultParam, 1);
    DLPC350_Frmw_WriteApplConfigData((char*)"DEFAULT.MAN_ENABLE_BLU_LED", &defaultParam, 1);
    DLPC350_Frmw_WriteApplConfigData((char*)"MACHINE_DATA.COLORPROFILE_0_BRILLIANTCOLORLOOK", &defaultParam, 1);
}

void addFile(const char* filename)
{
  	struct stat st;
  	if(stat(filename, &st) != 0)
  	{
  	    std::cout << "Filename not found.\n";
  	}
    
	int size = st.st_size;   

	char *pByteArray = (char*) malloc(size);

    std::ifstream imgFile(filename, std::ifstream::binary);

    // Read image file. Adapted from cpp documentation.
    if (imgFile)
    {
        imgFile.seekg(0, imgFile.end);
        int length = imgFile.tellg();
        imgFile.seekg(0, imgFile.beg);

        imgFile.read(pByteArray, length);

        imgFile.close();
    }

    int ret = DLPC350_Frmw_SPLASH_AddSplash((unsigned char*)pByteArray, &compression, &compSize);
    std::cout << "Added file " << filename << " with code " << std::to_string(ret) << "\n";
}

int loadEmptyFirmware()
{
    struct stat st;
    if(stat(emptyFrmwFile, &st) != 0)
    {
        std::cout << "Filename not found.\n";
    }

    int size = st.st_size;
    char* pByteArray = (char *)malloc(size);

    std::ifstream frmwFile(emptyFrmwFile, std::ifstream::binary);

    // Read empty firmware file. Adapted from cpp documentation.
    if (frmwFile)
    {
        frmwFile.seekg(0, frmwFile.end);
        int length = frmwFile.tellg();
        frmwFile.seekg(0, frmwFile.beg);

       	frmwFile.read(pByteArray, length);

        frmwFile.close();
    }


    return DLPC350_Frmw_CopyAndVerifyImage((const unsigned char*)pByteArray, size);
}

int main(int argc, char *argv[])
{
    unsigned char *newFrmwImage;
    uint32 newFrmwSize;

    interpretArgs(argc, argv);

    std::cout << "Loading empty firmware...\n";

    int ret = loadEmptyFirmware();

    std::cout << "Empty firmware loaded with code " << std::to_string(ret) << "...\n";

    std::cout << "Beginning file discovery...\n";
    int filecount = 0;
    DIR *dpdf;
    struct dirent *fileSearchPtr;

    std::vector<std::string> files;

    // File discovery. Locating all bmp files within the directory.
    dpdf = opendir("./");
	if (dpdf != NULL){
   		while (fileSearchPtr = readdir(dpdf))
   		{
   		    if (fileSearchPtr->d_type == DT_REG)
			{
				std::string fname = fileSearchPtr->d_name;
				if (fname.find(".bmp", (fname.length() - 4)) != std::string::npos)	
				{
				    filecount += 1;
					files.push_back(fname.c_str());
				}
			}
   		}	
	}

    closedir(dpdf);

	std::cout << "Files discovered...\n";
	std::cout << "Initializing buffer...\n";

	DLPC350_Frmw_SPLASH_InitBuffer(filecount);

	std::cout << "Buffer initialized...\n";
    std::cout << "Writing configuration data...\n";

    writeParams();

    std::cout << "Configuration data written...\n";
    std::cout << "Adding files...\n";

    for (int j = 0; j < filecount; j++)
    {
	    std::string sat = files.at(j);
	    addFile(sat.c_str());
    }

    std::cout << "Files added...\n";
    std::cout << "Building firmware image...\n";

    DLPC350_Frmw_Get_NewFlashImage(&newFrmwImage, &newFrmwSize);
    std::ofstream outfile (outputFile,std::ofstream::binary);
    outfile.write((const char*)newFrmwImage, newFrmwSize);
    outfile.close();

    //Calculate size of firmware image
    struct stat st;
    stat(outputFile, &st) != 0;

    int size = st.st_size;

    std::cout << "Firmware image built!\n Total size of " + std::to_string(size) + " bytes\n";
}

