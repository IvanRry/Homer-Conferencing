/*****************************************************************************
 *
 * Copyright (C) 2008-2011 Homer-conferencing project
 *
 * This software is free software.
 * Your are allowed to redistribute it and/or modify it under the terms of
 * the GNU General Public License version 2 as published by the Free Software
 * Foundation.
 *
 * This source is published in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License version 2
 * along with this program. Otherwise, you can write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 * Alternatively, you find an online version of the license text under
 * http://www.gnu.org/licenses/gpl-2.0.html.
 *
 *****************************************************************************/

/*
 * Name:    System.cpp
 * Purpose: Implementation of several basic system functions
 * Author:  Thomas Volkert
 * Since:   2011-02-25
 * Version: $Id$
 */

#include <Logger.h>
#include <HBSystem.h>

#include <string.h>
#include <stdlib.h>

#ifdef LINUX
#endif

#ifdef WIN32
#include <windows.h>
#endif

namespace Homer { namespace Base {

using namespace std;

///////////////////////////////////////////////////////////////////////////////

System::System()
{
}

System::~System()
{
}

///////////////////////////////////////////////////////////////////////////////

bool System::GetWindowsKernelVersion(int &pMajor, int &pMinor)
{
    pMajor = 0;
    pMinor = 0;

    #ifdef WIN32
        OSVERSIONINFOEX tVersionInfo;
        ZeroMemory(&tVersionInfo, sizeof(OSVERSIONINFOEX));
        tVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        if (GetVersionEx((LPOSVERSIONINFO)&tVersionInfo) == 0)
        {
            LOGEX(System, LOG_ERROR, "Failed when calling \"GetVersionEx\"");
            return false;
        }
        pMajor = tVersionInfo.dwMajorVersion;
        pMinor = tVersionInfo.dwMinorVersion;
    #endif

    return true;
}

string System::GetLinuxKernelVersion()
{
    FILE *tFile;
    string tResult = "";
    char tVersionBuffer[1024];
    memset(tVersionBuffer, 0, 1024);
    #ifdef LINUX
        if ((tFile = fopen("/proc/version", "r")) != NULL)
        {
            if (EOF == fscanf(tFile, "%*s %*s %s", tVersionBuffer))
                LOGEX(System, LOG_ERROR, "Failed to parse file content of /proc/version because of input failure");
            fclose(tFile);
        }
        LOGEX(System, LOG_VERBOSE, "Found linux kernel %s", tVersionBuffer);
        tResult = string(tVersionBuffer);
    #endif

    return tResult;
}

///////////////////////////////////////////////////////////////////////////////

}} //namespace
