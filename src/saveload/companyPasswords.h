/*
 * This file is part of a mod for OpenTTD to add the saving and loading of company passwords. It is important to note that this mod is not supported, moderated or promoted by the OpenTTD team. See https://github.com/theulings/OpenTTD/
 *
 * This mod for OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * This mod for OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SAVELOADCOMPANYPWORDS_H
#define SAVELOADCOMPANYPWORDS_H

class saveLoadCompanyPwords {
    public:
        static std::string filename;
        static Subdirectory subDir;

        static void save(const char *filename, Subdirectory sb);
        static void load(); //Before calling load you must set filename and subDir
};
#endif