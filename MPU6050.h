/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2014 Nasir Ahmad.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 *  @brief MPU6050 library for LeafLabs Maple
 */
 
 
#ifndef _MPU6050_H_
#define _MPU6050_H_


#include "libmaple_types.h"
#include "wirish.h"
#include "delay.h"
#include "io.h"
#include <i2c.h>

#define  DEV_ADDR		(0b01101000)
#define	 MAX_WRITE_SIZE	32

class MPU6050 {	
	public:
		MPU6050(uint8);
		
		void readPage(uint8, uint8*, uint8);
		uint8 read(uint8);
		void writePage(uint8, uint8*, uint8);
		void write(uint8, uint8);
		
		
	private:
		i2c_dev *_dev;
		i2c_msg _msgs[2];
};

#endif