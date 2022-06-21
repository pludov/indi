/*******************************************************************************
  Copyright(c) 2022 Ludovic Pollet. All rights reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License version 2 as published by the Free Software Foundation.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.

 You should have received a copy of the GNU Library General Public License
 along with this library; see the file COPYING.LIB.  If not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301, USA.
*******************************************************************************/

#include <stdexcept>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <system_error>
#include <thread>

#include "gtest/gtest.h"

#include "indibase/baseclient.h"
#include "indibase/property/indiproperty.h"

#include "utils.h"

#include "SharedBuffer.h"
#include "ServerMock.h"
#include "IndiClientMock.h"


#define TEST_TCP_PORT 17624
#define TEST_UNIX_SOCKET "/tmp/indi-test-server"
#define STRINGIFY_TOK(x) #x
#define TO_STRING(x) STRINGIFY_TOK(x)

TEST(SharedBlob, Allocations)
{
    std::vector<int> sizes = { 0, 1023, 4095, 4096, 65535, 0x10000, 0x30000, 0x100000, 0x800000 };

    for(auto it = sizes.begin(); it != sizes.end(); ++it) {
        int size = *it;

        void * data = IDSharedBlobAlloc(size);

        ASSERT_NE(data, nullptr) << "Allocation of size " << size;

        memset(data, 255, size);

        IDSharedBlobFree(data);
    }
}

TEST(SharedBlob, ReAllocations)
{
    std::vector<int> sizes = { 0, 1023, 4095, 4096, 65535, 0x10000, 0x30000, 0x100000, 0x800000 };
    int initialSize = 16300;

    void * data = IDSharedBlobAlloc(initialSize);
    memset(data, 255, initialSize);

    for(auto it = sizes.begin(); it != sizes.end(); ++it) {
        int size = *it;

        data = IDSharedBlobRealloc(data, size);
        if (data == nullptr) {
            perror("IDSharedBlobRealloc");
        }
        ASSERT_NE(data, nullptr) << "Reallocation to size " << size;

        memset(data, 255, size);
    }

    IDSharedBlobFree(data);
}


