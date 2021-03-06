/* 
 * Copyright (C) 2013 Simon Richter
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "lock.h"

#include "thread_pthread.h"

void *thread_func(void *arg)
{
        using librevisa::thread;
        using librevisa::lock;
        thread::startupinfo &sui = *reinterpret_cast<thread::startupinfo *>(arg);

        sui.r.init();

        {
                lock lk(sui.cs);
                sui.running = true;
                sui.cv.signal();
        }

        sui.r.run();

        {
                lock lk(sui.cs);
                sui.running = false;
                sui.cv.signal();
        }

        return 0;
}
