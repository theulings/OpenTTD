/*
 * This file is part of a mod for OpenTTD to add the saving and loading of company passwords. It is important to note that this mod is not supported, moderated or promoted by the OpenTTD team. See https://github.com/theulings/OpenTTD/
 *
 * This mod for OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * This mod for OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../stdafx.h"
#include "../fileio_func.h"
#include "../fios.h"
#include "../network/network_server.h"
#include "companyPasswords.h"
#include <string>

std::string saveLoadCompanyPwords::filename("");
Subdirectory saveLoadCompanyPwords::subDir = NO_DIRECTORY;

void saveLoadCompanyPwords::save(const char *filename, Subdirectory sb)
{
    std::string pFilename = filename + std::string(".p");
    FILE* passFile = FioFOpenFile(pFilename.c_str(), "wb", sb);

    //We write a new line for each company password.
    //The first char of the line contains the company index, the rest of the line contains the password.
    for (const Company *c : Company::Iterate()) {
		const char *password = _network_company_states[c->index].password;
        char companyslot = c->index + 48;
        fputc(companyslot, passFile);
        fwrite(password, sizeof(char), strlen(password), passFile);
        fputc('\n', passFile);
    }
    FioFCloseFile(passFile);
}

void saveLoadCompanyPwords::load()
{
    FILE* passFile = FioFOpenFile(filename.c_str(), "r", subDir);
    if (passFile == nullptr)
        return;

    char ch;
    int companyIndex = -1;
    std::string pWord = "";
     
    while((ch = fgetc(passFile)) != EOF){
        if (ch == '\n'){
            //Only set the password if the buffer has something in it
            if (!pWord.empty()){
                NetworkServerSetCompanyPassword((CompanyID)companyIndex, pWord.c_str(), true);
                pWord = "";
            }
            companyIndex = -1;
            continue;
        }

        //The first char of each line contains the company index
        if (companyIndex == -1){
            companyIndex = ch - 48;
            continue;
        }

        pWord += ch;
    }
}