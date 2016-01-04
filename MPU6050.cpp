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


#include "MPU6050.h"

MPU6050::MPU6050(uint8 i2c_dev){
	switch (i2c_dev){
		case 1:
			_dev = I2C1;
			break;
		default:			
		case 2:
			_dev = I2C2;
			break;
	}
	
	i2c_master_enable(_dev, 1);
}

uint8 MPU6050::read(uint8 addr){
	uint8 data[1];
	readPage(addr, data, 1);	
	return data[0];
}

void MPU6050::readPage(uint8 addr, uint8 *buffer, uint8 length){
	i2c_msg msgs[2];
	uint8 reg_addr[1];
	
	// First address of the register to write
	reg_addr[0] = addr;
	
	// Write command
	msgs[0].addr = DEV_ADDR;
	msgs[0].flags = 0;
	msgs[0].length = 1;
	msgs[0].data = reg_addr;	
	
	// Read command to the read buffer
	msgs[1].addr = DEV_ADDR;
	msgs[1].flags = I2C_MSG_READ;
	msgs[1].data = buffer;
	msgs[1].length = length;	

	i2c_master_xfer(_dev, msgs, 2, 200);	
}

void MPU6050::writePage(uint8 addr, uint8* data, uint8 length){
	i2c_msg msgs[1];
	uint8 buffer[MAX_WRITE_SIZE + 1]; //Max page size to write is 32byte + 1 address byte
		
	// First 1 byte contains the address of the register where to start writing	
	buffer[0] = addr;
	length = (length < MAX_WRITE_SIZE) ? length : MAX_WRITE_SIZE;
	
	for (uint8 i=0; i < length; i++){
		buffer[1 + i] = data[i];
	}
	
	msgs[0].addr = DEV_ADDR;
	msgs[0].flags = 0;
	msgs[0].data = buffer;
	msgs[0].length = length + 1;
	
	i2c_master_xfer(_dev, msgs, 1, 200);	//Timeout 50ms	
}

void MPU6050::write(uint8 addr, uint8 value){
	uint8 data[] = { value };	
	writePage(addr, data, 1);
}