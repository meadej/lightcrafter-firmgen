#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "dlpc350_firmware.h"
#include "dlpc350_firmware.cpp"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

uint8 compression = 0;
uint32 compSize;

void addFile(const char* filename)
{
  	struct stat st;
    	if(stat(filename, &st) != 0) {
        	return;
    	}	
    
	int size = st.st_size;   

	char *pByteArray = (char*) malloc(size);

    std::ifstream is (filename, std::ifstream::binary);
    if (is) {
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        is.read(pByteArray, length);

        is.close();

    }

    DLPC350_Frmw_SPLASH_AddSplash((unsigned char*)pByteArray, &compression, &compSize);
}

int main(int argc, char *argv[])
{
    unsigned char *newFrmwImage;
    uint32 newFrmwSize;

	std::cout << "Beginning file discovery...\n";    
    DIR *dpdf;
    struct dirent *epdf;

    dpdf = opendir("./");
	if (dpdf != NULL){
   		while (epdf = readdir(dpdf)){
      			if (epdf->d_type == DT_REG)
			{
				std::string fname = epdf->d_name;
				if (fname.find(".bmp", (fname.length() - 4)) != std::string::npos)	
				{
					addFile(fname.c_str());
				}
			}
   		}	
	}
    closedir(dpdf);
	std::cout << "Files discovered and added...\n";
	std::cout << "Building firmware image...\n";
    DLPC350_Frmw_Get_NewFlashImage(&newFrmwImage, &newFrmwSize);

    std::ofstream outfile ("firmware.bin",std::ofstream::binary);
    outfile.write((const char*)newFrmwImage, newFrmwSize);
    outfile.close();

    //Calculate size of firmware image
    struct stat st;
    if(stat(filename, &st) != 0) {
                return;
    }

    int size = st.st_size;

    std::cout << "Firmware image built!\n Total size of " + size.to_string();
}

